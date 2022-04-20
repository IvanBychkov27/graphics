/*    gcc training01.c -o training01 -lglut -lGL
    ./training01
*/

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

/* начальная ширина и высота окна */
GLint Width = 800, Height = 600;

/* размер куба */
const int CubeSize = 150;

int xq1 = 100, xq2 = 150, yq1 = 500, yq2 = 550, dx = 0, dy = 0;

/* эта функция управляет всем выводом на экран */
void Display()
{
    int left, right, top, bottom;

    left  = (Width - CubeSize) / 2;
    right = left + CubeSize;
    bottom = (Height - CubeSize) / 2;
    top = bottom + CubeSize;

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    int x1, x2, y1, y2;
    x1 = xq1+dx;
    x2 = xq2+dx;
    y1 = yq1+dy;
    y2 = yq2+dy;

    // прямоугольник
    glColor3ub(100,200,0);
    glBegin(GL_QUADS);
       glVertex2f(x1,y1);
       glVertex2f(x1,y2);
       glVertex2f(x2,y2);
       glVertex2f(x2,y1);
    glEnd();


    // квадрат
    glColor3ub(0,0,200);
    glBegin(GL_QUADS);
      glVertex2f(left,bottom);
      glVertex2f(left,top);
      glVertex2f(right,top);
      glVertex2f(right,bottom);
    glEnd();

    // прямоугольник
    glColor3ub(150,100,0);
    glBegin(GL_QUADS);
       glVertex2f(100,100);
       glVertex2f(100,250);
       glVertex2f(200,250);
       glVertex2f(200,100);
    glEnd();

     // линия белая
     glColor3ub(255,255,255);
     glBegin(GL_LINES);
        glVertex2f(10,60);
        glVertex2f(790,60);
     glEnd();

     // линия синяя
        glColor3ub(0,0,240);
        glBegin(GL_LINES);
           glVertex2f(10,50);
           glVertex2f(790,50);
        glEnd();

     // линия красная
     glColor3ub(255,0,0);
     glBegin(GL_LINES);
        glVertex2f(10,40);
        glVertex2f(790,40);
     glEnd();

     // сфера
     glColor3ub(0,0,255);
     glutSolidSphere(0.25f,30,10); //Рисуем сферу
     glutWireSphere(0.25f,30,10); // каркас сферы

    // диск


    glFinish();
}

/* Функция вызывается при изменении размеров окна */
void Reshape(GLint w, GLint h)
{
    Width = w;
    Height = h;

    /* устанавливаем размеры области отображения */
    glViewport(0, 0, w, h);

    /* ортографическая проекция */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Функция обрабатывает сообщения от клавиатуры */
void Keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27: /* escape */
         exit(0);
         break;
      case 97: /* "a" left - GLUT_KEY_LEFT */
         dx -=10;
         break;
     case 119: /* "w" up  - GLUT_KEY_UP */
         dy +=10;
         break;
     case 100: /* "d" right  - GLUT_KEY_RIGHT */
         dx +=10;
         break;
     case 115: /* "s" down - GLUT_KEY_DOWN */
         dy -=10;
         break;
   }

//   printf("key = %d, dx = %d \n", key, dx);
}

/* Главный цикл приложения */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);                     // производит начальную инициализацию самой библиотеки GLUT.
    glutInitDisplayMode(GLUT_RGB);             // инициализирует буфер кадра и настраивает полноцветный (непалитровый) режим RGB.
    glutInitWindowSize(Width, Height);         // используется для задания начальных размеров окна
    glutCreateWindow("Training 01");          // задает заголовок окна и визуализирует само окно на экране

                                 // функции, которые будут вызваны:
    glutDisplayFunc(Display);    // при перерисовке окна
    glutReshapeFunc(Reshape);    // изменении размеров окна
    glutKeyboardFunc(Keyboard);  // нажатии клавиши на клавиатуре

    glutMainLoop(); // Контроль всех событий и вызов нужных функций происходит внутри бесконечного цикла в функции glutMainLoop()
    return 0;
}