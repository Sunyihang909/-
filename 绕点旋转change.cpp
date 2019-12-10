#include<gl/glut.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <iostream>
using namespace std;
#define COLOR_NEW 1.0,0.0,0.0
#define FALSE 0
#define TRUE 1
double yuan[3];
double newroll[3];
double he[3][3];
int m, n;
struct Point
{
	int x;
	int y;
	Point(int a = 0, int b = 0)
	{
		x = a;
		y = b;
	}
};
Point sptt[7];
struct Bian_list
{
	float jx;
	float dx;
	int ymin;
	int ymax;
	bool sp;
};
struct Xb
{
	float x[10];
	int num;
};
struct Huo_list
{
	int num;
	Bian_list* next[10];
};



void InitiateHuo_list(Huo_list* H)
{
	H->num = 0;
	H->next[0] = NULL;
}
void InsertHuo_list(Huo_list* H, Bian_list* b_list)
{
	H->next[H->num] = b_list;
	H->num++;
}
/*void Deleteb_list(Huo_list* &H, int j)
{
	int i;
	for (i = j; i < H->num; i++)
	{
		H->next[i] = H->next[i + 1];
	}
	H->num--;
}*/
void pai_xuHuo_list(Xb* xb)
{
	int n = xb->num;
	int i, j;
	float temp;
	for (i = 0; i < n - 1; i++)
	{
		temp = xb->x[i + 1];
		j = i;
		while (j > -1 && temp < xb->x[j])
		{
			xb->x[j + 1] = xb->x[j];
			j--;
		}
		if (temp == xb->x[j])
		{
			while (j < n)
			{
				xb->x[j] = xb->x[j + 1];
				j++;
			}
			n--;
		}
		else
			xb->x[j + 1] = temp;
		xb->num = n;
	}
}
//ScanLine用于设多边形存储的顶点序列，顶点数等于边数

void ScanLine(Point* Polygon_point, int num_point)
{
	//point_ymax,point_ymin,num_smx用来确定扫描线链表的个数
	int i, j, point_ymax, point_ymin, num_smx;
	point_ymax = Polygon_point[1].y;
	point_ymin = Polygon_point[1].y;
	for (i = 0; i < num_point; i++)
	{
		if (Polygon_point[i].y > point_ymax)
			point_ymax = Polygon_point[i].y;
		if (Polygon_point[i].y < point_ymin)
			point_ymin = Polygon_point[i].y;
	}
	num_smx = point_ymax - point_ymin;
	//建立、初始化边表
	Bian_list* b_list = (Bian_list*)malloc(num_point * sizeof(Bian_list));
	//n个点n-1条边
	for (i = 0; i < num_point - 1; i++)
	{
		//jx其实是保存扫描线与边的当前交点值，即ymin对应的jx,Cpoint(jx,ymin)
		if (Polygon_point[i].y < Polygon_point[i + 1].y)
			b_list[i].jx = Polygon_point[i].x;
		else
			b_list[i].jx = Polygon_point[i + 1].x;

		if (Polygon_point[i].y != Polygon_point[i + 1].y)
		{
			//忽略斜率为无穷，即忽略水平线
			b_list[i].dx = (float)(Polygon_point[i].x - Polygon_point[i + 1].x) /
				(Polygon_point[i].y - Polygon_point[i + 1].y);
			b_list[i].sp = FALSE;
		}
		else
		{
			//dx取较大的x
			b_list[i].dx = (Polygon_point[i].x > Polygon_point[i + 1].x) ? Polygon_point[i].x : Polygon_point[i + 1].x;
			//jx取较小的x
			b_list[i].jx = (Polygon_point[i].x < Polygon_point[i + 1].x) ? Polygon_point[i].x : Polygon_point[i + 1].x;
			b_list[i].sp = TRUE;
		}
		b_list[i].ymax = (Polygon_point[i].y > Polygon_point[i + 1].y) ? Polygon_point[i].y : Polygon_point[i + 1].y;
		b_list[i].ymin = (Polygon_point[i].y < Polygon_point[i + 1].y) ? Polygon_point[i].y : Polygon_point[i + 1].y;
		//printf("%d \n",b_list[i].ymax);
	}


	//建立、初始化新边表
	Xb xb;
	Huo_list* h_list = new(Huo_list);
	h_list->num = 0;
	//for (i = 0; i < num_point ; i++)
	//printf("%f %f %d %d ", b_list[i].jx, b_list[i].dx, b_list[i].ymax, i);
	for (i = point_ymin; i < point_ymax;)
	{

		for (j = 0; j < num_point - 1; j++)
			if (i == b_list[j].ymin)
			{
				InsertHuo_list(h_list, &b_list[j]);
			}
		int n = 0;
		xb.num = 0;
		while (n < h_list->num)
		{
			if (h_list->next[n]->sp)
			{
				xb.x[xb.num] = h_list->next[n]->jx;
				//printf("%f ", xb.x[xb.num]);
				xb.num++;
				xb.x[xb.num] = h_list->next[n]->dx;
				xb.num++;
			}
			else
			{
				xb.x[xb.num] = h_list->next[n]->jx + h_list->next[n]->dx * (i - h_list->next[n]->ymin);
				//if (i == 101)
					//printf("i==101shi %f %f %d ", h_list->next[n]->jx, h_list->next[n]->dx, h_list->next[n]->ymax);
				xb.num++;

			}
			n++;
		}
		pai_xuHuo_list(&xb);

		bool tc = FALSE;
		for (j = 0; j < xb.num - 1; j++, j++)
		{
			//printf("%f %f ", xb.x[j], xb.x[j+1]);
			int x, x1, xr;
			x1 = xb.x[j];
			xr = xb.x[j + 1];
			x = x1;
			while (x <= xr)
			{
				glColor3f(COLOR_NEW);
				glVertex2i(x, i);
				x++;
			}
		}
		//printf("\n");
		if (i == point_ymin)
			i--;
		i++;
		for (j = 0; j < h_list->num; j++) {
			//if (i == 100)
				//printf("h-list:%d ", h_list->next[j]->ymax);
			if (i == h_list->next[j]->ymax)
			{
				//Deleteb_list(h_list, j);
				int k;
				for (k = j; k < h_list->num - 1; k++)
				{
					//cout << "11111";
					h_list->next[k]->dx = h_list->next[k + 1]->dx;
					h_list->next[k]->jx = h_list->next[k + 1]->jx;
					h_list->next[k]->sp = h_list->next[k + 1]->sp;
					h_list->next[k]->ymax = h_list->next[k + 1]->ymax;
					h_list->next[k]->ymin = h_list->next[k + 1]->ymin;
					//cout <<"slm"<< h_list->next[k + 1]->jx << endl;
				}
				//printf("%f ", h_list->next[j]->jx);
				//cout << " uuu"<< h_list->next[j]->jx << " ";
				h_list->num--;
				j--;
				//cout << h_list->num << endl;
			}
		}
		if (i == point_ymin)
			i++;
	}

}

