#pragma once
#include "GameNode.h"
class MainGame : public GameNode
{
private:
    bool _gameStart;
    HBITMAP hNewImage;
    BITMAP bit;
public:
    MainGame();
    ~MainGame();

    virtual HRESULT init() override;
    virtual void release() override;
    virtual void update() override;
    virtual void render(HDC hdc) override;

    void DrawBitmap(HWND hWnd, HDC hdc);
};