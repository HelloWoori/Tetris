#include "stdafx.h"
#include "mainGame.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

HRESULT MainGame::init()
{
    GameNode::init();
    _gameStart = false;
    /*��Ʈ�� �׸���*/
    hNewImage = (HBITMAP)LoadImage(NULL, TEXT("assets/bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hNewImage, sizeof(BITMAP), &bit);
    
    //for font
    AddFontResourceA("assets/BMJUA_ttf.ttf");

    GO->initObj();
    return S_OK;
}

void MainGame::release()
{
    //for font
    RemoveFontResourceA("assets/BMJUA_ttf.ttf");

    GameNode::release();
    GO->releaseObj();
}

void MainGame::update()
{
    //���͸� ������ ������ ���۵ǰ� ù���� �����ȴ�
    if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
    {
        if (!_gameStart)
        {
            _gameStart = true;
            Block::createBlocks();
        }
    }

    GO->updateObj();

    /*piece����*/
    vector<GameObject*> gameObj = GO->getGameObject();
    map<int, vector<GameObject*>> pieceInYaxis;
    for (size_t i = 0; i < gameObj.size(); ++i)
    {
        if (gameObj[i]->getTag() == TAG::Piece)
        {
            pieceInYaxis[dynamic_cast<Piece*>(gameObj[i])->getY()].push_back(gameObj[i]);
        }
    }

    int fallYaxis = 0; //������ ���� �ǽ����� �ִ� y���� �����ϱ� ���� ����
    //int deleteNum = 0;
    for (auto it = pieceInYaxis.rbegin(); it != pieceInYaxis.rend(); ++it)
    {
        //�� 10����� ���� x���ο� �ǽ��� �ִ°�
        //���� �ش� �ٿ� �ִ� ��� �ǽ��� �����Ѵ�
        if ((*it).second.size() == BOARDSIZEX / RATIO)
        {
            //++deleteNum;
            GO->setScore(GO->getScore() + 10);
            for (auto piece : (*it).second)
            {
                fallYaxis = (*it).first;
                GO->removeObj(piece->getId());
            }
            break;
        }
    }

    //������ piece�� ���� �ִ� piece�� �Ʒ��� ��������
    for (auto piece : pieceInYaxis)
    {
        if (piece.first < fallYaxis) //���� y�� ���� ���� ������
        {
            for (auto p : piece.second) //�� y���� x���� ���鼭
            {
                int y = dynamic_cast<Piece*>(p)->getY(); //�ڱ� �ڽ��� ��ǥ�� ����ͼ�
                dynamic_cast<Piece*>(p)->setY(y + 1); //�¸� 1������Ŵ
            }
        }
    }

    /*���ӿ���*/
    if (GO->getGameOver())
    {
        TCHAR str[128];
        wsprintf(str, TEXT("ȹ������: %d"), GO->getScore());
        if (MessageBox(_hWnd, str, TEXT("GAME OVER"), MB_OK))
        {
            SendMessage(_hWnd, WM_DESTROY, 0, 0);
        }
        else
        {
            init();
        }
    }

    GameNode::update();
}

void MainGame::render(HDC hdc)
{
    /*��Ʈ�� �׸���*/
    DrawBitmap(_hWnd, hdc);

    GameNode::render(hdc);

    //�����ʿ� �̸������ �簢��
    PenWithBrush(1, RGB(255, 255, 255), RGB(22, 23, 67))(hdc, [hdc]()
    {
        drawRect(hdc, MARGINSIDE + BOARDSIZEX + 30, MARGINTOP, RATIO * 4, RATIO * 4);
    });

    //���ȭ�� �ٴ�
    PenWithBrush(1, RGB(255, 255, 255), RGB(22, 23, 67))(hdc, [hdc]()
    {
        drawRect(hdc, MARGINSIDE + GAP, MARGINTOP + GAP, BOARDSIZEX - GAP, BOARDSIZEY - GAP);
    });

    //���ȭ�� ��
    //1. ����
    Pen(1, RGB(41, 26, 109))(hdc, [hdc]()
    {
        for (int i = 0; i <= 10; ++i)
        {
            drawLine(hdc, MARGINSIDE + (RATIO * i), MARGINTOP, MARGINSIDE + (RATIO * i), MARGINTOP + BOARDSIZEY);
        }
    });
    // 2. ����
    Pen(1, RGB(41, 26, 109))(hdc, [hdc]()
    {
        for (int i = 0; i <= 20; ++i)
        {
            drawLine(hdc, MARGINSIDE, (RATIO * i) + MARGINTOP, MARGINSIDE + BOARDSIZEX, (RATIO * i) + MARGINTOP);
        }
    });

    GO->renderObj(hdc);

    //�ֻ�ܿ� �������� ���� ������ �ʰԲ� ��� �簢�� �׸���
    //PenWithBrush(1, RGB(255, 255, 255), RGB(255, 255, 255))(hdc, [hdc]()
    //{
    //    drawRect(hdc, 0, 0, WINSIZEX, MARGINTOP);
    //});

    //������
    //Text(80, 100, 100, to_wstring(_fallYaxis))(hdc);
}

/*��Ʈ�� �׸���*/
void MainGame::DrawBitmap(HWND hWnd, HDC hdc)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;
    int bx, by;

    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hNewImage);
    bx = bit.bmWidth;
    by = bit.bmHeight;
    BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}