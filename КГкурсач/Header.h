#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#define NORM
#define CLASS
#define V 500
#define N 4
#define M 4//8
#ifdef ARR
void FillFigure(HDC hdc, double tri[3][2], int r = 47, int g = 47, int b = 89);
#endif
using namespace std;
double pro[N][N] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {sqrt(2) / 4, sqrt(2) / 4, 0, 1}, {0, 0,
0, 0} };
#ifdef paint
struct Point {
	double x, y, z;
	};
#endif

#ifdef ARR
double COPY[M][N];
void matrixRecalculation(double line[M][N], double array[N][N]) { //пересчеткоординат линии
		double res[M][N] = { 0 }; //вспомогательная матрица
	for (int k = 0; k < M; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				res[k][i] += line[k][j] * array[j][i]; //умножение матриц
	for (int k = 0; k < M; k++)
		for (int i = 0; i < N; i++)
			line[k][i] = res[k][i]; //присваивание новых координат, новая матрица для отрисовки
}
void move(double line[M][N], int dx, int dy, int dz)
{
	double move[N][N] = { {1, 0, 0, 0},
	 {0, 1, 0, 0},
	 {0, 0, 1, 0},
	 {dx, dy, dz, 1} };
	matrixRecalculation(line, move);
}
double aver(double line[M][N], int cnt)
{
	double average = 0;
	for (int i = 0; i < N; i++)
		average += line[i][cnt];
	return average / N;
}
void rotationOnOX(double line[M][N], double rot)
{
	double y = 0, z = 0;
	y = aver(line, 1);
	z = aver(line, 2);
	double res[N][N] = { {1, 0,
	0, 0},
	{0, cos(rot),
	sin(rot), 0},
	{0, -sin(rot),
	cos(rot), 0},
	{0, y * (1 - cos(rot)) + z * sin(rot), z * (1 -
	cos(rot)) - y * sin(rot), 1} };
	matrixRecalculation(line, res);
}
void rotationOnOY(double line[M][N], double rot)
{
	double x = 0, z = 0;
	x = aver(line, 0);
	z = aver(line, 2);
	double res[N][N] = { {cos(rot), 0,
	-sin(rot), 0},
	{0,
	1, 0, 0},
	{sin(rot),
	0, cos(rot), 0},
	{x * (1 - cos(rot)) - z * sin(rot), 0, z * (1 -
	cos(rot)) + x * sin(rot), 1} };
	matrixRecalculation(line, res);
}
void rotationOnOZ(double line[M][N], double rot)
{
	double x = 0, y = 0;
	x = aver(line, 0);
	y = aver(line, 1);
	double res[N][N] = { {cos(rot),
	sin(rot), 0, 0},
	{-sin(rot),
	cos(rot), 0, 0},
	{0,
	 0, 1, 0},
	{x * (1 - cos(rot)) + y * sin(rot), y * (1 -
	cos(rot)) - x * sin(rot), 0, 1} };
	matrixRecalculation(line, res);
}

double Gust[N][N]{
{100,100,100,1}, //лицо
{200,100,110,1},
{150,120,50,1},
{170,250,70,1},
};

void PinkGust(HDC hdc, double line[M][N]) {

	double av[4];
	double av1[4];
	av[0] =av1[0]=(Gust[0][2] + Gust[1][2] + Gust[2][2]) / 3.0;
	av[1] =av1[1]=(Gust[0][2] + Gust[1][2] + Gust[3][2]) / 3.0;
	av[2] =av1[2]=(Gust[0][2] + Gust[2][2] + Gust[3][2]) / 3.0;
	av[3] =av1[3]=(Gust[1][2] + Gust[2][2] + Gust[3][2]) / 3.0;

	for (int i = 0;i < 3;i++) {
		if (av[i] > av[i + 1]) {
			std::swap(av[i],av[i+1]);
		}
	}

	for (int i=0; i < 4;i++) {

		if (av[i] == av1[0]) {
			double fill[3][2] = { 0 };
			fill[0][0] = line[0][0];
			fill[0][1] = line[0][1];
			fill[1][0] = line[1][0];
			fill[1][1] = line[1][1];
			fill[2][0] = line[2][0];
			fill[2][1] = line[2][1];
			FillFigure(hdc, fill, 0, 0, 255);
		}

		else if (av[i] == av1[1]) {
			double fill[3][2] = { 0 };
			fill[0][0] = line[0][0];
			fill[0][1] = line[0][1];
			fill[1][0] = line[1][0];
			fill[1][1] = line[1][1];
			fill[2][0] = line[3][0];
			fill[2][1] = line[3][1];
			FillFigure(hdc, fill, 255, 0, 0);

		}

		else if (av[i] == av1[2]) {
			double fill[3][2] = { 0 };
			fill[0][0] = line[0][0];
			fill[0][1] = line[0][1];
			fill[1][0] = line[2][0];
			fill[1][1] = line[2][1];
			fill[2][0] = line[3][0];
			fill[2][1] = line[3][1];
			FillFigure(hdc, fill, 0, 255, 0);

		}

		else if (av[i] == av1[3]) {
			double fill[3][2] = { 0 };
			fill[0][0] = line[1][0];
			fill[0][1] = line[1][1];
			fill[1][0] = line[2][0];
			fill[1][1] = line[2][1];
			fill[2][0] = line[3][0];
			fill[2][1] = line[3][1];
			FillFigure(hdc, fill, 0, 255, 255);

		}
	}
	

	/*
	//1562
	if (((line[2][0] * line[6][1] - line[6][0] * line[2][1]) * V - (line[1][0] *
		line[6][1] - line[6][0] * line[1][1]) * V + (line[0][0] * line[2][1] - line[2][0] *
			line[0][1]) * V) >= 0) {
		double fill[4][2] = { 0 };
		fill[0][0] = line[1][0];
		fill[0][1] = line[1][1];
		fill[1][0] = line[5][0];
		fill[1][1] = line[5][1];
		fill[2][0] = line[6][0];
		fill[2][1] = line[6][1];
		fill[3][0] = line[2][0];
		fill[3][1] = line[2][1];
		FillFigure(hdc, fill, 0, 0, 255); //синий
	}
	//0123
	if (((line[2][0] * line[1][1] - line[1][0] * line[2][1]) * V - (line[3][0] *
		line[1][1] - line[1][0] * line[3][1]) * V + (line[3][0] * line[2][1] - line[2][0] *
			line[3][1]) * V) >= 0) {
		double fill[4][2] = { 0 };
		fill[0][0] = line[0][0];
		fill[0][1] = line[0][1];
		fill[1][0] = line[1][0];
		fill[1][1] = line[1][1];
		fill[2][0] = line[2][0];
		fill[2][1] = line[2][1];
		fill[3][0] = line[3][0];
		fill[3][1] = line[3][1];
		FillFigure(hdc, fill, 255, 0, 0); //красный
	}
	//0451
	if (((line[1][0] * line[5][1] - line[5][0] * line[1][1]) * V - (line[0][1] *
		line[5][1] - line[5][0] * line[0][1]) * V + (line[0][0] * line[1][1] - line[1][0] *
			line[0][1]) * V) >= 0) {
		double fill[4][2] = { 0 };
		fill[0][0] = line[0][0];
		fill[0][1] = line[0][1];
		fill[1][0] = line[4][0];
		fill[1][1] = line[4][1];
		fill[2][0] = line[5][0];
		fill[2][1] = line[5][1];
		fill[3][0] = line[1][0];
		fill[3][1] = line[1][1];
		FillFigure(hdc, fill, 0, 255, 0); //зеленый
	}
	//2376
	if (((line[2][0] * line[3][1] - line[3][0] * line[2][1]) * V - (line[6][0] *
		line[3][1] - line[3][0] * line[6][1]) * V + (line[6][0] * line[2][1] - line[2][0] *
			line[6][1]) * V) >= 0) {
		double fill[4][2] = { 0 };
		fill[0][0] = line[3][0];
		fill[0][1] = line[3][1];
		fill[1][0] = line[7][0];
		fill[1][1] = line[7][1];
		fill[2][0] = line[6][0];
		fill[2][1] = line[6][1];
		fill[3][0] = line[2][0];
		fill[3][1] = line[2][1];
		FillFigure(hdc, fill, 255, 255, 0); //желтый
	}
	//3047
	if (((line[3][0] * line[0][1] - line[0][0] * line[3][1]) * V - (line[7][0] *
		line[0][1] - line[0][0] * line[7][1]) * V + (line[7][0] * line[3][1] - line[3][0] *
			line[7][1]) * V) >= 0) {
		double fill[4][2] = { 0 };
		fill[0][0] = line[0][0];
		fill[0][1] = line[0][1];
		fill[1][0] = line[4][0];
		fill[1][1] = line[4][1];
		fill[2][0] = line[7][0];
		fill[2][1] = line[7][1];
		fill[3][0] = line[3][0];
		fill[3][1] = line[3][1];
		FillFigure(hdc, fill, 255, 0, 255); //фиолетовый
	}
	//4567
	if (((line[5][0] * line[6][1] - line[6][0] * line[5][1]) * V - (line[4][0] *
		line[6][1] - line[6][0] * line[4][1]) * V + (line[4][0] * line[5][1] - line[5][0] *
			line[4][1]) * V) >= 0) {
		double fill[4][2] = { 0 };
		fill[0][0] = line[4][0];
		fill[0][1] = line[4][1];
		fill[1][0] = line[5][0];
		fill[1][1] = line[5][1];
		fill[2][0] = line[6][0];
		fill[2][1] = line[6][1];
		fill[3][0] = line[7][0];
		fill[3][1] = line[7][1];
		FillFigure(hdc, fill, 0, 255, 255); //бирюзовый
	}*/
}

void FillFigure(HDC hdc, double tri[3][2], int r, int g, int b) {
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
				temp[temp_lp][1] + 0.5))
				* (temp[pick_l][0] - temp[temp_lp][0]) + temp[temp_lp][0];
			xr = ((temp_y - temp[temp_rp][1]) / (temp[pick_r][1] -
				temp[temp_rp][1] + 0.5))
				* (temp[pick_r][0] - temp[temp_rp][0]) + temp[temp_rp][0];
		}
		SelectObject(hdc, p);
		MoveToEx(hdc, xl, temp_y, NULL);
		LineTo(hdc, xr, temp_y);
		DeleteObject(p);
		temp_y++;
	}
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

