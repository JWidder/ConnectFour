#include "Board.h"
#include <QPainter>

Board::Board(QWidget* parent) {
    this->setMinimumSize(700, 600);
    this->setMaximumSize(700, 600);
}

void Board::Reset() {
    board_.Clear();
    repaint();
}

void Board::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(0, 0, this->width(), this->height(), Qt::darkBlue);

    for (int i = 0; i < 7; ++i) {
        for (int k = 0; k < 6; ++k) {
            painter.setBrush(Qt::gray);
            painter.drawEllipse(10 + i * 100, 10 + k * 100, 80, 80);
        }
    }
}
