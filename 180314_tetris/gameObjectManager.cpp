#include "stdafx.h"

GameObjectManager::GameObjectManager() 
{
    //_gameObj.resize(0);
    _score = 0;
    _gameOver = false;
    _instance_id = 0;

    //블럭생성용 공장 건설
    //BlockFactory* blockFactory = new BlockFactory();
    //blockFactory->setId(_instance_id++);
    //_gameObj.push_back(blockFactory);
}

GameObjectManager::~GameObjectManager()
{
}

//객체생성
void GameObjectManager::registerObj(GameObject* obj)
{
    //인스턴스별로 개별 ID를 지정해준뒤, vector에 집어넣음
    obj->setId(_instance_id++);
    _gameObj.push_back(obj);
}
//객체삭제
void GameObjectManager::removeObj(int id)
{
    for (size_t i = 0; i < _gameObj.size(); ++i)
    {
        if (_gameObj[i]->getId() == id)
            _gameObj.erase(_gameObj.begin() + i);
    }
}

void GameObjectManager::initObj()
{
    for (size_t i = 0; i < _gameObj.size(); ++i)
    {
        _gameObj[i]->init();
    }
}

void GameObjectManager::updateObj()
{
    for (size_t i = 0; i < _gameObj.size(); ++i)
    {
        _gameObj[i]->update();
    }
}

void GameObjectManager::renderObj(HDC hdc)
{
    for (size_t i = 0; i < _gameObj.size(); ++i)
    {
        _gameObj[i]->render(hdc);
    }

    Text(40, 90, 50, L"점수: ")(hdc);
    Text(30, 100, 100, to_wstring(_score))(hdc);
    //디버깅용    
    //WCHAR str[128];
    //for (size_t i = 0; i < _gameObj.size(); ++i)
    //{
    //    wsprintf(str, TEXT("id: %d, tag: %d"), _gameObj[i]->getId(), _gameObj[i]->getTag());
    //    TextOut(hdc, 5, 100 + (15 * i), str, lstrlen(str));
    //}
}

void GameObjectManager::releaseObj()
{
    for (size_t i = 0; i < _gameObj.size(); ++i)
    {
        _gameObj[i]->release();
    }
}
