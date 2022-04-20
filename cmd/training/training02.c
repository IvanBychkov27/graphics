// По экрану движется квадрат, отскакивая от границ экрана, в момент отскока скорость вращения возрастает, с течением времени – уменьшается.
/*    gcc training02.c -o training02 -lglut -lGL
    ./training02
*/

#include <GL/glut.h>

GLfloat xq1 = 0.0f;
GLfloat yq1 = 0.0f;
GLfloat rsize = 25;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat windowWidth;
GLfloat windowHeight;

void RenderScene(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f,0.0f,0.0f);
    glRectf(xq1,yq1,xq1+rsize,yq1-rsize);

    glutSwapBuffers();
}

void SetupRC(void){
    glClearColor(0.0f,0.0f,1.0f,1.0f);
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
    glutTimerFunc(10,TimerFunction,1);
}

int main(int argc,char**argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Bounce");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(10,TimerFunction,1);
    SetupRC();
    glutMainLoop();
    return 0;
}
