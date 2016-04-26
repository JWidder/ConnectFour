#pragma once
#include <QWidget>

#include "ConnectFour.hpp"

class Board : public QWidget {
    Q_OBJECT

  public:
    Board(QWidget* parent = nullptr);

  public slots:
    void Reset();

  protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

  private:
    tlCF::BitBoard board_;
    tlCF::BoardFieldStatus nextColor_;
};
