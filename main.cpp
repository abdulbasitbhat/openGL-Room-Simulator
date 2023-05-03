#include<windows.h>
#include<GL\glut.h>
#include <GL/glu.h>
#include<math.h>
#include <stdlib.h>
#include<stdio.h>
#include<iostream>
#include <chrono>
#include <thread>

void timer(int);
float x_position = 100.0;
float gun_y_pos = 240.0;
bool fire = false;
bool light = true;
bool up = true;
bool shot = false;
float varr = 900.0;
float b_yp;
bool door_op = false;
float angle = 10;
bool fan_move = true;
float tx = 10;
float ty = 5;
bool start_bug = false;
float sx = 10;
float sy = 10;




void init() {
	glClearColor(0.93, 0.93, 0.93, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1000.0, 0.0, 500.0);
}

void line(int x1, int y1, int x2, int y2){ 

	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_POINTS);
	float y, m, c;
	float dx = x2 - x1;
	float dy = y2 - y1;
	m = dy / dx;
	c = y1 - m * x1;
	for (int x = x1; x <= x2; x++) {
		y = m * x + c;
		glVertex2f(x, y);

	}
	glEnd();
}

void midPointElipse(int rx, int ry, int xc, int yc){
	float dx, dy, d1, d2, x, y;
	x = 0;
	y = ry;

	d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
	dx = 2 * ry * ry * x;
	dy = 2 * rx * rx * y;
	glBegin(GL_POINTS);
	glColor3f(0.9f, 0.8f, 0.0f);
	// For region 1
	while (dx < dy)
	{
		glVertex2f(xc + x, yc + y);
		glVertex2f(xc + x, yc - y);
		glVertex2f(xc - x, yc + y);
		glVertex2f(xc - x, yc - y);
	
		if (d1 < 0){
			x++;
			dx = dx + (2 * ry * ry);
			d1 = d1 + dx + (ry * ry);
		}
		else{
			x++;
			y--;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			d1 = d1 + dx - dy + (ry * ry);
		}
	}
	d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);

	while (y >= 0){
		glVertex2f(xc + x, yc + y);
		glVertex2f(xc + x, yc - y);
		glVertex2f(xc - x, yc + y);
		glVertex2f(xc - x, yc - y);

		if (d2 > 0){
			y--;
			dy = dy - (2 * rx * rx);
			d2 = d2 + (rx * rx) - dy;
		}
		else{
			y--;
			x++;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			d2 = d2 + dx - dy + (rx * rx);
		}
	}
	glEnd();
}

void translate_bug() {
	
	//int ty = 1;
	int tm[3][3] = { {1, 0, tx},{0, 1, ty},{0, 0, 1} };
	
	if (start_bug == false) {
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(200, 370);
		glVertex2f(202, 374);
		glVertex2f(204, 370);
		glEnd();
	}
	start_bug = true;
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	int x_coord[3] = { 200,202,204 };
	int y_coord[3] = { 370,374,370 };

	for (int i = 0; i < 3; i++) {
		int coord[3][1] = { {x_coord[i]},{y_coord[i]},{1} };
		int output[3][1];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 1; j++) {
				output[i][j] = 0;
				for (int k = 0; k < 3; k++) {
					output[i][j] += tm[i][k] * coord[k][j];
				}
			}
		}
		glVertex2f(output[0][0], output[1][0]);
	}
	glEnd();
	glFlush();

}

void rotation_bug() {
	//int angle = 45;
	int rad = (angle * 3.14) / 180;
	int tm[3][3] = { {cos(rad),-sin(rad),0},{sin(rad), cos(rad), 0},{0, 0, 1} };
	
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(200, 200);
	glVertex2f(202, 204);
	glVertex2f(204, 200);
	glEnd();

	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	int x_coord[3] = { 220,222,224 };
	int y_coord[3] = { 370,372,373 };


	for (int i = 0; i < 3; i++) {
		int coord[3][1] = { {x_coord[i]},{y_coord[i]},{1} };
		int output[3][1];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 1; j++) {
				output[i][j] = 0;
				for (int k = 0; k < 3; k++) {
					output[i][j] += tm[i][k] * coord[k][j];
				}
			}
		}
		glVertex2f(output[0][0], output[1][0]);
	}
	glEnd();
	glFlush();

}

