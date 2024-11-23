#include <GL/freeglut.h>
#include <math.h>
#include <vector>
using namespace std;
int winWidth=600,winHeight=600;
struct Vertex{
	GLfloat x,y;
};
vector<Vertex> V[3][7];//�ֱ��¼3���߸���6�ε��������ݣ�0��1��2��3��4��5��6��
int num=0;//��¼��������
//�û���ʼ������
void Initial(void)
{
	//���������Ļ����ɫ
	glClearColor(1.0f,1.0f,1.0f,1.0f);
	Vertex Start[3],End[3];//��ʼԪ�������Σ��������˵㣨ÿ�������������غϵģ�
	Start[0].x=100.0;
	Start[0].y=200.0;
	End[0].x=500;
	End[0].y=200;
	Start[1].x=End[0].x;
	Start[1].y=End[0].y;
	End[1].x=300;
	End[1].y=200+200*sqrt(3);
	Start[2].x=End[1].x;
	Start[2].y=End[1].y;
	End[2].x=Start[0].x;
	End[2].y=Start[0].y;
	//����ε�����û������
	for(int i=0;i<3;i++){
		V[i][0].push_back(Start[i]);
		V[i][0].push_back(End[i]);
	}

}
void ChangeSize(int w,int h)
{
    winWidth=w; winHeight=h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,winWidth,0.0,winHeight);
}
//���㵱ǰ���������µĸ���������
void compute()
{
	static int tmp=0;//��¼�ϴλ���ʱ��������
	int flag=0;//��¼���������Ƿ񱻸��¹�
	if(tmp<num){
		int len=V[0][num-1].size();
		for(int j=0;j<3;j++){
			for(int i=0;i<len-1;i++){
				V[j][num].push_back(V[j][num-1][i]);
				Vertex tmp;
				tmp.x=V[j][num-1][i].x+(V[j][num-1][i+1].x-V[j][num-1][i].x)/3;
				tmp.y=V[j][num-1][i].y+(V[j][num-1][i+1].y-V[j][num-1][i].y)/3;
				V[j][num].push_back(tmp);
				tmp.x=(V[j][num-1][i].x+V[j][num-1][i+1].x)/2-(V[j][num-1][i].y-V[j][num-1][i+1].y)*sqrt(3.0)/6;
				tmp.y=(V[j][num-1][i].y+V[j][num-1][i+1].y)/2-(V[j][num-1][i+1].x-V[j][num-1][i].x)*sqrt(3.0)/6;
				V[j][num].push_back(tmp);
				tmp.x=V[j][num-1][i].x+2*(V[j][num-1][i+1].x-V[j][num-1][i].x)/3;
				tmp.y=V[j][num-1][i].y+2*(V[j][num-1][i+1].y-V[j][num-1][i].y)/3;
				V[j][num].push_back(tmp);
			}
			V[j][num].push_back(V[j][num-1][len-1]);
		}
		tmp=num;
	}
}
//ÿ��OpenGL�����������������û�Ӧ�ð���ʾ����������������
void Display(void)
{
	//�����Ļ����
    glClear(GL_COLOR_BUFFER_BIT);
	compute();
	//��ʼ����
	glColor3f(1.0f,0.0f,0.0f);
	for(int j=0;j<3;j++){
		glBegin(GL_LINE_STRIP);
		for(int i=0;i<V[j][num].size();i++){
			glVertex2f(V[j][num][i].x,V[j][num][i].y);
		}
		glEnd();
	}
	//����ǰ�󻺳���
	glutSwapBuffers();
}
void Key(unsigned char key,int x,int y)
{
	switch(key) {
		case 97:	//��a���ӵ�������
			if(num<6){
				num++;
			}
			break;
		case 100:	//��d���ٵ�������
			if(num>0){
				num--;
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
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); //��ʼ�����ڵ���ʾģʽ
    glutInitWindowSize(600,600); //���ô��ڵĳߴ�
    glutInitWindowPosition(100,100); //���ô��ڵ�λ��
    glutCreateWindow("��껲�21013134��6����ҵ");//��������
    glutKeyboardFunc(Key);
    glutDisplayFunc(Display);
    glutReshapeFunc(ChangeSize);
    Initial(); //��ɴ��ڳ�ʼ��
    glutMainLoop(); //������GLUT�¼�����ѭ��
    return 0;
}


