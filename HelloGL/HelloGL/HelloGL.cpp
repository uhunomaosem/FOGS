#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	rotation = 0.0f;
	rotation2 = 0.0f;
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::KeyBoard);
	glutMainLoop();
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //this clears the scene
	DrawPolygon(); //calls function of drawing shape
	glFlush(); //flushes the scene drawn to the graphics card
	
}




void HelloGL::Update()
{

	glutPostRedisplay();
	rotation += 0.5f;
	rotation2 += 6.0f;

	if (rotation2 > 360.0)
	{
		rotation2 = 0.0f;
	}

	if (rotation > 360.0)
	{
		rotation = 0.0f;
	}
}


void HelloGL::DrawPolygon()
{

	glPushMatrix();
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);



	glBegin(GL_POLYGON); //starts to draw a polygon
	{


		glColor3f(0.0f, 1.0f, 0.0f);//Green
		glVertex2f(-0.75, 0.5); //define the first point of the polygon,top left
		glColor3f(0.1f, 0.1f, 0.0f);//Bronze
		glVertex2f(0.75, 0.5); //next point, top right
		glColor3f(0.1f, 0.0f, 0.0f);//Brown
		glVertex2f(0.75, -0.5); //bottom right
		glColor3f(0.0f, 0.1f, 0.0f);//Forest Green
		glVertex2f(-0.75, -0.5); //last point of the polygon, bottom left
		glEnd(); // defines the end of the draw

	}


	glPopMatrix();

	glFlush();//flushes the scene drawn to the graphics card


	glPushMatrix();
	glRotatef(rotation2, 0.0f, 0.0f, -1.0f);

	glBegin(GL_POLYGON); //starts to draw a polygon
	{


		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
		glVertex2f(-0.13f, -0.2f);//bottom left
		glVertex2f(0.13f, -0.2f);//bottom right
		glVertex2f(0.2f, 0.0f);//right
		glVertex2f(0.13f, 0.2f);//top right
		glVertex2f(-0.13f, 0.2f);//top left
		glVertex2f(-0.2f, 0.0f);//left

		glEnd(); // defines the end of the draw


	}
	glPopMatrix();

	glFlush();//flushes the scene drawn to the graphics card

	glutSwapBuffers();
}

HelloGL::~HelloGL(void)
{

}


void HelloGL::KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'd')
		rotation += 0.5f;

}