void scale_bug() {
	int tm[3][3] = { {sx,0,0},{0, sy, 0},{0, 0, 1} };
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(200, 200);
	glVertex2f(202, 204);
	glVertex2f(204, 200);
	glEnd();

	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	int x_coord[3] = { 200,202,204 };
	int y_coord[3] = { 200,204,200 };

	for (int i = 0; i < 3; i++) {
		int coord[3][1] = { {x_coord[i]},{y_coord[i]},{1} };
		int output[3][1];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 1; j++) {
				output[i][j] = 0;
				for (int k = 0; k < 3; k++) {
					output[i][j] += tm[i][k] * coord[k][j];
				}
			}
		}
		glVertex2f(output[0][0], output[1][0]);
	}
	glEnd();
	glFlush();
}

void bug() {
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(200,370);
	glVertex2f(202, 374);
	glVertex2f(204, 370);
	glEnd();
}

void fan() {
	glBegin(GL_QUADS);
	glColor3f(0.6f, 0.4f, 0.7f);
	glVertex2f(650,400);
	glVertex2f(650, 410);
	glVertex2f(750, 410);
	glVertex2f(750, 400);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.6f, 0.4f, 0.7f);
	glVertex2f(695, 355);
	glVertex2f(695, 455);
	glVertex2f(705, 455);
	glVertex2f(705, 355);
	glEnd();
}

void EightWaySymmetricPlot(int xc, int yc, int x, int y)
{   
	glBegin(GL_POINTS);
	glColor3f(0.9f,0.9f,0.0f);
	glVertex2f(x + xc, y + yc);
	glVertex2f(x + xc, -y + yc);
	glVertex2f(-x + xc, -y + yc);
	glVertex2f(-x + xc, y + yc);
	glVertex2f(y + xc, x + yc);
	glVertex2f(y + xc, -x + yc);
	glVertex2f(-y + xc, -x + yc);
	glVertex2f(-y + xc, x + yc);
	glEnd();
}

void BresenhamCircle(int xc, int yc, int r)
{
	int x = 0, y = r, d = 3 - (2 * r);
	EightWaySymmetricPlot(xc, yc, x, y);

	while (x <= y)
	{
		if (d <= 0){
			d = d + (4 * x) + 6;
		}
		else{
			d = d + (4 * x) - (4 * y) + 10;
			y = y - 1;
		}
		x = x + 1;
		EightWaySymmetricPlot(xc, yc, x, y);
	}
}

void door_opened() {
	glBegin(GL_QUADS);
	glColor3f(0.48f, 0.19f, 0.0f);
	glVertex2f(600.0f, 100.0f);
	glVertex2f(600.0f, 350.0f);
	glVertex2f(650.0f, 300.0f);
	glVertex2f(650.0f, 150.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.2f, 0.9f);
	glVertex2f(600.0f, 350.0f);
	glVertex2f(650.0f, 300.0f);
	glVertex2f(650.0f, 350.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.2f, 0.9f);
	glVertex2f(600.0f, 100.0f);
	glVertex2f(650.0f, 100.0f);
	glVertex2f(650.0f, 150.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.2f, 0.9f);
	glVertex2f(650.0f, 100.0f);
	glVertex2f(650.0f, 350.0f);
	glVertex2f(730.0f, 350.0f);
	glVertex2f(730.0f, 100.0f);
	glEnd();
}

void door_dark_opened() {
	glBegin(GL_QUADS);
	glColor3f(0.28f, 0.09f, 0.0f);
	glVertex2f(600.0f, 100.0f);
	glVertex2f(600.0f, 350.0f);
	glVertex2f(650.0f, 300.0f);
	glVertex2f(650.0f, 150.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.1f, 0.7f);
	glVertex2f(600.0f, 350.0f);
	glVertex2f(650.0f, 300.0f);
	glVertex2f(650.0f, 350.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.1f, 0.7f);
	glVertex2f(600.0f, 100.0f);
	glVertex2f(650.0f, 100.0f);
	glVertex2f(650.0f, 150.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.1f, 0.7f);
	glVertex2f(650.0f, 100.0f);
	glVertex2f(650.0f, 350.0f);
	glVertex2f(730.0f, 350.0f);
	glVertex2f(730.0f, 100.0f);
	glEnd();
}

