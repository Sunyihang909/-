#include<gl/glut.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <iostream>
using namespace std;
#define COLOR_NEW 1.0,0.0,0.0
#define FALSE 0
#define TRUE 1
struct Point{
	int x;
	int y;
	Point(int a = 0, int b = 0){
		x = a;
		y = b;
	}
};
struct Bian_list{
	float jx;
	float dx;
	int ymin;
	int ymax;
	bool sp;
};
struct Xb{
	float x[10];
	int num;
};
struct Huo_list{
	int num;
	Bian_list* next[10];
};
void InitiateHuo_list(Huo_list* H){
	H->num = 0;
	H->next[0] = NULL;
}
void InsertHuo_list(Huo_list* H, Bian_list* b_list){
	H->next[H->num] = b_list;
	H->num++;
}
void pai_xuHuo_list(Xb* xb){
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
		if(temp == xb->x[j])
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
//ScanLine���������δ洢�Ķ������У����������ڱ���
void ScanLine(Point* Polygon_point, int num_point){
	int i, j, point_ymax, point_ymin, num_smx;//point_ymax,point_ymin,num_smx����ȷ��ɨ��������ĸ���
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
	//��������ʼ���߱�
	Bian_list* b_list = (Bian_list*)malloc(num_point * sizeof(Bian_list));
	//n����n-1����
	for (i = 0; i < num_point - 1; i++)
	{
		//jx��ʵ�Ǳ���ɨ������ߵĵ�ǰ����ֵ����ymin��Ӧ��jx,Cpoint(jx,ymin)
		if (Polygon_point[i].y < Polygon_point[i + 1].y)
			b_list[i].jx = Polygon_point[i].x;
		else
			b_list[i].jx = Polygon_point[i + 1].x;

		if (Polygon_point[i].y != Polygon_point[i + 1].y)
		{
			//����б��Ϊ���������ˮƽ��
			b_list[i].dx = (float)(Polygon_point[i].x - Polygon_point[i + 1].x) /
				(Polygon_point[i].y - Polygon_point[i + 1].y);
			b_list[i].sp = FALSE;
		}
		else
		{
			//dxȡ�ϴ��x
	b_list[i].dx=(Polygon_point[i].x>Polygon_point[i+1].x)?Polygon_point[i].x:Polygon_point[i+1].x;
			//jxȡ��С��x
	b_list[i].jx=(Polygon_point[i].x<Polygon_point[i+1].x)?Polygon_point[i].x:Polygon_point[i+1].x;
		b_list[i].sp = TRUE;
		}
b_list[i].ymax=(Polygon_point[i].y > Polygon_point[i + 1].y) ? Polygon_point[i].y : Polygon_point[i + 1].y;
b_list[i].ymin=(Polygon_point[i].y < Polygon_point[i + 1].y) ? Polygon_point[i].y : Polygon_point[i + 1].y;
		//printf("%d \n",b_list[i].ymax);
	}
	//��������ʼ���±߱�
	Xb xb;
	Huo_list* h_list = new(Huo_list);
	h_list->num = 0;
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
				xb.num++;
				xb.x[xb.num] = h_list->next[n]->dx;
				xb.num++;
			}
			else
			{
				xb.x[xb.num] = h_list->next[n]->jx + h_list->next[n]->dx * (i - h_list->next[n]->ymin);
				xb.num++;
			}
			n++;
		}
		pai_xuHuo_list(&xb);
		
		bool tc = FALSE;
		for (j = 0; j < xb.num-1; j++, j++)
		{
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
		if (i == point_ymin)
			i--;
		i++;
		for (j = 0; j < h_list->num; j++) {
			if (i == h_list->next[j]->ymax){
				int k;
				for (k = j; k < h_list->num-1; k++){
					h_list->next[k]->dx = h_list->next[k + 1]->dx;
					h_list->next[k]->jx = h_list->next[k + 1]->jx;
					h_list->next[k]->sp = h_list->next[k + 1]->sp;
					h_list->next[k]->ymax = h_list->next[k + 1]->ymax;
					h_list->next[k]->ymin = h_list->next[k + 1]->ymin;
				}
				h_list->num--;
				j--;
			}
		}
		if (i == point_ymin)
			i++;
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
		spt[i] = Point( a, b);
	}
	/*230 230 280 230 275 280 245 290 200 270 215 235 230 230*/
	ScanLine(spt, 7);
	glEnd();
	glFlush();
}
void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("ɨ������㷨");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutDisplayFunc(ScanLineSegment);
	glutMainLoop();
}



