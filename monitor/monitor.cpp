#define _USE_MATH_DEFINES 

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

// Global variables for adjusting the monitor screen
GLfloat screenWidth = 2.0f;  // Initial width of the screen
GLfloat screenHeight = 1.2f; // Initial height of the screen
GLfloat screenDepth = 0.2f;  // Initial depth of the screen
GLfloat screenXRotation = 0.0f; // Initial rotation around the X-axis
GLfloat screenYRotation = 0.0f; // Initial rotation around the Y-axis

// Function to draw the 3D monitor and stand
void drawMonitor() {
    glPushMatrix();
    glRotatef(screenYRotation, 0.0f, 1.0f, 0.0f); // Apply Y-axis rotation
    glRotatef(screenXRotation, 1.0f, 0.0f, 0.0f); // Apply X-axis rotation

    // Draw the monitor screen as a 3D cube
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for the screen
    glTranslatef(0.0f, 0.0f, -screenDepth / 2); // Move to the center of the screen
    glScalef(screenWidth, screenHeight, screenDepth); // Scale the cube
    glutSolidCube(1.0f); // Draw a cube as the screen

    // Draw the monitor stand
    glColor3f(0.2f, 0.2f, 0.2f); // Gray color for the stand
    glTranslatef(0.0f, -(screenHeight / 2) - 0.1f, -screenDepth / 2); // Position the stand below the screen
    glScalef(0.1f, 0.4f, screenDepth); // Scale the stand
    glutSolidCube(1.0f); // Draw a cube as the stand

    // Draw the flat stand
    glColor3f(0.2f, 0.2f, 0.2f); // Gray color for the stand
    glPushMatrix();
    glTranslatef(0.0f, -(screenHeight / 2) - 0.0f, 0.0f); // Position the stand below the screen
    glScalef(0.6f, 0.03f, 1.5f); // Scale the stand
    glutSolidCube(7.0f); // Draw a cube as the flat stand

    glPopMatrix(); // Restore the original transformation matrix
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set the background color to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Set the camera position and view
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Draw the 3D monitor
    drawMonitor();

    glutSwapBuffers();
}

// Reshape callback function
void reshape(int width, int height) {
    if (height == 0) height = 1;
    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard callback function for adjusting parameters
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'i':
        screenHeight += 0.1f; // Increase screen height
        break;
    case 'k':
        screenHeight -= 0.1f; // Decrease screen height
        break;
    case 'j':
        screenWidth -= 0.1f; // Decrease screen width
        break;
    case 'l':
        screenWidth += 0.1f; // Increase screen width
        break;
    case 'z':
        screenDepth -= 0.1f; // Decrease screen depth
        break;
    case 'x':
        screenDepth += 0.1f; // Increase screen depth
        break;
    case 'w':
        screenXRotation += 5.0f; // Rotate screen upward
        break;
    case 's':
        screenXRotation -= 5.0f; // Rotate screen downward
        break;
    case 'a':
        screenYRotation -= 5.0f; // Rotate screen left
        break;
    case 'd':
        screenYRotation += 5.0f; // Rotate screen right
        break;
    case 27: // Escape key
        exit(0);
        break;
    }

    glutPostRedisplay(); // Request a redraw
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3D Monitor");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
