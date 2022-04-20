// https://www.youtube.com/watch?v=pFT_sL5hWo8&list=PLOMmu5g25xfUUk6dFM-0DZENdVkpC2Tdv&t=0s
// gcc glut.c -lglut -lGL -o glut  - компиляция
// ./glut - запуск
#include <GL/freeglut.h>

void display(){
   glClearColor(0.1f, 0.8f, 0.0f, 0.0f);
   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f( 0.0f, 0.0f, 0.0f );
   glLineWidth( 1 );
   glBegin( GL_LINES );
   glVertex2f( -0.9, 0.9f );
   glVertex2f( 0.9, -0.9f );
   glEnd();
   glFlush();

   glutSwapBuffers();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(300, 200);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("My first window");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}