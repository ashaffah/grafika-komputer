/****************
   OBJEK 2 DIMENSI
******************/

#include <GL/glut.h>
#include <math.h>
#include <string.h>

/*---------- stuktur titik ---------*/
typedef struct {
	float x;
	float y;
} Point2D_t;

/*------ struktur warna ------------*/
typedef struct {
	float r;
	float g;
	float b;
} Color_t;

/*---------- set warna --------------*/
void setWarna(Color_t col)
{
	glColor3f(col.r, col.g, col.b);
}

/*------------ menggambar titik --------*/
void gambarTitik(Point2D_t titik, Color_t warna, float ukuran)
{
	setWarna(warna);
	glPointSize(ukuran);
	glBegin(GL_POINTS);
	glVertex2f(titik.x, titik.y);
	glEnd();
}

/*------------- menggambar garis -------------*/
void gambarGaris(Point2D_t garis[], Color_t warna, float ukuran)
{
	setWarna(warna);
	glLineWidth(ukuran);
	glBegin(GL_LINES);
	/*glVertex2f(garis[0].x,garis[0].y);
	glVertex2f(garis[1].x,garis[1].y);*/

	for (int i = 0; i < 2; i++)
		glVertex2f(garis[i].x, garis[i].y);
	glEnd();
}

/*------------- menggambar polyline -------------*/
void gambarPolyline(Point2D_t polyline[], int n, Color_t warna, float ukuran)
{
	setWarna(warna);
	glLineWidth(ukuran);
	glBegin(GL_LINE_STRIP);

	/*glVertex2f(polyline[0].x,garis[0].y);
	glVertex2f(garis[1].x,garis[1].y);*/

	for (int i = 0; i < n; i++)
		glVertex2f(polyline[i].x, polyline[i].y);
	glEnd();
}

/*------------- menggambar polygon -------------*/
void gambarPolygon(Point2D_t polygon[], int n, Color_t warna, float ukuran)
{
	setWarna(warna);
	glLineWidth(ukuran);
	glBegin(GL_LINE_LOOP);
	/*glVertex2f(polyline[0].x,garis[0].y);
	glVertex2f(garis[1].x,garis[1].y);*/

	for (int i = 0; i < n; i++)
		glVertex2f(polygon[i].x, polygon[i].y);
	glEnd();
}

/*------------- menggambar fillpolygon -------------*/
void gambarfillPolygon(Point2D_t fillpolygon[], int n, Color_t warna, float ukuran)
{
	setWarna(warna);
	glLineWidth(ukuran);
	glBegin(GL_POLYGON);
	/*glVertex2f(polyline[0].x,garis[0].y);
	glVertex2f(garis[1].x,garis[1].y);*/

	for (int i = 0; i < n; i++)
		glVertex2f(fillpolygon[i].x, fillpolygon[i].y);
	glEnd();
}

/*----- FUNGSI MENGGAMBAR GRADATE POLYGON -----*/
void gradatePolygon(Point2D_t pnt[], int n, Color_t warna1, Color_t warna2, int b)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++) {
		if (i < b) setWarna(warna1);
		else setWarna(warna2);
		glVertex2f(pnt[i].x, pnt[i].y);
	}
	glEnd();
}
//------------------- gradate Laut ----------------//
void gradatePolygon2(Point2D_t pnt[], int n, Color_t warna1, Color_t warna2, int b)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++) {
		if (i < b) setWarna(warna1);
		else setWarna(warna2);
		glVertex2f(pnt[i].x, pnt[i].y);
	}
	glEnd();
}

/*----- FUNGSI MENGGAMBAR GRADATE CIRCLE -----*/
void gradateCircle(Point2D_t pnt[], int n, Color_t warna1, Color_t warna2, int b)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++) {
		if (i < b) setWarna(warna1);
		else setWarna(warna2);
		glVertex2f(pnt[i].x, pnt[i].y);
	}
	glEnd();
}

/*--- FUNGSI MENGGAMBAR LINGKARAN ---*/
void drawCircle(Point2D_t pusat, float jari2, int sudut, float size, Point2D_t pntCircle[])
{
	int sdt, i;
	sdt = 0;
	for (i = 0; i <= fabsf(sudut); i++)
	{
		float srad = sdt * 3.14 / 180;
		pntCircle[i].x = (float)((jari2 * cos(srad)) + pusat.x);
		pntCircle[i].y = (float)((jari2 * sin(srad)) + pusat.y);
		if (sudut > 0)sdt++;
		else sdt--;
	}
}

