#include <gl/glut.h>
void Initial()
{
	glEnable(GL_DEPTH_TEST);       // ������Ȳ���
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );	//����Ϊ��ɫ
}

void ChangeSize(int w, int h)
{
	if(h == 0)	h = 1;
    glViewport(0, 0, w, h);               // ���������ߴ�
	glMatrixMode(GL_PROJECTION);    // ָ����ǰ����ͶӰ�����ջ
	glLoadIdentity();                   // ����ͶӰ����

	GLfloat fAspect;
	fAspect = (float)w/(float)h;            // ���������Ŀ�߱�
	gluPerspective(45.0, fAspect, 1.0, 500.0); // ָ��͸��ͶӰ�Ĺ۲�ռ�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Display(void)
{
	static float fElect1 = 0.0f; // ������̫����ת�ĽǶ�
    static float fElect2 = 0.0f; // �����Ƶ�����ת�ĽǶ�

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �����ɫ����Ȼ�����

    glMatrixMode(GL_MODELVIEW); // ָ����ǰ����ģ����ͼ�����ջ
    glLoadIdentity();           // ����ģ����ͼ����
    glTranslatef(0.0f, 0.0f, -250.0f); // ��ͼ����z�Ḻ���ƶ�

    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(20.0f, 15, 15); // ���ƺ�ɫ��̫��

    glPushMatrix(); // ���浱ǰ��ģ����ͼ����
    glRotatef(fElect1, 0.0f, 0.0f, 1.0f); // ��y����ת����ĽǶ�
    glTranslatef(90.0f, 0.0f, 0.0f); // ƽ��һ�ξ���
    glPushMatrix(); // ���浱ǰ��ģ����ͼ����

    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidSphere(10.0f, 15, 15); // ���Ƶ���
    glPopMatrix(); // �ָ�ģ����ͼ����

    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef(fElect2, 0.0f, 0.0f, 1.0f); // ��y����ת�����ĽǶ�
    glTranslatef(30.0f, 0.0f, 0.0f); // ƽ��һ�ξ���
    glutSolidSphere(5.0f, 15, 15); // ��������
    glPopMatrix(); // �ָ�ģ����ͼ����



    fElect1 += 10.0f; // ���ӵ������ת�Ƕȣ���������Ч��
    fElect2 += 10.0f; // ������������ת�Ƕȣ���������Ч��
    if (fElect1 > 360.0f) fElect1 = 10.0f;
    if (fElect2 > 360.0f) fElect2 = 10.0f;

    glutSwapBuffers();
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("̫�������������˶�ģ��");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(Display);
    glutTimerFunc(500, TimerFunc, 1);     //ָ����ʱ���ص�����
	Initial();
	glutMainLoop();
	return 0;
}
