#include "MainWindow.h"

#include <QVboxLayout>
#include <QPushButton>

#include <thread>
#include "ConnectFour.hpp"


MainWindow::MainWindow() {

    QWidget* ui_area = new QWidget(this);
    setCentralWidget(ui_area);
    QVBoxLayout* mainLayout = new QVBoxLayout;
    board_ = new Board(this);
    mainLayout->addWidget(board_);
    QPushButton* start_game = new QPushButton(this);
    start_game->setText("Start");
    mainLayout->addWidget(start_game);
    ui_area->setLayout(mainLayout);
    setWindowTitle("Connect 4");

    //initialize game objects
    random_ = std::make_unique<tlCF::RandomPlayer>();
    game_ = std::make_unique<tlCF::Game>(board_, random_.get());
    game_->RegisterObserver([&](tlCF::BitBoard b) {
        board_->UpdateBoard(b);
    });

    connect(start_game, &QPushButton::clicked, [&]() {
        game_->Reset(false);
        board_->Reset();
        std::thread t([&]() {
            game_->PlayGame();
        });
        t.detach();
    });
}

void MainWindow::Clear() {
    board_->Reset();
}