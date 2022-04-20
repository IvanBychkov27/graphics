// https://firststeps.ru/mfc/opengl/r.php?1

/*
    gcc main.c -o main -lglut -lGL
    ./main
*/

// #include "afxwin.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glaux.h"

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_RGB);
	auxInitPosition (0, 0, 500, 500);
	auxInitWindow ("Step1");
	return 0;
}