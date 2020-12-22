#include <windows.h>
#include <gl/glut.h>
#include <gl\gl.h>						
#include <gl\glu.h>	
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <regex>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define PointNumber 50000
#define SurfaceNumber 100000
int pointNumber = 0;
int surfaceNumnber = 0;
GLfloat bunnyPoint[PointNumber][3];
int bunnysurface[SurfaceNumber][3];
using namespace std;
double X = 0, Y = 0, dx = 0, dy = 0;
double transX = 0, transY = 0, dTransX = 0, dTransY = 0, oldX = 0, oldY = 0;
double r = 50;
int buttonMode = 1;
//放大倍数
double scaleTime = 1;
//选中的点的名称
GLuint name = 100000000;
//选中的点的参数
GLfloat color_selected[] = { 1.0f,0.0f,0.0f };
GLfloat color_unselected[] = { 0.0f,0.0f,1.0f };
bool pickMode = false;

void readPly(string path) {
	ifstream in;
	in.open(path, ios::in);
	
	in >> pointNumber;
	in >> surfaceNumnber;
	double tempd = 0;
	//regex numberPattern = regex("\d+");
	//smatch result;

	for (int i = 0; i < pointNumber; i++) {
		
		//regex_match(temp, result, numberPattern);
	
		//bunnyPoint[i][0] = stof(result.str(1));
		//bunnyPoint[i][1] = stof(result.str(2));
		//bunnyPoint[i][2] = stof(result.str(3));
		in >> tempd;
		bunnyPoint[i][0] = tempd;
		in >> tempd;
		bunnyPoint[i][1] = tempd;
		in >> tempd;
		bunnyPoint[i][2] = tempd;
	}
	int tempi = 0;
	for (int i = 0; i < surfaceNumnber; i++) {
		in >> tempi;
		in >> tempi;
		bunnysurface[i][0] = tempi;
		in >> tempi;
		bunnysurface[i][1] = tempi;
		in >> tempi;
		bunnysurface[i][2] = tempi;
		//regex_match(temp, result, numberPattern);
		//bunnysurface[i][0] = stoi(result.str(2));
		//bunnysurface[i][1] = stoi(result.str(3));
		//bunnysurface[i][2] = stoi(result.str(4));
	}
	in.close();
}

//void drawPoints() {
//	//为什么要放在里面？
////不然的话选取的时候是没有变换的，不准
//
//
////先平移在旋转
////为什么不用这个，光源也移动
////glDisable(GL_LIGHT0);
//	glTranslatef(dTransX + oldX, -dTransY - oldY, 0);
//	//为什么不用移动视点？
//
//	//让光源在图中不动
//	/*GLfloat light_position[] = { 20,-10,20,0 };
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	glEnable(GL_LIGHT0);*/
//
//
//	glRotatef(dy, 1, 0, 0);
//	glRotatef(dx, 0, 1, 0);
//
//
//	//glLoadIdentity();
//
//	glScalef(scaleTime, scaleTime, scaleTime);
//
//
//	//if (keyboardMode == 1) {
//	//	glScalef(scaleTime, scaleTime, scaleTime);
//	//}
//	//else {
//	//	glScalef(scaleTime, 0.5, 0.5);
//	//}
//
//
//	//让光源在图中不动
//	/*GLfloat light_position[] = { 0,0,20,1 };
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	glEnable(GL_LIGHT0);*/
//
//
//	glPointSize(5.0f);
//
//	for (int i = 0; i < pointNumber; i++) {
//		//选取模式的栈
//
//			glLoadName(i + 1);
//			//glColor3fv((names == i) ? color_selected : color_unselected);
//			//if (names == i) {
//				//glColor3fv(color_selected);
//				//glPointSize(0.0001f);
//
//
//		glBegin(GL_POINTS);
//		glVertex3f(bunnyPoint[i][0], bunnyPoint[i][1], bunnyPoint[i][2] - 7);
//		glEnd();
//	}
//}


