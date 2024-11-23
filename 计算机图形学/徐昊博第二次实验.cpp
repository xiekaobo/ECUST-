#include<gl/glut.h>
#include <vector>
#include "lineClipping.h"
using namespace std;
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
int iPointNum=0,iKeyPointNum=0;
int x1=0,x2=0,y1=0,y2=0,p1=0,q1=0,p2=0,q2=0,a;
int winWidth=600,winHeight=600;
int draw=0,done=0;
vector <point> LINE;
std::vector<point>::iterator it;
rect winObj;
/***********************************************
*���p����<0�����㡢����umax����֤umax�����uֵ
*���p����>0�����㡢����umin����֤umin����Сuֵ
*���umax>umin������0�����򷵻�1
***********************************************/
int Clip_Top(float p,float q,float &umax,float &umin){
	float r=0.0;
    if(p<0.0)	//�߶δӲü������ⲿ���쵽�ڲ���ȡ���ֵr������umax
	{
		r=q/p;
		if (r>umin) return 0;	//umax>umin���������֮
		else if (r>umax)  umax=r;
	}
	else if(p>0.0)      //�߶δӲü������ڲ����쵽�ⲿ,ȡ��Сֵr������umin
		{
			r=q/p;
			if (r<umax) return 0;	//umax>umin���������֮
			else if(r<umin)  umin=r;
		}
	   else 		//p=0ʱ���߶�ƽ���ڲü�����
	      if(q<0.0) return 0;
	 return 1;
}
/*************************************************************
*��֪winRect�����ζ��󣬴�ű�׼�ü�����4������Ϣ
*    points����Ķ�̬���飬���ֱ��2���˵���Ϣ
*���ݲü����ڵ����ұ߽磬��umax��
*���ݲü����ڵ��¡��ϱ߽磬��umin
*���umax>umin���ü����ں�ֱ���޽��㣬������ü���ֱ���¶˵�
***************************************************************/
void Line_Clipping(vector<point> &points,rect & winRect){
	//�Ƚ����ұ߽磬�������umax
    for (it = points.begin(); std::next(it) != points.end(); ++it)
    {
	point &p1=*it,&p2=*std::next(it);
	float dx=p2.x-p1.x,dy=p2.y-p1.y,umax=0.0,umin=1.0;
	point p=p1;
	if (Clip_Top(-dx,p1.x- winRect.w_xmin,umax,umin))  //��߽�
		if (Clip_Top(dx,winRect.w_xmax-p1.x, umax,umin)) //�ұ߽�
			//�Ƚ��¡��ϱ߽磬�����С��umin
			if (Clip_Top(-dy,p1.y- winRect.w_ymin, umax,umin)) //�±߽�
				if (Clip_Top(dy,winRect.w_ymax-p1.y, umax,umin)) //�ϱ߽�
				{//��ü���ֱ���¶˵�
					p1.x=(int)(p.x+umax*dx);
					p1.y=(int)(p.y+umax*dy);
					p2.x=(int)(p.x+umin*dx);
					p2.y=(int)(p.y+umin*dy);
				}
    }
}
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
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.0f,0.0f);
    if(iPointNum>=1)
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
        glEnd();
    }
    if(iKeyPointNum>=1)
    {
        if(draw==1)
        {
            glBegin(GL_LINES);
            for (it = LINE.begin(); it != LINE.end(); std::advance(it, 2))
            {
            glVertex2i(it->x, it->y);
            std::advance(it, 1);
            glVertex2i(it->x, it->y);
            }
            glEnd();
            draw=0;
        }
        else
        {
            glBegin(GL_LINES);
            for (it = LINE.begin(); it != LINE.end(); std::advance(it, 2))
            {
            glVertex2i(it->x, it->y);
            std::advance(it, 1);
            glVertex2i(it->x, it->y);
            }
            glEnd();
        }

    }
    glutSwapBuffers();
}

void Key(unsigned char key, int x, int y)
{
	switch(key){
    case 'p':
        if(done!=0)
        {
            iKeyPointNum = 1;
            p1 = x;	q1 = winHeight - y;
            point n(p1,q1);
            LINE.push_back(n);
        }
        glutPostRedisplay();
        break;
    case 'c':
        draw=1;
        Line_Clipping(LINE,winObj);
        break;
    case 'e':
        done = 1;
		glutPostRedisplay();
		break;
    default: break;
    	}
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
            winObj.w_xmin=MIN(x1,x2);
            winObj.w_xmax=MAX(x1,x2);
            winObj.w_ymin=MIN(y1,y2);
            winObj.w_ymax=MAX(y1,y2);
            glutPostRedisplay();
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
        x2=xMouse;
        y2=winHeight-yMouse;
        glutPostRedisplay();
    }
    if(done!=0)
    {
        p1 = xMouse;	q1 = winHeight - yMouse;
        point n(p1,q1);
        LINE.push_back(n);
        glutPostRedisplay();
    }
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); //��ʼ�����ڵ���ʾģʽ
    glutInitWindowSize(600,600); //���ô��ڵĳߴ�
    glutInitWindowPosition(100,100); //���ô��ڵ�λ��
    glutCreateWindow("��껲�21013134�ڶ���ʵ��");//��������
    glutDisplayFunc(Display);
    glutReshapeFunc(ChangeSize);
    glutMouseFunc(MousePlot);
    glutKeyboardFunc(Key);
    glutPassiveMotionFunc(PassiveMouseMove);
    Initial(); //��ɴ��ڳ�ʼ��
    glutMainLoop(); //������GLUT�¼�����ѭ��
    return 0;
}
