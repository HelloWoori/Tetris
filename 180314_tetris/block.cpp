#include "stdafx.h"

Block::Block(TETRIMINO tetrimino, STATE state)
    : GameObject()
    , _state(state)
    , _tetrimino(tetrimino)
    , _startTime(GetTickCount())
{
    //태그지정
    setTag(TAG::Block);

    if (state == STATE::HandleNow)
    {
        //중심좌표
        _center.x = 11;
        _center.y = 2;
    }
    else if (state == STATE::Preview)
    {
        _center.x = 18;
        _center.y = 2;
    }

    //블럭별로 좌표를 지정한다
    assembleBlock(_tetrimino);
}

Block::~Block()
{
}

void Block::init()
{
}

void Block::update()
{
    MYPOINT myPoint(_center.x, _center.y + 1);
    if (_state == STATE::HandleNow)
    {
        //일정시간이 흐르면 자동으로 아래로 떨어진다
        int currentTime = GetTickCount();
        if (currentTime - _startTime >= DELAYTIME)
        {
            _startTime = currentTime;
            //MYPOINT temp(_center.x, _center.y + 1);
            if (!reachTheGround() && !checkOverlapWithPiece(myPoint))
                ++_center.y;
            //else
            //    removeBlockMakePiece();
        }
        //아래키 눌렀을 때(빠르게 내려감)
        if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
        {
            //MYPOINT temp(_center.x, _center.y + 1);
            if (!reachTheGround() && !checkOverlapWithPiece(myPoint))
                ++_center.y;
            //else
            //    removeBlockMakePiece();
        }
        //왼쪽
        if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
        {
            MYPOINT temp(_center.x - 1, _center.y);
            if (!checkOutOfRange(temp, _pt) && !checkOverlapWithPiece(temp))
                --_center.x;
        }
        //오른쪽
        if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
        {
            MYPOINT temp(_center.x + 1, _center.y);
            if (!checkOutOfRange(temp, _pt) && !checkOverlapWithPiece(temp))
                ++_center.x;
        }
        //위쪽 방향키를 누르면 회전이 된다
        if (KEYMANAGER->isOnceKeyDown(VK_UP))
        {
            //회전한 후에 포인터들이 범위를 넘어선다면 -90도회전
            //TODO: 적합하지 않은 방법같아서 중심점을 다시 잡는다는지 등 다시 생각해볼것
            //회전했을 때 피스 겹치면 그것도 조정
            if (_tetrimino != TETRIMINO::O)
            {
                rotateBlockAll();
                if (checkOutOfRange(_center, _pt) || checkOverlapWithPiece(_center))
                    goback_rotateBlockAll();
            }
        }


        //새로운 블럭 생성 및 기존 블럭을 피스로 변경( 약간의 딜레이를 준뒤 피스로 변경)
        if (reachTheGround() || checkOverlapWithPiece(myPoint))
        {
            int currentTime = GetTickCount();
            if (currentTime - _startTime >= 600)
            {
                _startTime = currentTime;
                removeBlockMakePiece();
            }
        }
    }
}

void Block::render(HDC hdc)
{
    //각 점을 기준으로 사각형을 그린다 
    PenWithHatchBrush(1, _color, _color)(hdc, [hdc, this]()         //this는 멤버함수와 변수를 함께 캡쳐
    { 
        for (int i = 0; i < 4; ++i)
        {
            drawRect(hdc, (getGlobalX(_pt[i].x) * RATIO) + GAP, (getGlobalY(_pt[i].y) * RATIO) + GAP, RATIO - GAP , RATIO - GAP);
        }
    });
    

    //디버깅용
    //Text(20, 100, 100, to_wstring(static_cast<int>(_state)))(hdc);
    //for (int i = 0; i < 4; ++i)
    //{
    //    Text(20, 10, 200 + 18 * i, to_wstring(_pt[i].x) + L", "+ to_wstring(_pt[i].y))(hdc);
    //}
    //for (int i = 0; i < 4; ++i)
    //{
    //    Text(20, 10, 400 + 18 * i, to_wstring(_center.x + _pt[i].x) + L", " + to_wstring(_center.y + _pt[i].y))(hdc);
    //}
}

void Block::release()
{
}

//상대좌표에서 윈창에 매칭시키기 위한 글로벌 좌표로(여기다 RATIO를 곱해서 그려준다)
int Block::getGlobalX(int x) const
{
    return _center.x + x;
}

int Block::getGlobalY(int y) const
{
    return _center.y + y;
}

