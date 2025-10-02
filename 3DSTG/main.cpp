#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int WIN_W = 800;
const int WIN_H = 600;
const float DT = 0.016f;          // 60FPS
const float WORLD_X = 500.0f;
const float WORLD_Y = 350.0f;

float angle = 0.0f;

void changeSize(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    float ratio = 1.0 * w / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45, ratio, 1, 1000);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void render()
{
    //Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    //Reset transformations
    glLoadIdentity();
    //Set the camera
    gluLookAt(  0.f, 0.f, 20.f,
                0.f, 0.f, 0.f,
                0.f, 1.f, 0.f);
    glRotatef(angle, 0.f, 1.f, 0.f);

    glBegin(GL_TRIANGLES);
    glVertex3f(-2, -2, -5.0);
    glVertex3f(2, 0.0, -5.0);
    glVertex3f(0.0, 2, -5.0);
    glEnd();

    angle += 0.1f;
    
    glutSwapBuffers();
}

// ---------------------------- ÉÅÉCÉì ----------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIN_W, WIN_H);
    glutCreateWindow("");
    glClearColor(0, 0, 0, 0);
    glutDisplayFunc(render);
    glutReshapeFunc(changeSize);
    glutIdleFunc(render);
    glutMainLoop();
    return 0;
}