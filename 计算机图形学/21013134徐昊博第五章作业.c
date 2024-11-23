#include<gl/glut.h>
void Initial(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //���ô��ڱ�����ɫΪ��ɫ
    glMatrixMode(GL_PROJECTION); //����ͶӰ����
    gluOrtho2D(0.0,400.0,0.0,400.0);
}
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //�õ�ǰ����ɫ��䴰��
    glColor3f(0.0f, 0.0f, 0.0f); //���õ�ǰ�Ļ�ͼ��ɫΪ��ɫ
    glBegin(GL_POINTS);
    float x=0,y;
    while(x<=400)
    {
        y=300+50*sin(x/50);
        glVertex2f(x,y);
        x=x+0.5;
    }
    glEnd();
    glBegin(GL_POINTS);
    x=0;
    while(x<=400)
    {
        y=150+50*cos(x/50);
        glVertex2f(x,y);
        x=x+0.5;
    }
    glEnd();
    float x1=0,y1,x2=0,y2;
    glBegin(GL_LINE_STRIP);
    while(x2<=400)
    {
        y1=250+50*sin(x1/50);
        x2=x1+0.5;
        y2=250+50*sin(x2/50);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        x1+=0.5;
    }
    glEnd();
    x1=0;
    x2=0;
    glBegin(GL_LINE_STRIP);
    while(x2<=400)
    {
        y1=100+50*cos(x1/50);
        x2=x1+0.5;
        y2=100+50*cos(x2/50);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        x1+=0.5;
    }
    glEnd();
    glFlush();
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //��ʼ�����ڵ���ʾģʽ
    glutInitWindowSize(400,400); //���ô��ڵĳߴ�
    glutInitWindowPosition(0,120); //���ô��ڵ�λ��
    glutCreateWindow("����ģʽ�µ���������ͼ�����ϵ�������Ϊ���ҵ�ģʽ����������ģʽ�����ҵ�ģʽ����������ģʽ"); //��������
    glutDisplayFunc(Display);
    Initial(); //��ɴ��ڳ�ʼ��
    glutMainLoop(); //������GLUT�¼�����ѭ��
    return 0;
}
