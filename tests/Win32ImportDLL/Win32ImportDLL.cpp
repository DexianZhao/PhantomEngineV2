// Win32ImportDLL.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Win32ImportDLL.h"
#include "EngineAPI.h"

#define MAX_LOADSTRING 100

class MyEngine : public EngineAPI
{
public:
	MyEngine() {
		Texture = 0;
		MapShape = 0;
		Map = 0;
		Rotation = 0;
		Scale = 1.0f;
	}
	virtual void		OnBefore() {
	}
	BOOL				OnWin32Proc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) {
		return false;
	}
	VOID			OnRender(double dElapsedTime)
	{
		//if (MapShape) {
			//MapShape->Render(g_manager.GetElapsedTime());
		//}
	}
	VOID			OnRenderUI()
	{
		g_manager.DrawRect2D(RectF(0, 0, 100, 100), color4(1.0f, 1.0f, 0.0f, 1.0f), true);
	}
	BOOL				OnFrameMove(double dElapsedTime)
	{
		if (Texture) {
			Rotation += dElapsedTime * 180.0f;
			Scale += dElapsedTime;
			Texture->SetPosition(float2(Rotation, 0));
			//Texture->SetScale(Scale);
			Texture->SetRotation(Rotation);
		}
		return true;
	}
	void				MapSetup() {
		Map = DexianManager::GetInstance().NewControl(DexianControlData::Type_Base);
		MapShape = Map->AddShape(RectF(0, 0, 1024, 1024));
		Texture = MapShape->AddTexture(AlignModeX::AlignLeft, AlignModeY::AlignTop, RectF(0, 0, 32, 32), color4(1, 1, 1, 1), "0\\0_0.png", 0);
		for (int i = 0; i < 16; i++) {
			char buf[128];
			sprintf(buf, "0\\0_%d.png", i);
			Texture->AddTexture(color4(1, 1, 1, 1), buf);
		}
		Texture->SetCenterMode(true, 0);
		Texture->PlayMultiFrame(0, 15, 15.0f);
	}
	DexianShape*		MapShape;
	DexianControl*		Map;
	DexianDrawTexture*	Texture;
	float				Rotation;
	float				Scale;
};
// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
MyEngine			g_engine;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: �ڴ˷��ô��롣
	SetEngineAPI(&g_engine);
    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32IMPORTDLL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32IMPORTDLL));

    MSG msg;
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			g_engine.Render();
		}
	}
    //// ����Ϣѭ��: 
    //while (GetMessage(&msg, nullptr, 0, 0))
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //    }
    //}
	DestroiyDevice();
    return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32IMPORTDLL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32IMPORTDLL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   g_engine.Init(hWnd);
   g_engine.MapSetup();
   g_manager.m_bShowFPS = true;
   DexianManager::GetInstance().NewTexture(DexianManager::GetInstance().AddTextureFile("1.png"));
   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �����˵�ѡ��: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_SIZE: {
		RECT rc;
		GetClientRect(hWnd, &rc);
		MoveWindow(g_engine.GetWindow(), 0, 0, rc.right - rc.left, rc.bottom - rc.top, true);
		break;
	}
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
