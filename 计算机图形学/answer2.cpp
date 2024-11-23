#include <gl/glut.h>
#include <stdio.h>
#include <vector>

using namespace std;
#include "lineClipping.h"

int iPointNum = 0, iKeyPointNum = 0;							//�Ѿ�ȷ���ĵ������
int xKey1 = 0, yKey1 = 0, xKey2 = 0, yKey2 = 0;					//��¼��ǰ���ߵ�
int m_x1 = 0, m_x2 = 0, m_y1 = 0, m_y2 = 0;						//��¼��ǰ���ε�
int winWidth = 400, winHeight = 300;							//��ʼ���ڴ�С
bool endDrow = false;											//�Ƿ������������
int ctimes = 0;													//�Ƿ������Liang_Barsky�㷨

vector<point> m_points;		//���ߵ�����
rect m_winRect;				//�ü���

/***********************************************
*���p����<0�����㡢����umax����֤umax�����uֵ
*���p����>0�����㡢����umin����֤umin����Сuֵ
*���umax>umin������0�����򷵻�1
***********************************************/
int Clip_Top(float p, float q, float& umax, float& umin) {
	float r = 0.0;
	if (p < 0.0)	//�߶δӲü������ⲿ���쵽�ڲ���ȡ���ֵr������umax
	{
		r = q / p;
		if (r > umin) return 0;	//umax>umin���������֮
		else if (r > umax)  umax = r;
	}
	else if (p > 0.0)      //�߶δӲü������ڲ����쵽�ⲿ,ȡ��Сֵr������umin
	{
		r = q / p;
		if (r < umax) return 0;	//umax>umin���������֮
		else if (r < umin)  umin = r;
	}
	else 		//p=0ʱ���߶�ƽ���ڲü�����
		if (q < 0.0) return 0;
	return 1;
}
/*************************************************************
*��֪winRect�����ζ��󣬴�ű�׼�ü�����4������Ϣ
*    points����Ķ�̬���飬���ֱ��2���˵���Ϣ
*���ݲü����ڵ����ұ߽磬��umax��
*���ݲü����ڵ��¡��ϱ߽磬��umin
*���umax>umin���ü����ں�ֱ���޽��㣬������ü���ֱ���¶˵�
***************************************************************/
void Line_Clipping(vector<point>& points, rect& winRect) {		//(���ߵ�����,�ü���)
	vector<point> new_points;								//�洢�ü����
	for (int i = 0; i < iKeyPointNum - 1; i++)
	{
		while (new_points.size() <= 2 * i + 2)
		{
			new_points.push_back((0, 0));
		}
		point& p1 = points[i], & p2 = points[i + 1];
		float dx = p2.x - p1.x, dy = p2.y - p1.y, umax = 0.0, umin = 1.0;
		point p = p1;
		//�Ƚ����ұ߽磬�������umax
		if (Clip_Top(-dx, p1.x - winRect.w_xmin, umax, umin))  //��߽�
			if (Clip_Top(dx, winRect.w_xmax - p1.x, umax, umin)) //�ұ߽�
				//�Ƚ��¡��ϱ߽磬�����С��umin
				if (Clip_Top(-dy, p1.y - winRect.w_ymin, umax, umin)) //�±߽�
					if (Clip_Top(dy, winRect.w_ymax - p1.y, umax, umin)) //�ϱ߽�
					{		//��ü���ֱ���¶˵�
						new_points[2 * i].x = (int)(p.x + umax * dx);
						new_points[2 * i].y = (int)(p.y + umax * dy);
						new_points[2 * i + 1].x = (int)(p.x + umin * dx);
						new_points[2 * i + 1].y = (int)(p.y + umin * dy);
					}
	}

	//�����ֵ��ԭVector
	for (int i = 0; i < new_points.size(); i++)
	{
		while (m_points.size() < new_points.size())
		{
			m_points.push_back((0, 0));
		}
		m_points[i] = new_points[i];
	}
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //�õ�ǰ����ɫ��䴰��
	glColor3f(1.0f, 0.0f, 0.0f); //���õ�ǰ�Ļ�ͼ��ɫΪ��ɫ

	//���ƾ��δ���
	if (iPointNum >= 1) {
		if (1) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(m_x1, m_y1, 0.0);
			glVertex3f(m_x2, m_y1, 0.0);
			glVertex3f(m_x2, m_y2, 0.0);
			glVertex3f(m_x1, m_y2, 0.0);
			glEnd();
		}
	}

	//�������߶�
	if (iKeyPointNum >= 1) {
		for (int i = 0; i < m_points.size() - 2; i++)
		{
			glBegin(GL_LINES);
			glVertex3f(m_points[i].x, m_points[i].y, 0.0);
			glVertex3f(m_points[i + 1].x, m_points[i + 1].y, 0.0);
			glEnd();
		}
		//��̬��ʾ��ǰ�������߶Σ�����������ִ���?��
		if (!endDrow) {
			glBegin(GL_LINES);
			glVertex3f(xKey1, yKey1, 0.0);
			glVertex3f(xKey2, yKey2, 0.0);
			glEnd();
		}
	}

	glutSwapBuffers();
}
void reStart() {
	endDrow = false;
	iKeyPointNum = 0;
	m_points.clear();
	m_points.push_back((0, 0));
	ctimes = 0;
}
void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if (iPointNum == 0 || iPointNum == 2) {
			iPointNum = 1;
			m_x1 = xMouse;
			m_y1 = winHeight - yMouse;
		}
		else
		{
			iPointNum = 2;
			m_x2 = xMouse;
			m_y2 = winHeight - yMouse;
			rect temp(min(m_x1, m_x2), min(m_y1, m_y2), max(m_x1, m_x2), max(m_y1, m_y2));		//�����ü���
			m_winRect = temp;
			glutPostRedisplay();
		}
		reStart();
		glutPostRedisplay();
	}
	if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
		iPointNum = 0;
		glutPostRedisplay();
	}
}


