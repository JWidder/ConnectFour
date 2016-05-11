#pragma once
#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>

#include <thread>

#include "Board.h"
#include "ConnectFour.hpp"
#include "Database.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow();
    ~MainWindow();
    
    void WriteGameRecord(tlCF::GameResult result);

  signals:
    void boardUpdated(tlCF::BitBoard board);
    void appendToLogTxt(const QString& message);
    void setLogTxtFont(const QFont& font = QFont("Arial", 12, QFont::Normal, false));

  private slots:
    void Clear();

  private:
    void appendToLog(const QString& message, const QFont& font = QFont("Arial", 12, QFont::Normal, false));
    void runGame(std::shared_ptr<tlCF::Player> red_player, std::shared_ptr<tlCF::Player> yellow_player, int rep);

    //used shared_ptr due to the type erasure of the custom deleter
    std::vector<std::shared_ptr<tlCF::Player>> players_;

    Board* board_;
    QTextEdit* log_;
    QSpinBox* lineEditRepetitions_;
    QComboBox* comboYellow_;
    QComboBox* comboRed_;
    std::unique_ptr<tlCF::Game> game_;
    std::unique_ptr<std::thread> gameThread_;
    std::atomic<bool> terminating_;
    DataBase db_;
    std::mutex startGameMutex_;
};