void printLines(HDC hdc) {
	Lines(hdc, COPY[0][0], COPY[0][1], COPY[1][0], COPY[1][1]);
	Lines(hdc, COPY[1][0], COPY[1][1], COPY[2][0], COPY[2][1]);
	Lines(hdc, COPY[2][0], COPY[2][1], COPY[0][0], COPY[0][1]);

	Lines(hdc, COPY[0][0], COPY[0][1], COPY[3][0], COPY[3][1]);
	Lines(hdc, COPY[1][0], COPY[1][1], COPY[3][0], COPY[3][1]);
	Lines(hdc, COPY[2][0], COPY[2][1], COPY[3][0], COPY[3][1]);
}

void zoom(double line[M][N], double st)
{
	double x = 0, y = 0, z = 0;
	x = aver(line, 0);
	y = aver(line, 1);
	z = aver(line, 2);
	double res[N][N] = { {st, 0, 0, 0},
	{0, st, 0,
	0},
	{0, 0, st,
	0},
	{x * (1 - st),y * (1 - st),z * (1 - st),1} };
	matrixRecalculation(line, res);
}
void realshoot(HDC hdc, double line[M][N]) {
	double Xrot;
	double Yrot;
	HPEN p;
	p = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); //цвет, толщина рисования
	SelectObject(hdc, p);
	Xrot = (line[40][0] + line[41][0]) / 2;
	Yrot = (line[40][1] + line[41][1]) / 2;
	int i = 0;
	while (i != 100) {
		Rectangle(hdc, Xrot + i, Yrot, Xrot + i + 10, Yrot + 10);
		//Sleep(5);
		i++;
	}
	DeleteObject(p);
}
/*
double prism[M][N] = {
{100, 400, 100, 1},
{250, 200, 100, 1},
{250, 200, 100, 1},
{400, 400, 100, 1},
{250, 300, 300, 1},
{250, 300, 300, 1},
{250, 300, 300, 1},
{250, 300, 300, 1} };
*/
/*
double Fig[M][N] = {
{100, 100, 100,1}, //лицевая
{150, 100, 100,1},
{100, 180, 100,1},
{150, 180, 100,1},
{100, 100, 150,1}, //задняя
{150, 100, 150,1},
{100, 180, 150,1},
{150, 180, 150,1},
{110, 160, 100,1},//рот
{140, 160, 100,1},
{125, 140, 100,1}, //нос
{125, 120, 100,1} };
*/
#endif


