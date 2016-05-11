#pragma once
#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>

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

    //used shared_ptr due to the type erasure of the custom deleter
    std::vector<std::shared_ptr<tlCF::Player>> players_;

    Board* board_;
    QTextEdit* log_;
    QLineEdit* lineEditRepetitions_;
    QComboBox* comboYellow_;
    QComboBox* comboRed_;
    std::unique_ptr<tlCF::Game> game_;
    std::unique_ptr<std::thread> gameThread_;
};
