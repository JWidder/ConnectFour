#pragma once
#include <QWidget>

#include "ConnectFour.hpp"

class Board : public QWidget, public tlCF::Player {
    Q_OBJECT

  public:
    Board(QWidget* parent = nullptr);

  public slots:
    void Reset();

  protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

    void Update(tlCF::BitBoard board);

  private:
    tlCF::BitBoard board_;

    //threading
    std::promise<unsigned char> move_;

    // Inherited via Player
    virtual std::future<unsigned char> Play_Impl(tlCF::BoardFieldStatus color, const tlCF::BitBoard & board, unsigned int timelimit) override;
    virtual std::string GetName_Impl() const override;
};
