#include "onMidPointEllispe.h"
#include<gl/glut.h>
int Abs(int a)
{
    if(a<0)
    {
        return -a;
    }
    else return a;
}
int MAX(int a,int b)
{
    if(a>b) return a;
    else return b;
}
int MIN(int a,int b)
{
    if(a<b) return a;
    else return b;
}
int iPointNum=0;
int ellipse=0;
int x1=0,x2=0,y1=0,y2=0,x20,y20,a0,b0,a;
int winWidth=600,winHeight=600;
void Initial(void)
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}
void ChangeSize(int w,int h)
{
    winWidth=w; winHeight=h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,winWidth,0.0,winHeight);
}
void Display(void)
{
    if(ellipse==1)//�ڲ˵���
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f,0.0f,0.0f);
        if(iPointNum>=1)
        {
            if(iPointNum==1)
            {
                glBegin(GL_LINES);
                glVertex2i(x1,y1);
                glVertex2i(x2,y1);

                glVertex2i(x2,y1);
                glVertex2i(x2,y2);

                glVertex2i(x2,y2);
                glVertex2i(x1,y2);

                glVertex2i(x1,y2);
                glVertex2i(x1,y1);
                glEnd();//������Ӿ���
            }
        if(iPointNum==2||iPointNum==1)
        {
            glTranslated((x1+x2)/2,(y1+y2)/2,0);
            //ƽ����������ԭ��
            onMidPointEllispe(Abs(x1-x2)/2,Abs(y1-y2)/2);
            //���㳤���ᵼ�뺯��
            glTranslated(-(x1+x2)/2,-(y1+y2)/2,0);
            //ƽ�ƻ���������ԭ�㣬���»���
        }
        }
    glutSwapBuffers();
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glutSwapBuffers();
    }
}
/**************************************************
* ��֪��Բ�ĳ�����a,b
* ������Բ���е�Bresenham�㷨��ɨ��ת����Բ
* ��glBegin(GL_POINTS);glEnd();��ʽ��������Բ
***************************************************/
void  onMidPointEllispe(int a,int b){
	int x,y;
    float d1,d2;
	glBegin(GL_POINTS);
		x=0;y=b;
		d1=b*b+a*a*(-b+0.25);
		glVertex2i(x,y);
		glVertex2i(-x,-y);
		glVertex2i(-x,y);
		glVertex2i(x,-y);
		while(b*b*(x+1)<a*a*(y-0.5))
		{
			if(d1<=0){
				d1+=b*b*(2*x+3);
				x++;
			}
			else{
				d1+=b*b*(2*x+3)+a*a*(-2*y+2);
				x++; y--;
			}
			glVertex2f(x,y);
			glVertex2f(-x,-y);
			glVertex2f(-x,y);
			glVertex2f(x,-y);
		}/*while�ϰ벿��*/
		d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
		while(y>0)
		{
			if(d2<=0){
        		d2+=b*b*(2*x+2)+a*a*(-2*y+3);
				x++; y--;
			}
			else{
				d2+=a*a*(-2*y+3);
				y--;
			}
			glVertex2f(x,y);
			glVertex2f(-x,-y);
			glVertex2f(-x,y);
			glVertex2f(x,-y);
		}
	glEnd();
}

void menu(int value)//�˵�������
{
    switch(value)
    {
        case 1:
        {
            ellipse=1;
            iPointNum=0;
        }
    }
}
void createMenu()//�����˵���Ϊ�˵�ѡ��ָ��������
{
    glutCreateMenu(menu);
    glutAddMenuEntry("Draw Ellipse", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);//���˵��󶨵��Ҽ�
}

void MousePlot(GLint button, GLint action,GLint xMouse,GLint yMouse)
{
    if(button==GLUT_LEFT_BUTTON&&action==GLUT_DOWN)
    {
        if(iPointNum==0||iPointNum==2)
        {
            iPointNum=1;
            x1=xMouse;
            y1=winHeight-yMouse;
        }
        else if(iPointNum==1)
        {
            iPointNum=2;
            x2=xMouse;
            y2=winHeight-yMouse;
            glutPostRedisplay();
            if(glutGetModifiers() & GLUT_ACTIVE_SHIFT)
            {
                x20=xMouse;
                y20=winHeight-yMouse;
                a0=Abs(x20-x1);
                b0=Abs(y20-y1);
                a=MIN(a0,b0);
                if(x20>x1) x2=x1+a;
                else x2=x1-a;
                if(y20>y1) y2=y1+a;
                else y2=y1-a;
                glutPostRedisplay();
            }
        }
    }
    if(button==GLUT_RIGHT_BUTTON&&action==GLUT_DOWN)
    {
        iPointNum=0;
        glutPostRedisplay();
    }
}
void PassiveMouseMove(GLint xMouse,GLint yMouse)
{
    if(iPointNum==1)
    {
        if(glutGetModifiers() & GLUT_ACTIVE_SHIFT)
        {
            x20=xMouse;
            y20=winHeight-yMouse;
            a0=Abs(x20-x1);
            b0=Abs(y20-y1);
            a=MIN(a0,b0);
            if(x20>x1) x2=x1+a;
            else x2=x1-a;
            if(y20>y1) y2=y1+a;
            else y2=y1-a;
            glutPostRedisplay();
        }
        else
        {
            x2=xMouse;
            y2=winHeight-yMouse;
            glutPostRedisplay();
        }
    }
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); //��ʼ�����ڵ���ʾģʽ
    glutInitWindowSize(600,600); //���ô��ڵĳߴ�
    glutInitWindowPosition(100,100); //���ô��ڵ�λ��
    glutCreateWindow("��껲�21013134��һ��ʵ��");//��������
    glutDisplayFunc(Display);
    glutReshapeFunc(ChangeSize);
    glutMouseFunc(MousePlot);
    glutPassiveMotionFunc(PassiveMouseMove);
    createMenu();
    Initial(); //��ɴ��ڳ�ʼ��
    glutMainLoop(); //������GLUT�¼�����ѭ��
    return 0;
}
