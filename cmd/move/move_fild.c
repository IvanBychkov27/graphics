// движение в поле (fild)
/*
       gcc move_fild.c -o move_fild -lglut -lGL -lm
       ./move_fild
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ширина и высота окна */
float Width = 1800;
float Height = 400;

float winX = 1.0;
float winY = 1.0;

float xq1 = -0.9f;
float yq1 = 0.2f;

float rsize = 0.1f;
float xsize = 0.1f;
float ysize = 0.1f;

float xstep = 0.0f; // шаг перемещениия по оси x
float ystep = 0.0f;

float t = 0.1f;      // время
float vector = 1.0f; // направление движения
float speed = 0.0f;  // скорость
float a = 0.0f;      // ускорение
float stop = 0;      // остановка

char numbers[][2] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

//int fild[1800][400]; // поле размерности окна
float xCoord = 0;
float yCoord = 0;
int xfild = 0;
int yfild = 0;

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

    int n = 4;

    char *msg;
    msg = (char*)malloc(n);

    int data = d;
    if (d < 1)  data = d * 10000;

    for (int i = 0; i < n; i++){
        msg[n-i-1] = *numbers[data % 10];
        data = data / 10;
    }

    return msg;
}

// d = от -1 до 1; base = Width или Height;
// преобразуем координату из формата float 0,1 в int 150
float convertCoord(float d, float base) {
    float res;
    res = (1 + d) * base / 2;
    return res;
}

/* управляет всем выводом на экран */
void Display(void)
{
     glClearColor(0, 0, 0, 1);
     glClear(GL_COLOR_BUFFER_BIT);

     glColor3ub( 255, 215, 0 );
     glRectf(xq1, yq1, xq1+xsize, yq1-ysize); /* функция отображает прямоугольник */

     glColor3ub( 255, 215, 10 );

     char *timeMsg = {"step = "};
     DrawText(timeMsg, 7, 37, 120);
     char *msgT = PrintText(xstep);
     DrawText(msgT, 4, 50, 120);

     char *speedMsg = {"v = 0."};
     DrawText(speedMsg, 6, 38, 100);
     char *msgV = PrintText(speed);
     DrawText(msgV, 4, 50, 100);

     char *speedupMsg = {"a = 0."};
     DrawText(speedupMsg, 6, 38, 80);
     char *msgA = PrintText(a);
     DrawText(msgA, 4, 50, 80);

     char *infoMsg = {"q, a - speedup;   w, s - speed;   space bar - stop;  esc - exit"};
     DrawText(infoMsg, 63, 20, 20);


//     xfild = (int)xCoord;
//     yfild = (int)yCoord;
//     fild[xfild][yfild] = 0;

     char *xMsg = {"x = "};
     DrawText(xMsg, 4, 38, 370);

     xCoord = convertCoord(xq1, Width);
     char *msgX = PrintText(xCoord);
     DrawText(msgX, 4, 45, 370);

     char *yMsg = {"y = "};
     DrawText(yMsg, 4, 38, 350);

     yCoord = convertCoord(yq1, Height);
     char *msgY = PrintText(yCoord);
     DrawText(msgY, 4, 45, 350);

//     xfild = (int)xCoord;
//     yfild = (int)yCoord;
//     fild[xfild][yfild] = 1;

     glutSwapBuffers();
}

/* Функция обрабатывает сообщения от клавиатуры */
void Keyboard(unsigned char key, int x, int y)
{
    switch (key) {
       case 27: /* escape */
          exit(0);
          break;
       case 119: /* w */
          speed += 0.0005;
          break;
       case 115: /* s */
          speed -= 0.0005;
          break;
       case 113: /* q */
          a += 0.0001;
          break;
       case 97: /* a */
          a -= 0.0001;
          break;
       case 32: /* пробел */
            stop = 1;
          break;
    }
    glutPostRedisplay();
}

void ChangeSize(GLsizei w, GLsizei h) {
      winX = w / Width;
      if   ( Height < Width ) { xsize = rsize * Height/Width; }
      if   ( Height > Width ) { ysize = rsize * Width/Height; }
}

void StopFunc(){
      if (speed > 0) {
         a = -0.015;
         if (speed <= 0.001) { a = 0;  speed = 0;  stop = 0; }
      }

      if (speed < 0) {
            a = 0.015;
            if (speed >= -0.001) { a = 0;  speed = 0;  stop = 0; }
      }
}

void TimerFunction(int value){
     if (xq1 > winX - xsize || xq1 < -winX + Width/1000000)   vector = -vector;

     if (stop == 1) {
       StopFunc();
     }

     speed = speed + a * t;
     xstep = speed * t +  a * t *t /2;

     xq1 += vector * xstep;

     if (xq1 > (Width-rsize+xstep))   xq1 = Width-rsize-1;
     else if (xq1 < -(Width + xstep)) xq1 = -Width - 1;

     glutPostRedisplay();
     glutTimerFunc(10,TimerFunction, 1);
}

/* Главный цикл приложения */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);                     // производит начальную инициализацию самой библиотеки GLUT.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // инициализирует буфер кадра и настраивает полноцветный (непалитровый) режим RGB.
    glutInitWindowSize(Width, Height);         // используется для задания начальных размеров окна
    glutCreateWindow("Move");                // задает заголовок окна и визуализирует само окно на экране

                                 // функции, которые будут вызваны:
    glutDisplayFunc(Display);    // при перерисовке окна
    glutReshapeFunc(ChangeSize); // при изменении размеров окна
    glutKeyboardFunc(Keyboard);  // нажатии клавиши на клавиатуре

    glutTimerFunc(10,TimerFunction, 1);
    glutMainLoop(); // Контроль всех событий и вызов нужных функций происходит внутри бесконечного цикла в функции glutMainLoop()
    return 0;
}