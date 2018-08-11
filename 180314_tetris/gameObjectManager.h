#pragma once
#include "singletonBase.h"
#include "GameObject.h"
class GameObjectManager : public SingletonBase<GameObjectManager>
{
private:
    int _score;
    bool _gameOver;
    vector<GameObject*> _gameObj;
    int _instance_id;
public:
    GameObjectManager();
    ~GameObjectManager();

    int getGameObjSize()
    {
        return _gameObj.size();
    }
    int getScore()
    {
        return _score;
    }
    void setScore(int score)
    {
        _score = score;
    }
    vector<GameObject*> getGameObject()
    {
        return _gameObj;
    }

    bool getGameOver()
    {
        return _gameOver;
    }

    void setGameOver(bool gameOver)
    {
        _gameOver = gameOver;
    }

    void registerObj(GameObject* gameObj);
    void removeObj(int id);

    void initObj();
    void updateObj();
    void renderObj(HDC hdc);
    void releaseObj();

};