#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <stack>

#define paint
#define CLASS
#define N 4
#define M 8

using namespace std;

double pro[N][N] = { 
	{1,					0,	   0, 0}, 
	{0,					1,     0, 0}, 
	{sqrt(2) / 4, sqrt(2) / 4, 0, 1}, 
	{0,					0,     0, 0} };

typedef struct Point {
	double x;
	double y;
	Point() {
		x = 0;
		y = 0;
	}
	Point(double xn, double yn) {
		x = xn;
		y = yn;
	}
}Point;

#ifdef CLASS
class Pyramid {
private:

	std::vector<std::vector<double>> data;	
	std::vector<std::vector<double>> copy;
	std::vector<std::vector<double>> sourceLight;
	std::vector<std::vector<double>> sourceLightCopy;
	
public:

	Pyramid() {
		data.push_back({ 400, 300, 100, 1 });
		data.push_back({ 500, 300, 100, 1 });
		data.push_back({ 450, 320,  50, 1 });
		data.push_back({ 470, 450,  70, 1 });

		data.push_back({ 630, 320, 20, 1 });
		data.push_back({ 650, 370, 15, 1 });
		data.push_back({ 600, 380, 50, 1 });
		data.push_back({ 410, 390, 70, 1 });

		sourceLight.push_back({ 550, 50, 75, 1 });
	}

	~Pyramid() {
		data.clear();
		copy.clear();
		sourceLight.clear();
		sourceLightCopy.clear();
	}

	void copyf() {
		copy= data;
		sourceLightCopy = sourceLight;
	}

	void matrixRecalculation1(double array[N][N], int f = 0) { //пересчет координат 
	
		if (f == 0) {
			double res[M][N] = { 0 }; //вспомогательная матрица
			for (int k = 0; k < M; k++)
				for (int i = 0; i < N; i++)
					for (int j = 0; j < N; j++)
						res[k][i] += data[k][j] * array[j][i]; //умножение матриц
			for (int k = 0; k < M; k++)
				for (int i = 0; i < N; i++)
					data[k][i] = res[k][i]; //присваивание новых координат, новая матрица для отрисовки
		}

		else if (f==1) {
			double res[M][N] = { 0 }; //вспомогательная матрица
			for (int k = 0; k < M; k++)
				for (int i = 0; i < N; i++)
					for (int j = 0; j < N; j++)
						res[k][i] += data[k][j] * array[j][i]; //умножение матриц
			for (int k = 0; k < M; k++)
				for (int i = 0; i < N; i++)
					copy[k][i] = res[k][i]; //присваивание новых координат, новая матрица для отрисовки
		}

		else if (f == 2) {
			double res[1][N] = { 0 }; //вспомогательная матрица
			for (int k = 0; k < 1; k++)
				for (int i = 0; i < N; i++)
					for (int j = 0; j < N; j++)
						res[k][i] += sourceLight[k][j] * array[j][i]; //умножение матриц
			for (int k = 0; k < 1; k++)
				for (int i = 0; i < N; i++)
					sourceLightCopy[k][i] = res[k][i]; //присваивание новых координат, новая матрица для отрисовки
		}
	}

	void matrixRecalculation2(double mas[N][N],double array[N][N]) { //пересчет координат 

			double res[N][N] = { 0 }; //вспомогательная матрица
			for (int k = 0; k < N; k++)
				for (int i = 0; i < N; i++)
					for (int j = 0; j < N; j++)
						res[k][i] += mas[k][j] * array[j][i]; //умножение матриц
			for (int k = 0; k < N; k++)
				for (int i = 0; i < N; i++)
					mas[k][i] = res[k][i]; //присваивание новых координат, новая матрица для отрисовки
	}

	double aver(int cnt)
	{
		double average = 0;
		for (int i = 0; i < M; i++)
			average += data[i][cnt];
		return average / M;
	}

	void rotationOnOZ(double rot)
	{
		double x = 0, y = 0;
		x = aver(0);
		y = aver(1);
		double res[N][N] = { 
			{cos(rot),										sin(rot),				0, 0},
			{-sin(rot),										cos(rot),				0, 0},
			{0,													0,					1, 0},
			{x * (1 - cos(rot)) + y * sin(rot), y * (1 -  cos(rot)) - x * sin(rot), 0, 1} };
		matrixRecalculation1(res);
	}

	void rotationOnOX(double rot)
	{
		double y = 0, z = 0;
		y = aver(1);
		z = aver(2);
		double res[N][N] = { 
			{1,					   0,						   0,					  0},
			{0,					cos(rot),					sin(rot),			      0},
			{0,				   -sin(rot),					cos(rot),				  0},
			{0, y * (1 - cos(rot)) + z * sin(rot), z * (1 - cos(rot)) - y * sin(rot), 1} };
		matrixRecalculation1(res);
	}

