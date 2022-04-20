/*
Этот простой пример предназначен для демонстрации структуры GLUT-приложения и простейших основ OpenGL.
Результатом работы программы является случайный набор цветных прямоугольников, который меняется при нажатии левой кнопки мыши.
С помощью правой кнопки мыши можно менять режим заливки прямоугольников.

    gcc main02.c -o main02 -lglut -lGL
    ./main02
*/

#include <stdlib.h>
#include <GL/glut.h>

#ifdef random
#undef random
#endif

#define random(m) (float)rand()*m/RAND_MAX

/* ширина и высота окна */
GLint Width = 512, Height = 512;
/* число прямоугольников в окне */
int   Times = 10;
/* с заполнением ?*/
int   FillFlag  = 1;

long  Seed = 0;

/* функция отображает прямоугольник */
void DrawRect( float x1, float y1, float x2, float y2, int FillFlag )
{
  glBegin(FillFlag ? GL_QUADS : GL_LINE_LOOP);
  glVertex2f(x1, y1);
  glVertex2f(x2, y1);
  glVertex2f(x2, y2);
  glVertex2f(x1, y2);
  glEnd();
}

/* управляет всем выводом на экран */
void Display(void)
{
  int i;
  float x1, y1, x2, y2;
  float r, g, b;

  srand(Seed);

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  for( i = 0; i < Times; i++ ) {
    r = random(1);
    g = random(1);
    b = random(1);
    glColor3f( r, g, b );

    x1 = random(1) * Width;
    y1 = random(1) * Height;
    x2 = random(1) * Width;
    y2 = random(1) * Height;
    DrawRect(x1, y1, x2, y2, FillFlag);
  }

  glFinish();
}

/* Вызывается при изменении размеров окна */
void Reshape(GLint w, GLint h)
{
  Width = w;
  Height = h;

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, w, 0, h, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/* Обрабатывает сообщения от мыши */
void Mouse(int button, int state, int x, int y)
{
  if( state == GLUT_DOWN ) {
    switch( button ) {
      case GLUT_LEFT_BUTTON:
        Seed = random(RAND_MAX);
        break;
      case GLUT_RIGHT_BUTTON:
        FillFlag = !FillFlag;
        break;
    }
    glutPostRedisplay();
  }
}

/* Обрабатывает сообщения от клавиатуры */
void Keyboard( unsigned char key, int x, int y )
{
#define ESCAPE '\033'

  if( key == ESCAPE )
      exit(0);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(Width, Height);
  glutCreateWindow("Rect draw example (RGB)");

  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);
  glutMouseFunc(Mouse);

  glutMainLoop();
  return 0;
}