void drawBunny(GLenum mode) {
	//为什么要放在里面？
	//不然的话选取的时候是没有变换的，不准

	
		//先平移在旋转
	//为什么不用这个，光源也移动
	//glDisable(GL_LIGHT0);
		glTranslatef(dTransX + oldX, -dTransY - oldY, 0);
		//为什么不用移动视点？

		//让光源在图中不动
		/*GLfloat light_position[] = { 20,-10,20,0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glEnable(GL_LIGHT0);*/


		glRotatef(dy, 1, 0, 0);
		glRotatef(dx, 0, 1, 0);


		//glLoadIdentity();

		glScalef(scaleTime, scaleTime, scaleTime);


		//if (keyboardMode == 1) {
		//	glScalef(scaleTime, scaleTime, scaleTime);
		//}
		//else {
		//	glScalef(scaleTime, 0.5, 0.5);
		//}


		//让光源在图中不动
		/*GLfloat light_position[] = { 0,0,20,1 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glEnable(GL_LIGHT0);*/
	if (pickMode) {

		glPointSize(1.0f);

		for (int i = 0; i < pointNumber; i++) {
			//选取模式的栈

			if (mode == GL_SELECT) {
				glLoadName(i + 1);
				//glColor3fv((names == i) ? color_selected : color_unselected);
				//if (names == i) {
					//glColor3fv(color_selected);
					//glPointSize(0.0001f);
			}


			glBegin(GL_POINTS);
			glVertex3f(bunnyPoint[i][0], bunnyPoint[i][1], bunnyPoint[i][2] - 7);
			glEnd();
		}


		if (name >= 1 && name <= 34834 /*&& mode == GL_SELECT*/) {

			glPointSize(5.0f);
			glBegin(GL_POINTS);
			glVertex3f(bunnyPoint[name - 1][0], bunnyPoint[name - 1][1], bunnyPoint[name - 1][2] - 7);
			//glVertex3f(bunnyPoint[1][0], bunnyPoint[1][1], bunnyPoint[1][2] - 7);
			glEnd();
		}
	}

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < surfaceNumnber; i++) {
		//glBegin(GL_POLYGON);

		//if (mode == GL_SELECT) {
		//	glLoadName(i + 1);
		//}
			//glBegin(GL_TRIANGLES);
			GLfloat a[3] = { bunnyPoint[bunnysurface[i][0]][0], bunnyPoint[bunnysurface[i][0]][1], bunnyPoint[bunnysurface[i][0]][2]-7 };
			GLfloat b[3] = { bunnyPoint[bunnysurface[i][1]][0], bunnyPoint[bunnysurface[i][1]][1], bunnyPoint[bunnysurface[i][1]][2]-7 };
			GLfloat c[3] = { bunnyPoint[bunnysurface[i][2]][0], bunnyPoint[bunnysurface[i][2]][1], bunnyPoint[bunnysurface[i][2]][2]-7 };
			//glNormal3f(1.0, 1.0, 1.0);

			//glNormal3f(bunnyPoint[bunnysurface[i][0]][0], bunnyPoint[bunnysurface[i][0]][1], bunnyPoint[bunnysurface[i][0]][2]);
			//glVertex3f(bunnyPoint[bunnysurface[i][0]][0], bunnyPoint[bunnysurface[i][0]][1], bunnyPoint[bunnysurface[i][0]][2]);
			////glNormal3f(bunnyPoint[bunnysurface[i][1]][0], bunnyPoint[bunnysurface[i][1]][1], bunnyPoint[bunnysurface[i][1]][2]);
			//glVertex3f(bunnyPoint[bunnysurface[i][1]][0], bunnyPoint[bunnysurface[i][1]][1], bunnyPoint[bunnysurface[i][1]][2]);
			////glNormal3f(bunnyPoint[bunnysurface[i][1]][0], bunnyPoint[bunnysurface[i][1]][1], bunnyPoint[bunnysurface[i][1]][2]);
			//glVertex3f(bunnyPoint[bunnysurface[i][2]][0], bunnyPoint[bunnysurface[i][2]][1], bunnyPoint[bunnysurface[i][2]][2]);

			GLfloat vector1[3] = { a[0] - b[0],a[1] - b[1],a[2] - b[2] };
			GLfloat vector2[3] = { b[0] - c[0],b[1] - c[1],b[2] - c[2] };
			//glNormal3f(a[0]+b[0]+c[0], a[1]+b[1]+c[1], a[2]+b[2]+c[2]);
			glNormal3f((vector1[1]*vector2[2]-vector2[1]*vector1[2]),
				(vector2[0] * vector1[2] - vector1[0] * vector2[2]),
				(vector1[0] * vector2[1] - vector2[0] * vector1[1]));
			glVertex3f(a[0], a[1], a[2]);
			glVertex3f(b[0], b[1], b[2]);
			glVertex3f(c[0], c[1], c[2]);
			
			
		//glEnd();
	}
	glEnd();
}

