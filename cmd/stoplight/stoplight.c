// светофор

/*
       gcc stoplight.c -o stoplight -lglut -lGL -lm
       ./stoplight
*/

#include <GL/glut.h>
#include <math.h>

/* ширина и высота окна */
GLfloat Width = 512, Height = 512;

GLfloat xx = 0.07f;
GLfloat yy = 0.07f;                //Координаты вершин квадрата
GLfloat xperem = 0.0f;
GLfloat yperem = 0.0f;              //Координаты центра квадрата
GLfloat rsize = 2*0.07f;                 //Длина стороны квадрата

GLfloat xstep = 0.01f;
GLfloat ystep = 0.00f;               //Изменение координат вершин квадрата

int Clicks = 1;

/* функция отображает прямоугольник */
void DrawRect( float x1, float y1, float x2, float y2 )
{
     glLoadIdentity();
     glPushMatrix();
     glTranslatef(xperem,yperem,0.0f);   //Перемещение

      glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
      glEnd();

      glPopMatrix();
      glutSwapBuffers();
}

/* функция отображает круг с центром x1, x2, и радиусом r */
void DrawCircle( float x1, float y1, float r )
{
  glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);
     for(float i = 0.0; i < 6.3; i+=0.1 ) {
          glVertex2f(x1 + r*cos( i ), y1 + r*sin( i ) );
     }
   glEnd();
}

 // светофор
void DrawStoplight(float x1, float y1, float radius)
{
      // параметры светофора
      float rStoplight = radius;     // радиус сигнала светофора
      float xStoplight = x1;      // x - координата центра светофора
      float yStoplight = y1;      // y - координата центра светофора
      float deltaStoplight = 0.01; // расстояние между сигналами светофора

      float r, g, b = 0;

      if  (Clicks == 1) {
           r = 255; g = 0;  b = 0;
      } else {
           r = 105; g = 105; b = 105;
      }
      glColor3ub( r, g, b ); // красный
      DrawCircle(xStoplight, yStoplight + 2*rStoplight + deltaStoplight, rStoplight);

      if  (Clicks == 2) {
           r = 255; g = 215;  b = 0;
      } else {
          r = 105; g = 105; b = 105;
      }
      glColor3ub( r, g, b ); // желтый
      DrawCircle(xStoplight, yStoplight, rStoplight);

      if  (Clicks == 3) {
           r = 50; g = 205; b = 50;
      } else {
           r = 105; g = 105; b = 105;
      }
      glColor3ub( r, g, b ); // зеленый
      DrawCircle(xStoplight, yStoplight - 2*rStoplight - deltaStoplight, rStoplight);

}

/* управляет всем выводом на экран */
void Display(void)
{
  float x1, y1, x2, y2;
  float r, g, b;

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

   r = 0;  g = 0;  b = 0;
   if (Clicks > 3) Clicks = 1;
   if (Clicks < 1) Clicks = 3;
   if (Clicks == 1) {r = 255; g = 0;  b = 0;}
   if (Clicks == 2) {r = 255; g = 200;  b = 0;}
   if (Clicks == 3) {r = 0; g = 200;  b = 0;}

   glColor3ub( r, g, b );

//   x1 = -0.8;  y1 = -0.8;
//   x2 = -0.7;  y2 = -0.7;


   x1 = -xx - 0.9;  y1 = -yy - 0.6;
   x2 = xx - 0.9;   y2 = yy - 0.6;
   DrawRect(x1, y1, x2, y2);

   DrawStoplight(0.0, 0.0, 0.09);

   glFinish();
}

/* Обрабатывает сообщения от мыши */
void Mouse(int button, int state, int x, int y)
{
  if( state == GLUT_DOWN ) {
    switch( button ) {
      case GLUT_LEFT_BUTTON:
        Clicks++;
        break;
      case GLUT_RIGHT_BUTTON:
        Clicks--;
        break;
    }
    glutPostRedisplay();
  }
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

//
//void ChangeSize(GLsizei w, GLsizei h) {     //Определение рабочего окна
//    GLfloat aspectRatio;
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    aspectRatio = (GLfloat)w / (GLfloat)h;
//    if (w <= h){
//        Width = 100;
//        Height = 100 / aspectRatio;
//        glOrtho(-100-xx,100-xx,-Height+yy,Height+yy,1.0,-1.0);
//    } else {
//        Width = 100 * aspectRatio;
//        Height = 100;
//        glOrtho(-Width-xx,Width-xx,-100+yy,100+yy,1.0,-1.0);
//    }
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}

void TimerFunction(int value){
    if (xperem > Width - rsize || xperem < -Width)
    {                                                               //Когда квадрат касается стенки,
       xstep = -xstep;                                              //изменяется направление его движения
    }

    xperem += xstep; //Квадрат передвигается на шаг вперёд
    yperem += ystep;

    if (xperem > (Width-rsize+xstep))
        xperem = Width-rsize-1;
    else if (xperem < -(Width + xstep))
        xperem = -Width - 1;                  //Проверка на случайный выход квадрата за рамки окна

    glutPostRedisplay();
    glClearColor(0.0f,0.0f,1.0f,1.0f);                   //Очистка экрана перед каждой прорисовкой квадрата

    glutTimerFunc(10,TimerFunction,1);              //Повторный вызов функции
}



/* Главный цикл приложения */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);                     // производит начальную инициализацию самой библиотеки GLUT.
    glutInitDisplayMode(GLUT_RGB);             // инициализирует буфер кадра и настраивает полноцветный (непалитровый) режим RGB.
    glutInitWindowSize(Width, Height);         // используется для задания начальных размеров окна
    glutCreateWindow("Stoplight");          // задает заголовок окна и визуализирует само окно на экране

                                 // функции, которые будут вызваны:
    glutDisplayFunc(Display);    // при перерисовке окна
//    glutReshapeFunc(Reshape);    // изменении размеров окна
    glutKeyboardFunc(Keyboard);  // нажатии клавиши на клавиатуре
    glutMouseFunc(Mouse);        // сообщения от мыши

//    glutReshapeFunc(ChangeSize);  // изменении размеров окна
//    glutTimerFunc(10,TimerFunction,1);

    glutMainLoop(); // Контроль всех событий и вызов нужных функций происходит внутри бесконечного цикла в функции glutMainLoop()
    return 0;
}