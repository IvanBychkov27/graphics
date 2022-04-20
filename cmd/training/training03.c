// По экрану движется вращающийся квадрат, отскакивая от границ экрана, в момент отскока скорость вращения возрастает, с течением времени – уменьшается.
/*    gcc training03.c -o training03 -lglut -lGL
    ./training03
*/

#include <GL/glut.h>


GLfloat xq1 = 15.0f;
GLfloat yy1 = 15.0f;                //Координаты вершин квадрата
GLfloat xperem = 0.0f;
GLfloat yperem = 0.0f;              //Координаты центра квадрата
GLfloat rsize = 30.0f;                 //Длина стороны квадрата
GLfloat angle = 3;                  //Угол поворота
GLfloat anglestep = 1;              //Изменение угла поворота

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;               //Изменение координат вершин квадрата

GLfloat windowWidth;
GLfloat windowHeight;               //Ширина и высота окна

void RenderScene(void){             //Прорисовка квадрата
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(xperem,yperem,0.0f);   //Перемещение
    glRotatef(angle,0,0,1);             //Вращение
        glBegin(GL_QUADS);
        glColor4f(1.0f,0.0f,0.0f,1.0f);
        glVertex3f(-xq1, -yy1, 0.0f);
        glVertex3f( xq1, -yy1, 0.0f);
        glVertex3f( xq1,yy1, 0.0f);
        glVertex3f(-xq1,yy1, 0.0f);
        glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {     //Определение рабочего окна
    GLfloat aspectRatio;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (GLfloat)w / (GLfloat)h;
    if (w <= h){
        windowWidth = 100;
        windowHeight = 100 / aspectRatio;
        glOrtho(-100-xq1,100-xq1,-windowHeight+yy1,windowHeight+yy1,1.0,-1.0);
    } else {
        windowWidth = 100 * aspectRatio;
        windowHeight = 100;
        glOrtho(-windowWidth-xq1,windowWidth-xq1,-100+yy1,100+yy1,1.0,-1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void TimerFunction(int value){
    anglestep-=0.004;              //Уменьшение скорости вращения со временем
    if (xperem > windowWidth - rsize || xperem < -windowWidth)
    {                                                               //Когда квадрат касается стенки,
       xstep = -xstep;                                              //изменяется направление его движения
       anglestep+=0.5;                                              //и увеличивается скорость вращения
    }
    if (yperem > windowHeight || yperem < -windowHeight + rsize)
    {
       ystep = -ystep;
       anglestep+=0.5;
    }
    xperem += xstep;
    yperem += ystep;                        //Квадрат передвигается на шаг вперёд
    angle+=anglestep;                       //и поворачивается
    if (xperem > (windowWidth-rsize+xstep))
        xperem = windowWidth-rsize-1;
    else if (xperem < -(windowWidth + xstep))
        xperem = -windowWidth - 1;                  //Проверка на случайный выход квадрата за рамки окна
    if (yperem > (windowHeight+ystep))
        yperem = windowHeight-1;
    else if(yperem < -(windowHeight-rsize+ystep))
        yperem = -windowHeight+rsize-1;
    glutPostRedisplay();
    glClearColor(0.0f,0.0f,1.0f,1.0f);                   //Очистка экрана перед каждой прорисовкой квадрата
    glutTimerFunc(10,TimerFunction,1);              //Повторный вызов функции
}

int main(int argc,char**argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Square R&M");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(10,TimerFunction,1);
    glutMainLoop();
    return 0;
}