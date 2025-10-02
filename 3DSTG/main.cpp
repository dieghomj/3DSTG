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

float red=1.f, green=1.f, blue=1.f;

//angle of rotation for the camera direction
float angle = 0.0f;
//actual vector representing the cameras direction
float lx = 0.f, lz = 1.f;
//XZ positions of the camera
float x = 0.f, z = 5.f;
//camera speed
float fraction = 1.f;

void drawSnowMan();

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
    gluLookAt(  x, 3.f, z,
                x+lx, 3.f, z+lz,
                0.f, .5f, 0.f);
    // Draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    // Draw 36 SnowMen
    for (int i = -3; i < 3; i++)
        for (int j = -3; j < 3; j++) {
            glPushMatrix();
            glTranslatef(i * 10.0, 0, j * 10.0);
            drawSnowMan();
            glPopMatrix();
        }

    glutSwapBuffers();
}

void processInput(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);

}

void processSpecialInput(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_LEFT:
        angle -= 0.05f;
        lx = sin(angle) * fraction;
        lz = -cos(angle) * fraction;
        break;
    case GLUT_KEY_RIGHT:
        angle += 0.05f;
        lx = sin(angle) * fraction;
        lz = -cos(angle) * fraction;
        break;
    case GLUT_KEY_UP:
        x += lx * fraction;
        z += lz * fraction;
        break;
    case GLUT_KEY_DOWN:
        x -= lx * fraction;
        z -= lz * fraction;
        break;
    }
}

// ---------------------------- ƒƒCƒ“ ----------------------------
int main(int argc, char** argv) {
    //Init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIN_W, WIN_H);
    glutCreateWindow("");
    
    glClearColor(0, 0, 0, 0);
    
    glutDisplayFunc(render);
    glutReshapeFunc(changeSize);
    glutIdleFunc(render);

    glutKeyboardFunc(processInput);
    glutSpecialFunc(processSpecialInput);
    //glutGetModifiers();

    // OpenGL init
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}

void drawSnowMan()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw Body
    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidSphere(0.75f, 20, 20);

    // Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f, 20, 20);

    // Draw Eyes
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f, 10, 10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();

    // Draw Nose
    glColor3f(1.0f, 0.5f, 0.5f);
    glutSolidCone(0.08f, 0.5f, 10, 2);
}