	void rotationOnOY(double rot)
	{
		double x = 0, z = 0;
		x = aver(0);
		z = aver(2);
		double res[N][N] = { 
			{cos(rot),							0,				-sin(rot),			  0},
			{0,									1,					0,				  0},
			{sin(rot),							0,				cos(rot),			  0},
			{x * (1 - cos(rot)) - z * sin(rot), 0, z * (1 - cos(rot)) + x * sin(rot), 1} };
		matrixRecalculation1(res);
	}

	void zoom(double st)
	{
		double x = 0, y = 0, z = 0;
		x = aver(0);
		y = aver(1);
		z = aver(2);
		double res[N][N] = { 
			{st,				0,			 0,		0},
			{0,					st,			 0,		0},
			{0,					0,			 st,	0},
			{x * (1 - st),y * (1 - st),z * (1 - st),1} };
		matrixRecalculation1(res);
	}

	void move(int dx, int dy, int dz)
	{
		double move[N][N]{
		 {1, 0, 0, 0},
		 {0, 1, 0, 0},
		 {0, 0, 1, 0},
		 {dx, dy, dz, 1}
		};
		
		matrixRecalculation1(move);
	}

	void Lines(HDC hdc, int x1, int y1, int x2, int y2, int r = 0, int g = 0, int b = 0) {
		//библиотечная отрисовка
		HPEN p;
		p = CreatePen(PS_SOLID, 1, RGB(r, g, b)); //цвет, толщина рисования
		SelectObject(hdc, p);
		MoveToEx(hdc, x1, y1, NULL); //перемещение в кооридинату
		LineTo(hdc, x2, y2); //отрисовка из текущей координаты вкоориднату - аргумент
		DeleteObject(p);
	}

#ifdef paint

	void painter(HDC hdc) {

		short int in1 = 0;
		short int in2 = 0;
		short int in3 = 0;
		short int in4 = 0;
		short int in5 = 0;
		short int in6 = 0;
		short int in7 = 0;
		short int in8 = 0;
		double av[8];
		double av1[8];

		av[0] = av1[0] = (data[0][2] + data[1][2] + data[2][2]) / 3.0;
		av[1] = av1[1] = (data[0][2] + data[1][2] + data[3][2]) / 3.0;
		av[2] = av1[2] = (data[0][2] + data[2][2] + data[3][2]) / 3.0;
		av[3] = av1[3] = (data[1][2] + data[2][2] + data[3][2]) / 3.0;

		av[4] = av1[4] = (data[4][2] + data[5][2] + data[6][2]) / 3.0;
		av[5] = av1[5] = (data[4][2] + data[5][2] + data[7][2]) / 3.0;
		av[6] = av1[6] = (data[4][2] + data[6][2] + data[7][2]) / 3.0;
		av[7] = av1[7] = (data[5][2] + data[6][2] + data[7][2]) / 3.0;

		for (int i =0;i < 8;i++){
			for (int i = 0;i < 7;i++) {
				if (av[i] > av[i + 1]) {
					std::swap(av[i], av[i + 1]);
				}
			}
		}

		for (int i = 0; i < 8;i++) {

			if (av[i] == av1[0] && in1 == 0) {
				in1++;
				double fill[3][2] = { 0 };
				fill[0][0] = copy[0][0];
				fill[0][1] = copy[0][1];
				fill[1][0] = copy[1][0];
				fill[1][1] = copy[1][1];
				fill[2][0] = copy[2][0];
				fill[2][1] = copy[2][1];
				FillFigure3(hdc, fill, 0, 0, 255);	//синий
			}

			else if (av[i] == av1[1] && in2 == 0) {
				in2++;
				double fill[3][2] = { 0 };
				fill[0][0] = copy[0][0];
				fill[0][1] = copy[0][1];
				fill[1][0] = copy[1][0];
				fill[1][1] = copy[1][1];
				fill[2][0] = copy[3][0];
				fill[2][1] = copy[3][1];
				FillFigure3(hdc, fill, 255, 0, 0);//КРАСНЫЙ
			}

			else if (av[i] == av1[2] && in3 ==0) {
				in3++;
				double fill[3][2] = { 0 };
				fill[0][0] = copy[0][0];
				fill[0][1] = copy[0][1];
				fill[1][0] = copy[2][0];
				fill[1][1] = copy[2][1];
				fill[2][0] = copy[3][0];
				fill[2][1] = copy[3][1];
				FillFigure3(hdc, fill, 0, 255, 0);//зеленый
			}

			else if (av[i] == av1[3] && in4==0) {
				in4++;
				double fill[3][2] = { 0 };
				fill[0][0] = copy[1][0];
				fill[0][1] = copy[1][1];
				fill[1][0] = copy[2][0];
				fill[1][1] = copy[2][1];
				fill[2][0] = copy[3][0];
				fill[2][1] = copy[3][1];
				FillFigure3(hdc, fill, 0, 255, 255);//бирюза
			}


			///////////////////////////////////////
			
			else if (av[i] == av1[4] && in5 == 0) {
				in5++;
				double fill[3][2] = { 0 };
				fill[0][0] = copy[4][0];
				fill[0][1] = copy[4][1];
				fill[1][0] = copy[5][0];
				fill[1][1] = copy[5][1];
				fill[2][0] = copy[6][0];
				fill[2][1] = copy[6][1];
				FillFigure3(hdc, fill, 255, 0, 255);	//синий
			}

			else if (av[i] == av1[5] && in6 == 0) {
				in6++;
				double fill[3][2] = { 0 };
				fill[0][0] = copy[4][0];
				fill[0][1] = copy[4][1];
				fill[1][0] = copy[5][0];
				fill[1][1] = copy[5][1];
				fill[2][0] = copy[7][0];
				fill[2][1] = copy[7][1];
				FillFigure3(hdc, fill, 255, 255, 0);//КРАСНЫЙ
			}

			else if (av[i] == av1[6] && in7 == 0) {
				in7++;
				double fill[3][2] = { 0 };
				fill[0][0] = copy[4][0];
				fill[0][1] = copy[4][1];
				fill[1][0] = copy[6][0];
				fill[1][1] = copy[6][1];
				fill[2][0] = copy[7][0];
				fill[2][1] = copy[7][1];
				FillFigure3(hdc, fill, 155, 155, 50);//зеленый
			}

			else if (av[i] == av1[7] && in8 == 0) {
				in8++;
				double fill[3][2] = { 0 };
				fill[0][0] = copy[5][0];
				fill[0][1] = copy[5][1];
				fill[1][0] = copy[6][0];
				fill[1][1] = copy[6][1];
				fill[2][0] = copy[7][0];
				fill[2][1] = copy[7][1];
				FillFigure3(hdc, fill, 75, 65, 155);//бирюза
			}
		}
	}
#endif // paint
	