void myinit()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 0.5 };
	GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 0.5 };
	GLfloat mat_shininess = { 30.0 };
	GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 0.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 0.5, 0.5, 0.5, 0.5 };
	GLfloat light_position[] = { 0,0,20,1 };
	/* set up ambient, diffuse, and specular components for light 0 */
	glEnable(GL_NORMALIZE);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	/* define material proerties for front face of all polygons */

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	//glEnable(GL_SMOOTH);
	glShadeModel(GL_SMOOTH); /*enable smooth shading */
	//glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING); /* enable lighting */
	glEnable(GL_LIGHT0);  /* enable light 0 */
	glEnable(GL_DEPTH_TEST); /* enable z buffer */
	

	gluLookAt(0, 0, r, 0, 0, -1, 0, 1, 0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);




	////材质反光性设置
	//GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 0.5 };  //镜面反射参数
	//GLfloat mat_shininess[] = { 10.0 };               //高光指数
	////GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	//GLfloat white_light[] = { 1.0, 1.0, 1.0, 0.0 };   //灯位置(1,1,1), 最后1-开关
	//GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 }; //环境光参数

	//glClearColor(0.0, 0.0, 0.0, 0.0);  //背景色
	//glShadeModel(GL_SMOOTH);           //多变性填充模式

	////材质属性
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	////灯光设置
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光属性
	//glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //镜面反射光
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数

	//glEnable(GL_LIGHTING);   //开关:使用光
	//glEnable(GL_LIGHT0);     //打开0#灯
	//glEnable(GL_DEPTH_TEST); //打开深度测试
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glRotatef(150, 0.0, 1.0, 0.0);

	

	//旋转视点法
	//gluLookAt(r*sin(dx/r),r*cos(dy/r),r*cos(dx/r),0,0,0,0,1,0);

	glLoadIdentity();
	/*if (dy != 0) {
		glRotatef(1, -dx / dy, -1, 0);
	}*/

	//旋转对象法
	//为什么不能用这个？

	//正交投影的视点
	//gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);

	//让光源固定
	GLfloat light_position[] = { -dTransX - oldX,dTransY + oldY,20,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	
	//透视投影的视点
	


	gluLookAt(0, 0, r, 0, 0, -1, 0, 1, 0);


//	//先平移在旋转
//	//为什么不用这个，光源也移动
////glDisable(GL_LIGHT0);
//	glTranslatef(dTransX + oldX, -dTransY - oldY, 0);
//	//为什么不用移动视点？
//
//	//让光源在图中不动
//	/*GLfloat light_position[] = { 20,-10,20,0 };
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	glEnable(GL_LIGHT0);*/
//
//
//	glRotatef(dy, 1, 0, 0);
//	glRotatef(dx, 0, 1, 0);
//
//
//	//glLoadIdentity();
//
//	glScalef(scaleTime, scaleTime, scaleTime);
//
//
//	//if (keyboardMode == 1) {
//	//	glScalef(scaleTime, scaleTime, scaleTime);
//	//}
//	//else {
//	//	glScalef(scaleTime, 0.5, 0.5);
//	//}
//
//
//	//让光源在图中不动
//	/*GLfloat light_position[] = { 0,0,20,1 };
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	glEnable(GL_LIGHT0);*/




	//glBegin(GL_POLYGON);
	drawBunny(GL_RENDER);

	//glFlush();
	glutSwapBuffers();

}