//��̬��ʾ��ǰ�߶�
void PassiveMouseMove(GLint xMouse, GLint yMouse) {
	//���Ʋü���
	if (iPointNum == 1) {
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
			m_x2 = xMouse;
			m_y2 = m_y1 + m_x2 - m_x1;
		}
		else {
			m_x2 = xMouse;
			m_y2 = winHeight - yMouse;
		}
		glutPostRedisplay();
	}

	//��������
	if (!endDrow) {
		xKey2 = xMouse;
		yKey2 = winHeight - yMouse;
		point temp = (xKey2, yKey2);
		m_points[iKeyPointNum] = temp;
		glutPostRedisplay();
	}
}

void Key(unsigned char key, int x, int y) {
	switch (key) {
	case'p':			//ȷ�����߶˵�
		if (!endDrow) {
			xKey1 = x;
			yKey1 = winHeight - y;
			//����˵�
			point temp(xKey1, yKey1);
			if (m_points.size() < iKeyPointNum + 2) {
				m_points.push_back(temp);
			}
			m_points[iKeyPointNum] = temp;
			iKeyPointNum++;
			glutPostRedisplay();
		}
		else {
			reStart();
		}
		break;
	case'c':			//ִ��Liang_Barsky�ü�
		if (endDrow && iPointNum == 2&& ctimes==0) {
			Line_Clipping(m_points, m_winRect);
			ctimes = 1;
			glutPostRedisplay();
		}
		else {
			reStart();
		}
		break;
	case'e':			//������������
		endDrow = true;
		glutPostRedisplay();
		break;
	default:break;
	}
}

void ChangeSize(int w, int h) {
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);					//����ͶӰ����(ָ��Ҫ���Ƶĵ�Ԫ)
	glLoadIdentity();								//���õ�λ����ȥ����ǰ��ͶӰ��������
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);		//����ͶӰ����
}

void Initial(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //���ô��ڱ�����ɫΪ��ɫ
	m_points.push_back((0, 0));
}

int min(int a, int b) {
	if (a > b) {
		return b;
	}
	else {
		return a;
	}
}

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);				//��ʼ�����ڵ���ʾģʽ
	glutInitWindowSize(winWidth, winHeight);					//���ô��ڵĳߴ�
	glutInitWindowPosition(100, 100);							//���ô��ڵ�λ��

	glutCreateWindow("��Ƥ���");

	glutDisplayFunc(Display);									//���õ�ǰ���ڵ���ʾ�ص�����
	glutReshapeFunc(ChangeSize);								//�����ڴ�С�ı�ʱ����������

	glutMouseFunc(MousePlot);
	glutKeyboardFunc(Key);
	glutPassiveMotionFunc(PassiveMouseMove);


	Initial();													//��ɴ��ڳ�ʼ��
	glutMainLoop();												//������GLUT�¼�����ѭ��
	return 0;
}