void door() {
	glBegin(GL_QUADS);
	glColor3f(0.48f, 0.19f, 0.0f);
	glVertex2f(600.0f, 100.0f);
	glVertex2f(600.0f, 350.0f);
	glVertex2f(730.0f, 350.0f);
	glVertex2f(730.0f, 100.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.2f, 0.3f, 0.4f);
	glVertex2f(600.0f, 100.0f);
	glVertex2f(600.0f, 350.0f);

	glVertex2f(730.0f, 350.0f);
	glVertex2f(730.0f, 100.0f);

	glVertex2f(600.0f, 100.0f);
	glVertex2f(730.0f, 100.0f);

	glVertex2f(600.0f, 350.0f);
	glVertex2f(730.0f, 350.0f);
	glEnd();
}

void door_dark() {
	glBegin(GL_QUADS);
	glColor3f(0.28f, 0.02f, 0.0f);
	glVertex2f(600.0f, 100.0f);
	glVertex2f(600.0f, 350.0f);
	glVertex2f(730.0f, 350.0f);
	glVertex2f(730.0f, 100.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.2f, 0.3f, 0.4f);
	glVertex2f(600.0f, 100.0f);
	glVertex2f(600.0f, 350.0f);

	glVertex2f(730.0f, 350.0f);
	glVertex2f(730.0f, 100.0f);

	glVertex2f(600.0f, 100.0f);
	glVertex2f(730.0f, 100.0f);

	glVertex2f(600.0f, 350.0f);
	glVertex2f(730.0f, 350.0f);
	glEnd();
}

void window() {
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.6f, 0.9f);
	glVertex2f(200.0f, 250.0f);
	glVertex2f(200.0f, 350.0f);
	glVertex2f(400.0f, 350.0f);
	glVertex2f(400.0f, 250.0f);
	glEnd();

	//glBegin(GL_LINES);
	glColor3f(0.38f, 0.09f, 0.5f);
	/*
	glVertex2f(200.0f, 300.0f);
	glVertex2f(400.0f, 300.0f);

	glVertex2f(300.0f, 350.0f);
	glVertex2f(300.0f, 250.0f);
	*/
	line(200.0, 300.0, 400.0, 300.0);
	line(300.0, 350.0, 300.0, 250.0);
	//glEnd();

	glBegin(GL_LINES);
	glColor3f(0.38f, 0.09f, 0.5f);
	glVertex2f(200.0f, 250.0f);
	glVertex2f(400.0f, 250.0f);

	glVertex2f(400.0f, 350.0f);
	glVertex2f(200.0f, 350.0f);

	glVertex2f(200.0f, 250.0f);
	glVertex2f(200.0f, 350.0f);

	glVertex2f(400.0f, 250.0f);
	glVertex2f(400.0f, 350.0f);
	glEnd();
}

void window_dark() {
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.4f, 0.7f);
	glVertex2f(200.0f, 250.0f);
	glVertex2f(200.0f, 350.0f);
	glVertex2f(400.0f, 350.0f);
	glVertex2f(400.0f, 250.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.28f, 0.05f, 0.5f);
	glVertex2f(200.0f, 300.0f);
	glVertex2f(400.0f, 300.0f);

	glVertex2f(300.0f, 350.0f);
	glVertex2f(300.0f, 250.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.28f, 0.05f, 0.5f);
	glVertex2f(200.0f, 250.0f);
	glVertex2f(400.0f, 250.0f);

	glVertex2f(400.0f, 350.0f);
	glVertex2f(200.0f, 350.0f);

	glVertex2f(200.0f, 250.0f);
	glVertex2f(200.0f, 350.0f);

	glVertex2f(400.0f, 250.0f);
	glVertex2f(400.0f, 350.0f);
	glEnd();
}

void tube_light() {
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(300.0f, 400.0f);
	glVertex2f(300.0f, 410.0f);
	glVertex2f(530.0f, 410.0f);
	glVertex2f(530.0f, 400.0f);
	glEnd();
}

