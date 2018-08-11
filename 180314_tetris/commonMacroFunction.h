#pragma once
inline void drawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
}

inline RECT makeRect(int x, int y, int width, int height)
{
    RECT rc = { x, y, x + width, y + height };
    return rc;
}

inline RECT makeRectCenter(int x, int y, int width, int height)
{
    RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
    return rc;
}

inline void drawRect(HDC hdc, int x, int y, int width, int height)
{
    Rectangle(hdc, x, y, x + width, y + height);
}

inline void drawRectCenter(HDC hdc, int x, int y, int width, int height)
{
    Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void drawEllipse(HDC hdc, int x, int y, int width, int height)
{
    Ellipse(hdc, x, y, x + width, y + height);
}

inline void drawEllipseCenter(HDC hdc, int x, int y, int width, int height)
{
    Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void drawStar(HDC hdc, POINT* pt)
{
    SetPolyFillMode(hdc, WINDING);
    Polygon(hdc, pt, 5);
}

