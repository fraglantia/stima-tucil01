// C PROGRAM TO FIND (AND DISPLAY) CONVEX HULL WITH BRUTE FORCE ALGORITHM

// CONVEX HULL IMPLEMENTATION
// FOR EVERY 2 POINTS DRAW A LINE
// THE LINE DRAWN WILL DIVIDE THE REMAINING POINTS TO 2 POSSIBLE AREAS, NAMELY + AND - (0)
// IF ALL THE POINTS LIE IN THE SAME AREA, THEN THE 2 POINTS WILL BE THE POINTS THAT MAKE THE CONVEX POLYGON.

// PROGRAM SPECIFICATION
// TAKE AN INPUT OF N (NUMBER OF POINT GENERATED)
// RANDOMLY GENERATE N POINTS
// GIVE THE CONVEX HULL BY LISTING THE POINTS MAKING THE CONVEX POLYGON
// (DISPLAY THE CONVEX HULL)

// gcc convhull.c -o convhull -lglut -lGL -lGLU

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

#define MAXL 200


typedef struct {
    int x;
    int y;
} Point;

Point Ps[MAXL];
Point Rs[MAXL];
int Result[MAXL];
int N, ResCount;

void InitPoints(){

	for(int i=0; i<MAXL; i++){
		if(i<N){
			Ps[i].x = rand()%250;
			Ps[i].y = rand()%250;
		}
		else{
			Ps[i].x = -1;
			Ps[i].y = -1;
		}
	}

}

void PrintPoint(Point P){
	printf("(%d, %d)", P.x, P.y);
}

void InputPoint(Point* P){
	// DEBUG PURPOSES
	printf("x: ");
	scanf("%d", &((*P).x));
	printf("y: ");
	scanf("%d", &((*P).y));
	
}

int Side(Point P1, Point P2, Point P3){
	// DETERMINE P3's POSITION IN THE LINE MADE BY P1 P2:
	// 1  : +
	// -1 : -
	// 0  : right on

	// P1 P2:
	// (x2-x1)y - (y2-y1)x = x2y1-x1y2
	//   a           b           c

	int a, b, c, leftside;
	a = P2.x - P1.x;
	b = P2.y - P1.y;
	c = P2.x*P1.y - P2.y*P1.x;
	leftside = a*P3.y - b*P3.x;

	if(leftside > c){
		return 1;
	}
	else if(leftside < c){
		return -1;
	}
	else{
		return 0;
	}
}

void Union(int X){
	// Rs.Union(X)

	int found, i;

	found = 0;
	i = 0;

	while(!found && i < ResCount){
		if(Result[i] == X){
			found = 1;
		}
		else{
			i++;
		}
	}

	if(!found){
		ResCount = ResCount + 1;
		Result[ResCount-1] = X;
	}
}


int CheckLine(int idx1, int idx2, Point *Pts, int PtsCount){
	//  1: SUCCESS
	//  0: FAIL

	int Fail, i;
	int First, Current;

	Fail = 0;
	i = 0;

	First = 0;

	while(i<PtsCount && !Fail){
		if(i!=idx1 && i!=idx2){

			Current = Side(Pts[idx1], Pts[idx2], Pts[i]);

			if(Current !=0){
				if(First == 0){
					First = Current;
				}
				else{
					if(Current != First){
						Fail = 1;
					}
				}
			}
		}
		i++;
	}

	if(Fail){
		return 0;
	}
	else{
		return 1;
	}
}

void ConvexHull(){
	int i, j;

	ResCount = 0;

	for(i=0; i<N; i++){

		for(j=i+1; j<N; j++){

			if(CheckLine(i, j, Ps, N)){
				Union(i);
				Union(j);
			}

		}	
	}
}

void SortPoints(){
	int i, j;
	Point tmp;

	for(i=0; i<ResCount; i++){
		Rs[i] = Ps[Result[i]];
	}

	for(i=0; i<ResCount; i++){
		j = i+1;

		while(j<ResCount){

			if(CheckLine(i, j, Rs, ResCount)){
				break;
			}
			j++;
		}

		if(j<ResCount && i<ResCount){
			tmp = Rs[i+1];
			Rs[i+1] = Rs[j];
			Rs[j] = tmp;
		}
	}
}


void DrawPoint(Point P, int m){

	
	if(m == 1){
		glColor3f(1.0, 0.0, 0.0);
	}
	else{
		glColor3f(1.0, 1.0, 1.0);
	}

	glBegin(GL_LINES);

	glVertex2i(P.x+1, P.y+1);
	glVertex2i(P.x-1, P.y-1);

	glVertex2i(P.x-1, P.y+1);
	glVertex2i(P.x+1, P.y-1);

	glEnd();
}

void DrawLine(Point P1, Point P2){

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);

	glVertex2i(P1.x, P1.y);
	glVertex2i(P2.x, P2.y);

	glEnd();
}

void Display(){
	glClear(GL_COLOR_BUFFER_BIT);

   // DRAW POINTS

   Point P;
   P.x = 0;
   P.y = 100;

   for(int i=0; i<N; i++){
		DrawPoint(Ps[i], 1);
	}

	DrawPoint(Rs[0], 0);

	for(int i=0; i<ResCount-1; i++){
		// DrawLine(Ps[Result[i]], Ps[Result[i+1]]);
		DrawLine(Rs[i], Rs[i+1]);	
	}
	// DrawLine(Ps[Result[ResCount]], Ps[Result[0]]);
	DrawLine(Rs[ResCount-1], Rs[0]);

   glFlush();
}

void initialize() {
	glClearColor(0.0, 0.0, 0.0, 0.0);  
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

int main(int argc,char *argv[]){
	srand(time(NULL));
	setbuf(stdout, NULL);

	printf("Number of points: ");
	scanf("%d", &N);

	InitPoints();

	for(int i=0; i<N; i++){
		PrintPoint(Ps[i]); printf(" ");
	}
	printf("\n\n");

	ConvexHull();

	for(int i=0; i<ResCount; i++){
		PrintPoint(Ps[Result[i]]); printf(" ");
	}
	printf("\n");

	SortPoints();

	for(int i=0; i<ResCount; i++){
		PrintPoint(Rs[i]); printf(" ");
	}
	printf("\n");

	Draw(argc, argv);

	return 0;
}