//블럭 모양별로 좌표들 초기화
void Block::assembleBlock(TETRIMINO tetrimino)
{
    switch (tetrimino)
    {
    case TETRIMINO::I:
        _pt[0].x =  0; _pt[0].y = -1;
        _pt[1].x =  0; _pt[1].y =  1;
        _pt[2].x =  0; _pt[2].y =  2;
        _pt[3].x =  0; _pt[3].y =  0;
        _color = RGB(98, 255, 234); //형광하늘
        break;
    case TETRIMINO::J:
        _pt[0].x = -1; _pt[0].y = -1;
        _pt[1].x = -1; _pt[1].y =  0;
        _pt[2].x =  1; _pt[2].y =  0;
        _pt[3].x =  0; _pt[3].y =  0;
        _color = RGB(1, 86, 140); //파랑
        break;
    case TETRIMINO::L:
        _pt[0].x =  1; _pt[0].y = -1;
        _pt[1].x = -1; _pt[1].y =  0;
        _pt[2].x =  1; _pt[2].y =  0;
        _pt[3].x =  0; _pt[3].y =  0;
        _color = RGB(254, 64, 68); //귤
        break;
    case TETRIMINO::O:
        _pt[0].x =  0; _pt[0].y =  1;
        _pt[1].x = -1; _pt[1].y =  1;
        _pt[2].x = -1; _pt[2].y =  0;
        _pt[3].x =  0; _pt[3].y =  0;
        _color = RGB(255, 231, 76); //노랑
        break;
    case TETRIMINO::S:
        _pt[0].x =  0; _pt[0].y = -1;
        _pt[1].x =  1; _pt[1].y =  0;
        _pt[2].x =  1; _pt[2].y =  1;
        _pt[3].x =  0; _pt[3].y =  0;
        _color = RGB(99, 255, 127); //연두
        break;
    case TETRIMINO::T:
        _pt[0].x = -1; _pt[0].y =  0;
        _pt[1].x =  1; _pt[1].y =  0;
        _pt[2].x =  0; _pt[2].y =  1;
        _pt[3].x =  0; _pt[3].y =  0;
        _color = RGB(165, 76, 255); //보라
        break;
    case TETRIMINO::Z:
        _pt[0].x =  1; _pt[0].y = -1;
        _pt[1].x =  1; _pt[1].y =  0;
        _pt[2].x =  0; _pt[2].y =  1;
        _pt[3].x =  0; _pt[3].y =  0;
        _color = RGB(255, 18, 86); //빨강
        break;
    }
}

//90도 회전
void Block::rotateBlock(int& x, int& y)
{
    int temp = x;
    x = -y;
    y = temp;   
}

//-90도 회전
void Block::goback_rotateBlock(int& x, int& y)
{
    int temp = x;
    x = y;
    y = -temp;
}

//모든 좌표들에 대해서 90도 회전
void Block::rotateBlockAll()
{
    for (int i = 0; i < POINTNUM; ++i)
    {
        rotateBlock(_pt[i].x, _pt[i].y);
    }
}

//모든 좌표들에 대해서 -90도 회전
void Block::goback_rotateBlockAll()
{
    for (int i = 0; i < POINTNUM; ++i)
    {
        goback_rotateBlock(_pt[i].x, _pt[i].y);
    }
}

//x축 범위를 넘어서진 않았는지
bool Block::checkOutOfRange(const MYPOINT center, const MYPOINT pt[]) const
{
    for (int i = 0; i < POINTNUM; ++i)
    {
        //즉 5부터 14까지
        if (center.x + pt[i].x < (MARGINSIDE / RATIO) || center.x + pt[i].x > (MARGINSIDE + BOARDSIZEX) / RATIO - 1)
            return true;
    }
    return false;
}

//바닥에 닿았는지
bool Block::reachTheGround()
{
    for (int i = 0; i < POINTNUM; ++i)
    {
        //즉 30까지
        if (_center.y + _pt[i].y >= (MARGINTOP + BOARDSIZEY) / RATIO - 1)
            return true;
    }
    return false;
}

//다른 피스와 겹치는 지
bool Block::checkOverlapWithPiece(MYPOINT center)
{
    //피스를 찾아 백터에 담는다
   vector<GameObject*> gameObj = GO->getGameObject();
   vector<GameObject*> piece;
   for (size_t i = 0; i < gameObj.size(); ++i)
   {
       if (gameObj[i]->getTag() == TAG::Piece)
       {
           piece.push_back(gameObj[i]);
       }
   }

   for (size_t i = 0; i < piece.size(); ++i)
   {
       for (int j = 0; j < POINTNUM; ++j)
       {
           if (dynamic_cast<Piece*>(piece[i])->getX() == (_pt[j].x + center.x)
               && dynamic_cast<Piece*>(piece[i])->getY() == (_pt[j].y + center.y))
               return true;
       }
   }
   return false;
}

//바닥이나 다른 피스와 닿았을 때
void Block::removeBlockMakePiece()
{
    //블럭의 상태를 frozen으로 변경
    //블럭의 각 포인터를 가지고 피스를 만들어 게임오브젝트에 저장
    //블럭은 게임오브젝트에서 삭제한다
    _state = STATE::Frozen;
    for (int i = 0; i < POINTNUM; ++i)
    {
        GO->registerObj(new Piece(getGlobalX(_pt[i].x), getGlobalY(_pt[i].y), _color));
    }
    GO->removeObj(this->getId());
    

    //Preview에 있는 블럭의 좌표 변경
    vector<GameObject*> gameObj = GO->getGameObject();
    for (int i = gameObj.size() - 1; i >= 0; --i)
    {
        if (gameObj[i]->getTag() == TAG::Block)
        {
            if (dynamic_cast<Block*>(gameObj[i])->getState() == STATE::Preview)
            {
                //블럭 좌표 및 태그 변경
                dynamic_cast<Block*>(gameObj[i])->setState(STATE::HandleNow);
                dynamic_cast<Block*>(gameObj[i])->setCenterX(11);
                dynamic_cast<Block*>(gameObj[i])->setCenterY(1);

            }
        }
    }
    //새로운 블럭 생성
    createBlock();
    
}

void Block::createBlock()
{
    TETRIMINO random = static_cast<TETRIMINO>(RANDOM->getIntFromTo(0, 6));
    Block* block = new Block(random, STATE::Preview);
    //Block* block = new Block(TETRIMINO::I);//디버깅용
    //생성한 블럭을 게임오브젝트매니저에 전달한다
    GO->registerObj(block);
}

void Block::createBlocks()
{
    TETRIMINO random = static_cast<TETRIMINO>(RANDOM->getIntFromTo(0, 6));
    Block* block1 = new Block(random, STATE::HandleNow);
    GO->registerObj(block1);

    random = static_cast<TETRIMINO>(RANDOM->getIntFromTo(0, 6));
    Block* block2 = new Block(random, STATE::Preview);
    GO->registerObj(block2);
}