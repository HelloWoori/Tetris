# Tetris
- C/C++, WinAPI를 활용한 테트리스 게임  
- OS: Windows 10
- IDE: Visual Studio 2017
- 개발기간: 2018.03.14 ~ 2018.03.16  

## 조작법
- Enter키로 게임 시작
- ← → 방향키: 좌우 이동
- ↑ 방향키: 블럭 회전
- ↓ 방향키: 빠르게 이동

## 코드 설명   
- 테트리스의 block과 block을 이루는 piece들은 GameObject를 상속받음, Tag로 구분  
- 싱글톤 패턴으로 구현된 GameObjectManager는 게임 오브젝트들을 std::vector로 관리  
- GameObjectManager는 게임 오브젝트를 등록할 때 게임 오브젝트 별로 id를 지정해줌 (id는 오브젝트 삭제 시 사용)  
- WinAPI의 펜과 브러시를 편리하게 사용하기 위해 람다식과 functor를 사용  

**functor(function object) 추가 설명**
1. WinAPI에서 펜과 브러시를 사용하기 위해서는 핸들을 얻어야 하며,
2. 메모리 누수를 막기 위해 반드시 핸들을 반환해야 한다.
3. 이 과정은 실수를 유발할 수 있으므로, 핸들을 얻고 반환하는 과정을 하나의 함수로 묶는다. 
4. 하지만 핸들을 사용하는 작업은 그때그때 다르므로
5. 함수의 인자로 행동(함수)을 넘겨주기 위해 functor를 사용했다. 

<renderer.h>  
``` 
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
``` 
<piece.cpp>
``` 
void Piece::render(HDC hdc)
{
    PenWithBrush(1, RGB(255, 255, 255), _color)(hdc, [hdc, this]()
    {
        drawRect(hdc, (_x * RATIO) + GAP, (_y * RATIO) + GAP, RATIO - GAP, RATIO - GAP);
    });
}
``` 

## 시연영상 (Click!)
[![Video Label](https://i.ytimg.com/vi/ru1RxTmAlMQ/maxresdefault.jpg)](https://youtu.be/ru1RxTmAlMQ)  

## 스크린샷
![](https://github.com/HelloWoori/Tetris/blob/master/PlayScene.png)

*Game background image designed by [Freepik](https://www.freepik.com/free-vector/star-background-with-planets_1594486.htm)* 
