#include<iostream>
#include<vector>
#include<windows.h>
#include<GL/glut.h>
using namespace std;
#include "setLookAt.h"
#include "getAxis.h"
#include "getTetrahedron.h"
GLuint objectID,axisID;//���������ID��������ID��
int winWidth = 400, winHeight = 200; //���ڵĿ�Ⱥ͸߶�
static float angle = 45.0;		//angle�����������ת��
static GLfloat xRot = 0.0f;  //��ת����
static GLfloat yRot = 0.0f;  //��ת����
static GLfloat zRot = 0.0f;  //��ת����
static GLsizei iMode = 1;		//�˵�ֵ
static point3D s_eye(5.0,5.0,5.0); //�۲��λ��
static point3D s_at(0.0,0.0,0.0);  //�ӵ�����
static point3D A(2.0f,0.0f,0.0),B(2.0f,1.0f,0.0),C(0.0f,1.0f,0.0),D(1.0f,1.0f,1.0);//��ͼ7-41
void initial(void)
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}
void triangle (GLsizei mode)
{
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT ,vp); //������������½����ꡢ��Ⱥ͸߶���Ϣ
    int w = vp[2], h = vp[3];
    float aspect;
    if(w < h)
    {
        aspect = (float)w/(float)h;
    }
    else
    {
        aspect = (float)h/(float)w;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(mode==1)
    {
        setLookAt(iMode,s_eye,s_at);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-5.0,5.0,-5.0,5.0,-5,5);
        objectID=getTetrahedron(A, B, C, D);
        axisID=getAxis(3.0);
        glCallList(objectID);
        glCallList(axisID);
    }
    else if(mode==2)
    {
        setLookAt(xRot,yRot,zRot,s_eye,s_at);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45,aspect,-5,5);
        objectID=getTetrahedron(A, B, C, D);
        axisID=getAxis(3.0);
        glCallList(objectID);
        glCallList(axisID);
    }
}
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glViewport(0, 0, 200, 200);  // ������
    triangle(1);
    glViewport(200, 0, 200, 200);  // ������
    triangle(2);
    glutSwapBuffers();
}
void ChangeSize(int w,int h)
{
    winWidth=w; winHeight=h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,winWidth,0.0,winHeight);
}
void ProcessMenu(int value)
{
    iMode=value;
    glutPostRedisplay();
}
void Key(unsigned char key,int x,int y)
{
    if(key=='x')
    {
        xRot+=1;
    }
    if(key=='y')
    {
        yRot+=1;
    }
    if(key=='z')
    {
        zRot+=1;
    }
    glutPostRedisplay();//ˢ��
}
void SpecialKeys(int key,int x,int y)
{
    if(key == GLUT_KEY_UP)
    {
        angle = angle+2;
    }
    else if(key == GLUT_KEY_DOWN)
    {
        angle = angle-2;
    }
    glutPostRedisplay();//ˢ��
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE  | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("��껲�21013134��������չʵ��");
    int nGlutPolyMenu = glutCreateMenu(ProcessMenu);//�����˵�������˵��ص�����
    glutAddMenuEntry("front view XOZ(V)",1);
    glutAddMenuEntry("vertical view XOY(H)",2);
    glutAddMenuEntry("side view YOZ(W)",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);//���˵�������Ҽ�����
    initial();
    glutDisplayFunc(Display);		//ָ�������ػ���Ӧ����
    glutReshapeFunc(ChangeSize);    //ָ�����ڴ�С�ı���Ӧ����
    glutKeyboardFunc(Key);        //ָ��������Ӧ����
    glutSpecialFunc(SpecialKeys);   //ָ�����ܼ���Ӧ����
    glutMainLoop();
    return 0;
}