/*---FUNGSI MENGGAMBAR ELLIPSE ---*/
void drawEllipse(Point2D_t pusat, float jariH, float jariV, int sudut, float size, Point2D_t ellipse[])
{
	int sdt, i;
	//Point2D_t titik[365];
	sdt = 0;
	for (i = 0; i < fabsf(sudut); i++)
	{
		float srad = sdt * 3.14 / 180;
		ellipse[i].x = (float)((jariH * cos(srad)) + pusat.x);
		ellipse[i].y = (float)((jariV * sin(srad)) + pusat.y);
		if (sudut > 0) sdt++;
		else sdt--;
		//fillPolygon(titik, fabs(sudut), warna, size);
	}
}

/*------------------- menggambar polar ------------*/
void gambarPolar(Point2D_t pusat, float jari2, float daun,
	int sudut, float size, Point2D_t pntPolar[])
{
	int sdt, i;
	float r;
	sdt = 0;
	for (i = 0; i <= fabsf(sudut); i++)
	{
		float srad = sdt * 3.14 / 180;
		r = sin(daun * srad);
		pntPolar[i].x = (float)((r * cos(srad) * jari2) + pusat.x);
		pntPolar[i].y = (float)((r * sin(srad) * jari2) + pusat.y);
		if (sudut > 0) sdt++;
		else sdt--;
	}
}

/*============== TRANSFORMASI 2D ===============*/
//------------------- Translasi Awan -----------------//
/*----------------------------------------------------------------
Fungsi Translasi ini bisa digunakan untuk Polyline, Polygon,
Circle, Ellipse, dan Polar.
------------------------------------------------------------------
t_objek[] - objek hasil translasi
  objek[] - objek yang akan ditranslasi
		n - banyaknya titik yang akan ditranslasi
	   dx - jarak translasi searah sumbu x (- kekiri, + ke kanan)
	   dy - jarak translasi searah sumbu y (- ke bawah, + ke atas )
	 tick - kecepatan animasi (tanpa animasi nilainya 0.)
-------------------------------------------------------------------*/

void Translasi(Point2D_t t_objek[], Point2D_t objek[], int n, float dx,
	float dy, float tick)

{
	static float transX = 0., transY = 0.;
	float ddx, ddy, batasX, batasY, gerakX, gerakY;
	int aba, kika;

	for (int i = 0; i < n; i++)
	{
		t_objek[i].x = objek[i].x + transX;
		t_objek[i].y = objek[i].y + transY;
	}

	if (dx == 0.)
	{
		ddx = 0.;
		ddy = tick;
	}
	else if (dy == 0.)
	{
		ddx = tick;
		ddy = 0.;
	}
	else if ((fabsf(dx) < fabsf(dy)) && (dx != 0.))
	{
		ddx = tick;
		ddy = (fabsf(dy) / fabsf(dx)) * tick;
	}
	else if ((fabsf(dy) < fabsf(dx)) && (dy != 0.))
	{
		ddy = tick;
		ddx = (fabsf(dx) / fabsf(dy)) * tick;
	}

	if (dx < 0.)
	{
		ddx = -ddx;
		kika = -1;
	}
	else if (dx > 0.) kika = 1;
	else kika = 0;

	if (dy < 0.)
	{
		ddy = -ddy;
		aba = -1;
	}
	else if (dy > 0.) aba = 1;
	else aba = 0;

	batasX = objek[0].x + dx;
	batasY = objek[0].y + dy;

	gerakX = objek[0].x + transX;
	gerakY = objek[0].y + transY;

	if (tick == 0.)
	{
		transX = dx;
		transY = dy;
	}
	else
	{
		if ((gerakX > batasX) && (gerakY > batasY) && (kika == -1) && (aba == -1))// kiribawah 

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX > batasX) && (gerakY < batasY) && (kika == -1) && (aba == 1)) // kiri-atas 

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX < batasX) && (gerakY < batasY) && (kika == 1) && (aba == 1)) // kanan-atas

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX < batasX) && (gerakY > batasY) && (kika == 1) && (aba == -1)) // kanan-bawah 

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX == batasX) && (gerakY > batasY) && (kika == 0) && (aba == -1)) // bawah 

		{
			transX = 0.;
			transY += ddy;
		}
		else if ((gerakX == batasX) && (gerakY < batasY) && (kika == 0) && (aba == 1)) // atas 

		{
			transX = 0.;
			transY += ddy;
		}
		else if ((gerakX > batasX) && (gerakY == batasY) && (kika == -1) && (aba == 0)) // kiri 

		{
			transX += ddx;
			transY = 0.;
		}
		else if ((gerakX < batasX) && (gerakY == batasY) && (kika == 1) && (aba == 0)) // kanan 

		{
			transX += ddx;
			transY = 0.;
		}
		else

		{
			transX = 0.;
			transY = 0.;
		}
	}
}

