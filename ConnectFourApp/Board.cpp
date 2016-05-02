#include "Board.h"
#include <QPainter>
#include <QMouseEvent>

Board::Board(QWidget* parent)
    : nextColor_(tlCF::BoardFieldStatus::yellow) {
    this->setMinimumSize(700, 600);
    this->setMaximumSize(700, 600);
}

void Board::Reset() {
    board_.Clear();
    game_.Reset(false);
    repaint();
}

void Board::mousePressEvent(QMouseEvent* event) {
    if (event->button() == 1) { //left mouse button
        auto x = event->x();
        auto collumn = x / 100;
        move_.set_value(collumn);
    }
}

void Board::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(0, 0, this->width(), this->height(), Qt::darkBlue);

    for (int i = 0; i < 7; ++i) {
        for (int k = 0; k < 6; ++k) {
            auto status = board_.GetStatus(5-k, i);
            if (status == tlCF::BoardFieldStatus::empty) painter.setBrush(Qt::gray);
            else if (status == tlCF::BoardFieldStatus::red) painter.setBrush(Qt::red);
            else if (status == tlCF::BoardFieldStatus::yellow) painter.setBrush(Qt::yellow);
            else painter.setBrush(Qt::black);
            painter.drawEllipse(10 + i * 100, 10 + k * 100, 80, 80);
        }
    }
}

void Board::Update(tlCF::BitBoard board) {
    board_ = board;
    repaint();
}

std::future<unsigned char> Board::Play_Impl(tlCF::BoardFieldStatus color, const tlCF::BitBoard & board, unsigned int timelimit) {
    move_ = std::promise<unsigned char>();
    return move_.get_future();
}

std::string Board::GetName_Impl() const {
    return "Human";
}
