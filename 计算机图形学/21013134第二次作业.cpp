#include <gl/glut.h>
void Initial(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //���ô��ڱ�����ɫΪ��ɫ
    glMatrixMode(GL_PROJECTION); //����ͶӰ����
    gluOrtho2D(0.0,1200.0,0.0,400.0);
}
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //�õ�ǰ����ɫ��䴰��
    glColor3f(0.0f, 0.0f, 0.0f); //���õ�ǰ�Ļ�ͼ��ɫΪ��ɫ
    glLineWidth(3.0);
    //���ơ��족
    glBegin(GL_LINE_STRIP);
    glVertex2i(25,250);
    glVertex2i(100,325);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(25,175);
    glVertex2i(100,250);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(75,50);
    glVertex2i(75,225);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(75,50);
    glVertex2i(75,225);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(125,225);
    glVertex2i(225,350);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(225,350);
    glVertex2i(325,225);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(175,250);
    glVertex2i(275,250);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(150,175);
    glVertex2i(300,175);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(225,50);
    glVertex2i(175,75);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(150,100);
    glVertex2i(200,150);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(250,150);
    glVertex2i(300,100);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(225,250);
    glVertex2i(225,50);
    glEnd();
    //���ơ�껡�
    glBegin(GL_LINE_STRIP);
    glVertex2i(500,350);
    glVertex2i(700,350);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(500,300);
    glVertex2i(700,300);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(500,250);
    glVertex2i(700,250);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(500,250);
    glVertex2i(500,350);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(700,250);
    glVertex2i(700,350);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(500,200);
    glVertex2i(700,200);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(450,150);
    glVertex2i(750,150);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(600,150);
    glVertex2i(600,200);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(600,150);
    glVertex2i(550,75);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(550,75);
    glVertex2i(475,50);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(600,150);
    glVertex2i(650,75);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(650,75);
    glVertex2i(725,50);
    glEnd();

    //���ơ�����
    glBegin(GL_LINE_STRIP);
    glVertex2i(850,250);
    glVertex2i(950,250);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(900,50);
    glVertex2i(900,350);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(975,325);
    glVertex2i(1125,325);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1075,375);
    glVertex2i(1100,350);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1050,350);
    glVertex2i(1050,175);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(975,300);
    glVertex2i(975,175);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1125,300);
    glVertex2i(1125,175);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(975,300);
    glVertex2i(1125,300);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1100,200);
    glVertex2i(1125,175);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1000,275);
    glVertex2i(1100,275);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1000,225);
    glVertex2i(1100,225);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(950,150);
    glVertex2i(1125,150);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1075,175);
    glVertex2i(1075,50);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1025,75);
    glVertex2i(1075,50);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1025,125);
    glVertex2i(1050,100);
    glEnd();
    glFlush(); //�������е�OpenGL����
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //��ʼ�����ڵ���ʾģʽ
    glutInitWindowSize(1200,400); //���ô��ڵĳߴ�
    glutInitWindowPosition(0,120); //���ô��ڵ�λ��
    glutCreateWindow("��껲�21013134"); //����һ����Ϊ���εĴ���
    glutDisplayFunc(Display); //���õ�ǰ���ڵ���ʾ�ص�����
    Initial(); //��ɴ��ڳ�ʼ��
    glutMainLoop(); //������GLUT�¼�����ѭ��
    return 0;
}
