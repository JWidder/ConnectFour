#include "MainWindow.h"

#include <QVboxLayout>

MainWindow::MainWindow() {
    QWidget* ui_area = new QWidget(this);
    setCentralWidget(ui_area);
    QVBoxLayout* mainLayout = new QVBoxLayout;
    board_ = new Board(this);
    mainLayout->addWidget(board_);
    ui_area->setLayout(mainLayout);
    setWindowTitle("Connect 4");
}

void MainWindow::Clear() {
    board_->Reset();
}