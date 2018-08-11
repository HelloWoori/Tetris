#pragma once
/*
����� ���� ������ �Ϸõ� Ŭ������ ���� �������� �Ծ��� ������ �� �ִ�.
��, �����ϰ��� ����Ծ��� ��� GameObjectŬ������ �����Ͽ���, 
�̷����ؼ� GameObject�� ����ϴ� ��� Ŭ������ ��ü�� GameObject�� ��ü�� �ٶ� �� �ְ� �� ��
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