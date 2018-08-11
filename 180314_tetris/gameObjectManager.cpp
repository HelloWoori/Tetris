#include "stdafx.h"

GameObjectManager::GameObjectManager() 
{
    //_gameObj.resize(0);
    _score = 0;
    _gameOver = false;
    _instance_id = 0;

    //�������� ���� �Ǽ�
    //BlockFactory* blockFactory = new BlockFactory();
    //blockFactory->setId(_instance_id++);
    //_gameObj.push_back(blockFactory);
}

GameObjectManager::~GameObjectManager()
{
}

//��ü����
void GameObjectManager::registerObj(GameObject* obj)
{
    //�ν��Ͻ����� ���� ID�� �������ص�, vector�� �������
    obj->setId(_instance_id++);
    _gameObj.push_back(obj);
}
//��ü����
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

    Text(40, 90, 50, L"����: ")(hdc);
    Text(30, 100, 100, to_wstring(_score))(hdc);
    //������    
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
