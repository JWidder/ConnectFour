#pragma once
#include <QMainWindow>
#include <QTextEdit>

#include <thread>

#include "Board.h"
#include "ConnectFour.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow();
    ~MainWindow();

  private slots:
    void Clear();

  private:
    Board* board_;
    QTextEdit* log_;
    std::unique_ptr<tlCF::Game> game_;
    std::unique_ptr<tlCF::Player> random_;
    std::unique_ptr<std::thread> gameThread_;
};
