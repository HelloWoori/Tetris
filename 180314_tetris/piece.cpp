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
    if ((_y * RATIO) <= MARGINTOP) //�ǽ��� y�� ��ǥ�� ���� ��ų� �Ѿ�����ٸ�
    {
        KillTimer(_hWnd, 1); //Ÿ�̸� ����
        GO->setGameOver(true); //���ӿ���
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