//-------------------- Translasi Matahari ----------------//
/*----------------------------------------------------------------
Fungsi Translasi ini bisa digunakan untuk Polyline, Polygon,
Circle, Ellipse, dan Polar.
------------------------------------------------------------------
t_objek[] - objek hasil translasi
  objek[] - objek yang akan ditranslasi
		n - banyaknya titik yang akan ditranslasi
	   dx - jarak translasi searah sumbu x (- kekiri, + ke kanan)
	   dy - jarak translasi searah sumbu y (- ke bawah, + ke atas )
	 tick - kecepatan animasi (tanpa animasi nilainya 0.)
-------------------------------------------------------------------*/

void Translasi2(Point2D_t t_objek[], Point2D_t objek[], int n, float dx,
	float dy, float tick)

{
	static float transX = 0., transY = 0.;
	float ddx, ddy, batasX, batasY, gerakX, gerakY;
	int aba, kika;

	for (int i = 0; i < n; i++)
	{
		t_objek[i].x = objek[i].x + transX;
		t_objek[i].y = objek[i].y + transY;
	}

	if (dx == 0.)
	{
		ddx = 0.;
		ddy = tick;
	}
	else if (dy == 0.)
	{
		ddx = tick;
		ddy = 0.;
	}
	else if ((fabsf(dx) < fabsf(dy)) && (dx != 0.))
	{
		ddx = tick;
		ddy = (fabsf(dy) / fabsf(dx)) * tick;
	}
	else if ((fabsf(dy) < fabsf(dx)) && (dy != 0.))
	{
		ddy = tick;
		ddx = (fabsf(dx) / fabsf(dy)) * tick;
	}

	if (dx < 0.)
	{
		ddx = -ddx;
		kika = -1;
	}
	else if (dx > 0.) kika = 1;
	else kika = 0;

	if (dy < 0.)
	{
		ddy = -ddy;
		aba = -1;
	}
	else if (dy > 0.) aba = 1;
	else aba = 0;

	batasX = objek[0].x + dx;
	batasY = objek[0].y + dy;

	gerakX = objek[0].x + transX;
	gerakY = objek[0].y + transY;

	if (tick == 0.)
	{
		transX = dx;
		transY = dy;
	}
	else
	{
		if ((gerakX > batasX) && (gerakY > batasY) && (kika == -1) && (aba == -1))// kiribawah 

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX > batasX) && (gerakY < batasY) && (kika == -1) && (aba == 1)) // kiri-atas 

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX < batasX) && (gerakY < batasY) && (kika == 1) && (aba == 1)) // kanan-atas

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX < batasX) && (gerakY > batasY) && (kika == 1) && (aba == -1)) // kanan-bawah 

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX == batasX) && (gerakY > batasY) && (kika == 0) && (aba == -1)) // bawah 

		{
			transX = 0.;
			transY += ddy;
		}
		else if ((gerakX == batasX) && (gerakY < batasY) && (kika == 0) && (aba == 1)) // atas 

		{
			transX = 0.;
			transY += ddy;
		}
		else if ((gerakX > batasX) && (gerakY == batasY) && (kika == -1) && (aba == 0)) // kiri 

		{
			transX += ddx;
			transY = 0.;
		}
		else if ((gerakX < batasX) && (gerakY == batasY) && (kika == 1) && (aba == 0)) // kanan 

		{
			transX += ddx;
			transY = 0.;
		}
		else

		{
			transX = 0.;
			transY = 0.;
		}
	}
}

//-------------------- Translasi Ombak ke Kiri ----------------//
/*----------------------------------------------------------------
Fungsi Translasi ini bisa digunakan untuk Polyline, Polygon,
Circle, Ellipse, dan Polar.
------------------------------------------------------------------
t_objek[] - objek hasil translasi
  objek[] - objek yang akan ditranslasi
		n - banyaknya titik yang akan ditranslasi
	   dx - jarak translasi searah sumbu x (- kekiri, + ke kanan)
	   dy - jarak translasi searah sumbu y (- ke bawah, + ke atas )
	 tick - kecepatan animasi (tanpa animasi nilainya 0.)
-------------------------------------------------------------------*/

void Translasi3(Point2D_t t_objek[], Point2D_t objek[], int n, float dx,
	float dy, float tick)

