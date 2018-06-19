#include <GL/glut.h>
#include <GL/GLU.h>
#include "SOIL.h"
#include <cstdlib>

static float angle = 0;

//光源坐标
static float z = 330;
static float x = -20;
static float y = 60;

//金字塔旋转角度
static float crotate = 0;

//摄像机旋转
static float pitch = 0;
static float yaw = 0;

//画包围盒
void drawBox(float distance) {
	float d = distance;

	glBegin(GL_QUADS);

	glNormal3f(0,0,-1);
	glVertex3f(d, d, d);
	glVertex3f(-d, d, d);
	glVertex3f(-d, -d, d);
	glVertex3f(d, -d, d);	

	glNormal3f(0, 0, 1);
	glVertex3f(d, d, -d);
	glVertex3f(-d, d, -d);
	glVertex3f(-d, -d, -d);
	glVertex3f(d, -d, -d);

	glNormal3f(0, -1, 0);
	glVertex3f(d, d, d);
	glVertex3f(d, d, -d);
	glVertex3f(-d, d, -d);
	glVertex3f(-d, d, d);

	glNormal3f(0, 1, 0);
	glVertex3f(d, -d, d);
	glVertex3f(d, -d, -d);
	glVertex3f(-d, -d, -d);
	glVertex3f(-d, -d, d);

	glNormal3f(-1, 0, 0);
	glVertex3f(d, d, d);
	glVertex3f(d, d, -d);
	glVertex3f(d, -d, -d);
	glVertex3f(d, -d, d);

	glNormal3f(1, 0, 0);
	glVertex3f(-d, d, d);
	glVertex3f(-d, d, -d);
	glVertex3f(-d, -d, -d);
	glVertex3f(-d, -d, d);

	glEnd();
}