void myReshape(int w, int h)
{
	//glViewport(0, 0, w, h);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//if (w <= h)
	//	glOrtho(-20.0, 20.0, -100.0 * (GLfloat)h / (GLfloat)w,
	//		100.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	//else
	//	glOrtho(-100.0 * (GLfloat)w / (GLfloat)h,
	//		100.0 * (GLfloat)w / (GLfloat)h, -20.0, 20.0, -10.0, 10.0);
	//glMatrixMode(GL_MODELVIEW);
	////glutPostRedisplay();
	//display();
	int bound = w > h ? h : w;
	glViewport(0, 0, bound, bound);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//if (w <= h)
	//	glOrtho(-30.0, 30.0, -30.0* (GLfloat)h / (GLfloat)w,
	//		30.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	//else
	//	glOrtho(-30.0 * (GLfloat)w / (GLfloat)h,
	//		30.0 * (GLfloat)w / (GLfloat)h, -30.0, 30.0, -10.0, 10.0);


	//透视投影
	//gluPerspective(60,1,1,100);
	//正交投影
	glOrtho(-20.0 ,20.0 , -20.0, 20.0, -100, 100.0);
	glMatrixMode(GL_MODELVIEW);
	//display();
}

void processHits(GLint hits, GLuint buffer[])
{
	cout << "选中了" << hits << "个点" << endl;
	int names;
	int maxDeep = -1000000000;
	for (int i = 0; i < hits; i++) {
		int tempDeep = buffer[i * 4 + 1];
		if (tempDeep > maxDeep) {
			name = buffer[i * 4 + 3] > 34833 ? name : buffer[i * 4 + 3];
			maxDeep = tempDeep;
		}
	}
	if (hits > 0) {
		cout << "选中的是第" << name << "个点，它的Z为" << maxDeep << endl;
	}
	
	//unsigned int i, j;
	//GLuint *ptr;

	//printf("hits = %d\n", hits);
	//ptr = (GLuint *)buffer;

	//

	////if(names != -1) names = buffer[3];
	////hits表示有多少个对象被选中
	//for (i = 0; i < hits; i++)
	//{ /*  for each hit  */
	//   //选中发生时名称堆栈中的名称数目
	//	//names = *ptr;
	//	int tempDeep = *(ptr+1);
	//	if (tempDeep > maxDeep) {
	//		name = *ptr;
	//	}
	//	/*printf("选中发生时名称堆栈中的名称数目:%d\n", names); ptr++;
	//	printf(" Z坐标的最小值:%u\n", *ptr); ptr++;
	//	printf(" Z坐标的最大值:%u\n", *ptr); ptr++;*/
	//	ptr += 3;

	//	printf("选中的内容:");
	//	for (j = 0; j < names; j++)
	//	{ /*  for each name */
	//		printf("%d,", *ptr);
	//		ptr++;
	//	}
	//	printf("\n");
	//}
}

#define SIZE 512

void mouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) {
		X = x;
		Y = y;
		buttonMode = 1;

	}
	if (button == GLUT_RIGHT_BUTTON) {
		transX = x;
		transY = y;
		buttonMode = 0;
		//if (state == GLUT_UP) {
		//	
		//	oldX = dTransX;
		//	oldY = dTransY;
		//}
	}
}

