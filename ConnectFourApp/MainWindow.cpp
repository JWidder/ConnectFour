#include "MainWindow.h"

#include <QVboxLayout>
#include <QHboxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>

#include "ConnectFour.hpp"
#include "Players.hpp"


MainWindow::MainWindow() {

    players_.push_back(std::make_shared<tlCF::RandomPlayer>());
    players_.push_back(std::make_shared<tlCF::MonteCarlo_ST>(2000));
    players_.push_back(std::make_shared<tlCF::MonteCarlo_ST>(500));

    QWidget* ui_area = new QWidget(this);
    setCentralWidget(ui_area);
    auto* mainLayout = new QHBoxLayout;
    auto* rightSide = new QVBoxLayout;

    log_ = new QTextEdit(this);
    mainLayout->addWidget(log_);
    log_->setReadOnly(true);

    //board
    board_ = new Board(this);
    rightSide->addWidget(board_);
    players_.push_back(std::shared_ptr<tlCF::Player>(board_, [](tlCF::Player*) {}));
    //player configuration
    auto* labelYellow = new QLabel(this);
    labelYellow->setText("Yellow: ");
    comboYellow_ = new QComboBox(this);
    for (const auto& i : players_) {
        comboYellow_->addItem(i->GetName().c_str());
    }
    auto* yellowLayout = new QHBoxLayout(this);
    yellowLayout->addWidget(labelYellow);
    yellowLayout->addWidget(comboYellow_);

    auto* labelRed = new QLabel(this);
    labelRed->setText("Red: ");
    comboRed_ = new QComboBox(this);
    for (const auto& i : players_) {
        comboRed_->addItem(i->GetName().c_str());
    }
    auto* redLayout = new QHBoxLayout(this);
    redLayout->addWidget(labelRed);
    redLayout->addWidget(comboRed_);

    auto* labelRepetitions = new QLabel(this);
    labelRepetitions->setText("Repetitions: ");
    lineEditRepetitions_ = new QLineEdit(this);
    lineEditRepetitions_->setText("1");
    auto* validatorRepetitions = new QIntValidator(1,999, this);
    lineEditRepetitions_->setValidator(validatorRepetitions);
    auto* layoutRepetitions = new QHBoxLayout(this);
    layoutRepetitions->addWidget(labelRepetitions);
    layoutRepetitions->addWidget(lineEditRepetitions_);

    auto* configLayout = new QHBoxLayout(this);
    configLayout->addLayout(yellowLayout);
    configLayout->addLayout(redLayout);
    configLayout->addLayout(layoutRepetitions);
    rightSide->addLayout(configLayout);

    //start button
    QPushButton* start_game = new QPushButton(this);
    start_game->setText("Start");
    rightSide->addWidget(start_game);

    mainLayout->addLayout(rightSide);
    ui_area->setLayout(mainLayout);
    setWindowTitle("Connect 4");

    connect(start_game, &QPushButton::clicked, [&]() {
        auto yellowIndex = comboYellow_->currentIndex();
        auto redIndex = comboRed_->currentIndex();
        game_ = std::make_unique<tlCF::Game>(players_[yellowIndex].get(), players_[redIndex].get());
        game_->RegisterObserver([&](tlCF::BitBoard b) {
            board_->UpdateBoard(b);
        });
        board_->Reset();
        if (gameThread_ && gameThread_->joinable()) {
            gameThread_->join();
        }
        gameThread_ = std::make_unique<std::thread>(([&]() {
            QString tmp;
            tmp.append(game_->GetYellow().c_str());
            tmp.append(" vs. ");
            tmp.append(game_->GetRed().c_str());
            tmp.append("\n");
            log_->append(tmp);
            auto result = game_->PlayGame();
            switch (result.result) {
            case tlCF::VictoryStatus::VictoryRed:
                log_->append("Red Wins\n");
                break;
            case tlCF::VictoryStatus::VictoryYellow:
                log_->append("Yellow Wins\n");
                break;
            case tlCF::VictoryStatus::Draw:
                log_->append("Draw\n");
                break;
            default:
                break;
            }
        }));
    });
}

void MainWindow::Clear() {
    board_->Reset();
}

MainWindow::~MainWindow() {
    if (gameThread_) {
        game_->terminate();
        gameThread_->join();
        gameThread_.reset();
    }
}

