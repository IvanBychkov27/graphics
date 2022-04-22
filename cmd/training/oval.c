// рисуем овал
/*
       gcc oval.c -o oval -lglut -lGL -lm
       ./oval
*/

#include <GL/glut.h>
#include <math.h>

/* ширина и высота окна */
GLfloat Width = 1600, Height = 800;

/* функция отображает круг */
void DrawCircle(float x1, float y1, float radius)
{
    glBegin(GL_LINE_LOOP);
        for(float i = 0.0; i < 6.2; i+=0.1 ) {
            glVertex2f(x1 + radius*cos( i ), y1 + radius*sin( i ) );
        }
    glEnd();
}

/* функция отображает овал, flatten от -1 до 1, если 0 - будет круг */
void DrawOval(float x1, float y1, float radius, float flatten)
{
    float xf = 1, yf = 1;
    if (flatten < 0) {xf = flatten; }
    if (flatten > 0) {yf = flatten; }

    glBegin(GL_LINE_LOOP);
        for(float i = 0.0; i < 6.2; i+=0.1 ) {
            glVertex2f(x1 + xf * radius * cos(i), y1 + yf * radius * sin(i));
        }
    glEnd();
}

/* управляет всем выводом на экран */
void Display(void)
{
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub( 255, 215, 0 );
  DrawOval(0.0, 0.0,0.7, 0.5);
  DrawOval(0.0, 0.0,0.9, 0.5);

  glFinish();
}

/* Функция обрабатывает сообщения от клавиатуры */
void Keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27: /* escape */
         exit(0);
         break;
   }
}

/* Главный цикл приложения */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);                     // производит начальную инициализацию самой библиотеки GLUT.
    glutInitDisplayMode(GLUT_RGB);             // инициализирует буфер кадра и настраивает полноцветный (непалитровый) режим RGB.
    glutInitWindowSize(Width, Height);         // используется для задания начальных размеров окна
    glutCreateWindow("Oval");                // задает заголовок окна и визуализирует само окно на экране

                                 // функции, которые будут вызваны:
    glutDisplayFunc(Display);    // при перерисовке окна
    glutKeyboardFunc(Keyboard);  // нажатии клавиши на клавиатуре

    glutMainLoop(); // Контроль всех событий и вызов нужных функций происходит внутри бесконечного цикла в функции glutMainLoop()
    return 0;
}