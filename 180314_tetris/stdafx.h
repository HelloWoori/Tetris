// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
//디버깅용
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") //되는지 안되는지 다시 확인
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <functional>
using namespace std;

//내가 만든 헤더
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "renderer.h"

#include "tag.h"
#include "gameObjectManager.h"
#include "gameObject.h"
#include "block.h"
#include "piece.h"


//싱글톤
#define KEYMANAGER KeyManager::getSingleton()
#define RANDOM RandomFunction::getSingleton()
#define GO GameObjectManager::getSingleton()


//define
#define BOARDSIZEX   300 //실제 테트리스 게임공간의 너비
#define BOARDSIZEY   600 //실제 테트리스 게임공간의 높이
#define MARGINTOP    30  //위쪽 마진
#define MARGINBOTTOM 30  //아래쪽 마진
#define MARGINSIDE   180 //양쪽 마진
#define GAP          1   //테트리미노와 판 내부 조정 위함
#define RATIO        30  //윈창에 실제 그릴 배율, 기준은 가로 10, 세로 20

#define WINNAME (LPTSTR)(TEXT("테트리스으으으으!"))
#define WINSTARTX    350
#define WINSTARTY    60
#define WINSIZEX     (300 + MARGINSIDE * 2)
#define WINSIZEY     (600 + MARGINTOP + MARGINBOTTOM)
#define WINSTYLE WS_CAPTION | WS_SYSMENU


//SAFE DELETE
#define SAFE_DELETE(p)          {if(p)  {delete   (p);   (p)=NULL;}}
#define SAFE_DELETE_ARRAY(p)    {if(p)  {delete[] (p);   (p)=NULL;}}
#define SAFE_RELEASE(p)         {if(p)  {(p)->release(); (p)=NULL;}}


//extern : 컴파일에게 해당 변수가 외부에 선언되어 있음을 알리는 것
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT ptMouse;