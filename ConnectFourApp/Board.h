#pragma once
#include <QWidget>
#include <QTimer>

#include "ConnectFour.hpp"
#include <atomic>

class Board : public QWidget, public tlCF::Player {
    Q_OBJECT

  public:
    Board(QWidget* parent = nullptr);

  public slots:
    void Reset();
    void UpdateBoard(tlCF::BitBoard board);
    void UpdateGui();

  protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;



  private:
    std::unique_ptr<tlCF::BitBoard> board_;
    std::atomic<bool> promise_already_set_;
    QTimer* timer_;

    //threading
    std::promise<unsigned char> move_;

    // Inherited via Player
    virtual std::future<unsigned char> Play_Impl(tlCF::BoardFieldStatus color, const tlCF::BitBoard & board) override final;
    virtual std::string GetName_Impl() const override final;
};