{
	static float transX = 0., transY = 0.;
	float ddx, ddy, batasX, batasY, gerakX, gerakY;
	int aba, kika;

	for (int i = 0; i < n; i++)
	{
		t_objek[i].x = objek[i].x + transX;
		t_objek[i].y = objek[i].y + transY;
	}

	if (dx == 0.)
	{
		ddx = 0.;
		ddy = tick;
	}
	else if (dy == 0.)
	{
		ddx = tick;
		ddy = 0.;
	}
	else if ((fabsf(dx) < fabsf(dy)) && (dx != 0.))
	{
		ddx = tick;
		ddy = (fabsf(dy) / fabsf(dx)) * tick;
	}
	else if ((fabsf(dy) < fabsf(dx)) && (dy != 0.))
	{
		ddy = tick;
		ddx = (fabsf(dx) / fabsf(dy)) * tick;
	}

	if (dx < 0.)
	{
		ddx = -ddx;
		kika = -1;
	}
	else if (dx > 0.) kika = 1;
	else kika = 0;

	if (dy < 0.)
	{
		ddy = -ddy;
		aba = -1;
	}
	else if (dy > 0.) aba = 1;
	else aba = 0;

	batasX = objek[0].x + dx;
	batasY = objek[0].y + dy;

	gerakX = objek[0].x + transX;
	gerakY = objek[0].y + transY;

	if (tick == 0.)
	{
		transX = dx;
		transY = dy;
	}
	else
	{
		if ((gerakX > batasX) && (gerakY > batasY) && (kika == -1) && (aba == -1))// kiribawah 

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX > batasX) && (gerakY < batasY) && (kika == -1) && (aba == 1)) // kiri-atas 

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX < batasX) && (gerakY < batasY) && (kika == 1) && (aba == 1)) // kanan-atas

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX < batasX) && (gerakY > batasY) && (kika == 1) && (aba == -1)) // kanan-bawah 

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX == batasX) && (gerakY > batasY) && (kika == 0) && (aba == -1)) // bawah 

		{
			transX = 0.;
			transY += ddy;
		}
		else if ((gerakX == batasX) && (gerakY < batasY) && (kika == 0) && (aba == 1)) // atas 

		{
			transX = 0.;
			transY += ddy;
		}
		else if ((gerakX > batasX) && (gerakY == batasY) && (kika == -1) && (aba == 0)) // kiri 

		{
			transX += ddx;
			transY = 0.;
		}
		else if ((gerakX < batasX) && (gerakY == batasY) && (kika == 1) && (aba == 0)) // kanan 

		{
			transX += ddx;
			transY = 0.;
		}
		else

		{
			transX = 0.;
			transY = 0.;
		}
	}
}

//-------------------- Translasi Ombak ke Kanan ----------------//
/*----------------------------------------------------------------
Fungsi Translasi ini bisa digunakan untuk Polyline, Polygon,
Circle, Ellipse, dan Polar.
------------------------------------------------------------------
t_objek[] - objek hasil translasi
  objek[] - objek yang akan ditranslasi
		n - banyaknya titik yang akan ditranslasi
	   dx - jarak translasi searah sumbu x (- kekiri, + ke kanan)
	   dy - jarak translasi searah sumbu y (- ke bawah, + ke atas )
	 tick - kecepatan animasi (tanpa animasi nilainya 0.)
-------------------------------------------------------------------*/

void Translasi4(Point2D_t t_objek[], Point2D_t objek[], int n, float dx,
	float dy, float tick)

