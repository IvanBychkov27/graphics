// вывод текста
/*
       gcc text.c -o text -lglut -lGL -lm
       ./text
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>

/* ширина и высота окна */
GLfloat Width = 400;
GLfloat Height = 400;

GLfloat d = 0.12345f;

// вывод текста
void DrawText(const char *text, int length, int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    double matrix[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0,400,0,400,-2,2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x,y);
    for(int i=0; i<length; i++)
    {
       glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

char *PrintText(float d) {
    if (d < 0) d = -d;

    char numbers[][2] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    int n = 5;

    char *msg;
    msg = (char*)malloc(n);

    int data = d;
    if (d < 1)  data = 100000*d;

    for (int i = 0; i < n; i++){
        msg[n-i-1] = *numbers[data % 10];
        data = data / 10;
    }

    return msg;
}

/* управляет всем выводом на экран */
void Display(void)
{
  glClearColor(0.1, 0.1, 0.1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub( 255, 215, 0 );

  char *text = {"Text"};
  DrawText(text, 4, 180, 350);

  char *msg = PrintText(d);
  DrawText(msg, 5, 150, 200);

  glFinish();
//  glutSwapBuffers();
}

/* Функция обрабатывает сообщения от клавиатуры */
void Keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27: /* escape */
         exit(0);
         break;
      case 119: /* w */
         d += 0.00001;
         break;
      case 115: /* s */
         d -= 0.00001;
         break;
   }
   printf("key = %d  d = %f\n", key, d);
   glutPostRedisplay();
}

/* Главный цикл приложения */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);                     // производит начальную инициализацию самой библиотеки GLUT.
    glutInitDisplayMode(GLUT_RGB);             // инициализирует буфер кадра и настраивает полноцветный (непалитровый) режим RGB.
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Width, Height);         // используется для задания начальных размеров окна
    glutCreateWindow("Text");                // задает заголовок окна и визуализирует само окно на экране

                                 // функции, которые будут вызваны:
    glutDisplayFunc(Display);    // при перерисовке окна
    glutKeyboardFunc(Keyboard);  // нажатии клавиши на клавиатуре

    glutMainLoop(); // Контроль всех событий и вызов нужных функций происходит внутри бесконечного цикла в функции glutMainLoop()
    return 0;
}