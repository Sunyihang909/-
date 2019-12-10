#include <GL/glut.h>
#include <cmath>
#include<iostream>
#include<math.h>
using namespace std;
struct Point{
	float x;
	float y;
	Point(float a = 0, float b = 0){
		x = a;
		y = b;
	}
};
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}
void Midpointline(int x0, int y0, int x1, int y1) {
	int m=x0,n=y0, ml=x1,nl=y1;
	int a, b, d1, d2, d, x, y;
	float k;
	k=(float)1.0*(nl - n) /(float) (ml - m);
	cout << k<<endl;
	if (0 <= k&&k <= 1) {
		if (m > ml) {
			swap(m, ml);
			swap(n, nl);
		}
		a = n - nl;
		b = ml - m;
		d = 2 * a + b;
		d1 = 2 * a;
		d2 = 2 * (a + b);
		x = m;
		y = n;
		glVertex2f(x, y);
		while (x < ml) {
			if (d < 0) {
				x++;
				y++;
				d += d2;
			}
			else {
				x++;
				d += d1;
			}
			glVertex2f(x, y);
		}
	}
	else if(k>1){
		if (n > nl) {
			swap(m, ml);
			swap(n, nl);
		}
		a = n - nl;
		b = ml - m;
		d = a + 2*b;
		x = m;
		y = n;
		d1 = 2*b;
		d2 = 2 * (a + b);
		glVertex2f(x, y);
		while (y < nl) {
			if (d < 0) {
				y++;
				d += d1;
			}
			else {
				x++;
				y++;
				d += d2;
			}
			glVertex2f(x, y);
		}
	}
	else if (-1 <= k&&k < 0) {
		if (m > ml) {
			swap(m, ml);
			swap(n, nl);
		}
		a = n - nl;
		b = ml - m;
		d = 2 * a - b;
		d1 = 2 * a;
		d2 = 2 * (a - b);
		x = m;
		y = n;
		glVertex2f(x, y);
		while (x < ml) {
			if (d > 0) {
				x++;
				y--;
				d += d2;
			}
			else {
				x++;
				d += d1;
			}
			glVertex2f(x, y);
		}
	}
	else if(k<-1){//k<-1
		cout << "e";
		if (m>ml) {
			swap(m, ml);
			swap(n, nl);
		}
		a = n - nl;
		b = ml - m;
		d = a - 2 * b;
		d1 = -2*b;
		d2 = 2*(a - b);
		x = m;
		y = n;
		glVertex2f(x, y);
		while (y > nl) {
			if (d < 0) {
				x++;
				y--;
				d += d2;
			}
			else {
				y--;
				d += d1;
			}
			glVertex2f(x, y);
		}
	}
}
void  myDisplay(){
	Point str[7];
	Point temp[8][8];
	for (int i = 0; i < 6; i++) {
		cin >> str[i].x >> str[i].y;
	}
	str[6].x = str[0].x;
	str[6].y = str[0].y;
	cout << str[6].x << " " << str[6].y << endl;
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 6; i++) {
		Midpointline(str[i].x, str[i].y, str[i + 1].x, str[i + 1].y);
		cout << str[i].x << " " << str[i].y << " " << str[i + 1].x << " " << str[i + 1].y << endl;
	}
	glEnd();
	/*200 125 350 125 425 245 350 365 200 365 125 245*/
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 6; i++) {
		temp[1][i].x = str[i].x;
		temp[1][i].y = str[i].y;
	}
	for (float t = 0; t <= 1; t += 0.01){
		for (int i = 2; i <= 7; i++) {
			for (int j = 0; j <= 7 - i ; j++) {
				temp[i][j].x = (1 - t) * temp[i - 1][j].x + t * temp[i - 1][j + 1].x;
				temp[i][j].y = (1 - t) * temp[i - 1][j].y + t * temp[i - 1][j + 1].y;
			}
		}
		glVertex2f(temp[7][0].x, temp[7][0].y);
		cout << temp[7][0].x << " " << temp[7][0].y << endl;
	}
	glEnd();
	glFlush();
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Èý´ÎBezierÇúÏß");
	init();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}