void mouseMove(int x,int y) {
	//左键
	if (buttonMode == 1) {
		//旋转对象法
		//dx = (x - X)/100;
		//dy = (y - Y)/100;
		//为什么是加等于？glLoadIdentity()
		dx += (x - X);
		dy += (y - Y);
		/*cout << x << " " << y << " " << 1 << endl;
		cout << dx << " " << dy << endl;
		cout << X << " " << Y << " " << 2 << endl;*/
		X = x, Y = y;
	}
	//右键
	else if(buttonMode == 0){
		//移动对象法
		
		dTransX += (x - transX) / 20;
		dTransY += (y - transY) / 20;
		//移动视点法
		/*dTransX += (x - transX) / 20;
		dTransY += (y - transY) / 20;*/
		//cout << dTransX << " " << dTransY << " " << transX << " " << transY << " "<< dTransX + oldX<< " "<< dTransY + oldY  <<endl;
		transX = x;
		transY = y;
	}
	
	glutPostRedisplay();

	
}

void keyboard(unsigned char key,int x,int y) {

	GLuint selectBuf[SIZE];
	GLint hits;
	GLint viewport[4];
	if (key == 'w') {
		scaleTime *= 1.05;
		glutPostRedisplay();
	}
	else if (key == 's') {
		scaleTime *= 0.95;
		glutPostRedisplay();
	}else if (key == 'q') {
		glGetIntegerv(GL_VIEWPORT, viewport);
		glSelectBuffer(SIZE, selectBuf);//指定用于保存返回点击记录的数组
		glRenderMode(GL_SELECT);//进入选择模式
		glInitNames();//初始化名称栈
		glPushName(0);

		//glPushMatrix();
		glMatrixMode(GL_PROJECTION);//选择视景体
		glPushMatrix();
		glLoadIdentity();//注意矩阵堆栈执行的顺序
		gluPickMatrix(x, viewport[3] - y, 3, 3, viewport);//定义以鼠标位置为中心，大小为5个像素的新视景体

		/*float m[16];
		glGetFloatv(GL_PROJECTION_MATRIX, m);*/

		//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
		glOrtho(-20.0, 20.0, -20.0, 20.0, -100, 100.0);
		//gluPerspective(60, 1, 1, 100);


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		//gluLookAt(0, 0, r, 0, 0, -1, 0, 1, 0);

		//glBegin(GL_POINTS);
		//for (int i = 0; i < pointNumber; i++) {
		//	//选取模式的栈
		//	glLoadName(i);
		//	//glColor3fv((names == i) ? color_selected : color_unselected);
		//	//if (names == i) {

		//		//glColor3fv(color_selected);
		//		//glPointSize(0.0001f);

		//	glVertex3f(bunnyPoint[i][0], bunnyPoint[i][1], bunnyPoint[i][2] - 7);

		//}
		//glEnd();
		//
		
		drawBunny(GL_SELECT);
		//drawPoints();

		glMatrixMode(GL_PROJECTION);//返回并出栈


		glPopMatrix();

		glFlush();
		glMatrixMode(GL_MODELVIEW);

		

		int hits = glRenderMode(GL_RENDER);//获得此射线上命中图元数量
		if (hits > 0) {
			processHits(hits, selectBuf);
		}
 		glutPostRedisplay();

		//double modelview[16], projection[16];
		//int viewport[4];
		//float winX, winY, winZ;
		//double object_x = 0, object_y = 0, object_z = 0; //3D坐标
		//glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		//glGetDoublev(GL_PROJECTION_MATRIX, projection);
		//glGetIntegerv(GL_VIEWPORT, viewport);
		//winX = (float)mouse_x;
		//winY = (float)viewport[3] - (float)mouse_y;
		//glReadPixels(mouse_x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
		//gluUnProject((GLdouble)winX, (GLdouble)winY, (GLdouble)winZ, modelview, projection, viewport, &object_x, &object_y, &object_z);

	}
	else if (key == 'a') {
		//glRenderMode(GL_RENDER);
		//drawBunny(GL_RENDER);
		
		pickMode = !pickMode;
		glutPostRedisplay();
	}
}

int main(int argc, char **argv)
{
	readPly("bunny_iH.ply2");
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("bunny");
	
	myinit();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	
	//glutPassiveMotionFunc(mouseMove);

	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	//glutIdleFunc(spinBunny);
	glutKeyboardFunc(keyboard);
	//glutMotionFunc(MyMotion);
	
	//glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	
}
