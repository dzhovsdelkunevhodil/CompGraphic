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



#include "Header.h"
#define WIN_WIDTH 1500
#define WIN_HEIGHT 1500
//#define CLASS

 LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
 int flag = 0;

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
		p->matrixRecalculation(pro,1);
#endif

#ifdef ARR
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				COPY[i][j] = Gust[i][j];
		matrixRecalculation(COPY, pro);
#endif
		hdc = BeginPaint(hWnd, &ps); //{

		hdcMem = CreateCompatibleDC(hdc);
		hbmMem = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
		hOld = SelectObject(hdcMem, hbmMem);

		PatBlt(hdcMem, 0, 0, rc.right - rc.left, rc.bottom - rc.top, WHITENESS);


		
		char text[2] = {' ','\0'};
		text[0] = (char)p->getCoord();
		//itoa(p->getCoord(), text, 10);
		TextOutA(hdcMem, 500, 700, text, strlen(text));
		
#ifdef CLASS
		p->printLines(hdcMem);
#ifdef paint
		p->painter(hdcMem);
#endif
#ifdef NORM

		p->Bres(hdcMem);
#endif
#endif
		
#ifdef ARR
		PinkGust(hdcMem, COPY);
		printLines(hdcMem);

#endif
		TextOutW(hdcMem, 500, 50, L"Лабораторная №5", lstrlen(L"Лабораторная №5"));
		TextOutW(hdcMem, 500, 70, L"Жабин Матвей 1144", lstrlen(L"Жабин Матвей 1144"));
		TextOutW(hdcMem, 1000, 120, L"WASD - вверх/влево/вниз/вправо", lstrlen(L"WASD - вверх/влево/вниз/вправо"));
		TextOutW(hdcMem, 1000, 140, L"12 - перемещение по OZ", lstrlen(L"12 - перемещение по OZ"));
		TextOutW(hdcMem, 1000, 160, L"RT - поворот относительно OX", lstrlen(L"RT - поворот относительно OX"));
		TextOutW(hdcMem, 1000, 180, L"FG - поворот относительно OY", lstrlen(L"FG - поворот относительно OY"));
		TextOutW(hdcMem, 1000, 200, L"ZX - поворот относительно OZ", lstrlen(L"ZX - поворот относительно OZ"));
		TextOutW(hdcMem, 1000, 220, L"QE - уменьшение/увеличение масштаба", lstrlen(L"QE - уменьшение/увеличение масштаба"));


	


		BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, hOld);
		DeleteObject(hbmMem);
		DeleteDC(hdcMem);
		EndPaint(hWnd, &ps);} //}
		break;

	case WM_KEYDOWN:
		hdc = BeginPaint(hWnd, &ps);//{
		switch (wParam) {
		case 0x41://A

#ifdef CLASS
			p->move(-10, 0, 0);
#endif
			

			//flag = 0; 
#ifdef ARR
			move(Gust, -10, 0, 0);
#endif
			break;
		case 0x44: //D
#ifdef CLASS
			p->move(10, 0, 0);
#endif 

			//

			//flag = 0;
#ifdef ARR
			move(Gust, 10, 0, 0);
#endif
			break;
		case 0x31:
			//1
#ifdef CLASS
			p->move(0, 0, -10);
#endif
			// 
			//flag = 0;
#ifdef ARR
			move(Gust, 0, 0, -10);
#endif
			break;
		case 0x32:
			//2
#ifdef CLASS
			p->move(0, 0, 10);
#endif
			//flag = 0;
#ifdef ARR
			move(Gust, 0, 0, 10);
#endif
			break;
		case 0x57:
			//W
#ifdef CLASS
			p->move(0, -10, 0);
#endif
			// 
			//flag = 0;
#ifdef ARR
			move(Gust, 0, -10, 0);
#endif
			break;
		case 0x53:
			//S
#ifdef CLASS
			p->move(0, 10, 0);
#endif

			//flag = 0;
#ifdef ARR
			move(Gust, 0, 10, 0);
#endif
			break;
		case 0x51:
			//Q 
#ifdef CLASS
			p->zoom(0.95);
#endif
			//flag = 0;
#ifdef ARR
			zoom(Gust, 0.95);
#endif
			break;
		case 0x45:
			//E
#ifdef CLASS
			p->zoom(1.05);
#endif // CLASS

#ifdef ARR

			zoom(Gust, 1.05);

#endif
			break;
		case 0x52:
			// R //против часовой на +-градус
#ifdef CLASS
			p->rotationOnOX(-0.05);
#endif // CLASS

#ifdef ARR

			rotationOnOX(Gust, -0.05);

#endif
			break;
		case 0x54:
			//T //по часовой на +-градус
#ifdef CLASS
			p->rotationOnOX(0.05);
#endif // CLASS

#ifdef ARR

			rotationOnOX(Gust, 0.05);

#endif
			break;
		case 0x46:
#ifdef CLASS
			p->rotationOnOY(- 0.05);
#endif // CLASS

#ifdef ARR
			rotationOnOY(Gust, -0.05); //F

#endif
			break;
		case 0x47:
#ifdef CLASS
			p->rotationOnOY(0.05);
#endif // CLASS

#ifdef ARR
			rotationOnOY(Gust, 0.05); //G

#endif
			break;
		case 0x5A:
#ifdef CLASS
			p->rotationOnOZ(-0.05);
#endif // CLASS

#ifdef ARR
			rotationOnOZ(Gust, -0.05); //Z

#endif

			break;
		case 0x58:
#ifdef CLASS
			p->rotationOnOZ(0.05);
#endif // CLASS

#ifdef ARR
			rotationOnOZ(Gust, 0.05); //X

#endif
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