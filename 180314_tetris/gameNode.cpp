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
    SetTimer(_hWnd, 1, 5, NULL); //Ÿ�̸� �ʱ�ȭ
    return S_OK;
}

void GameNode::release()
{
    KillTimer(_hWnd, 1); //Ÿ�̸� ���̱�

    /*������۸���*/
    if (g_BackBitmap)//BackBitmap�� ���� �ִٸ� ������
    {
        DeleteObject(g_BackBitmap);
    }

    //�̱���
    KEYMANAGER->release();
    KEYMANAGER->releaseSingleton();
    RANDOM->releaseSingleton();
    GO->releaseSingleton();
}

void GameNode::update()
{
    //���߿� ���� Ÿ�̸Ӹ� ���� �Ŀ��� ��뤤��
    //������� ���� ������� ���� true->false
    InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(HDC hdc)
{
}

LRESULT GameNode::MainProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc, hMemDC;
    PAINTSTRUCT ps;

    //hMemDC�� �Ʒ� ������ ������۸���
    HBITMAP oldBitmap;
    RECT crt;

    switch (iMessage)
    {
    case WM_TIMER:
        this->update();
        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps); //�׸��� ����
        /*���� ���۸� ����*/
        GetClientRect(hwnd, &crt);
        if (g_BackBitmap == nullptr)
        {
            g_BackBitmap = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
        }
        hMemDC = CreateCompatibleDC(hdc); //hMemDC�� �޸𸮿� �׷��� DC
        oldBitmap = (HBITMAP)SelectObject(hMemDC, g_BackBitmap);
        FillRect(hMemDC, &crt, GetSysColorBrush(COLOR_WINDOW));
        SetBkMode(hMemDC, TRANSPARENT);

        this->render(hMemDC);//�� �κп� hMemDC�� �׸��̳� �ؽ�Ʈ �� �ʿ��� �� ������ش�

        BitBlt(hdc, 0, 0, crt.right, crt.bottom, hMemDC, 0, 0, SRCCOPY);
        SelectObject(hMemDC, oldBitmap);
        DeleteDC(hMemDC);
        /*���� ���۸� ��*/
        EndPaint(hwnd, &ps); //�׸��� ����
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
