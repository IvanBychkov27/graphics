// рисуем круг
/*
       gcc circle.c -o circle -lglut -lGL -lm
       ./circle
*/

#include <GL/glut.h>
#include <math.h>

/* ширина и высота окна */
GLfloat Width = 800, Height = 800;

/* функция отображает круг */
void DrawCircle(float x1, float y1, float radius)
{
    glBegin(GL_LINE_LOOP);
        for(float i = 0.0; i < 6.2; i+=0.1 ) {
            glVertex2f(x1 + radius*cos( i ), y1 + radius*sin( i ) );
        }
    glEnd();
}

/* функция отображает прямоугольник */
void DrawRect( float x1, float y1, float x2, float y2 )
{
    glBegin(GL_QUADS);
      glVertex2f(x1, y1);
      glVertex2f(x2, y1);
      glVertex2f(x2, y2);
      glVertex2f(x1, y2);
    glEnd();
}

/* управляет всем выводом на экран */
void Display(void)
{
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub( 255, 215, 0 );
  DrawCircle(-0.5,-0.1,0.3);
  DrawRect(-0.8, -0.8, -0.7, -0.7);

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
    glutCreateWindow("Circle");                // задает заголовок окна и визуализирует само окно на экране

                                 // функции, которые будут вызваны:
    glutDisplayFunc(Display);    // при перерисовке окна
    glutKeyboardFunc(Keyboard);  // нажатии клавиши на клавиатуре

    glutMainLoop(); // Контроль всех событий и вызов нужных функций происходит внутри бесконечного цикла в функции glutMainLoop()
    return 0;
}