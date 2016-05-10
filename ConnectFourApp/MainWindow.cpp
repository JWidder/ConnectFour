#include "MainWindow.h"

#include <QVboxLayout>
#include <QHboxLayout>
#include <QPushButton>


#include <thread>
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

    board_ = new Board(this);
    rightSide->addWidget(board_);
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
        std::thread t([&]() {
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
            }
        });
        t.detach();
    });
}

void MainWindow::Clear() {
    board_->Reset();
}