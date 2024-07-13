#include <windows.h>
#include<iostream>
#include <GL/glut.h>
#include <Math.h>
#include <unistd.h>
#include <cmath>
#include <string>
#include <stdio.h>
#define PI 3.14159265f
typedef float GameCoordinates;
using namespace std;

char title[] = "TicTac";
int windowWidth  = 500;
int windowHeight = 500;
int windowPosX   = 50;
int windowPosY   = 50;

int refreshMillis = 30;
GLdouble xMaxNegative, xMaxPositive, yMaxNegative, yMaxPositive;
bool draw = false;

void initGL() {
   glClearColor(0.0, 0.0, 0.0, 1.0);
}

void drawLines(float x1, float y1,float x2, float y2) {
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glPopMatrix();
}

void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
}

class Matrix{
    private:
        int A[3][3];
    public:
        void DrawMatrix(){
            glPushMatrix();
            drawLines(-0.2,-0.5,-0.2,0.5);
            drawLines(0.2,-0.5,0.2,0.5);
            drawLines(-0.5,0.2,0.5,0.2);
            drawLines(-0.5,-0.2,0.5,-0.2);
            glPopMatrix();
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    A[i][j]=0;
                }
            }
        }
        void DrawX(float x, float y){
            glPushMatrix();
            glColor3f(0.14,0.67,0.98);
            drawLines(x,y,x+0.1,y+0.1);
            drawLines(x,y+0.1,x+0.1,y);
            glPopMatrix();
        }
        void DrawO(float X, float Y){
            glPushMatrix();
            DrawCircle(X,Y,0.5,10000);
            glPopMatrix();
        }
}M;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    M.DrawMatrix();
    if(draw==true){
        M.DrawX(0,0);
        glColor3f(1,1,1);
    }
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height) {
        xMaxNegative   = -1.0 * aspect;
        xMaxPositive  = 1.0 * aspect;
        yMaxNegative = -1.0;
        yMaxPositive    = 1.0;
    } else {
        xMaxNegative   = -1.0;
        xMaxPositive  = 1.0;
        yMaxNegative = -1.0 / aspect;
        yMaxPositive    = 1.0 / aspect;
    }
    gluOrtho2D(xMaxNegative, xMaxPositive, yMaxNegative, yMaxPositive);
}

void Timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(refreshMillis, Timer, 0);
}

iswithinthisblock(float x, float y){
    if(x<-0.2){
        return true;
    }
    else{
        return false;
    }
}
void MouseFunc(int button, int state, int x, int y)
{
    float X = (float) x / (windowWidth/2) - 1.0;
    float Y = (float) (windowHeight-y) / (windowHeight/2) - 1.0;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && iswithinthisblock(X,Y))
    {
        draw = true;
    }
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE);
   glutInitWindowSize(windowWidth, windowHeight);
   glutInitWindowPosition(windowPosX, windowPosY);
   glutCreateWindow(title);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutTimerFunc(0, Timer, 0);
   glutMouseFunc(MouseFunc);
   initGL();
   glutMainLoop();
   return 0;
}
