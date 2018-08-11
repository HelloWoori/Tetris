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
    /*비트맵 그리기*/
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
    //엔터를 누르면 게임이 시작되고 첫블럭이 생성된다
    if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
    {
        if (!_gameStart)
        {
            _gameStart = true;
            Block::createBlocks();
        }
    }

    GO->updateObj();

    /*piece삭제*/
    vector<GameObject*> gameObj = GO->getGameObject();
    map<int, vector<GameObject*>> pieceInYaxis;
    for (size_t i = 0; i < gameObj.size(); ++i)
    {
        if (gameObj[i]->getTag() == TAG::Piece)
        {
            pieceInYaxis[dynamic_cast<Piece*>(gameObj[i])->getY()].push_back(gameObj[i]);
        }
    }

    int fallYaxis = 0; //밑으로 내릴 피스들이 있는 y축을 저장하기 위한 변수
    //int deleteNum = 0;
    for (auto it = pieceInYaxis.rbegin(); it != pieceInYaxis.rend(); ++it)
    {
        //즉 10개라는 것은 x축모두에 피스가 있는것
        //따라서 해당 줄에 있는 모든 피스를 삭제한다
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

    //삭제된 piece들 위에 있던 piece는 아래로 떨어진다
    for (auto piece : pieceInYaxis)
    {
        if (piece.first < fallYaxis) //날라간 y축 보다 위에 있으면
        {
            for (auto p : piece.second) //그 y축의 x축을 돌면서
            {
                int y = dynamic_cast<Piece*>(p)->getY(); //자기 자신의 좌표를 갖고와서
                dynamic_cast<Piece*>(p)->setY(y + 1); //걔를 1증가시킴
            }
        }
    }

    /*게임오버*/
    if (GO->getGameOver())
    {
        TCHAR str[128];
        wsprintf(str, TEXT("획득점수: %d"), GO->getScore());
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
    /*비트맵 그리기*/
    DrawBitmap(_hWnd, hdc);

    GameNode::render(hdc);

    //오른쪽에 미리보기용 사각형
    PenWithBrush(1, RGB(255, 255, 255), RGB(22, 23, 67))(hdc, [hdc]()
    {
        drawRect(hdc, MARGINSIDE + BOARDSIZEX + 30, MARGINTOP, RATIO * 4, RATIO * 4);
    });

    //배경화면 바닥
    PenWithBrush(1, RGB(255, 255, 255), RGB(22, 23, 67))(hdc, [hdc]()
    {
        drawRect(hdc, MARGINSIDE + GAP, MARGINTOP + GAP, BOARDSIZEX - GAP, BOARDSIZEY - GAP);
    });

    //배경화면 선
    //1. 세로
    Pen(1, RGB(41, 26, 109))(hdc, [hdc]()
    {
        for (int i = 0; i <= 10; ++i)
        {
            drawLine(hdc, MARGINSIDE + (RATIO * i), MARGINTOP, MARGINSIDE + (RATIO * i), MARGINTOP + BOARDSIZEY);
        }
    });
    // 2. 가로
    Pen(1, RGB(41, 26, 109))(hdc, [hdc]()
    {
        for (int i = 0; i <= 20; ++i)
        {
            drawLine(hdc, MARGINSIDE, (RATIO * i) + MARGINTOP, MARGINSIDE + BOARDSIZEX, (RATIO * i) + MARGINTOP);
        }
    });

    GO->renderObj(hdc);

    //최상단에 삐져나온 블럭이 보이지 않게끔 흰색 사각형 그리기
    //PenWithBrush(1, RGB(255, 255, 255), RGB(255, 255, 255))(hdc, [hdc]()
    //{
    //    drawRect(hdc, 0, 0, WINSIZEX, MARGINTOP);
    //});

    //디버깅용
    //Text(80, 100, 100, to_wstring(_fallYaxis))(hdc);
}

/*비트맵 그리기*/
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