// Kompilasi:
// gcc drawing.c -o drawing -lglut -lGL -lGLU

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

#define MAXL 200


typedef struct {
    int x;
    int y;
} Point;

void DrawPoint(Point P){

	glBegin(GL_LINES);

	glColor3f(1.0, 0.0, 0.0);

	glVertex2i(P.x+1, P.y+1);
	glVertex2i(P.x-1, P.y-1);

	glVertex2i(P.x-1, P.y+1);
	glVertex2i(P.x+1, P.y-1);

	glEnd();
}

void DrawLine(Point P1, Point P2, int Mode){

	if(Mode == 1){
		glColor3f(0.75, 0.75, 0.75);
	}
	else{
		glColor3f(0.0, 0.0, 0.0);	
	}
	
	glBegin(GL_LINES);

	glVertex2i(P1.x, P1.y);
	glVertex2i(P2.x, P2.y);

	glEnd();
}


void Display(){

	Point P1, P2;

	glClear(GL_COLOR_BUFFER_BIT);

	// Sumbu X
	P1.x = -10; P1.y = 0;
	P2.x = 260; P2.y = 0;
	DrawLine(P1, P2, 1);

	for(int i=0; i<=250; i++){
		P1.x = i*10; P1.y = -2;
		P2.x = i*10; P2.y = 2;
		DrawLine(P1, P2, 1);
	}

	// Sumbu Y
	P1.x = 0; P1.y = -10;
	P2.x = 0; P2.y = 260;
	DrawLine(P1, P2, 1);

	for(int i=0; i<=250; i++){
		P1.x = -2; P1.y = i*10;
		P2.x = 2; P2.y = i*10;
		DrawLine(P1, P2, 1);
	}


	P1.x = 10; P1.y = 14;
	P2.x = 70; P2.y = 56;
	DrawPoint(P1);
	DrawPoint(P2);

	P1.x = 32; P1.y = 90;
	P2.x = 40; P2.y = 40;
	DrawPoint(P1);
	DrawPoint(P2);

	P1.x = 89; P1.y = 12;
	DrawPoint(P1);

	P1.x = 40; P1.y = 40;
	P2.x = 70; P2.y = 56;
	DrawLine(P1, P2, 0);

	glFlush();
}

void initialize() {
	glClearColor(1.0, 1.0, 1.0, 0.0);  
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-10.0, 260.0, -10.0, 260.0);
}

void Draw(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize (800, 800);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("CONVEX HULL VISUALIZATION");

	initialize(0.0f, 0.0f, 0.0f);
	glutDisplayFunc(Display);

	glutMainLoop();
}

// PROGRAM UTAMA

int main(int argc,char *argv[]){

	Draw(argc, argv);

	return 0;
}