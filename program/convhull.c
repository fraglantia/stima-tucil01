// PROGRAM C UNTUK MENENTUKAN CONVEX HULL DENGAN ALGORITMA BRUTE-FORCE

// IMPLEMENTASI ALGORITMA (BRUTE FORCE)
// 1. Untuk setiap 2 titik pada himpunan titik-titik buat sebuah garis.
// 2. Garis yang terbentuk memiliki persamaan (x2-x1)y - (y2-y1)x = (x2-y1)-(x1-y2)
//    Terdapat 3 kemungkinan dari titik-titik lainnya terhadap garis:
// 		a. pada sisi positif >
// 		b. pada sisi negatif <
// 		c. tepat pada.
// 3. Jika semua titik (kecuali 2 titik yang dipilih) ada pada sisi yang sama, maka 2 titik yang dipilih adalah bagian dari poligon Convex Hull.

// SPESIFIKASI PROGRAM
// Program menerima input N yaitu jumlah titik.
// N titik akan dibangkitkan secara acak.
// Program akan mengoutput titik-titik yang membentuk Convex Hull.
// Convex Hull divisualisasikan.

// Kompilasi:
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

// BAGIAN TIPE DATA POINT

void InitPoints(){

	for(int i=0; i<MAXL; i++){
		if(i<N){
			Ps[i].x = rand()%200;
			Ps[i].y = rand()%200;
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

// CONVEX HULL

int Side(Point P1, Point P2, Point P3){
	// Untuk menentukan posisi P3 terhadap garis P1 P2.
	// 1  : +
	// -1 : -
	// 0  : tepat pada

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

// KEPERLUAN VISUALISASI

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

// BAGIAN VISUALISASI

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
		glColor3f(0.25, 0.25, 0.25);
	}
	else{
		glColor3f(1.0, 1.0, 1.0);	
	}
	
	glBegin(GL_LINES);

	glVertex2i(P1.x, P1.y);
	glVertex2i(P2.x, P2.y);

	glEnd();
}

void Display(){

	Point P1, P2;

	glClear(GL_COLOR_BUFFER_BIT);

	for(int i=0; i<N; i++){
		DrawPoint(Ps[i]);
	}

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

	for(int i=0; i<ResCount-1; i++){
		DrawLine(Rs[i], Rs[i+1], 0);	
	}
	DrawLine(Rs[ResCount-1], Rs[0], 0);

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

// PROGRAM UTAMA

int main(int argc,char *argv[]){
	clock_t t;
	double time_taken;

	srand(time(NULL));
	setbuf(stdout, NULL);

	printf("Jumlah titik-titik: ");
	scanf("%d", &N);
	printf("\n");

	InitPoints();

	printf("Titik-titik yang dihasilkan:\n");
	for(int i=0; i<N-1; i++){
		PrintPoint(Ps[i]); printf(", ");
	}
	PrintPoint(Ps[N-1]); printf("\n\n");

	t = clock();

	ConvexHull();

	t = clock() - t;
	time_taken = ((double) t)/CLOCKS_PER_SEC;
	printf("Waktu yang diperlukan: %f ms\n\n", time_taken*1000);
	
	SortPoints();

	printf("Titik-titik yang membentuk Convex Hull:\n");
	for(int i=0; i<ResCount; i++){
		PrintPoint(Rs[i]); printf(", ");
	}
	PrintPoint(Rs[0]); printf("\n\n");

	Draw(argc, argv);

	return 0;
}