#include<iostream>
#include<gl/glut.h>
using namespace std;
int a, b;
void MidpointEllipse() {
	int x, y;
	float d1, d2;
	x = 0; y = b;
	d1 = b * b + a * a * (-b + 0.25);//��ʼλ����x=0ʱ��F��0��b��
	glVertex2d(x, y);
	glVertex2d(x, -y);
	glVertex2d(-x, y);
	glVertex2d(-x, -y);
	while (b * b * (x + 1) < a * a * (y - 0.5)) {
		if (d1 < 0) {
			d1 = d1 + b * b * (2*x + 3);
			x++;
		}
		else {
			d1 = d1 + b * b * (2 * x + 3) + a * a * (2 - 2 * y);
			x++;
			y--;
		}
		glVertex2d(x, y);
		glVertex2d(x, -y);
		glVertex2d(-x, y);
		glVertex2d(-x, -y);
	}
	d2 = sqrt(b * (x + 0.5)) + sqrt(a * (y - 1)) - sqrt(a * b);
	while (y > 0) {
		if (d2 < 0) {
			d2 = d2 + b * b * (2 * x + 2) + a * a * (-2 * y + 3);
			x++;
			y--;
		}
		else {
			d2 = d2 + a * a * (-2*y + 3);
			y--;
		}
		glVertex2d(x, y);
		glVertex2d(x, -y);
		glVertex2d(-x, y);
		glVertex2d(-x, -y);
	}
}

void PaintCircle() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	MidpointEllipse();
	glEnd();
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);  //��ʼ��glut��
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //���ó�ʼ��ʾģʽ
	cout << "Please enter the long and short half axes of the ellipse: " << endl;
	cin >> a >> b;
	glutInitWindowPosition(50, 100);//���ó�ʼ����λ��
	glutInitWindowSize(500, 500);   //���ó�ʼ���ڵĴ�С����λ������
	glutCreateWindow("��Բ��ɨ��ת����");
	glClearColor(0, 0, 0, 0);  //��ɫ���򱳾���ɫΪ��ɫ
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-250, +250, -250, +250);//ָ����Ļ�����Ӧ��ģ�����귶Χ
	glutDisplayFunc(PaintCircle);
	glutMainLoop();
	system(0);
	return 0;
}