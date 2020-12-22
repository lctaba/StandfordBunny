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
//�Ŵ���
double scaleTime = 1;
//ѡ�еĵ������
GLuint name = 100000000;
//ѡ�еĵ�Ĳ���
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
//	//ΪʲôҪ�������棿
////��Ȼ�Ļ�ѡȡ��ʱ����û�б任�ģ���׼
//
//
////��ƽ������ת
////Ϊʲô�����������ԴҲ�ƶ�
////glDisable(GL_LIGHT0);
//	glTranslatef(dTransX + oldX, -dTransY - oldY, 0);
//	//Ϊʲô�����ƶ��ӵ㣿
//
//	//�ù�Դ��ͼ�в���
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
//	//�ù�Դ��ͼ�в���
//	/*GLfloat light_position[] = { 0,0,20,1 };
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	glEnable(GL_LIGHT0);*/
//
//
//	glPointSize(5.0f);
//
//	for (int i = 0; i < pointNumber; i++) {
//		//ѡȡģʽ��ջ
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
	//ΪʲôҪ�������棿
	//��Ȼ�Ļ�ѡȡ��ʱ����û�б任�ģ���׼

	
		//��ƽ������ת
	//Ϊʲô�����������ԴҲ�ƶ�
	//glDisable(GL_LIGHT0);
		glTranslatef(dTransX + oldX, -dTransY - oldY, 0);
		//Ϊʲô�����ƶ��ӵ㣿

		//�ù�Դ��ͼ�в���
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


		//�ù�Դ��ͼ�в���
		/*GLfloat light_position[] = { 0,0,20,1 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glEnable(GL_LIGHT0);*/
	if (pickMode) {

		glPointSize(1.0f);

		for (int i = 0; i < pointNumber; i++) {
			//ѡȡģʽ��ջ

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




	////���ʷ���������
	//GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 0.5 };  //���淴�����
	//GLfloat mat_shininess[] = { 10.0 };               //�߹�ָ��
	////GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	//GLfloat white_light[] = { 1.0, 1.0, 1.0, 0.0 };   //��λ��(1,1,1), ���1-����
	//GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 }; //���������

	//glClearColor(0.0, 0.0, 0.0, 0.0);  //����ɫ
	//glShadeModel(GL_SMOOTH);           //��������ģʽ

	////��������
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	////�ƹ�����
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //ɢ�������
	//glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //���淴���
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //���������

	//glEnable(GL_LIGHTING);   //����:ʹ�ù�
	//glEnable(GL_LIGHT0);     //��0#��
	//glEnable(GL_DEPTH_TEST); //����Ȳ���
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glRotatef(150, 0.0, 1.0, 0.0);

	

	//��ת�ӵ㷨
	//gluLookAt(r*sin(dx/r),r*cos(dy/r),r*cos(dx/r),0,0,0,0,1,0);

	glLoadIdentity();
	/*if (dy != 0) {
		glRotatef(1, -dx / dy, -1, 0);
	}*/

	//��ת����
	//Ϊʲô�����������

	//����ͶӰ���ӵ�
	//gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);

	//�ù�Դ�̶�
	GLfloat light_position[] = { -dTransX - oldX,dTransY + oldY,20,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	
	//͸��ͶӰ���ӵ�
	


	gluLookAt(0, 0, r, 0, 0, -1, 0, 1, 0);


//	//��ƽ������ת
//	//Ϊʲô�����������ԴҲ�ƶ�
////glDisable(GL_LIGHT0);
//	glTranslatef(dTransX + oldX, -dTransY - oldY, 0);
//	//Ϊʲô�����ƶ��ӵ㣿
//
//	//�ù�Դ��ͼ�в���
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
//	//�ù�Դ��ͼ�в���
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


	//͸��ͶӰ
	//gluPerspective(60,1,1,100);
	//����ͶӰ
	glOrtho(-20.0 ,20.0 , -20.0, 20.0, -100, 100.0);
	glMatrixMode(GL_MODELVIEW);
	//display();
}

void processHits(GLint hits, GLuint buffer[])
{
	cout << "ѡ����" << hits << "����" << endl;
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
		cout << "ѡ�е��ǵ�" << name << "���㣬����ZΪ" << maxDeep << endl;
	}
	
	//unsigned int i, j;
	//GLuint *ptr;

	//printf("hits = %d\n", hits);
	//ptr = (GLuint *)buffer;

	//

	////if(names != -1) names = buffer[3];
	////hits��ʾ�ж��ٸ�����ѡ��
	//for (i = 0; i < hits; i++)
	//{ /*  for each hit  */
	//   //ѡ�з���ʱ���ƶ�ջ�е�������Ŀ
	//	//names = *ptr;
	//	int tempDeep = *(ptr+1);
	//	if (tempDeep > maxDeep) {
	//		name = *ptr;
	//	}
	//	/*printf("ѡ�з���ʱ���ƶ�ջ�е�������Ŀ:%d\n", names); ptr++;
	//	printf(" Z�������Сֵ:%u\n", *ptr); ptr++;
	//	printf(" Z��������ֵ:%u\n", *ptr); ptr++;*/
	//	ptr += 3;

	//	printf("ѡ�е�����:");
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
	//���
	if (buttonMode == 1) {
		//��ת����
		//dx = (x - X)/100;
		//dy = (y - Y)/100;
		//Ϊʲô�Ǽӵ��ڣ�glLoadIdentity()
		dx += (x - X);
		dy += (y - Y);
		/*cout << x << " " << y << " " << 1 << endl;
		cout << dx << " " << dy << endl;
		cout << X << " " << Y << " " << 2 << endl;*/
		X = x, Y = y;
	}
	//�Ҽ�
	else if(buttonMode == 0){
		//�ƶ�����
		
		dTransX += (x - transX) / 20;
		dTransY += (y - transY) / 20;
		//�ƶ��ӵ㷨
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
		glSelectBuffer(SIZE, selectBuf);//ָ�����ڱ��淵�ص����¼������
		glRenderMode(GL_SELECT);//����ѡ��ģʽ
		glInitNames();//��ʼ������ջ
		glPushName(0);

		//glPushMatrix();
		glMatrixMode(GL_PROJECTION);//ѡ���Ӿ���
		glPushMatrix();
		glLoadIdentity();//ע������ջִ�е�˳��
		gluPickMatrix(x, viewport[3] - y, 3, 3, viewport);//���������λ��Ϊ���ģ���СΪ5�����ص����Ӿ���

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
		//	//ѡȡģʽ��ջ
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

		glMatrixMode(GL_PROJECTION);//���ز���ջ


		glPopMatrix();

		glFlush();
		glMatrixMode(GL_MODELVIEW);

		

		int hits = glRenderMode(GL_RENDER);//��ô�����������ͼԪ����
		if (hits > 0) {
			processHits(hits, selectBuf);
		}
 		glutPostRedisplay();

		//double modelview[16], projection[16];
		//int viewport[4];
		//float winX, winY, winZ;
		//double object_x = 0, object_y = 0, object_z = 0; //3D����
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