{
	static float transX = 0., transY = 0.;
	float ddx, ddy, batasX, batasY, gerakX, gerakY;
	int aba, kika;

	for (int i = 0; i < n; i++)
	{
		t_objek[i].x = objek[i].x + transX;
		t_objek[i].y = objek[i].y + transY;
	}

	if (dx == 0.)
	{
		ddx = 0.;
		ddy = tick;
	}
	else if (dy == 0.)
	{
		ddx = tick;
		ddy = 0.;
	}
	else if ((fabsf(dx) < fabsf(dy)) && (dx != 0.))
	{
		ddx = tick;
		ddy = (fabsf(dy) / fabsf(dx)) * tick;
	}
	else if ((fabsf(dy) < fabsf(dx)) && (dy != 0.))
	{
		ddy = tick;
		ddx = (fabsf(dx) / fabsf(dy)) * tick;
	}

	if (dx < 0.)
	{
		ddx = -ddx;
		kika = -1;
	}
	else if (dx > 0.) kika = 1;
	else kika = 0;

	if (dy < 0.)
	{
		ddy = -ddy;
		aba = -1;
	}
	else if (dy > 0.) aba = 1;
	else aba = 0;

	batasX = objek[0].x + dx;
	batasY = objek[0].y + dy;

	gerakX = objek[0].x + transX;
	gerakY = objek[0].y + transY;

	if (tick == 0.)
	{
		transX = dx;
		transY = dy;
	}
	else
	{
		if ((gerakX > batasX) && (gerakY > batasY) && (kika == -1) && (aba == -1))// kiribawah 

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX > batasX) && (gerakY < batasY) && (kika == -1) && (aba == 1)) // kiri-atas 

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX < batasX) && (gerakY < batasY) && (kika == 1) && (aba == 1)) // kanan-atas

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX < batasX) && (gerakY > batasY) && (kika == 1) && (aba == -1)) // kanan-bawah 

		{
			transX += ddx;
			transY += ddy;
		}
		else if ((gerakX == batasX) && (gerakY > batasY) && (kika == 0) && (aba == -1)) // bawah 

		{
			transX = 0.;
			transY += ddy;
		}
		else if ((gerakX == batasX) && (gerakY < batasY) && (kika == 0) && (aba == 1)) // atas 

		{
			transX = 0.;
			transY += ddy;
		}
		else if ((gerakX > batasX) && (gerakY == batasY) && (kika == -1) && (aba == 0)) // kiri 

		{
			transX += ddx;
			transY = 0.;
		}
		else if ((gerakX < batasX) && (gerakY == batasY) && (kika == 1) && (aba == 0)) // kanan 

		{
			transX += ddx;
			transY = 0.;
		}
		else

		{
			transX = 0.;
			transY = 0.;
		}
	}
}

/*----------------------------------------------------------------
Fungsi skalaPolygon ini bisa digunakan untuk Polyline dan Polygon.
------------------------------------------------------------------
s_objek[] - objek hasil skala
  objek[] - objek yang akan diskala
		n - banyaknya titik yang akan diskala
		m - nilai skala (tidak boleh 0., <1. diperkecil, >1. diperbesar)
	   fp - fixed point (titik yang tidak berubah posisi)
	 tick - kecepatan animasi (tanpa animasi nilainya 0.)
-------------------------------------------------------------------*/

void skalaPolygon(Point2D_t s_objek[], Point2D_t objek[], int n, float m,
	Point2D_t fp, float tick)

{
	static float skala = 1.;

	for (int i = 0; i < n; i++)
	{
		s_objek[i].x = fp.x + (objek[i].x - fp.x) * skala;
		s_objek[i].y = fp.y + (objek[i].y - fp.y) * skala;
	}

	if (tick == 0.) skala = m;
	else
	{
		if ((m > 1.) && (skala < m))
			skala += tick;
		else if ((m < 1.) && (skala > m))
			skala -= tick;
		else skala = 1.;
	}
}

/*----------------------------------------------------------------------
Fungsi skalaCircle ini bisa digunakan untuk Circle, Ellipse, dan Polar.
- yang diskala jari-jarinya
- jika objek yang diskala Circle atau Polar, maka nilai r1=r2
------------------------------------------------------------------------
*s_r1 - jari-jari mendatar hasil skala
*s_r2 - jari-jari tegak hasil skala
   r1 - jari-jari mendatar objek yang diskala
   r2 - jari-jari tegak objek yang diskala
	m - nilai skala (tidak boleh 0.,<1. diperkecil, >1. diperbesar)
 tick - kecepatan animasi (tanpa animasi nilainya 0.)
------------------------------------------------------------------------*/

void skalaCircle(float* s_r1, float* s_r2, float r1, float r2, float m, float tick)

{
	static float skala = 1.;

	*s_r1 = r1 * skala;
	*s_r2 = r2 * skala;

	if (tick == 0.) skala = m;
	else
	{
		if ((m > 1.) && (skala < m))
			skala += tick;
		else if ((m < 1.) && (skala > m))

			skala -= tick;
		else skala = 1.;
	}
}

/*----------------------------------------------------------------
Fungsi rotasiPolygon ini bisa digunakan untuk Polyline dan Polygon.
------------------------------------------------------------------
  r_objek[] - objek hasil rotasi
	objek[] - objek yang akan dirotasi
		  n - banyaknya titik yang akan dirotasi
		 as - koordinat sumbu putaran (poros)
sudut_putar - besarnya sudut putaran (- putar ke kanan, + putar ke kiri)
	   tick - kecepatan animasi (tanpa animasi nilainya 0.)
-------------------------------------------------------------------*/

void rotasiPolygon(Point2D_t r_objek[], Point2D_t objek[], int n,
	Point2D_t as, float sudut_putar, float tick)

