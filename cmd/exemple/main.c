// https://www.rsdn.org/article/opengl/ogltut2.xml - Графическая библиотека OpenGL - методическое пособие

/*
    gcc main.c -o main -lglut -lGL
    ./main
*/

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

//void setup() {   glClearColor(1.0f, 1.0f, 1.0f, 1.0f); } // очистка всей формы -  заливка белым цветом

void display()
   {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glColor3f(0.0f, 0.0f, 0.0f);            // устанавливаем цвет черный
      glRectf(-0.75f,0.75f, 0.75f, -0.75f);   // рисуем черный прямоугольник

      // рисуем треугольник
      GLfloat BlueCol[3] = {0,0,1};
      glBegin(GL_TRIANGLES);
      glColor3f(1.0, 0.0, 0.0);   /* красный */
      glVertex3f(-0.5, -0.5, 0.0); // установка красной точки
      glColor3ub(0,255,0);          /* зеленый */
      glVertex3f(0.5, -0.5, 0.0);   // установка зеленой точки
      glColor3fv(BlueCol);       /* синий */
      glVertex3f(0.5, 0.5, 0.0); // установка синей точки
      glEnd();

//      GLUquadricObj* m_qObj;
//      m_qObj = gluNewQuadric();
//      gluSphere(m_qObj, 0.1, 0, 0);

      glutSwapBuffers(); // вывод в буфер
   }

int main(int argc, char *argv[])
  {
     /* Инициализация GLUT */
     glutInit(&argc, argv);
     glutInitWindowSize(400,400);

     /* Открытие окна */
     glutCreateWindow("Hello World");

     /* Выбор режима:  двойной буфер и RGBA цвета */
     glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

     glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // очистка всей формы -  заливка белым цветом

     /* Регистрация вызываемых функций */
     glutDisplayFunc(display);

     glutMainLoop(); // бесконечный цикл программы - Запуск механизма обработки событий
     return 0;
  }
