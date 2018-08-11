#pragma once
/*
상속을 통해 연관된 일련된 클래스에 대해 공통적인 규약을 정의할 수 있다.
즉, 적용하고픈 공통규약을 묶어서 GameObject클래스를 정의하였고, 
이로인해서 GameObject를 상속하는 모든 클래스의 객체를 GameObject의 객체로 바라볼 수 있게 된 것
*/
class GameObject
{
private:
    int _instance_id;
    TAG _tag;
public:
    GameObject()
        : _instance_id(-1)
        , _tag(TAG::Not)
    {
    }
    virtual ~GameObject() 
    {
    }

    void setId(const int id)
    {
        _instance_id = id;
    }
    int getId() const
    {
        return _instance_id;
    }

    void setTag(const TAG tag)
    {
        _tag = tag;
    }

    TAG getTag() const
    {
        return _tag;
    }

    virtual void init() { }
    virtual void update() { }
    virtual void render(HDC hdc) { }
    virtual void release() { }
};