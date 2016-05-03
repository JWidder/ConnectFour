#include "Board.h"
#include <QPainter>
#include <QMouseEvent>

Board::Board(QWidget* parent)
    : promise_already_set_(false) {
    this->setMinimumSize(700, 600);
    this->setMaximumSize(700, 600);
}

void Board::Reset() {
    board_.Clear();
    promise_already_set_ = false;
    update();
}

void Board::mousePressEvent(QMouseEvent* event) {
    if (event->button() == 1) { //left mouse button
        auto x = event->x();
        auto collumn = x / 100;
        if (!promise_already_set_) {
            move_.set_value(collumn);
            promise_already_set_ = true;
        }
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

void Board::UpdateBoard(tlCF::BitBoard board) {
    board_ = board;
    update();
}

std::future<unsigned char> Board::Play_Impl(tlCF::BoardFieldStatus color, const tlCF::BitBoard & board) {
    move_ = std::promise<unsigned char>();
    promise_already_set_ = false;
    return move_.get_future();
}

std::string Board::GetName_Impl() const {
    return "Human";
}
