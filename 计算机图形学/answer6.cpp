#include <GL/freeglut.h>
#include <math.h>
#include <vector>
#define max_iteration_num 6
using namespace std;

struct Vertex{
	GLfloat x,y;
};
vector<Vertex> V[max_iteration_num+1];//6�������ֱ��¼6�ε��������ݣ�0��1��2��3��4��5��6��
int iteration_num=0;//��¼��������

//�û���ʼ������
void myinit(void)
{
	//���������Ļ����ɫ
	glClearColor(1.0f,1.0f,1.0f,1.0f);

	Vertex Start,End;//��ʼԪ��ֱ�߶Σ��������˵�
	//��ʼԪ��ֱ�߶Σ��������˵�
	Start.x=0.0;
	Start.y=400.0;
	End.x=800.0;
	End.y=400.0;
	//����ε�����û������
	V[0].push_back(Start);
	V[0].push_back(End);
}

//���ڴ�С�仯ʱ�Ļص�����
void myReshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0.0,800.0,0.0,800.0);
}
//���㵱ǰ���������µĸ���������
void compute()
{
	static int tmp=0;//��¼�ϴλ���ʱ��������
	int flag=0;//��¼���������Ƿ񱻸��¹�
	if(tmp<iteration_num){
		int len=V[iteration_num-1].size();
		for(int i=0;i<len-1;i++){
			V[iteration_num].push_back(V[iteration_num-1][i]);
			Vertex tmp;
			tmp.x=V[iteration_num-1][i].x+(V[iteration_num-1][i+1].x-V[iteration_num-1][i].x)/3;
			tmp.y=V[iteration_num-1][i].y+(V[iteration_num-1][i+1].y-V[iteration_num-1][i].y)/3;
			V[iteration_num].push_back(tmp);
			tmp.x=(V[iteration_num-1][i].x+V[iteration_num-1][i+1].x)/2+(V[iteration_num-1][i].y-V[iteration_num-1][i+1].y)*sqrt(3.0)/6;
			tmp.y=(V[iteration_num-1][i].y+V[iteration_num-1][i+1].y)/2+(V[iteration_num-1][i+1].x-V[iteration_num-1][i].x)*sqrt(3.0)/6;
			V[iteration_num].push_back(tmp);
			tmp.x=V[iteration_num-1][i].x+2*(V[iteration_num-1][i+1].x-V[iteration_num-1][i].x)/3;
			tmp.y=V[iteration_num-1][i].y+2*(V[iteration_num-1][i+1].y-V[iteration_num-1][i].y)/3;
			V[iteration_num].push_back(tmp);
		}
		V[iteration_num].push_back(V[iteration_num-1][len-1]);
		tmp=iteration_num;
	}
}
//ÿ��OpenGL�����������������û�Ӧ�ð���ʾ����������������
void display(void)
{
	//�����Ļ����
    glClear(GL_COLOR_BUFFER_BIT);
	compute();
	//��ʼ����
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_STRIP);
		for(int i=0;i<V[iteration_num].size();i++){
			glVertex2f(V[iteration_num][i].x,V[iteration_num][i].y);
		}
	glEnd();
	//����ǰ�󻺳���
	glutSwapBuffers();
}
void processNormalKeys(unsigned char key,int x,int y)
{
	switch(key) {
		case 97:	//��a���ӵ�������
			if(iteration_num<max_iteration_num){
				iteration_num++;
			}
			break;
		case 100:	//��d���ٵ�������
			if(iteration_num>0){
				iteration_num--;
			}
			break;
		case 27:	//"esc"
			exit(0);
	}
	glutPostRedisplay();
}

//������
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	//��ʼ��OPENGL��ʾ��ʽ
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	//�趨OPENGL����λ�úʹ�С
	glutInitWindowSize (800, 800);
	glutInitWindowPosition (100, 100);
	//�򿪴���
	glutCreateWindow ("kock����");
	//���ó�ʼ������
    myinit();
	//�趨���ڴ�С�仯�Ļص�����
	glutReshapeFunc(myReshape);
	//�趨���̿��ƵĻص�����
	glutKeyboardFunc(processNormalKeys);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}


