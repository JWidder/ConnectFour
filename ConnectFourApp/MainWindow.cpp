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
    //player configuration
    auto* labelYellow = new QLabel(this);
    labelYellow->setText("Yellow: ");
    auto* comboYellow = new QComboBox(this);
    auto* yellowLayout = new QHBoxLayout(this);
    yellowLayout->addWidget(labelYellow);
    yellowLayout->addWidget(comboYellow);
    
    auto* labelRed = new QLabel(this);
    labelRed->setText("Red: ");
    auto* comboRed = new QComboBox(this);
    auto* redLayout = new QHBoxLayout(this);
    redLayout->addWidget(labelRed);
    redLayout->addWidget(comboRed);

    auto* labelRepetitions = new QLabel(this);
    labelRepetitions->setText("Repetitions: ");
    auto* lineEditRepetitions = new QLineEdit(this);
    lineEditRepetitions->setText("1");
    auto* layoutRepetitions = new QHBoxLayout(this);
    layoutRepetitions->addWidget(labelRepetitions);
    layoutRepetitions->addWidget(lineEditRepetitions);
    
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

    //initialize game objects
    random_ = std::make_unique<tlCF::MonteCarlo_ST>();
    game_ = std::make_unique<tlCF::Game>(board_, random_.get());
    game_->RegisterObserver([&](tlCF::BitBoard b) {
        board_->UpdateBoard(b);
    });

    connect(start_game, &QPushButton::clicked, [&]() {
        game_->Reset(false);
        board_->Reset();
        if (gameThread_) {
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
                throw std::logic_error("Game should not end with 'Continue' state");
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
