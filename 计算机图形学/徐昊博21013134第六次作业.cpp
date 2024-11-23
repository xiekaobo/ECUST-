#include<gl/glut.h>
#include<math.h>
#include <vector>
using namespace std;
int winWidth=600,winHeight=600;
struct Vertex{
	GLfloat x,y;
};
vector<Vertex> V[7];//6�������ֱ��¼6�ε��������ݣ�0��1��2��3��4��5��6��
int num=0;
void Initial(void)
{
	glClearColor(1.0f,1.0f,1.0f,1.0f);
	Vertex Start,End;
	Start.x=100.0;
	Start.y=300.0;
	End.x=500.0;
	End.y=300.0;
	V[0].push_back(Start);
	V[0].push_back(End);
}
void ChangeSize(int w,int h)
{
    winWidth=w; winHeight=h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,winWidth,0.0,winHeight);
}
void compute()
{
	static int tmp=0;//��¼�ϴλ���ʱ��������
	int flag=0;//��¼���������Ƿ񱻸��¹�
	if(tmp<num){
		int len=V[num-1].size();
		for(int i=0;i<len-1;i++){
			V[num].push_back(V[num-1][i]);
			Vertex tmp;
			tmp.x=V[num-1][i].x+(V[num-1][i+1].x-V[num-1][i].x)/3;
			tmp.y=V[num-1][i].y+(V[num-1][i+1].y-V[num-1][i].y)/3;
			V[num].push_back(tmp);
			tmp.x=(V[num-1][i].x+V[num-1][i+1].x)/2+(V[num-1][i].y-V[num-1][i+1].y)*sqrt(3.0)/6;
			tmp.y=(V[num-1][i].y+V[num-1][i+1].y)/2+(V[num-1][i+1].x-V[num-1][i].x)*sqrt(3.0)/6;
			V[num].push_back(tmp);
			tmp.x=V[num-1][i].x+2*(V[num-1][i+1].x-V[num-1][i].x)/3;
			tmp.y=V[num-1][i].y+2*(V[num-1][i+1].y-V[num-1][i].y)/3;
			V[num].push_back(tmp);
		}
		V[num].push_back(V[num-1][len-1]);
		tmp=num;
	}
}
void Display(void)
{
	//�����Ļ����
    glClear(GL_COLOR_BUFFER_BIT);
	compute();
	glColor3f(1.0f,0.0f,0.0f);
	glBegin(GL_LINE_STRIP);
		for(int i=0;i<V[num].size();i++){
			glVertex2f(V[num][i].x,V[num][i].y);
		}
	glEnd();
	glutSwapBuffers();
}
void Key(unsigned char key,int x,int y)
{
	switch(key) {
		case 'a':	//��a���ӵ�������
			if(num<6)
            {
            num++;
            }
			break;
		case 'b':	//��d���ٵ�������
			if(num>0)
            {
				num--;
			}
			break;
	}
	glutPostRedisplay();
}
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
