// светофор в действии

/*
       gcc work.c -o work -lglut -lGL
       ./work
*/

#include <GL/glut.h>
#include <string.h>

/* ширина и высота окна */
GLfloat Width = 400, Height = 400;

int signalStoplight = 1;
int timer = 0;

char msg[] = "Stoplight";
char msgTimer[][2] = {"8", "7", "6", "5", "4", "3", "2", "1", "0", "0", "8", "7", "6", "5", "4", "3", "2", "1"};

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

// светофор из прямоугольников
void DrawStoplight(float x1, float y1, float h)
{
      float delta = h/10; // расстояние между сигналами светофора

      float r, g, b;

      if  (signalStoplight == 1) {
           r = 50; g = 205; b = 50; // зеленый
      } else {
           r = 105; g = 105; b = 105;
      }
      glColor3ub( r, g, b );
      DrawRect(x1, y1, x1+h, y1+h/2);

      if  (signalStoplight == 2 || signalStoplight == 4) {
           r = 255; g = 215;  b = 0; // желтый
      } else {
          r = 105; g = 105; b = 105;
      }
      glColor3ub( r, g, b );
      DrawRect(x1, y1+h/2 + delta, x1+h, y1+h + delta);

      if  (signalStoplight > 2) {
           r = 255; g = 0;  b = 0; // красный
      } else {
           r = 105; g = 105; b = 105;
      }
      glColor3ub( r, g, b );
      DrawRect(x1, y1+h + 2*delta, x1+h, y1+h*3/2 + 2*delta);
}

/* управляет всем выводом на экран */
void Display(void)
{
  float r = 0, g = 0, b = 0;

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  DrawStoplight(-0.3, -0.3, 0.6);

  glColor3ub( 255, 215, 0 );
  DrawText(msg, 9, 30, 370);

  if  (signalStoplight == 1) {
       glColor3ub( 50, 205, 50 );
       DrawText(msgTimer[timer], 2, 200, 237);
  }

  if  (signalStoplight == 3) {
         glColor3ub( 255, 0, 0 );
         DrawText(msgTimer[timer], 2, 200, 237);
  }

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

 // таймер
void TimerFunction(int value){
    timer++;

    // управление светофором
    if (timer == 8) { signalStoplight = 2;}
    if (timer == 10) { signalStoplight = 3;}
    if (timer == 18) { signalStoplight = 4;}
    if (timer == 20) { signalStoplight = 1; timer = 0;}

    glutPostRedisplay();
    glutTimerFunc(1000,TimerFunction,1);        //Повторный вызов функции
}

/* Главный цикл приложения */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);                     // производит начальную инициализацию самой библиотеки GLUT.
    glutInitDisplayMode(GLUT_RGB);             // инициализирует буфер кадра и настраивает полноцветный (непалитровый) режим RGB.
    glutInitWindowSize(Width, Height);         // используется для задания начальных размеров окна
    glutCreateWindow("Stoplight work");          // задает заголовок окна и визуализирует само окно на экране

                                 // функции, которые будут вызваны:
    glutDisplayFunc(Display);    // при перерисовке окна
    glutKeyboardFunc(Keyboard);  // нажатии клавиши на клавиатуре

    glutTimerFunc(1000,TimerFunction,1); // таймер на 1000 мс

    glutMainLoop(); // Контроль всех событий и вызов нужных функций происходит внутри бесконечного цикла в функции glutMainLoop()
    return 0;
}