void tube_light_dark() {
	glBegin(GL_QUADS);
	glColor3f(0.7f, 0.7f, 0.7f);
	glVertex2f(300.0f, 400.0f);
	glVertex2f(300.0f, 410.0f);
	glVertex2f(530.0f, 410.0f);
	glVertex2f(530.0f, 400.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(300.0f, 400.0f);
	glVertex2f(300.0f, 410.0f);

	glVertex2f(530.0f, 410.0f);
	glVertex2f(530.0f, 400.0f);
	glEnd();

}

void gun() {
	glBegin(GL_QUADS);
	glColor3f(0.72f, 0.72f, 0.73f);
	glVertex2f(50.0f, 250.0f);
	glVertex2f(160.0f, 250.0f);
	glVertex2f(160.0f, 230.0f);
	glVertex2f(50.0f, 230.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.72f, 0.72f, 0.73f);
	glVertex2f(80.0f, 230.0f);
	glVertex2f(70.0f, 200.0f);
	glVertex2f(40.0f, 200.0f);
	glVertex2f(50.0f, 250.0f);
	glEnd();
}

void gun_move() {
	glBegin(GL_QUADS);
	glColor3f(0.72f, 0.72f, 0.73f);
	glVertex2f(50.0f, gun_y_pos +10.0);
	glVertex2f(160.0f, gun_y_pos + 10.0);
	glVertex2f(160.0f, gun_y_pos - 10.0);
	glVertex2f(50.0f, gun_y_pos - 10.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.72f, 0.72f, 0.73f);
	glVertex2f(80.0f, gun_y_pos - 10.0);
	glVertex2f(70.0f, gun_y_pos - 40.0);
	glVertex2f(40.0f, gun_y_pos - 40.0);
	glVertex2f(50.0f, gun_y_pos + 10.0);
	glEnd();
}

void gun_rotate() {
	glPushMatrix();
	float deg = 3.0;
	float rad = deg * 3.14 / 180.0;
	glRotatef(rad,0,0,1);
	glPopMatrix();
}

void bullet() {
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(180.0f, 242.0f);
	glVertex2f(190.0f, 242.0f);
	glVertex2f(190.0f, 238.0f);
	glVertex2f(180.0f, 238.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(190.0f, 242.0f);
	glVertex2f(195.0f, 240.0f);
	glVertex2f(190.0f, 238.0f);
	glEnd();

}

void bullet_move() {
	
	glBegin(GL_QUADS);
	glColor3f(0.72f, 0.72f, 0.73f);
	glVertex2f(x_position, 242.0f);
	glVertex2f(x_position+10.0, 242.0f);
	glVertex2f(x_position + 10.0, 238.0f);
	glVertex2f(x_position, 238.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.72f, 0.72f, 0.73f);
	glVertex2f(x_position + 10.0, 242.0f);
	glVertex2f(x_position + 15.0, 240.0f);
	glVertex2f(x_position + 10.0, 238.0f);
	glEnd();
}

void bullet_move_dynamic() {
	
	if (shot == true) {
		float y_pos = gun_y_pos;

		//it will be 240
		glBegin(GL_QUADS);
		glColor3f(0.72f, 0.72f, 0.73f);
		glVertex2f(x_position, y_pos + 2.0);
		glVertex2f(x_position + 10.0, y_pos + 2.0);
		glVertex2f(x_position + 10.0, y_pos - 2.0);
		glVertex2f(x_position, y_pos - 2.0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.72f, 0.72f, 0.73f);
		glVertex2f(x_position + 10.0, y_pos + 2.0);
		glVertex2f(x_position + 15.0, y_pos);
		glVertex2f(x_position + 10.0, y_pos - 2.0);
		varr = y_pos;
		shot = false;
		glEnd();
	}
	else {
		glBegin(GL_QUADS);
		glColor3f(0.72f, 0.72f, 0.73f);
		glVertex2f(x_position, varr + 2.0);
		glVertex2f(x_position + 10.0, varr+ 2.0);
		glVertex2f(x_position + 10.0, varr - 2.0);
		glVertex2f(x_position, varr - 2.0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.72f, 0.72f, 0.73f);
		glVertex2f(x_position + 10.0, varr + 2.0);
		glVertex2f(x_position + 15.0, varr);
		glVertex2f(x_position + 10.0, varr - 2.0);
		glEnd();
	}
}

void bullet_move_dynamic_dark() {

	if (shot == true) {
		float y_pos = gun_y_pos;

		//it will be 240
		glBegin(GL_QUADS);
		glColor3f(0.32f, 0.32f, 0.33f);
		glVertex2f(x_position, y_pos + 2.0);
		glVertex2f(x_position + 10.0, y_pos + 2.0);
		glVertex2f(x_position + 10.0, y_pos - 2.0);
		glVertex2f(x_position, y_pos - 2.0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.32f, 0.32f, 0.33f);
		glVertex2f(x_position + 10.0, y_pos + 2.0);
		glVertex2f(x_position + 15.0, y_pos);
		glVertex2f(x_position + 10.0, y_pos - 2.0);
		varr = y_pos;
		shot = false;
		glEnd();
	}
	else {
		glBegin(GL_QUADS);
		glColor3f(0.32f, 0.32f, 0.33f);
		glVertex2f(x_position, varr + 2.0);
		glVertex2f(x_position + 10.0, varr + 2.0);
		glVertex2f(x_position + 10.0, varr - 2.0);
		glVertex2f(x_position, varr - 2.0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.32f, 0.32f, 0.33f);
		glVertex2f(x_position + 10.0, varr + 2.0);
		glVertex2f(x_position + 15.0, varr);
		glVertex2f(x_position + 10.0, varr - 2.0);
		glEnd();
	}
}

void animate_bullet() {
	for (int i = 0; i < 10; i++) {
		Sleep(1000);
		bullet_move();
	}
}

void wall() {
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex2f(870, 600.0f);
	glVertex2f(1000, 900.0f);
	glVertex2f(1000, 0.0f);
	glVertex2f(870, 100.0f);
	glEnd();
}

void sw() {
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(895, 250.0f);
	glVertex2f(905, 250.0f);
	glVertex2f(905, 230.0f);
	glVertex2f(895, 230.0f);
	glEnd();
}

void floor() {
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.2f, 0.5f);
	glVertex2f(0.0f, 100.0f);
	glVertex2f(870.0f, 100.0f);
	glVertex2f(1000.0f, 0.0f);

	glVertex2f(0.0f, 0.0f);
	glEnd();
}

void wall_dark() {
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.0f, 0.4f);
	glVertex2f(870, 600.0f);
	glVertex2f(1000, 900.0f);
	glVertex2f(1000, 0.0f);
	glVertex2f(870, 100.0f);
	glEnd();
}

