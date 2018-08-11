#pragma once
class GameNode
{
protected:
    HBITMAP g_BackBitmap; //더블버퍼링용
public:
    GameNode();
    virtual ~GameNode();

    virtual HRESULT init();
    virtual void release();
    virtual void update();
    virtual void render(HDC hdc);

    LRESULT MainProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};