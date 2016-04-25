#pragma once
#include <QMainWindow>
#include <Board.h>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow();

  private slots:
    void Clear();

  private:
    Board* board_;
};
