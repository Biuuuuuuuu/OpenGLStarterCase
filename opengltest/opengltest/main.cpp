#include <windows.h>
#include <GL/glut.h>
#include <GL/GLU.h>

static float angle = 0;

void renderScene(){
	glClear(GL_COLOR_BUFFER_BIT); //清颜色缓冲
	glClear(GL_DEPTH_BUFFER_BIT);	//清zbuffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glRotatef(15, 1, 0, 0);//摄像机pitch
	glTranslatef(0, -10, -30);//摄像机后退抬高	

	glPushMatrix();//世界坐标系中画地球
		glRotatef(angle / 3, 0, 1, 0);//地球公转
		glTranslatef(15, 0, 0);	//地球轨道半径
		
			glPushMatrix();//地球公转坐标系下画月球
				glRotatef(angle*3, 0, 1, 0);////月球公转
				glTranslatef(6, 0, 0);//月球轨道半径
				glRotatef(123, 1, 2, 3);//月球倾角
				glutWireTeapot(1);//月球
			glPopMatrix();//回到地球公转坐标系

		glRotatef(-angle / 3, 0, 1, 0);//抵消地球公转
		glRotatef(angle * 2, 1, 0, 0);//地球自转			
		glutWireTeapot(2);//地球
	glPopMatrix();//回到世界坐标系
	glRotatef(angle/10, 0, 1, 0);	//太阳自转
	glutWireTeapot(3);//太阳
	
	//glFlush();
	glutSwapBuffers(); //交换缓冲
	angle += 0.1;
}

void windowResize(int w,int h) {
	if (h == 0) h = 1;
	float aspect = (float)w / h;	
	//设投影矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,aspect,1,1000);

	//设视口大小
	glViewport(0, 0, w, h);
}

void setupRC(){
	glClearColor( 0.1f, 0.1f, 0.1f, 1.0f); //设置背景色
	glEnable(GL_DEPTH_TEST);
}

int main() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 576);
	glutCreateWindow("OpenGLTest"); //创建窗口
	glutDisplayFunc(renderScene);//设显示回调函数
	glutIdleFunc(renderScene);//不停地渲染
	glutReshapeFunc(windowResize);//设窗口尺寸改变回调函数
	
	setupRC();//初始化
	
	glutMainLoop();//GLUT主循环
	
	return 0;
}