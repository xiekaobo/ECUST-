#include <gl/glut.h>
void Initial(void)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}
void ChangeSize(int w,int h)
{
    if(h==0) h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat fAspect;
    fAspect=(float)w/(float)h;
    gluPerspective(45.0,fAspect,1.0,700.0);
    glMatrixMode(GL_MODELVIEW);
}
void Display(void)
{
    static float fElect1=0.0f;
    static float fElect2=0.0f;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //��̫��
    glTranslatef(0.0f,0.0f,-250.0f);
    glColor3f(1.0f,0.0f,0.0f);
    glutSolidSphere(24.0f,15,15);
    //������
    glPushMatrix();// ���浱ǰ��ģ����ͼ����
    glColor3f(0.0f,0.0f,1.0f);
    glRotatef(fElect1,0.0f,0.0f,1.0f);
    glTranslatef(90.0f,0.0f,0.0f);
    glutSolidSphere(10.0f,15,15);
    //������,ע���ʱ�����ָܻ������Ƶ���ǰ��ģ����ͼ���󣬷�������Ҳ������̫��ת
    glColor3f(1.0f,1.0f,0.0f);
    glRotatef(fElect2,0.0f,0.0f,1.0f);
    glTranslatef(30.0f,0.0f,0.0f);
    glutSolidSphere(6.0f,15,15);
    glPopMatrix();//�ָ������Ƶ���ǰ��ģ����ͼ����
    glPopMatrix();//�ָ�����ʼ��ģ����ͼ����

    fElect1+=1.0f;
    fElect2+=10.0f;
    if(fElect1>360.0f) fElect1=1.0f;
    if(fElect2>360.0f) fElect2=10.0f;
    glutSwapBuffers();
}
void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100,TimerFunc,1);
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH); //��ʼ�����ڵ���ʾģʽ
    glutCreateWindow("��껲�21013134̫����������ģ��"); //����һ����Ϊ���εĴ���
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(Display);
    glutTimerFunc(500,TimerFunc,1); //���õ�ǰ���ڵ���ʾ�ص�����
    Initial(); //��ɴ��ڳ�ʼ��
    glutMainLoop(); //������GLUT�¼�����ѭ��
    return 0;
}