#ifdef CLASS
class Pyramid {
private:

	std::vector<std::vector<double>> data;
	std::vector<std::vector<double>> copy;
	
public:

	Pyramid() {

		data.push_back({ 100, 100, 100, 1 });
		data.push_back({ 200, 100, 100, 1 });
		data.push_back({ 150, 120, 50, 1 });
		data.push_back({ 170, 250, 70, 1 });
	
	}

	~Pyramid() {
		data.clear();
		copy.clear();
	}

	double getCoord() {
		return data[0][0];
	}

	void copyf() {
		copy= data;
	}

	void matrixRecalculation(double array[N][N], bool f = 0) { //пересчет координат 
	
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
						res[k][i] += copy[k][j] * array[j][i]; //умножение матриц
			for (int k = 0; k < M; k++)
				for (int i = 0; i < N; i++)
					copy[k][i] = res[k][i]; //присваивание новых координат, новая матрица для отрисовки

		}
	}

	double aver(int cnt)
	{
		double average = 0;
		for (int i = 0; i < N; i++)
			average += data[i][cnt];
		return average / N;
	}

	void rotationOnOZ(double rot)
	{
		double x = 0, y = 0;
		x = aver(0);
		y = aver(1);
		double res[N][N] = { 
			{cos(rot), sin(rot), 0, 0},
			{-sin(rot), cos(rot), 0, 0},
			{0, 0, 1, 0},
			{x * (1 - cos(rot)) + y * sin(rot), y * (1 -  cos(rot)) - x * sin(rot), 0, 1} };
		matrixRecalculation(res);
	}

	void rotationOnOX(double rot)
	{
		double y = 0, z = 0;
		y = aver(1);
		z = aver(2);
		double res[N][N] = { 
			{1, 0, 0, 0},
			{0, cos(rot), sin(rot), 0},
			{0, -sin(rot), cos(rot), 0},
			{0, y * (1 - cos(rot)) + z * sin(rot), z * (1 - cos(rot)) - y * sin(rot), 1} };
		matrixRecalculation(res);
	}
	void rotationOnOY(double rot)
	{
		double x = 0, z = 0;
		x = aver(0);
		z = aver(2);
		double res[N][N] = { 
			{cos(rot), 0, -sin(rot), 0},
			{0, 1, 0, 0},
			{sin(rot), 0, cos(rot), 0},
			{x * (1 - cos(rot)) - z * sin(rot), 0, z * (1 - cos(rot)) + x * sin(rot), 1} };
		matrixRecalculation(res);
	}

	
	void zoom(double st)
	{
		double x = 0, y = 0, z = 0;
		x = aver(0);
		y = aver(1);
		z = aver(2);
		double res[N][N] = { {st, 0, 0, 0},
		{0, st, 0, 0},
		{0, 0, st, 0},
		{x * (1 - st),y * (1 - st),z * (1 - st),1} };
		matrixRecalculation(res);
	}


	void move(int dx, int dy, int dz)
	{
		//std::vector<std::vector<double>> t = {

		double move[N][N]{
		 {1, 0, 0, 0},
		 {0, 1, 0, 0},
		 {0, 0, 1, 0},
		 {dx, dy, dz, 1}
		};
		
		matrixRecalculation(move);
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
		double av[4];
		double av1[4];
		av[0] = av1[0] = (data[0][2] + data[1][2] + data[2][2]) / 3.0;
		av[1] = av1[1] = (data[0][2] + data[1][2] + data[3][2]) / 3.0;
		av[2] = av1[2] = (data[0][2] + data[2][2] + data[3][2]) / 3.0;
		av[3] = av1[3] = (data[1][2] + data[2][2] + data[3][2]) / 3.0;

		for (int i = 0;i < 3;i++) {
			if (av[i] > av[i + 1]) {
				std::swap(av[i], av[i + 1]);
			}
		}

		for (int i = 0; i < 4;i++) {

			if (av[i] == av1[0] && in1 == 0) {
				in1++;
				double fill[3][2] = { 0 };
				fill[0][0] = copy[0][0];
				fill[0][1] = copy[0][1];
				fill[1][0] = copy[1][0];
				fill[1][1] = copy[1][1];
				fill[2][0] = copy[2][0];
				fill[2][1] = copy[2][1];
				FillFigure(hdc, fill, 0, 0, 255);	//синий
			}

			if (av[i] == av1[1] && in2 == 0) {
				in2++;
				double fill[3][2] = { 0 };
				fill[0][0] = copy[0][0];
				fill[0][1] = copy[0][1];
				fill[1][0] = copy[1][0];
				fill[1][1] = copy[1][1];
				fill[2][0] = copy[3][0];
				fill[2][1] = copy[3][1];
				FillFigure(hdc, fill, 255, 0, 0);//КРАСНЫЙ

			}

			if (av[i] == av1[2] && in3 ==0) {
				in3++;
				double fill[3][2] = { 0 };
				fill[0][0] = copy[0][0];
				fill[0][1] = copy[0][1];
				fill[1][0] = copy[2][0];
				fill[1][1] = copy[2][1];
				fill[2][0] = copy[3][0];
				fill[2][1] = copy[3][1];
				FillFigure(hdc, fill, 0, 255, 0);//зеленый

			}

			if (av[i] == av1[3] && in4==0) {
				in4++;
				double fill[3][2] = { 0 };
				fill[0][0] = copy[1][0];
				fill[0][1] = copy[1][1];
				fill[1][0] = copy[2][0];
				fill[1][1] = copy[2][1];
				fill[2][0] = copy[3][0];
				fill[2][1] = copy[3][1];
				FillFigure(hdc, fill, 0, 255, 255);//бирюза

			}
		}

	}
