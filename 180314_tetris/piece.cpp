#include "stdafx.h"

Piece::Piece(int x, int y, COLORREF color) 
    : GameObject()
    ,_x(x)
    ,_y(y)
    ,_color(color)
{
    setTag(TAG::Piece);
}

Piece::~Piece()
{
}

void Piece::init()
{
}

void Piece::update()
{
    if ((_y * RATIO) <= MARGINTOP) //피스의 y축 좌표가 위에 닿거나 넘어버린다면
    {
        KillTimer(_hWnd, 1); //타이머 종료
        GO->setGameOver(true); //게임오버
    }
}

void Piece::render(HDC hdc)
{
    PenWithBrush(1, RGB(255, 255, 255), _color)(hdc, [hdc, this]()
    {
        drawRect(hdc, (_x * RATIO) + GAP, (_y * RATIO) + GAP, RATIO - GAP, RATIO - GAP);
    });
}

void Piece::release()
{
}
