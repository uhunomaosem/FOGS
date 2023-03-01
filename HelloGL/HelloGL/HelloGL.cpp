#include "HelloGL.h"

Vertex HelloGL::vertices[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
				-1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

				1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
				1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

				1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
				-1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

				-1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
				-1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

				-1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
				1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

				1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
				-1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4

Colour HelloGL::colours[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
				1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0

				1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
				0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0

				1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
				0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0

				1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
				0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

				0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
				1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7

				0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
				0, 1, 0,   0, 1, 1,   0, 0, 1 };    // v6-v5-v4

Vertex HelloGL::indexedVertices[] = { 1, 1, 1,  -1, 1, 1,  // v0,v1,
				-1,-1, 1,   1,-1, 1,   // v2,v3
				1,-1,-1,   1, 1,-1,    // v4,v5
				-1, 1,-1,   -1,-1,-1 }; // v6,v7

Colour HelloGL::indexedColours[] = { 1, 1, 1,   1, 1, 0,   // v0,v1,
				1, 0, 0,   1, 0, 1,   // v2,v3
				0, 0, 1,   0, 1, 1,   // v4,v5
				0, 1, 0,   0, 0, 0 }; //v6,v7

GLushort HelloGL::indices[] = { 0, 1, 2,  2, 3, 0,      // front
				0, 3, 4,  4, 5, 0,      // right
				0, 5, 6,  6, 1, 0,      // top
				1, 6, 7,  7, 2, 1,      // left
				7, 4, 3,  3, 2, 7,      // bottom
				4, 7, 6,  6, 5, 4 };    // back



HelloGL::HelloGL(int argc, char* argv[])
{
	camera = new Camera();

	/*camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;*/
	camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, 800, 800);

	// Set the correct perspective.
	gluPerspective(45, 1, 0, 1000);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glutMainLoop();
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //this clears the scene
	glPushMatrix();
	DrawIndexedCube();
	/*DrawCubeArray();*/
	glPopMatrix();
	glutSwapBuffers();
	/*DrawPolygon();*/ //calls function of drawing shape
	glFlush(); //flushes the scene drawn to the graphics card
	
}




void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();
	rotation += 0.5f;
	rotation2 += 1.0f;

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
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(rotation, 1.0f, 0.0f, 0.0f);
	


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
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(rotation2, 1.0f, 0.0f, -1.0f);
	

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
	delete camera;
}


void HelloGL::KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'd')
		camera->up.x += 2.0f;

	if (key == 'a')
		camera->up.x -= 2.0f;

	if (key == 's')
		camera->eye.z += 0.5f;

	if (key == 'w')
		camera->eye.z -= 0.5f;
}

void HelloGL::DrawCubeArray()
{
	glPushMatrix();

	//glBegin(GL_TRIANGLES);
	//for (int i = 0; i < 36; i++)
	//{
	//	
	//	//glColor3f(colours[i].r,colours[i].g,colours[i].b);
	//	//glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	//	glColor3fv(&colours[i].r);
	//	glVertex3fv(&vertices[i].x);

	//}
	//glEnd();

	glPopMatrix();
}

void HelloGL::DrawIndexedCube()
{
	glPushMatrix();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i++)
	{
		//Implement draw code here
		glColor3f(indexedColours[indices[i]].r, indexedColours[indices[i]].g, indexedColours[indices[i]].b);
		glVertex3f(indexedVertices[indices[i]].x, indexedVertices[indices[i]].y, indexedVertices[indices[i]].z);
	}
	glEnd();

	glPopMatrix();

}
