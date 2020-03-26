#include <GL/glut.h>

typedef struct {

	float x;
	float y;

}Point2D_t;

typedef struct {

	float r;
	float g;
	float b;

}Color_t;

void setWarna(Color_t col) {

	glColor3f(col.r, col.g, col.b);

}

void gambarTitik(Point2D_t titik, Color_t warna, float ukuran) {

	setWarna(warna);
	glPointSize(ukuran);
	glBegin(GL_POINTS);
	glVertex2f(titik.x, titik.y);
	glEnd();

}

void gambarGaris(Point2D_t garis[], Color_t warna, float ukuran) {

	setWarna(warna);
	glLineWidth(ukuran);
	glBegin(GL_LINES);
			for (int i = 0; i < 2; i++)
				glVertex2f(garis[i].x, garis[i].y);
	glEnd();

}

void gambarPolyLine(Point2D_t poliLines[], int n, Color_t warna, float ukuran) {

	setWarna(warna);
	glLineWidth(ukuran);
	glBegin(GL_LINE_STRIP);
			for (int i = 0; i < n; i++)
				glVertex2f(poliLines[i].x, poliLines[i].y);
	glEnd();

}

void gambarPoligon(Point2D_t poliGon[], int n, Color_t warna, float ukuran) {

	setWarna(warna);
	glLineWidth(ukuran);
	glBegin(GL_LINE_LOOP);
			for (int i = 0; i < n; i++)
				glVertex2f(poliGon[i].x, poliGon[i].y);
	glEnd();

}

void gambarFillPoligon(Point2D_t fillPoli[], int n, Color_t warna, float ukuran) {

	setWarna(warna);
	glLineWidth(ukuran);
	glBegin(GL_POLYGON);
			for (int i = 0; i < n; i++)
				glVertex2f(fillPoli[i].x, fillPoli[i].y);
	glEnd();

}

void userdraw() {

	Color_t merah = { 1, 0, 0 };
	Color_t hijau = { 0, 1, 0 };
	Color_t biru  = { 0, 0, 1 };
	Color_t putih = { 1, 1, 1 };
	Color_t hitam = { 0, 0, 0 };

	Point2D_t kakiMejaKiri1[4] = {{220, 160}, {236, 152}, {236, 396}, {220, 400}};
    gambarFillPoligon(kakiMejaKiri1, 4, merah, 1);
    gambarPoligon(kakiMejaKiri1, 4, hitam, 3);

	Point2D_t kakiMejaKiri2[4] = { {236, 152}, {252, 160}, {252, 354}, {236, 360} };
	gambarFillPoligon(kakiMejaKiri2, 4, merah, 1);
	gambarPoligon(kakiMejaKiri2, 4, hitam, 3);

	Point2D_t sisiMejaKiriBawah[4] = { {236, 360}, {364, 312}, {364, 348}, {236, 396} };
	gambarFillPoligon(sisiMejaKiriBawah, 4, merah, 1);
	gambarPoligon(sisiMejaKiriBawah, 4, hitam, 3);

	Point2D_t kakiMejaKiriBelakang1[4] = { {364, 64}, {376, 60}, {376, 344}, {364, 348} };
	gambarFillPoligon(kakiMejaKiriBelakang1, 4, merah, 1);
	gambarPoligon(kakiMejaKiriBelakang1, 4, hitam, 3);

	Point2D_t kakiMejaKiriBelakang2[4] = { {376, 60}, {392, 64}, {392, 343}, {376, 342} };
	gambarFillPoligon(kakiMejaKiriBelakang2, 4, merah, 1);
	gambarPoligon(kakiMejaKiriBelakang2, 4, hitam, 3);

	Point2D_t alasMejaKiri[4] = { {204, 400}, {376, 340}, {376, 352}, {204, 412} };
	gambarFillPoligon(alasMejaKiri, 4, merah, 1);
	gambarPoligon(alasMejaKiri, 4, hitam, 3);

	Point2D_t alasMejaKanan[4] = { {376, 340}, {672, 380}, {672, 392}, {376, 352} };
	gambarFillPoligon(alasMejaKanan, 4, merah, 1);
	gambarPoligon(alasMejaKanan, 4, hitam, 3);

	Point2D_t sisiMejaTengahBawah[4] = { {392, 307}, {632, 340}, {632, 374}, {392, 342} };
	gambarFillPoligon(sisiMejaTengahBawah, 4, merah, 1);
	gambarPoligon(sisiMejaTengahBawah, 4, hitam, 3);

	Point2D_t kakiMejaKananBelakang1[4] = { {620, 130}, {632, 120}, {632, 340}, {620, 339} };
	gambarFillPoligon(kakiMejaKananBelakang1, 4, merah, 1);
	gambarPoligon(kakiMejaKananBelakang1, 4, hitam, 3);

	Point2D_t kakiMejaKananBelakang2[4] = { {632, 120}, {652, 127}, {652, 377}, {632, 374} };
	gambarFillPoligon(kakiMejaKananBelakang2, 4, merah, 1);
	gambarPoligon(kakiMejaKananBelakang2, 4, hitam, 3);

	Point2D_t alasMejaAtas[4] = { {376, 352}, {672, 392}, {476, 440}, {204, 412} };
	gambarFillPoligon(alasMejaAtas, 4, merah, 1);
	gambarPoligon(alasMejaAtas, 4, hitam, 3);

	Point2D_t kakiMejaKananDepan1[4] = { {476, 160}, {487, 162}, {487, 320}, {476, 318} };
	gambarFillPoligon(kakiMejaKananDepan1, 4, merah, 1);
	gambarPoligon(kakiMejaKananDepan1, 4, hitam, 3);

	Point2D_t kakiMejaKananDepan2[4] = { {467, 165}, {476, 160}, {476, 318}, {467, 317} };
	gambarFillPoligon(kakiMejaKananDepan2, 4, merah, 1);
	gambarPoligon(kakiMejaKananDepan2, 4, hitam, 3);

}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	userdraw();
	glutSwapBuffers();

}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 75);										//POSISI KANVAS
	glutInitWindowSize(900,600);											//UKURAN KANVAS
	glutCreateWindow("INI UTS M.RAFI DWI A - B34170012");					//NAMA KANVAS
	glClearColor(1.0, 1.0, 1.0, 0.0);										//WARNA BG KANVAS
	gluOrtho2D(0., 900., 0., 600.);											//KORDINAT KANVAS
	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