#endif // paint


#ifdef NORM
	void Bres(HDC hdc) {

		if (((copy[0][0] * copy[1][1] - copy[1][0] * copy[0][1]) * V - (copy[2][0] *
			copy[1][1] - copy[1][0] * copy[2][1]) * V + (copy[0][0] * copy[2][1] - copy[2][0] *
				copy[0][1]) * 210) > 0) {
			double fill[3][2] = { 0 };
			fill[0][0] = copy[0][0];
			fill[0][1] = copy[0][1];
			fill[1][0] = copy[1][0];
			fill[1][1] = copy[1][1];
			fill[2][0] = copy[2][0];
			fill[2][1] = copy[2][1];
			FillFigure(hdc, fill, 0, 0, 255);
		}

		else if (((copy[0][0] * copy[1][1] - copy[1][0] * copy[0][1]) * V - (copy[3][0] *
			copy[1][1] - copy[1][0] * copy[3][1]) * V + (copy[0][0] * copy[3][1] - copy[3][0] *
				copy[0][1]) * 210) > 0) {
			double fill[3][2] = { 0 };
			fill[0][0] = copy[0][0];
			fill[0][1] = copy[0][1];
			fill[1][0] = copy[1][0];
			fill[1][1] = copy[1][1];
			fill[2][0] = copy[3][0];
			fill[2][1] = copy[3][1];
			FillFigure(hdc, fill, 255, 0, 0);

		}

		else if (((copy[0][0] * copy[2][1] - copy[2][0] * copy[0][1]) * V - (copy[3][0] *
			copy[2][1] - copy[2][0] * copy[3][1]) * V + (copy[0][0] * copy[3][1] - copy[3][0] *
				copy[0][1]) * 210) > 0) {
			double fill[3][2] = { 0 };
			fill[0][0] = copy[0][0];
			fill[0][1] = copy[0][1];
			fill[1][0] = copy[2][0];
			fill[1][1] = copy[2][1];
			fill[2][0] = copy[3][0];
			fill[2][1] = copy[3][1];
			FillFigure(hdc, fill, 0, 255, 0);

		}

		else if (((copy[1][0] * copy[2][1] - copy[2][0] * copy[1][1]) * V - (copy[3][0] *
			copy[2][1] - copy[2][0] * copy[3][1]) * V + (copy[1][0] * copy[3][1] - copy[3][0] *
				copy[1][1]) * 210) > 0) {
			double fill[3][2] = { 0 };
			fill[0][0] = copy[1][0];
			fill[0][1] = copy[1][1];
			fill[1][0] = copy[2][0];
			fill[1][1] = copy[2][1];
			fill[2][0] = copy[3][0];
			fill[2][1] = copy[3][1];
			FillFigure(hdc, fill, 0, 255, 255);

		}
	}
#endif
	void FillFigure(HDC hdc, double tri[3][2] , int r = 50, int g = 50, int b = 50) {
		HPEN p;
		/*double tri[3][2] = {0};
		tri[0][0] = copy[0][0];
		tri[0][1] = copy[0][1];
		tri[1][0] = copy[2][0];
		tri[1][1] = copy[2][1];
		tri[2][0] = copy[3][0];
		tri[2][1] = copy[3][1];*/
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
					temp[temp_lp][1] + 0.5))
					* (temp[pick_l][0] - temp[temp_lp][0]) + temp[temp_lp][0];
				xr = ((temp_y - temp[temp_rp][1]) / (temp[pick_r][1] -
					temp[temp_rp][1] + 0.5))
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

bool compare(const double* p1, const double* p2) {
	return p1[2] < p2[2];
}

#endif
