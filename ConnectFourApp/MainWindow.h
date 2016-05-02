#pragma once
#include <QMainWindow>
#include <Board.h>

#include "ConnectFour.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow();

  private slots:
    void Clear();

  private:
    Board* board_;
    std::unique_ptr<tlCF::Game> game_;
    std::unique_ptr<tlCF::Player> random_;
};