	void FillFigure3(HDC hdc, double tri[3][2], int r = 50, int g = 50, int b = 50) {

		HPEN p;
		double temp[3][2] = { 0 };
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++)
				temp[i][j] = round(tri[i][j]);
		}
		p = CreatePen(PS_SOLID, 1, RGB(r, g, b));
		double min = temp[0][1];
		double max = temp[0][1];
		int pick_l = 0, pick_r = 0, temp_lp = 0, temp_rp = 0;
		double temp_y = 0;
		for (int i = 0; i < 3; i++) {
			if (min > temp[i][1]) { min = temp[i][1]; pick_l = i; pick_r = i; }
			if (max < temp[i][1]) max = temp[i][1];
		}
		temp_y = min;
		double xl = 0, xr = 0;
		while (temp_y < max) {
			int flag = 0;
			if (temp_y == temp[temp_lp][1]) pick_l = temp_lp;
			else if (temp_y == temp[temp_rp][1]) pick_r = temp_rp;
			else if (temp[pick_l][1] == temp[temp_lp][1]) {
				pick_l = temp_lp; flag = 1;
			}
			else if (temp[pick_r][1] == temp[temp_rp][1]) {
				pick_r = temp_rp; flag = 1;
			}
			temp_lp = pick_l - 1;
			temp_rp = pick_r + 1;
			if (temp_lp == -1) temp_lp = 2;
			if (temp_rp == 3) temp_rp = 0;
			if (flag == 0) {
				xl = ((temp_y - temp[temp_lp][1]) / (temp[pick_l][1] -
					temp[temp_lp][1]))
					* (temp[pick_l][0] - temp[temp_lp][0]) + temp[temp_lp][0];
				xr = ((temp_y - temp[temp_rp][1]) / (temp[pick_r][1] -
					temp[temp_rp][1]))
					* (temp[pick_r][0] - temp[temp_rp][0]) + temp[temp_rp][0];
			}
			else if (flag == 1) {
				xl = ((temp_y - temp[temp_lp][1]) / (temp[pick_l][1] -
					temp[temp_lp][1] + 0.7))
					* (temp[pick_l][0] - temp[temp_lp][0]) + temp[temp_lp][0];
				xr = ((temp_y - temp[temp_rp][1]) / (temp[pick_r][1] -
					temp[temp_rp][1] + 0.7))
					* (temp[pick_r][0] - temp[temp_rp][0]) + temp[temp_rp][0];
			}
			SelectObject(hdc, p);
			MoveToEx(hdc, xl, temp_y, NULL);
			LineTo(hdc, xr, temp_y);
			DeleteObject(p);
			temp_y++;
		}
	}
	
	void FillFigure4(HDC hdc, double tri[4][2], int r = 50, int g = 50, int b = 50) {
		
		HPEN p;
		double temp[4][2] = { 0 };
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 2; j++)
				temp[i][j] = round(tri[i][j]);
		}
		p = CreatePen(PS_SOLID, 1, RGB(r, g, b));
		double min = temp[0][1];
		double max = temp[0][1];
		int pick_l = 0, pick_r = 0, temp_lp = 0, temp_rp = 0;
		double temp_y = 0;
		for (int i = 0; i < 4; i++) {
			if (min > temp[i][1]) { min = temp[i][1]; pick_l = i; pick_r = i; }
			if (max < temp[i][1]) max = temp[i][1];
		}
		temp_y = min;
		double xl = 0, xr = 0;
		while (temp_y < max) {
			int flag = 0;
			if (temp_y == temp[temp_lp][1]) pick_l = temp_lp;
			else if (temp_y == temp[temp_rp][1]) pick_r = temp_rp;
			else if (temp[pick_l][1] == temp[temp_lp][1]) {
				pick_l = temp_lp; flag = 1;
			}
			else if (temp[pick_r][1] == temp[temp_rp][1]) {
				pick_r = temp_rp; flag = 1;
			}
			temp_lp = pick_l - 1;
			temp_rp = pick_r + 1;
			if (temp_lp == -1) temp_lp = 3;
			if (temp_rp == 4) temp_rp = 0;
			if (flag == 0) {
				xl = ((temp_y - temp[temp_lp][1]) / (temp[pick_l][1] -
					temp[temp_lp][1]))
					* (temp[pick_l][0] - temp[temp_lp][0]) + temp[temp_lp][0];
				xr = ((temp_y - temp[temp_rp][1]) / (temp[pick_r][1] -
					temp[temp_rp][1]))
					* (temp[pick_r][0] - temp[temp_rp][0]) + temp[temp_rp][0];
			}
			else if (flag == 1) {
				xl = ((temp_y - temp[temp_lp][1]) / (temp[pick_l][1] -
					temp[temp_lp][1] + 0.7))
					* (temp[pick_l][0] - temp[temp_lp][0]) + temp[temp_lp][0];
				xr = ((temp_y - temp[temp_rp][1]) / (temp[pick_r][1] -
					temp[temp_rp][1] + 0.7))
					* (temp[pick_r][0] - temp[temp_rp][0]) + temp[temp_rp][0];
			}
			SelectObject(hdc, p);
			MoveToEx(hdc, xl, temp_y, NULL);
			LineTo(hdc, xr, temp_y);
			DeleteObject(p);
			temp_y++;
		}
	}

	void shadow(HDC hdc) {

		matrixRecalculation1(pro, 2);
		Lines(hdc, sourceLightCopy[0][0] + 5, sourceLightCopy[0][1] + 5, sourceLightCopy[0][0] - 5, sourceLightCopy[0][1] + 5, 240,240,40);
		Lines(hdc, sourceLightCopy[0][0] - 5, sourceLightCopy[0][1] + 5, sourceLightCopy[0][0] - 5, sourceLightCopy[0][1] - 5, 240, 240, 40);
		Lines(hdc, sourceLightCopy[0][0] - 5, sourceLightCopy[0][1] - 5, sourceLightCopy[0][0] + 5, sourceLightCopy[0][1] - 5, 240, 240, 40);
		Lines(hdc, sourceLightCopy[0][0] + 5, sourceLightCopy[0][1] - 5, sourceLightCopy[0][0] + 5, sourceLightCopy[0][1] + 5, 240, 240, 40);
		double src[4][2];
		src[0][0] = sourceLightCopy[0][0] + 5;
		src[0][1] = sourceLightCopy[0][1] + 5;
		src[1][0] = sourceLightCopy[0][0] - 5;
		src[1][1] = sourceLightCopy[0][1] + 5;
		src[2][0] = sourceLightCopy[0][0] - 5;
		src[2][1] = sourceLightCopy[0][1] - 5;
		src[3][0] = sourceLightCopy[0][0] + 5;
		src[3][1] = sourceLightCopy[0][1] - 5;
		FillFigure4(hdc, src, 240,240,40);

			double mas[N][4];
			int k = 0;
			while (k <= 4) {
				vector<Point> dis;

				for (int i = 0; i < N;i++) {
					mas[i][0] = data[i + k][0] + ((700 - data[i + k][1]) * (sourceLight[0][0] - data[i + k][0])) / (sourceLight[0][1] - data[i + k][1]);
					mas[i][1] = 700;
					mas[i][2] = data[i + k][2] + ((700 - data[i + k][1]) * (sourceLight[0][2] - data[i + k][2])) / (sourceLight[0][1] - data[i + k][1]);
					mas[i][3] = 1;
				}

				matrixRecalculation2(mas, pro);

				for (int i = 0; i < N;i++) {
					Point* p = new Point;

					p->x = mas[i][0];
					p->y = mas[i][1];

					dis.push_back(*p);
				}

				vector<int> index;
				ConvexHullJarvis(dis, index);

				if (index.size() == 3) {

					double fill[3][2];

					fill[0][0] = dis[index[0]].x;
					fill[0][1] = dis[index[0]].y;
					fill[1][0] = dis[index[1]].x;
					fill[1][1] = dis[index[1]].y;
					fill[2][0] = dis[index[2]].x;
					fill[2][1] = dis[index[2]].y;

					FillFigure3(hdc, fill);
				}
				else {

					double fill[4][2];

					fill[0][0] = dis[index[0]].x;
					fill[0][1] = dis[index[0]].y;
					fill[1][0] = dis[index[1]].x;
					fill[1][1] = dis[index[1]].y;
					fill[2][0] = dis[index[2]].x;
					fill[2][1] = dis[index[2]].y;
					fill[3][0] = dis[index[3]].x;
					fill[3][1] = dis[index[3]].y;

					FillFigure4(hdc, fill);
				}

				dis.clear();
				index.clear();
				k += 4;
			}
			
	}

	void ConvexHullJarvis(const vector<Point>& mas, vector<int>& convex_hull)
	{
		// находим самую левую из нижних
		int base = 0;
		for (int i = 1;i < N;i++)
		{
			if (mas[i].y < mas[base].y)
				base = i;
			else
				if (mas[i].y == mas[base].y &&
					mas[i].x < mas[base].x)
					base = i;
		}
		// эта точка точно входит в выпуклую оболочку
		convex_hull.push_back(base);

		int first = base;
		int cur = base;
		do
		{
			int next = (cur + 1) % N;
			for (int i = 0;i < N;i++)
			{
				int sign = OrientTriangl2(mas[cur], mas[next], mas[i]);
				// точка mas[i] находится левее прямой ( mas[cur], mas[next] )
				if (sign < 0) // обход выпуклой оболочки против часовой стрелки
					next = i;
				// точка лежит на прямой, образованной точками  mas[cur], mas[next]
				else if (sign == 0)
				{
					// точка mas[i] находится дальше, чем mas[next] от точки mas[cur]
					if (isInside(mas[cur], mas[next], mas[i]))
						next = i;
				}
			}
			cur = next;
			convex_hull.push_back(next);
		} while (cur != first);
	}

	bool isInside(const Point& p1, const Point& p, const Point& p2)
	{
		return (p1.x <= p.x && p.x <= p2.x && p1.y <= p.y && p.y <= p2.y);
	}

	int OrientTriangl2(const Point& p1, const Point& p2, const Point& p3)
	{
		return p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y);
	}

	void printLines(HDC hdc) {
		Lines(hdc, static_cast<int>(copy[0][0]), static_cast<int>(copy[0][1]), static_cast<int>(copy[1][0]), static_cast<int>(copy[1][1]));
		Lines(hdc, static_cast<int>(copy[1][0]), static_cast<int>(copy[1][1]), static_cast<int>(copy[2][0]), static_cast<int>(copy[2][1]));
		Lines(hdc, static_cast<int>(copy[2][0]), static_cast<int>(copy[2][1]), static_cast<int>(copy[0][0]), static_cast<int>(copy[0][1]));

		Lines(hdc, static_cast<int>(copy[0][0]), static_cast<int>(copy[0][1]), static_cast<int>(copy[3][0]), static_cast<int>(copy[3][1]));
		Lines(hdc, static_cast<int>(copy[1][0]), static_cast<int>(copy[1][1]), static_cast<int>(copy[3][0]), static_cast<int>(copy[3][1]));
		Lines(hdc, static_cast<int>(copy[2][0]), static_cast<int>(copy[2][1]), static_cast<int>(copy[3][0]), static_cast<int>(copy[3][1]));
	}
};

#endif
