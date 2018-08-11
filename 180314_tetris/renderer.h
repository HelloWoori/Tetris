#pragma once

struct Pen
{
    Pen(int size, COLORREF penColor)
    : size(size)
    , penColor(penColor)
{}
void operator()(HDC hdc, function<void()> functor)
{

    HPEN myPen, oldPen;
    myPen = CreatePen(PS_SOLID, size, penColor);
    oldPen = (HPEN)SelectObject(hdc, myPen);

    functor();

    SelectObject(hdc, oldPen);
    DeleteObject(myPen);
}

HDC hdc;
int size;
COLORREF penColor;
};

struct PenWithBrush
{
    PenWithBrush(int size, COLORREF penColor, COLORREF brushColor)
        : size(size)
        , penColor(penColor)
        , brushColor(brushColor)
    {}
    void operator()(HDC hdc, function<void()> functor)
    {
        
        HPEN myPen, oldPen;
        HBRUSH myBrush, oldBrush;
        myPen = CreatePen(PS_SOLID, size, penColor);
        oldPen = (HPEN)SelectObject(hdc, myPen);
        myBrush = CreateSolidBrush(brushColor);
        oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

        functor();

        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);
        DeleteObject(myPen);
        DeleteObject(myBrush);
    }

    HDC hdc;
    int size;
    COLORREF penColor;
    COLORREF brushColor;
};

struct PenWithHatchBrush
{
    PenWithHatchBrush(int size, COLORREF penColor, COLORREF brushColor)
        : size(size)
        , penColor(penColor)
        , brushColor(brushColor)
    {}
    void operator()(HDC hdc, function<void()> functor)
    {

        HPEN myPen, oldPen;
        HBRUSH myBrush, oldBrush;
        myPen = CreatePen(PS_SOLID, size, penColor);
        oldPen = (HPEN)SelectObject(hdc, myPen);
        myBrush = CreateHatchBrush(HS_FDIAGONAL, brushColor);
        oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

        functor();

        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);
        DeleteObject(myPen);
        DeleteObject(myBrush);
    }

    HDC hdc;
    int size;
    COLORREF penColor;
    COLORREF brushColor;
};

struct Text
{
    Text(int size, int x, int y, wstring str)
        : size(size)
        , x(x)
        , y(y)
        , str(str)
    {}
    void operator()(HDC hdc)
    {
        HFONT font, oldFont;
        font = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("배달의민족 주아"));
        oldFont = (HFONT)SelectObject(hdc, font);
        SetTextColor(hdc, RGB(255, 255, 255));
        TextOut(hdc, x, y, str.c_str(), str.size());
        SelectObject(hdc, oldFont);
        DeleteObject(font);
    }

    int size;
    int x;
    int y;
    wstring str;
};