void sw_dark() {
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.0f, 0.0f);
	glVertex2f(895, 250.0f);
	glVertex2f(905, 250.0f);
	glVertex2f(905, 230.0f);
	glVertex2f(895, 230.0f);
	glEnd();
}

void floor_dark() {
	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.1f, 0.25f);
	glVertex2f(0.0f, 100.0f);
	glVertex2f(870.0f, 100.0f);
	glVertex2f(1000.0f, 0.0f);

	glVertex2f(0.0f, 0.0f);
	glEnd();
}

void bullet_move_dark() {
	
	glBegin(GL_QUADS);
	glColor3f(0.32f, 0.32f, 0.33f);
	glVertex2f(x_position, 242.0f);
	glVertex2f(x_position + 10.0, 242.0f);
	glVertex2f(x_position + 10.0, 238.0f);
	glVertex2f(x_position, 238.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.32f, 0.32f, 0.33f);
	glVertex2f(x_position + 10.0, 242.0f);
	glVertex2f(x_position + 15.0, 240.0f);
	glVertex2f(x_position + 10.0, 238.0f);
	glEnd();
}

void gun_dark() {
	glBegin(GL_QUADS);
	glColor3f(0.32f, 0.32f, 0.33f);
	glVertex2f(50.0f, 250.0f);
	glVertex2f(160.0f, 250.0f);
	glVertex2f(160.0f, 230.0f);
	glVertex2f(50.0f, 230.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.32f, 0.32f, 0.33f);
	glVertex2f(80.0f, 230.0f);
	glVertex2f(70.0f, 200.0f);
	glVertex2f(40.0f, 200.0f);
	glVertex2f(50.0f, 250.0f);
	glEnd();
}

void gun_move_dark() {
	glBegin(GL_QUADS);
	glColor3f(0.32f, 0.32f, 0.33f);
	glVertex2f(50.0f, gun_y_pos + 10.0);
	glVertex2f(160.0f, gun_y_pos + 10.0);
	glVertex2f(160.0f, gun_y_pos - 10.0);
	glVertex2f(50.0f, gun_y_pos - 10.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.32f, 0.32f, 0.33f);
	glVertex2f(80.0f, gun_y_pos - 10.0);
	glVertex2f(70.0f, gun_y_pos - 40.0);
	glVertex2f(40.0f, gun_y_pos - 40.0);
	glVertex2f(50.0f, gun_y_pos + 10.0);
	glEnd();
}

