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

  private:
    tlCF::BitBoard board_;
};
