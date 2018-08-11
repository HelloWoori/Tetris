#pragma once
class BlockFactory : public GameObject
{
private:
    static int count;
public:
    BlockFactory();
    ~BlockFactory();

    virtual void init() override;
    virtual void update() override;
    virtual void render(HDC hdc) override;
    virtual void release() override;

    void createBlock();
};