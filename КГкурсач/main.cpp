// КГкурсач.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*	
* Множество многогранников пространственной сцены
	Две треугольные пирамиды

 Алгоритм закраски
	Построчное заполнение 

Алгоритм удаления невидимых линий и поверхностей
	Алгоритм «художника»

Алгоритм построения тени
	Построение «на землю» (источник света на конечном расстоянии)
*/

#pragma comment(lib, "Winmm.lib")

#include "Pyramid.h"
#include <mmsystem.h>
#define WIN_WIDTH 1500
#define WIN_HEIGHT 1500
int flag = 1;

 LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

 //
 //создание и инициализация
 WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon,
	LPCWSTR Name, WNDPROC Procedure) {
	 WNDCLASS NWC = { 0 };
	 NWC.hIcon = Icon;
	 NWC.hCursor = Cursor;
	 NWC.hInstance = hInst;
	 NWC.lpszClassName = Name;
	 NWC.hbrBackground = BGColor;
	 NWC.lpfnWndProc = Procedure;
	 return NWC;
	
 }
#ifdef CLASS
	Pyramid* p = new Pyramid;
#endif

int WINAPI WinMain(HINSTANCE hjs, HINSTANCE hpi, LPSTR iops, int ncg) {
	
	HWND hWnd;
	

	WNDCLASS w = NewWindowClass(NULL, LoadCursor(NULL, IDC_ARROW), hjs, LoadIcon(NULL,IDI_QUESTION), L"WClass", WndProc); //Класс окна
	MSG Msg; //сообщение
	
	if (!RegisterClass(&w)) return 0;
	
		hWnd = CreateWindow(L"WClass", L"CG", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0,1500, 1500,
		(HWND)NULL, (HMENU)NULL, (HINSTANCE)hjs, (HINSTANCE)NULL);//окно
	
		ShowWindow(hWnd, ncg);
		UpdateWindow(hWnd);
	
		while (GetMessage(&Msg, NULL, 0, 0)) { //главный цикл
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
		
		}
	delete p;
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
	//обработка событий
	HDC hdcMem;
	HBITMAP hbmMem;
	HANDLE hOld;
	RECT rc;
	GetClientRect(hWnd, &rc);
	
	HDC hdc;
	PAINTSTRUCT ps;
	
	switch (messg) {

	case WM_CREATE:break; //событие создания

	case WM_PAINT: { //событие рисования

#ifdef CLASS
		p->copyf();
		p->matrixRecalculation1(pro,1);
#endif

		hdc = BeginPaint(hWnd, &ps); //{

		if (flag == 0) {
			hdcMem = CreateCompatibleDC(hdc);
			hbmMem = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
			hOld = SelectObject(hdcMem, hbmMem);

			PatBlt(hdcMem, 0, 0, rc.right - rc.left, rc.bottom - rc.top, WHITENESS);
			SetTextColor(hdcMem, RGB(248,24,148));
			TextOutW(hdcMem, 1000, 50, L"Курсовая работа", lstrlen(L"Курсовая работа"));
			TextOutW(hdcMem, 1000, 70, L"Жабин Матвей 1144", lstrlen(L"Жабин Матвей 1144"));
			TextOutW(hdcMem, 1000, 120, L"WASD - вверх/влево/вниз/вправо", lstrlen(L"WASD - вверх/влево/вниз/вправо"));
			TextOutW(hdcMem, 1000, 140, L"12 - перемещение по OZ", lstrlen(L"12 - перемещение по OZ"));
			TextOutW(hdcMem, 1000, 160, L"RT - поворот относительно OX", lstrlen(L"RT - поворот относительно OX"));
			TextOutW(hdcMem, 1000, 180, L"FG - поворот относительно OY", lstrlen(L"FG - поворот относительно OY"));
			TextOutW(hdcMem, 1000, 200, L"ZX - поворот относительно OZ", lstrlen(L"ZX - поворот относительно OZ"));
			TextOutW(hdcMem, 1000, 220, L"QE - уменьшение/увеличение масштаба", lstrlen(L"QE - уменьшение/увеличение масштаба"));
			TextOutW(hdcMem, 1000, 240, L"SPACE - уникальное действие", lstrlen(L"SPACE - уникальное действие"));

#ifdef CLASS
		
			p->shadow(hdcMem);
#ifdef paint
			p->painter(hdcMem);
#endif

#endif
			BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, hdcMem, 0, 0, SRCCOPY);

			SelectObject(hdcMem, hOld);
			DeleteObject(hbmMem);
			DeleteDC(hdcMem);
		}
		else if (flag == 1) {
			hdc = GetDC(hWnd);
			hdcMem = CreateCompatibleDC(hdc);
			hbmMem = (HBITMAP)LoadImage(NULL, (L"im.bmp"), IMAGE_BITMAP, 0 ,0 , LR_LOADFROMFILE);

			SelectObject(hdcMem, hbmMem);

			TextOutW(hdc, 600, 120, L"Нажмите Space чтобы начать", lstrlen(L"Нажмите Space чтобы начать"));

			BitBlt(hdc, 450, 150, WIN_WIDTH, WIN_HEIGHT, hdcMem, 0, 0, SRCCOPY);

			DeleteObject(hbmMem);
			DeleteDC(hdcMem);
			ReleaseDC(hWnd, hdc);	
		}

		else if (flag == 2){
			hdc = GetDC(hWnd);
			hdcMem = CreateCompatibleDC(hdc);
			hbmMem = (HBITMAP)LoadImage(NULL, (L"im1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

			SelectObject(hdcMem, hbmMem);

			TextOutW(hdc, 600, 120, L"Нажмите Space чтобы начать", lstrlen(L"Нажмите Space чтобы начать"));

			BitBlt(hdc, 450, 150, WIN_WIDTH, WIN_HEIGHT, hdcMem, 0, 0, SRCCOPY);

			PlaySoundW(L"cg1.wav", NULL, SND_FILENAME);
			DeleteObject(hbmMem);
			DeleteDC(hdcMem);
			ReleaseDC(hWnd, hdc);
			//flag == 0;
		}

		EndPaint(hWnd, &ps);} //}
		break;

	case WM_KEYDOWN:
		hdc = BeginPaint(hWnd, &ps);//{

		switch (wParam) {
		case 0x41://A

#ifdef CLASS
			p->move(-10, 0, 0);
			flag = 0;
#endif
			break;

		case 0x44: //D
#ifdef CLASS
			p->move(10, 0, 0);
			flag = 0;

#endif 
			break;
		case 0x31://1
#ifdef CLASS
			p->move(0, 0, -10);
			flag = 0;

#endif
			break;
		case 0x32://2
#ifdef CLASS
			p->move(0, 0, 10);
			flag = 0;

#endif
			break;
		case 0x57://W
			
#ifdef CLASS

			p->move(0, -10, 0);
			flag = 0;


#endif
			break;
		case 0x53://S
#ifdef CLASS
			p->move(0, 10, 0);
			flag = 0;

#endif
			break;
		case 0x51://Q 
#ifdef CLASS
			p->zoom(0.95);
			flag = 0;

#endif
			break;
		case 0x45://E
#ifdef CLASS
			p->zoom(1.05);
			flag = 0;

#endif // CLASS
			break;
		case 0x52:// R //против часовой на +-градус
#ifdef CLASS
			
			p->rotationOnOX(-0.073);
			flag = 0;

#endif // CLASS
			break;
		case 0x54: //T //по часовой на +-градус
#ifdef CLASS
			p->rotationOnOX(0.073);
			flag = 0;

#endif // CLASS
			break;
		case 0x46:
#ifdef CLASS
			p->rotationOnOY(-0.073);
			flag = 0;

#endif // CLASS
			break;
		case 0x47:
#ifdef CLASS
			p->rotationOnOY(0.073);
			flag = 0;

#endif // CLASS
			break;
		case 0x5A:
#ifdef CLASS
			p->rotationOnOZ(-0.073);
			flag = 0;

#endif // CLASS
			break;
		case 0x58:
#ifdef CLASS
			p->rotationOnOZ(0.073);
			flag = 0;

#endif // CLASS
			break;
		case VK_SPACE:
#ifdef CLASS
			flag = 2;
#endif // CLASS
			break;
		default: break;

		}
		InvalidateRect(hWnd, NULL, TRUE); //обновление окна
		EndPaint(hWnd, &ps); //}
		break;

	case WM_DESTROY: //крестик
		PostQuitMessage(0);
		break;

	default: return(DefWindowProc(hWnd, messg, wParam, lParam));

	}
	return 0;
}