#pragma once
#include <QWidget>

#include "ConnectFour.hpp"
#include <atomic>

class Board : public QWidget, public tlCF::Player {
    Q_OBJECT

  public:
    Board(QWidget* parent = nullptr);

    void UpdateBoard(tlCF::BitBoard board);

  public slots:
    void Reset();

  protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;



  private:
    tlCF::BitBoard board_;
    std::atomic<bool> promise_already_set_;

    //threading
    std::promise<unsigned char> move_;

    // Inherited via Player
    virtual std::future<unsigned char> Play_Impl(tlCF::BoardFieldStatus color, const tlCF::BitBoard & board, unsigned int timelimit) override;
    virtual std::string GetName_Impl() const override;
};