void renderScene(){
	glClear(GL_COLOR_BUFFER_BIT); //清颜色缓冲
	glClear(GL_DEPTH_BUFFER_BIT);	//清zbuffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//摄像机位置		
	glTranslatef(0, 0, -800);
	glRotatef(pitch, 1, 0, 0);
	glRotatef(yaw, 0, 1, 0);
	
	//包围盒
	GLfloat a[] = { 0.1f, 0.1f, 0.1f, 1.0f };  //定义材质的环境光颜色 
	GLfloat d[] = { 0.5f, 0.5f, 0.5f, 1.0f };  //定义材质的漫反射光颜色
	GLfloat s[] = { 0.5f, 0.5f, 1.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat e[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的自发光颜色，为0  
	GLfloat shine = 30.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, e);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

	glColor3f(0.3,0.3,0.3);
	drawBox(800);
	
	glPushMatrix();//圆
		glTranslatef(150, 150, 200);
		glColor3f(0.8, 0, 0.8);
		GLfloat a1[] = { 0.21f, 0.21f, 0.21f, 1.0f };  //定义材质的环境光颜色 
		GLfloat d1[] = { 1.0f, 0.0f, 0.5f, 1.0f };  //定义材质的漫反射光颜色
		GLfloat s1[] = { 1.0f, 0.0f, 0.5f, 1.0f };   //定义材质的镜面反射光颜色
		GLfloat e1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的自发光颜色，为0  
		GLfloat shine1 = 30.0f;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, e1);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine1);
		glutSolidSphere(120, 128, 128);
	glPopMatrix();

	glPushMatrix();//光滑的甜甜圈
	glTranslatef(-150, -150, 200);
	glRotatef(75, 0, 1, 0);
	GLfloat a4[] = { 0.21f, 0.21f, 0.21f, 1.0f };  //定义材质的环境光颜色 
	GLfloat d4[] = { 0.21f, 0.21f, 0.21f, 1.0f };  //定义材质的漫反射光颜色
	GLfloat s4[] = { 0.5f, 1.0f, 1.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat e4[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的自发光颜色，为0  
	GLfloat shine4 = 120.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a4);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d4);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s4);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, e4);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine4);
	glutSolidTorus(60, 120, 128, 128);
	glPopMatrix();

	glPushMatrix();// 发光的金字塔
	glTranslatef(100, -100, 100);
	glRotatef(crotate, 0, 1, 0);
	crotate += 0.1;
	if (crotate > 360)crotate = 0;
	glRotatef(-90, 1, 0, 0);
	GLfloat a5[] = { 0.21f, 0.21f, 0.1f, 1.0f };  //定义材质的环境光颜色 
	GLfloat d5[] = { 1.0f, 1.0f, 0.1f, 1.0f };  //定义材质的漫反射光颜色
	GLfloat s5[] = { 0.1f, 0.1f, 0.9f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat e5[] = { 0.5f, 0.5f, 0.0f, 1.0f };   //定义材质的自发光颜色
	GLfloat shine5 = 120.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a5);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d5);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s5);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, e5);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine5);
	glutSolidCone(300, 400, 4, 99);
	glPopMatrix();
	
	glPushMatrix();//正方体
		glTranslatef(-150, 150, 200);
		glRotatef(45, 0, 1, 0);
		glRotatef(45, 1, 0, 0);
		glColor3f(0.1, 0.5, 1);
		GLfloat a2[] = { 0.21f, 0.21f, 0.21f, 1.0f };  //定义材质的环境光颜色 
		GLfloat d2[] = { 0.5f, 1.0f, 0.5f, 1.0f };  //定义材质的漫反射光颜色
		GLfloat s2[] = { 0.5f, 1.0f, 0.5f, 1.0f };   //定义材质的镜面反射光颜色
		GLfloat e2[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的自发光颜色，为0  
		GLfloat shine2 = 30.0f;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, e2);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine2);
		glutSolidCube(150);

	glPopMatrix();

	glPushMatrix();//光
		GLfloat light_position[] = { 0.0, 0.0, 0.0, 1 };
		light_position[0] = x;
		light_position[1] = y;
		light_position[2] = z;
		GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
		GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glEnable(GL_LIGHT0);

		glPushMatrix();//光源位置指示球		
			glTranslatef(x, y, z);
			GLfloat a3[] = { 0.3f, 0.3f, 0.3f, 1.0f };  //定义材质的环境光颜色 
			GLfloat d3[] = { 0.5f, 1.0f, 0.5f, 1.0f };  //定义材质的漫反射光颜色
			GLfloat s3[] = { 0.5f, 1.0f, 0.5f, 1.0f };   //定义材质的镜面反射光颜色
			GLfloat e3[] = { 1.0f, 1.0f, 1.0f, 1.0f };   //定义材质的自发光颜色
			GLfloat shine3 = 30.0f;
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a3);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d3);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s3);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, e3);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine3);
			glutSolidSphere(5.0,25,25);
		glPopMatrix();

		/*z += 2;
		if (z > 500) {
			z = -500;
			x += 333;
			if (x > 500) {
				x = -500;
				y += 200;
				if (y > 500) y = -500;
			}
		}*/
	glPopMatrix();

	glutSwapBuffers(); //交换缓冲
}

void windowResize(int w,int h) {
	if (h == 0) h = 1;
	float aspect = (float)w / h;	
	//设投影矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,aspect,1,5000);

	//设视口大小
	glViewport(0, 0, w, h);
}

void setupRC() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); //设置背景色

	glEnable(GL_DEPTH_TEST);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glEnable(GL_LIGHTING);

}

void keyEvent(unsigned char key,int x_,int y_) {
	switch (key) {
		case 27 :
			exit(0); break;
		case 'w':
		case 'W':
			z -= 10; break;
		case 's':
		case 'S':
			z += 10; break;
		case 'a':
		case 'A':
			x -= 10; break;
		case 'd':
		case 'D':
			x += 10; break;
		case 'q':
		case 'Q':
			y += 10; break;
		case 'e':
		case 'E':
			y -= 10; break;
		default:
			break;
	}
}

void specialKeyEvent(int key, int x_, int y_) {
	switch (key) {
	case GLUT_KEY_UP:
		pitch += 3;
		break;
	case GLUT_KEY_DOWN:
		pitch -= 3;
		break;
	case GLUT_KEY_LEFT:
		yaw += 3;
		break;
	case GLUT_KEY_RIGHT:
		yaw -= 3;
		break;
	}
}

int main() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 576);
	glutCreateWindow("scene"); //创建窗口
	glutDisplayFunc(renderScene);//设显示回调函数
	glutIdleFunc(renderScene);//不停地渲染
	glutReshapeFunc(windowResize);//设窗口尺寸改变回调函数
	glutKeyboardFunc(keyEvent);
	glutSpecialFunc(specialKeyEvent);

	setupRC();//初始化
	
	glutMainLoop();//GLUT主循环
	
	return 0;
}