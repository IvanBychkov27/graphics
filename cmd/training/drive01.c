/*    gcc drive01.c -o drive01 -lglut -lGL
    ./drive01   */

#include <GL/glut.h>
#include <stdio.h>

GLfloat windowWidth;
GLfloat windowHeight;

GLfloat xq1 = -0.1f;
GLfloat yq1 = 0.1f;
GLfloat rsize = 20;

GLfloat xstep = 0.0f;
GLfloat ystep = 0.0f;

void SetupRC(void){
    glClearColor(0.1, 0.1, 0.1, 1);
}

void RenderScene(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(230,230,0);
    glRectf(xq1,yq1,xq1+rsize,yq1-rsize);

    glutSwapBuffers();
}

/* Функция обрабатывает сообщения от клавиатуры */
void Keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27: /* escape */
         exit(0);
         break;
      case 97: /* "a" left - GLUT_KEY_LEFT */
          if (xstep != 0) {
             xstep = 0.0f;
          } else {
             xstep = -1.0f;
          }
          break;
      case 119: /* "w" up  - GLUT_KEY_UP */
          if (ystep != 0) {
              ystep = 0.0f;
          } else {
              ystep = 1.0f;
          }
          break;
      case 100: /* "d" right  - GLUT_KEY_RIGHT */
          if (xstep != 0) {
              xstep = 0.0f;
          } else {
              xstep = 1.0f;
          }
          break;
      case 115: /* "s" down - GLUT_KEY_DOWN */
          if (ystep != 0) {
              ystep = 0.0f;
          } else {
              ystep = -1.0f;
          }
          break;
      case 32: /* "пробел" stop */
          xstep = 0.0f;
          ystep = 0.0f;
          break;
   }
//   printf("key = %d\n", key);
}

void ChangeSize(GLsizei w, GLsizei h) {
    GLfloat aspectRatio;
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (GLfloat)w / (GLfloat)h;
    if (w <= h){
        windowWidth = 100;
        windowHeight = 100 / aspectRatio;
        glOrtho(-100.0,100.0,-windowHeight,windowHeight,1.0,-1.0);
    } else {
        windowWidth = 100 * aspectRatio;
        windowHeight = 100;
        glOrtho(-windowWidth,windowWidth,-100.0,100.0,1.0,-1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void TimerFunction(int value){
   if (xq1 > windowWidth - rsize || xq1 < -windowWidth)
           xstep = -xstep;
   if (yq1 > windowHeight || yq1 < -windowHeight + rsize)
           ystep = -ystep;
      xq1 += xstep;
      yq1 += ystep;

   if (xq1 > (windowWidth-rsize+xstep))
       xq1 = windowWidth-rsize-1;
   else if (xq1 < -(windowWidth + xstep))
       xq1 = -windowWidth - 1;
   if (yq1 > (windowHeight+ystep))
       yq1 = windowHeight-1;
   else if(yq1 < -(windowHeight-rsize+ystep))
       yq1 = -windowHeight+rsize-1;
   glutPostRedisplay();
   glutTimerFunc(10,TimerFunction, 1);
}

int main(int argc,char**argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Drive 01");

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(Keyboard);  // нажатии клавиши на клавиатуре

    glutTimerFunc(10,TimerFunction,1);
    SetupRC();
    glutMainLoop();
    return 0;
}