void bullet_drop() {
	glBegin(GL_QUADS);
	glColor3f(0.32f, 0.32f, 0.33f);
	glVertex2f(900.0f, 242.0f);
	glVertex2f(900.0f + 10.0, 242.0f);
	glVertex2f(900.0f + 10.0, 238.0f);
	glVertex2f(900.0f, 238.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.32f, 0.32f, 0.33f);
	glVertex2f(900.0f + 10.0, 242.0f);
	glVertex2f(900.0f + 15.0, 240.0f);
	glVertex2f(900.0f + 10.0, 238.0f);
	glEnd();
}





void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	
	if (light == true) {
		window();
		tube_light();
		if (door_op == false) {
			door();
			BresenhamCircle(710, 220, 4);
			midPointElipse(10, 15, 710, 220);
		}
		else {
			door_opened();
			BresenhamCircle(642, 210, 2);
			midPointElipse(7, 10, 642, 210);
		}
		gun_move();
		wall();
		sw();
		floor();
		bullet_move_dynamic();
	}
	else {
		window_dark();
		tube_light_dark();
		if (door_op == false) {
			door_dark();
			BresenhamCircle(710, 220, 4);
			midPointElipse(10, 15, 710, 220);
		}
		else {
			door_dark_opened();
			BresenhamCircle(642, 210, 2);
			midPointElipse(7, 10, 642, 210);
		}
		gun_move_dark();
		wall_dark();
		sw_dark();
		floor_dark();
		bullet_move_dynamic_dark();
	}
	if (fan_move == true) {
		glPushMatrix();
		glTranslatef(700.0f, 405.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(-700.0f, -405.0f, 0.0f);
		fan();
		glPopMatrix();
	}
	else {
		fan();
	}
	/*
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(200, 370);
	glVertex2f(202, 372);
	glVertex2f(204, 374);
	glEnd();
	*/
	//bug();
	translate_bug();
	//scale_bug();
	//rotation_bug();
	glutSwapBuffers();

}

void mouse(int key,int state,int x,int y) {
	switch (key)
	{
	case GLUT_LEFT_BUTTON:

		if(state == GLUT_DOWN && x>=882 && x<=1073 && y>=252 && y<=670) {
			if (door_op == false) {
				door_op = true;
			}
			else {
				door_op = false;
			}
		}
		else if (state == GLUT_DOWN && x >= 969 && x <= 1090 && y >= 109 && y <= 180) {
			if (fan_move == false) {
				fan_move= true;
			}
			else {
				fan_move = false;
			}
		}
		/*
		else if (state == GLUT_DOWN && x >= 1317 && x <= 1330 && y >= 421 && y <= 452) {
			if (light == false) {
				light = true;
			}
			else {
				light = false;
			}
		}
		*/
		else if (state == GLUT_DOWN) {
			printf("The values of x and y are %d   %d",x,y);
			fire = true;
			//gun_rotate();
			shot = true;
		}

		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			fire = false;
		}
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("OpenGL Setup Test");
	glutInitWindowSize(640, 320);  
	glutInitWindowPosition(50, 50); 
	glutDisplayFunc(display); 
	glutTimerFunc(0, timer, 0);
	init();
	glutMouseFunc(mouse);
	glutMainLoop();       
	return 0;
}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
	angle += 10;
	tx += 0.2;
	ty += 0.1;
	sx += 10;
	sy += 10;
	if (x_position < 902.0 && fire==true) {
		x_position += 10;
	}
	if (x_position == 900.0) {
		if (light == true && varr <=250 && varr >=230) {
			glClearColor(0.72, 0.72, 0.72, 0.0);
			light = false;
		}
		else if(light == false && varr <= 250 && varr >= 230) {
		    glClearColor(0.93, 0.93, 0.93, 0.0);
			light = true;
		}
		fire = false;
		x_position = 100.0;
	}

	if (gun_y_pos < 471.0 && up == true) {
		//up
		gun_y_pos += 3;
	}
	
	if (gun_y_pos > 470.0) {
		//down dir
		up = false;
	}
	
	if (gun_y_pos > 199.0 && up == false) {
		//up
		gun_y_pos -= 3;
	}
	if (gun_y_pos < 200.0) {
		//down dir
		up = true;
	}

}