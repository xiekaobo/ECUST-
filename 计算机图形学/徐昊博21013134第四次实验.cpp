#include <vector>
using namespace std;
#include <GL/glut.h>
#include "graphicType.h"
//��������
vector <point> pointVertex;   //���ƶ���ζ�������
point temp,mouse;   //���ƶ���ζ�������
bool isEnd=false;			  //��ʶ���ƶ�����Ƿ�ȷ��
const GLint ControlN=4;       //��4�����Ƶ㶨������bezier���߶�
color redColor(1,0,0),blackColor(0,0,0);//��ɫ����ɫ
int x,y,p;
int winWidth = 600, winHeight = 600;
static GLsizei iMode=1;
void drawPolygonalLine(vector<point> &points,color &c ){
    //���ݵ�������������points����������
	glColor3f(c.r, c.g, c.b);
	glBegin (GL_LINE_STRIP);
		for(int i=0;i<points.size();i++){
			glVertex2i(points[i].x, points[i].y);
		}
	glEnd();
}
//��������
void drawPolygonalLine(vector<point> &points ,point &p,color &c){
    //���ݵ�������������points����������
	glColor3f(c.r, c.g, c.b);
	glBegin (GL_LINE_STRIP);
		for(int i=0;i<points.size();i++){
			glVertex2i(points[i].x, points[i].y);
		}
		glVertex2i(p.x, p.y);
	glEnd();
}
//������Ƶ���n<4������һ��n-1��Bezier���߶Σ��������һ������Bezier����
void drawBezierCurve(vector<Point> &points,color &c){
	GLfloat ControlP[4][3];
	int iPointNum=points.size();
	int i;
	if(iPointNum<4){//���Ƶ���<4������һ��n-1��Bezier���߶�
		for(i=0;i<iPointNum;i++){
			ControlP[i][0]=points[i].x;
			ControlP[i][1]=points[i].y;
			ControlP[i][2]=0.0;
		}
	}
	else{
		for(i=0;i<4;i++){//���Ƶ���>=4������һ������Bezier���߶�
			ControlP[i][0]=points[i].x;
			ControlP[i][1]=points[i].y;
			ControlP[i][2]=0.0;
		}
	}
	glColor3f(c.r, c.g, c.b);
	glPointSize(2);
	if(iPointNum>4)
		glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,*ControlP);//����һάȡֵ��
	else
		glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,iPointNum,*ControlP);//����һάȡֵ��
	glEnable(GL_MAP1_VERTEX_3);
	glMapGrid1f(100,0.0,1.0);//���ɾ��ȷֲ���һά�������ֵ
	glEvalMesh1(GL_LINE, 0, 100);//����Bezier����
}
//ͨ����m��3+1�����Ƶ㣬����m��n-1��ezier���߶�
void drawBezierCurve(vector<Point> &points,int n,color &c)
{
    GLfloat ControlP[4][3];
	int iPointNum=points.size();
	int i,temp=0;
	while(temp<iPointNum)
    {
    if((iPointNum-temp)<4)
    {//���Ƶ���<4������һ��n-1��Bezier���߶�
        p=iPointNum-temp;
        for(i=0;i<p;i++)
        {
            ControlP[i][0]=points[temp].x;
            ControlP[i][1]=points[temp].y;
            ControlP[i][2]=0.0;
            temp++;
        }
        glColor3f(c.r, c.g, c.b);
        glPointSize(2);
        glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,p,*ControlP);
        glEnable(GL_MAP1_VERTEX_3);
        glMapGrid1f(100,0.0,1.0);//���ɾ��ȷֲ���һά�������ֵ
        glEvalMesh1(GL_LINE, 0, 100);//����Bezier����
    }
    if((iPointNum-temp)>=4)
    {
        for(i=0;i<4;i++)
        {//���Ƶ���>=4������һ������Bezier���߶�
            ControlP[i][0]=points[temp].x;
            ControlP[i][1]=points[temp].y;
            ControlP[i][2]=0.0;
            temp++;
        }
        glColor3f(c.r, c.g, c.b);
        glPointSize(2);
        glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,*ControlP);
        glEnable(GL_MAP1_VERTEX_3);
        glMapGrid1f(100,0.0,1.0);//���ɾ��ȷֲ���һά�������ֵ
        glEvalMesh1(GL_LINE, 0, 100);//����Bezier����
        temp--;
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
    if(isEnd==false&&iMode==4)
    {
        glLineStipple(1,0x00FF);
        glEnable(GL_LINE_STIPPLE);
        drawPolygonalLine(pointVertex,mouse,blackColor);
    }
    if(isEnd==true&&iMode==4)
    {
        drawPolygonalLine(pointVertex,mouse,blackColor);
        glDisable(GL_LINE_STIPPLE);
        drawBezierCurve(pointVertex,4,redColor);
    }
    glutSwapBuffers();
}
void MousePlot(GLint button, GLint action,GLint xMouse,GLint yMouse)
{
    if(button==GLUT_LEFT_BUTTON&&action==GLUT_DOWN&&iMode==4)
    {
        temp.x=xMouse;
        temp.y=winHeight-yMouse;
        pointVertex.push_back(temp);
    }
    if(button==GLUT_RIGHT_BUTTON&&action==GLUT_DOWN&&iMode==4)
    {
        isEnd=true;
    }
}
void PassiveMouseMove(GLint xMouse,GLint yMouse)
{
    if(isEnd==false)
    {
        mouse.x=xMouse;
        mouse.y=winHeight-yMouse;
        pointVertex.push_back(temp);
        glutPostRedisplay();
        pointVertex.pop_back();
    }
}
void ProcessMenu(int value)
{
    iMode=value;
    glutPostRedisplay();
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); //��ʼ�����ڵ���ʾģʽ
    glutInitWindowSize(600,600); //���ô��ڵĳߴ�
    glutInitWindowPosition(100,100); //���ô��ڵ�λ��
    glutCreateWindow("��껲�21013134���Ĵ�ʵ��");//��������
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("DrawBezier",4);
    glutAddMenuEntry("DrawBezier2",5);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
    glutDisplayFunc(Display);
    glutReshapeFunc(ChangeSize);
    glutMouseFunc(MousePlot);
    glutPassiveMotionFunc(PassiveMouseMove);
    Initial(); //��ɴ��ڳ�ʼ��
    glutMainLoop(); //������GLUT�¼�����ѭ��
    return 0;
}
