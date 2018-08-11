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
    I, //긴 작대기
    O, //정사각형
    Z, //오른쪽이 솟아있는 형태 
    S, //왼쪽이 솟아있는 형태
    J, //|__
    L, //__|
    T  //ㅜ
};

enum class STATE
{
    Preview,
    HandleNow,
    Frozen
};