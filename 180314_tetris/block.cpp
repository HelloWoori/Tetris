#include "stdafx.h"

Block::Block(TETRIMINO tetrimino, STATE state)
    : GameObject()
    , _state(state)
    , _tetrimino(tetrimino)
    , _startTime(GetTickCount())
{
    //�±�����
    setTag(TAG::Block);

    if (state == STATE::HandleNow)
    {
        //�߽���ǥ
        _center.x = 11;
        _center.y = 2;
    }
    else if (state == STATE::Preview)
    {
        _center.x = 18;
        _center.y = 2;
    }

    //������ ��ǥ�� �����Ѵ�
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
        //�����ð��� �帣�� �ڵ����� �Ʒ��� ��������
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
        //�Ʒ�Ű ������ ��(������ ������)
        if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
        {
            //MYPOINT temp(_center.x, _center.y + 1);
            if (!reachTheGround() && !checkOverlapWithPiece(myPoint))
                ++_center.y;
            //else
            //    removeBlockMakePiece();
        }
        //����
        if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
        {
            MYPOINT temp(_center.x - 1, _center.y);
            if (!checkOutOfRange(temp, _pt) && !checkOverlapWithPiece(temp))
                --_center.x;
        }
        //������
        if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
        {
            MYPOINT temp(_center.x + 1, _center.y);
            if (!checkOutOfRange(temp, _pt) && !checkOverlapWithPiece(temp))
                ++_center.x;
        }
        //���� ����Ű�� ������ ȸ���� �ȴ�
        if (KEYMANAGER->isOnceKeyDown(VK_UP))
        {
            //ȸ���� �Ŀ� �����͵��� ������ �Ѿ�ٸ� -90��ȸ��
            //TODO: �������� ���� ������Ƽ� �߽����� �ٽ� ��´ٴ��� �� �ٽ� �����غ���
            //ȸ������ �� �ǽ� ��ġ�� �װ͵� ����
            if (_tetrimino != TETRIMINO::O)
            {
                rotateBlockAll();
                if (checkOutOfRange(_center, _pt) || checkOverlapWithPiece(_center))
                    goback_rotateBlockAll();
            }
        }


        //���ο� �� ���� �� ���� ���� �ǽ��� ����( �ణ�� �����̸� �ص� �ǽ��� ����)
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
    //�� ���� �������� �簢���� �׸��� 
    PenWithHatchBrush(1, _color, _color)(hdc, [hdc, this]()         //this�� ����Լ��� ������ �Բ� ĸ��
    { 
        for (int i = 0; i < 4; ++i)
        {
            drawRect(hdc, (getGlobalX(_pt[i].x) * RATIO) + GAP, (getGlobalY(_pt[i].y) * RATIO) + GAP, RATIO - GAP , RATIO - GAP);
        }
    });
    

    //������
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

//�����ǥ���� ��â�� ��Ī��Ű�� ���� �۷ι� ��ǥ��(����� RATIO�� ���ؼ� �׷��ش�)
int Block::getGlobalX(int x) const
{
    return _center.x + x;
}

int Block::getGlobalY(int y) const
{
    return _center.y + y;
}

//�� ��纰�� ��ǥ�� �ʱ�ȭ
void Block::assembleBlock(TETRIMINO tetrimino)
{
    switch (tetrimino)
    {
    case TETRIMINO::I:
        _pt[0].x =  0; _pt[0].y = -1;
        _pt[1].x =  0; _pt[1].y =  1;
        _pt[2].x =  0; _pt[2].y =  2;
        _pt[3].x =  0; _pt[3].y =  0;
        _color = RGB(98, 255, 234); //�����ϴ�
        break;
    case TETRIMINO::J:
        _pt[0].x = -1; _pt[0].y = -1;
        _pt[1].x = -1; _pt[1].y =  0;
        _pt[2].x =  1; _pt[2].y =  0;
        _pt[3].x =  0; _pt[3].y =  0;
        _color = RGB(1, 86, 140); //�Ķ�
        break;
    case TETRIMINO::L:
        _pt[0].x =  1; _pt[0].y = -1;
        _pt[1].x = -1; _pt[1].y =  0;
        _pt[2].x =  1; _pt[2].y =  0;
        _pt[3].x =  0; _pt[3].y =  0;
        _color = RGB(254, 64, 68); //��
        break;
    case TETRIMINO::O:
        _pt[0].x =  0; _pt[0].y =  1;
        _pt[1].x = -1; _pt[1].y =  1;
        _pt[2].x = -1; _pt[2].y =  0;
        _pt[3].x =  0; _pt[3].y =  0;
        _color = RGB(255, 231, 76); //���
        break;
    case TETRIMINO::S:
        _pt[0].x =  0; _pt[0].y = -1;
        _pt[1].x =  1; _pt[1].y =  0;
        _pt[2].x =  1; _pt[2].y =  1;
        _pt[3].x =  0; _pt[3].y =  0;
        _color = RGB(99, 255, 127); //����
        break;
    case TETRIMINO::T:
        _pt[0].x = -1; _pt[0].y =  0;
        _pt[1].x =  1; _pt[1].y =  0;
        _pt[2].x =  0; _pt[2].y =  1;
        _pt[3].x =  0; _pt[3].y =  0;
        _color = RGB(165, 76, 255); //����
        break;
    case TETRIMINO::Z:
        _pt[0].x =  1; _pt[0].y = -1;
        _pt[1].x =  1; _pt[1].y =  0;
        _pt[2].x =  0; _pt[2].y =  1;
        _pt[3].x =  0; _pt[3].y =  0;
        _color = RGB(255, 18, 86); //����
        break;
    }
}

//90�� ȸ��
void Block::rotateBlock(int& x, int& y)
{
    int temp = x;
    x = -y;
    y = temp;   
}

//-90�� ȸ��
void Block::goback_rotateBlock(int& x, int& y)
{
    int temp = x;
    x = y;
    y = -temp;
}

//��� ��ǥ�鿡 ���ؼ� 90�� ȸ��
void Block::rotateBlockAll()
{
    for (int i = 0; i < POINTNUM; ++i)
    {
        rotateBlock(_pt[i].x, _pt[i].y);
    }
}

//��� ��ǥ�鿡 ���ؼ� -90�� ȸ��
void Block::goback_rotateBlockAll()
{
    for (int i = 0; i < POINTNUM; ++i)
    {
        goback_rotateBlock(_pt[i].x, _pt[i].y);
    }
}

//x�� ������ �Ѿ�� �ʾҴ���
bool Block::checkOutOfRange(const MYPOINT center, const MYPOINT pt[]) const
{
    for (int i = 0; i < POINTNUM; ++i)
    {
        //�� 5���� 14����
        if (center.x + pt[i].x < (MARGINSIDE / RATIO) || center.x + pt[i].x > (MARGINSIDE + BOARDSIZEX) / RATIO - 1)
            return true;
    }
    return false;
}

//�ٴڿ� ��Ҵ���
bool Block::reachTheGround()
{
    for (int i = 0; i < POINTNUM; ++i)
    {
        //�� 30����
        if (_center.y + _pt[i].y >= (MARGINTOP + BOARDSIZEY) / RATIO - 1)
            return true;
    }
    return false;
}

//�ٸ� �ǽ��� ��ġ�� ��
bool Block::checkOverlapWithPiece(MYPOINT center)
{
    //�ǽ��� ã�� ���Ϳ� ��´�
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

//�ٴ��̳� �ٸ� �ǽ��� ����� ��
void Block::removeBlockMakePiece()
{
    //���� ���¸� frozen���� ����
    //���� �� �����͸� ������ �ǽ��� ����� ���ӿ�����Ʈ�� ����
    //���� ���ӿ�����Ʈ���� �����Ѵ�
    _state = STATE::Frozen;
    for (int i = 0; i < POINTNUM; ++i)
    {
        GO->registerObj(new Piece(getGlobalX(_pt[i].x), getGlobalY(_pt[i].y), _color));
    }
    GO->removeObj(this->getId());
    

    //Preview�� �ִ� ���� ��ǥ ����
    vector<GameObject*> gameObj = GO->getGameObject();
    for (int i = gameObj.size() - 1; i >= 0; --i)
    {
        if (gameObj[i]->getTag() == TAG::Block)
        {
            if (dynamic_cast<Block*>(gameObj[i])->getState() == STATE::Preview)
            {
                //�� ��ǥ �� �±� ����
                dynamic_cast<Block*>(gameObj[i])->setState(STATE::HandleNow);
                dynamic_cast<Block*>(gameObj[i])->setCenterX(11);
                dynamic_cast<Block*>(gameObj[i])->setCenterY(1);

            }
        }
    }
    //���ο� �� ����
    createBlock();
    
}

void Block::createBlock()
{
    TETRIMINO random = static_cast<TETRIMINO>(RANDOM->getIntFromTo(0, 6));
    Block* block = new Block(random, STATE::Preview);
    //Block* block = new Block(TETRIMINO::I);//������
    //������ ���� ���ӿ�����Ʈ�Ŵ����� �����Ѵ�
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