void funcshuzu(int x, int y) {
	he[0][0] = 0.5;
	he[0][1] = -0.5;
	he[0][2] = 0;
	he[1][0] = -0.5;
	he[1][1] = 0.5;
	he[1][2] = 0;
	he[2][0] = 0.5 * x + 0.5 * y;
	he[2][1] = 0.5 * x + 0.5 * y;
	he[2][2] = 1;
}
void roll(Point* Polygon) {
	funcshuzu(m, n);
	for (int j = 0; j < 3; j++) {
		newroll[j] = 0;
	}
	for (int i = 0; i < 7; i++) {
		yuan[0] = Polygon[i].x;
		yuan[1] = Polygon[i].y;
		yuan[2] = 1;
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				newroll[j] += yuan[k] * he[k][j];
			}
		}
		//sptt[i] = Point(newroll[0], newroll[1]);
		sptt[i].x = newroll[0];
		sptt[i].y = newroll[1];
		for (int j = 0; j < 3; j++) {
			newroll[j] = 0;
		}
	}
}

void ScanLineSegment()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	int a, b;
	Point spt[7];
	for (size_t i = 0; i < 7; i++)
	{
		cin >> a >> b;
		spt[i] = Point(a, b);
	}
	cin >> m >> n;
	/*
	230 230
	280 230
	275 280
	245 290
	200 270
	215 235
	230 230
	*//*0 100 0 200 50 250 100 200 100 100 50 50 0 100*/
	/*0 5
2 2
8 2
10 5
8 8
2 8
0 5*/
	//ScanLine(spt, 7);
	roll(spt);
	ScanLine(sptt, 7);
	for (int i = 0; i < 7; i++) {
		printf("%d %d\n", sptt[i].x, sptt[i].y);
	}
	glEnd();
	glFlush();
}
void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("扫描填充算法");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutDisplayFunc(ScanLineSegment);
	glutMainLoop();
}