{
	static float putar = 0.;

	float sp_rad = putar * 3.14 / 180;

	for (int i = 0; i < n; i++)
	{
		r_objek[i].x = as.x + (objek[i].x - as.x) * cos(sp_rad) - (objek[i].y -
			as.y) * sin(sp_rad);
		r_objek[i].y = as.y + (objek[i].x - as.x) * sin(sp_rad) + (objek[i].y -
			as.y) * cos(sp_rad);
	}

	if (tick == 0.) putar = sudut_putar;
	else
	{
		if ((sudut_putar > 0.) && (putar < sudut_putar))
			putar += tick;
		else if ((sudut_putar < 0.) && (putar > sudut_putar))
			putar -= tick; else putar = 0.;
	}
}

/*----------------------------------------------------------------
Fungsi rotasiCircle ini bisa digunakan untuk Circle dan Ellipse.
------------------------------------------------------------------
  r_objek[] - objek hasil rotasi
	pusat[] - koordinat pusat objek yang akan dirotasi
		 r1 - jari-jari mendatar objek yang akan dirotasi
		 r2 - jari-jari tegak objek yang akan dirotasi
	  sudut - sudut lingkaran atau ellipse yang akan dirotasi
			   (360 lingkaran/ellipse penuh)
		 as - koordinat sumbu putaran (poros)
sudut_putar - besarnya sudut putaran (- putar ke kanan, + putar ke kiri)
tick - kecepatan animasi (tanpa animasi nilainya 0.)
-------------------------------------------------------------------*/

void rotasiCircle(Point2D_t r_objek[], Point2D_t pusat[], float r1, float r2,
	float sudut, Point2D_t as, float sudut_putar, float tick)

{
	static float putar = 0.;

	Point2D_t objek[365];

	float sp_rad = putar * 3.14 / 180;

	float sdt = 0.;

	for (int i = 0; i <= fabsf(sudut); i++)
	{
		//--------- menentuka titik-titik objek ---------//

		float srad = sdt * 3.14 / 180;
		objek[i].x = (float)((r1 * cos(srad)) + pusat[0].x);
		objek[i].y = (float)((r2 * sin(srad)) + pusat[0].y);

		//--------- memutar objek -------------//
		r_objek[i].x = as.x + (objek[i].x - as.x) * cos(sp_rad) - (objek[i].y -
			as.y) * sin(sp_rad);
		r_objek[i].y = as.y + (objek[i].x - as.x) * sin(sp_rad) + (objek[i].y -
			as.y) * cos(sp_rad);

		if (sudut > 0.) sdt += 1.;
		else sdt -= 1.;
	}

	if (tick == 0.) putar = sudut_putar;
	else
	{
		if ((sudut_putar > 0.) && (putar < sudut_putar))
			putar += tick;
		else if ((sudut_putar < 0.) && (putar > sudut_putar))
			putar -= tick;
		else putar = 0.;
	}
}

/*----------------------------------------------------------------
Fungsi rotasiPolar ini bisa digunakan untuk Polar.
------------------------------------------------------------------
   r_objek[] - objek hasil rotasi
	 pusat[] - koordinat pusat objek yang akan dirotasi
		   n - banyaknya daun
	 (ganjil - daun sebanyak n, genap - daun sebanyak 2*n)
panjang daun - jari-jari/panjang daun
	   sudut - sudut polar yang akan dirotasi
			   (360 polar penuh)
		  as - koordinat sumbu putaran (poros)
 sudut_putar - besarnya sudut putaran (- putar ke kanan, + putar ke kiri)
		tick - kecepatan animasi (tanpa animasi nilainya 0.)
-------------------------------------------------------------------*/

void rotasiPolar(Point2D_t r_objek[], Point2D_t pusat[], int n, float pj_daun,
	float sudut, Point2D_t as, float sudut_putar, float tick)

{
	static float putar = 0.;

	Point2D_t objek[365]; //1085

	float sp_rad = putar * 3.14 / 180;

	float sdt = 0.;

	for (int i = 0; i <= fabsf(sudut); i++)
	{
		//--------- menentuka titik-titik objek ---------//

		float srad = sdt * 3.14 / 180;
		float jari2 = sin(n * srad);
		objek[i].x = (float)(jari2 * cos(srad) * pj_daun) + pusat[0].x;
		objek[i].y = (float)(jari2 * sin(srad) * pj_daun) + pusat[0].y;

		//--------- memutar objek -------------//
		r_objek[i].x = as.x + (objek[i].x - as.x) * cos(sp_rad) - (objek[i].y -
			as.y) * sin(sp_rad);
		r_objek[i].y = as.y + (objek[i].x - as.x) * sin(sp_rad) + (objek[i].y -
			as.y) * cos(sp_rad);

		if (sudut > 0.) sdt += 1.;
		else sdt -= 1.;
	}
	if (tick == 0.) putar = sudut_putar;
	else
	{
		if ((sudut_putar > 0.) && (putar < sudut_putar))
			putar += tick;
		else if ((sudut_putar < 0.) && (putar > sudut_putar))
			putar -= tick;
		else putar = 0.;
	}
}

