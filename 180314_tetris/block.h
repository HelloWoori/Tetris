#pragma once
#define DELAYTIME 1500
#define POINTNUM 4
class Block : public GameObject
{
private:
    MYPOINT _pt[POINTNUM];
    MYPOINT _center;
    COLORREF _color;
    TETRIMINO _tetrimino;
    STATE _state;
    int _startTime;

public:
    Block(TETRIMINO tetrimino, STATE state);
    ~Block();

    virtual void init() override;
    virtual void update() override;
    virtual void render(HDC hdc) override;
    virtual void release() override;

    int getGlobalX(const int x) const;
    int getGlobalY(const int y) const;
    STATE getState() const
    {
        return _state;
    }
    void setState(STATE state)
    {
        _state = state;
    }
    void setCenterX(const int x)
    {
        _center.x = x;
    }
    void setCenterY(const int y)
    {
        _center.y = y;
    }
    
    void assembleBlock(TETRIMINO tetrimino);
    void createBlock();
    static void createBlocks();

    void rotateBlock(int& x, int& y);
    void goback_rotateBlock(int& x, int& y);
    void rotateBlockAll();
    void goback_rotateBlockAll();

    bool checkOutOfRange(const MYPOINT center, const MYPOINT pt[]) const;
    bool reachTheGround();
    bool checkOverlapWithPiece(MYPOINT center);
    void removeBlockMakePiece();
};