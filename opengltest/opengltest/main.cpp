#include <windows.h>
#include <GL/glut.h>
#include <GL/GLU.h>

static float angle = 0;

void renderScene(){
	glClear(GL_COLOR_BUFFER_BIT); //����ɫ����
	glClear(GL_DEPTH_BUFFER_BIT);	//��zbuffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glRotatef(15, 1, 0, 0);//�����pitch
	glTranslatef(0, -10, -30);//���������̧��	

	glPushMatrix();//��������ϵ�л�����
		glRotatef(angle / 3, 0, 1, 0);//����ת
		glTranslatef(15, 0, 0);	//�������뾶
		
			glPushMatrix();//����ת����ϵ�»�����
				glRotatef(angle*3, 0, 1, 0);////����ת
				glTranslatef(6, 0, 0);//�������뾶
				glRotatef(123, 1, 2, 3);//�������
				glutWireTeapot(1);//����
			glPopMatrix();//�ص�����ת����ϵ

		glRotatef(-angle / 3, 0, 1, 0);//��������ת
		glRotatef(angle * 2, 1, 0, 0);//������ת			
		glutWireTeapot(2);//����
	glPopMatrix();//�ص���������ϵ
	glRotatef(angle/10, 0, 1, 0);	//̫����ת
	glutWireTeapot(3);//̫��
	
	//glFlush();
	glutSwapBuffers(); //��������
	angle += 0.1;
}

void windowResize(int w,int h) {
	if (h == 0) h = 1;
	float aspect = (float)w / h;	
	//��ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,aspect,1,1000);

	//���ӿڴ�С
	glViewport(0, 0, w, h);
}

void setupRC(){
	glClearColor( 0.1f, 0.1f, 0.1f, 1.0f); //���ñ���ɫ
	glEnable(GL_DEPTH_TEST);
}

int main() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 576);
	glutCreateWindow("OpenGLTest"); //��������
	glutDisplayFunc(renderScene);//����ʾ�ص�����
	glutIdleFunc(renderScene);//��ͣ����Ⱦ
	glutReshapeFunc(windowResize);//�贰�ڳߴ�ı�ص�����
	
	setupRC();//��ʼ��
	
	glutMainLoop();//GLUT��ѭ��
	
	return 0;
}