void userdraw()
{
	Color_t kuningL = { 1,1,0.9 };
	Color_t hitam = { 0,0,0 };
	Color_t merah = { 1,0,0 };
	Color_t kuning = { 1,1,0 };
	Color_t kuning1 = { 1,1,0.4 };
	Color_t putihA = { 1,1,1 };
	Color_t cokelat1 = { 0.8,0.7,0.6 };
	Color_t oranye = { 1,0.6,0 };
	Color_t biruL = { 0.2,0.2,1 };
	Color_t kuningM = { 1,1,0 };
	Color_t senja = { 1,0.4,0.2 };
	Color_t biru = { 0,0.4,0.8 };
	Color_t cokelat = { 0.8,0.7,0.6 };
	Color_t cream = { 0.7,0.6,0.8 };
	Color_t hijau = { 0,0.6,0 };
	Color_t hijau1 = { 0.2,1,0.2 };
	Color_t  abu2 = { 0.5,0.5,0.5 };

	//----------- langit ---------------//
	Point2D_t  langit[4] = { {0.,160.},{900.,160.},{900.,680.},{0.,680.} };
	gradatePolygon(langit, 4, putihA, biruL, 2);

	//------------------ tanah -------------------------//
	Point2D_t tanah[4] = { {0.,0.},{900.,0.},{900.,160.},{0.,160.} };
	gradatePolygon2(tanah, 4, putihA, cokelat, 2);

	//------------------ matahari ------------------------//
	Point2D_t t_matahari[2];
	Point2D_t matahari[1] = { 580.,240. };// Point2D_t  matahari [] = {{340.,440.},{.,.},{.,.},{.,.},{.,.},{.,.},{.,.}};

	Point2D_t pntM[365];

	float s_r1;
	float s_r2; //jari-jari hasil skala 
	float r1 = 80.;
	float r2 = 50.; //jari-jari lingkaran
	float m = 0.9; //skala 

	float dxM = -60.;
	float dyM = 360.;

	skalaCircle(&s_r1, &s_r2, r1, r2, m, 0.0005); //operasi scaling
	Translasi2(t_matahari, matahari, 1, dxM, dyM, 0.02);
	drawCircle(t_matahari[0], s_r1, 360, 3., pntM);
	gambarfillPolygon(pntM, 360., kuningM, 1.);

	//-------------------- awan 1 ---------------------//
	//********* pola awan 1 *********//

	Point2D_t t_polaawan[2];
	Point2D_t  polaawan[1] = { 80.,360. };
	Point2D_t pntawan[365];

	float dx = 520.;
	float dy = 220.;

	Translasi(t_polaawan, polaawan, 1, dx, dy, 0.02);
	drawEllipse(t_polaawan[0], 65, 35, 360, 3, pntawan);
	gambarfillPolygon(pntawan, 360, putihA, 1.);

	//********* pola awan 2 *********//

	Point2D_t t_polaawan1[2];
	Point2D_t  polaawan1[1] = { 160.,360. };
	Point2D_t pntawan1[365];

	float dx1 = 560.;
	float dy1 = 220.;

	Translasi(t_polaawan1, polaawan1, 1, dx1, dy1, 0.02);
	drawEllipse(t_polaawan1[0], 65, 35, 360, 3, pntawan1);
	gambarfillPolygon(pntawan1, 360, putihA, 1.);

	//********** pola awan 3 ********//

	Point2D_t t_polaawan2[2];
	Point2D_t  polaawan2[1] = { 100.,360. };
	Point2D_t pntawan2[365];

	float dx2 = 540.;
	float dy2 = 220.;

	Translasi(t_polaawan2, polaawan2, 1, dx2, dy2, 0.02);
	drawEllipse(t_polaawan2[0], 40, 70, 360, 3, pntawan2);
	gambarfillPolygon(pntawan2, 360, putihA, 1.);

	//********** pola awan 4 ********//

	Point2D_t t_polaawan3[2];
	Point2D_t  polaawan3[1] = { 140.,360. };
	Point2D_t pntawan3[365];

	float dx3 = 560.;
	float dy3 = 220.;

	Translasi(t_polaawan3, polaawan3, 1, dx3, dy3, 0.02);
	drawEllipse(t_polaawan3[0], 40, 65, 360, 3, pntawan3);
	gambarfillPolygon(pntawan3, 360, putihA, 1.);

	//******** tembok depan ******//
	Point2D_t tembokdepan[4] = { {60.,80.},{260.,80.},{260.,320.},{60.,320.} };
	gambarfillPolygon(tembokdepan, 4, oranye, 1.);

	//********* kusen tembok depan*******//
	Point2D_t kusentembokD[3] = { {260.,80.},{60.,80.},{60.,320.} };
	gambarPolyline(kusentembokD, 3, hitam, 3.);


	//********* tembok samping *********//

	Point2D_t temboksamping[4] = { {260.,80.},{620.,80.},{620.,320.},{260.,320.} };
	gambarfillPolygon(temboksamping, 4, kuning1, 1.);
	gambarPolygon(temboksamping, 4, hitam, 3.);

	//******* atap segitiga besar*******//
	Point2D_t atapsegitigaB[3] = { {40.,320.},{280.,320.},{160.,440.} };
	gambarfillPolygon(atapsegitigaB, 3, cokelat, 1.);

	//********* kusen atap segitiga besar*******//
	Point2D_t kusensegitigaB[3] = { {60.,320.},{40.,320},{160.,440.} };
	gambarPolyline(kusensegitigaB, 3, hitam, 3.);

	//****** genting **********//
	Point2D_t genting[4] = { {280.,320.},{640.,320.},{520.,440.},{160.,440.} };
	gambarfillPolygon(genting, 4, cokelat1, 1.);
	gambarPolygon(genting, 4, hitam, 3.);

	//******* atap segitiga kecil******//
	Point2D_t atapsegitigak[3] = { {60.,320.},{260.,320.},{160.,420.} };
	gambarfillPolygon(atapsegitigak, 3, oranye, 1.);

	//********* kusen atap segitiga besar *******//
	Point2D_t kusensegitigaK[4] = { {60.,320.},{160.,420},{260.,320},{280.,320.} };
	gambarPolyline(kusensegitigaK, 4, hitam, 3.);

	//********** cendela atap *********//
	Point2D_t cendelaatap[4] = { {120.,312.},{200.,312.},{200.,332.},{120.,332.} };
	gambarfillPolygon(cendelaatap, 4, biru, 1.);
	gambarPolygon(cendelaatap, 4, cream, 3.);

	//********* pintu *************//
	Point2D_t pintu[4] = { {100.,80.},{160.,80.},{160.,260.},{100.,260.} };
	gambarfillPolygon(pintu, 4, cream, 1.);
	gambarPolygon(pintu, 4, abu2, 3.);

	//********* kunci *************//
	Point2D_t kunci[4] = { {112.,180.},{124.,180.},{124.,192.},{112.,192.} };
	gambarfillPolygon(kunci, 4, hijau1, 1.);
	gambarPolygon(kunci, 4, biru, 3.);

	//********* jendela depan*************//
	Point2D_t jendelaD[4] = { {180.,120.},{220.,120.},{220.,260.},{180.,260.} };
	gambarfillPolygon(jendelaD, 4, abu2, 1.);
	gambarPolygon(jendelaD, 4, merah, 3.);

	//********* jendela samping*************//
	Point2D_t jendelaS[4] = { {340.,140.},{540.,140.},{540.,260.},{340.,260.} };
	gambarfillPolygon(jendelaS, 4, hijau, 1.);
	gambarPolygon(jendelaS, 4, hitam, 3.);

	//****** kusen cendela - *******//
	Point2D_t kusenCendela[] = { {340.,200.},{540.,200.} };
	gambarGaris(kusenCendela, hitam, 3);

	//****** kusen cendela I *******//
	Point2D_t kusenCendela2[] = { {440.,140,},{440.,260.} };
	gambarGaris(kusenCendela2, hitam, 3);

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	userdraw();
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 75);//jarak kanvas dgn layar
	glutInitWindowSize(900, 700);//ukuran kanvas pxl
	glutCreateWindow("UAS RAFI-B34170012");//pemberian nama
	glClearColor(1.0, 1.0, 1.0, 0.0);//warnah bacroon red,green,blu yg belakang sendiri gk blh di hilangkan
	gluOrtho2D(0., 900., 0., 700.);//seting koordinat mau menggunakan 2koordinat atau4koordinat
	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}