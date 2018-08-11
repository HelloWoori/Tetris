#include "stdafx.h"
#include "gameNode.h"

GameNode::GameNode()
{
}

GameNode::~GameNode()
{
}

HRESULT GameNode::init()
{
    SetTimer(_hWnd, 1, 5, NULL); //타이머 초기화
    return S_OK;
}

void GameNode::release()
{
    KillTimer(_hWnd, 1); //타이머 죽이기

    /*더블버퍼링용*/
    if (g_BackBitmap)//BackBitmap에 무언가 있다면 지워라
    {
        DeleteObject(g_BackBitmap);
    }

    //싱글톤
    KEYMANAGER->release();
    KEYMANAGER->releaseSingleton();
    RANDOM->releaseSingleton();
    GO->releaseSingleton();
}

void GameNode::update()
{
    //나중에 고성능 타이머를 만든 후에는 사용ㄴㄴ
    //더블버퍼 이후 사용하지 않음 true->false
    InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(HDC hdc)
{
}

LRESULT GameNode::MainProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc, hMemDC;
    PAINTSTRUCT ps;

    //hMemDC와 아래 변수는 더블버퍼링용
    HBITMAP oldBitmap;
    RECT crt;

    switch (iMessage)
    {
    case WM_TIMER:
        this->update();
        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps); //그리기 시작
        /*더블 버퍼링 시작*/
        GetClientRect(hwnd, &crt);
        if (g_BackBitmap == nullptr)
        {
            g_BackBitmap = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
        }
        hMemDC = CreateCompatibleDC(hdc); //hMemDC는 메모리에 그려줄 DC
        oldBitmap = (HBITMAP)SelectObject(hMemDC, g_BackBitmap);
        FillRect(hMemDC, &crt, GetSysColorBrush(COLOR_WINDOW));
        SetBkMode(hMemDC, TRANSPARENT);

        this->render(hMemDC);//이 부분에 hMemDC로 그림이나 텍스트 등 필요한 걸 출력해준다

        BitBlt(hdc, 0, 0, crt.right, crt.bottom, hMemDC, 0, 0, SRCCOPY);
        SelectObject(hMemDC, oldBitmap);
        DeleteDC(hMemDC);
        /*더블 버퍼링 끝*/
        EndPaint(hwnd, &ps); //그리기 종료
        break;
    case WM_MOUSEMOVE:
        ptMouse.x = LOWORD(lParam);
        ptMouse.y = HIWORD(lParam);
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hwnd, iMessage, wParam, lParam));
}
