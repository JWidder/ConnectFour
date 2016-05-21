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
    terminating_ = false;
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

    connect(this,&MainWindow::appendToLog, log_,&QTextEdit::append, Qt::QueuedConnection);

    connect(start_game, &QPushButton::clicked, [&]() {
        auto repetitions = lineEditRepetitions_->text().toInt();
        auto yellowIndex = comboYellow_->currentIndex();
        auto redIndex = comboRed_->currentIndex();

        auto red = players_[redIndex];
        auto yellow = players_[yellowIndex];

        if (gameThread_ && gameThread_->joinable()) {
            gameThread_->join();
        }

        gameThread_ = std::make_unique<std::thread>(([&,red_player = red, yellow_player = yellow, rep = repetitions]() {
            for (int i = 0; i < rep; ++i) {
                if (this->terminating_) {
                    break;
                }
                board_->Reset();
                board_->update();

                game_ = std::make_unique<tlCF::Game>(yellow_player.get(), red_player.get());
                game_->RegisterObserver([&](tlCF::BitBoard b) {
                    board_->UpdateBoard(b);
                });
                game_->RegisterLogger([&](const std::string& log) {
                    this->appendToLog(log.c_str());
                });
                QString tmp;
                tmp.append(game_->GetYellow().c_str());
                tmp.append(" vs. ");
                tmp.append(game_->GetRed().c_str());
                tmp.append("\n");
                emit this->appendToLog(tmp);
                board_->update();
                auto result = game_->PlayGame();
                switch (result.result) {
                case tlCF::VictoryStatus::VictoryRed:
                    emit this->appendToLog("Red Wins\n");
                    break;
                case tlCF::VictoryStatus::VictoryYellow:
                    emit this->appendToLog("Yellow Wins\n");
                    break;
                case tlCF::VictoryStatus::Draw:
                    emit this->appendToLog("Draw\n");
                    break;
                default:
                    break;
                }
                this->WriteGameRecord(result);
            }
        }));
    });
}

void MainWindow::Clear() {
    board_->Reset();
}

MainWindow::~MainWindow() {
    if (gameThread_) {
        terminating_ = true;
        game_->terminate();
        gameThread_->join();
        gameThread_.reset();
    }
}

void MainWindow::WriteGameRecord(tlCF::GameResult result) {
    db_.AddGameRecord(result);
}

