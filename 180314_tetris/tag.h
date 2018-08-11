#pragma once
struct MYPOINT
{
    MYPOINT() : x(0), y(0){ }
    MYPOINT(int x, int y) : x(x), y(y){ }
    int x;
    int y;
};
enum class TAG
{
    Not,
    Block,
    Piece
};

enum class TETRIMINO
{
    I, //�� �۴��
    O, //���簢��
    Z, //�������� �ھ��ִ� ���� 
    S, //������ �ھ��ִ� ����
    J, //|__
    L, //__|
    T  //��
};

enum class STATE
{
    Preview,
    HandleNow,
    Frozen
};