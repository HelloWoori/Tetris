#pragma once
class Piece : public GameObject
{
private:
    int _x;
    int _y;
    COLORREF _color;
public:
    Piece(int _x, int _y, COLORREF color);
    ~Piece();

    int getX() const
    {
        return _x;
    }
    int getY() const
    {
        return _y;
    }
    void setY(const int y)
    {
        _y = y;
    }

    virtual void init() override;
    virtual void update() override;
    virtual void render(HDC hdc) override;
    virtual void release() override;

};