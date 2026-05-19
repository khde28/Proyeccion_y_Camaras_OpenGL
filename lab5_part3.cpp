#include <GL/glut.h>

float camX = 0.0f;
float camY = 2.0f;
float camZ = 10.0f;

float atX = 0.0f;
float atY = 0.0f;
float atZ = 0.0f;

float velocidad = 0.5f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(camX, camY, camZ,
              atX, atY, atZ,
              0.0f, 1.0f, 0.0f);

    glColor3f(0.8f, 0.3f, 0.3f);
    glutSolidTeapot(1.5);

    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_LINES);
    for (int i = -10; i <= 10; i++) {
        glVertex3f((float)i, -1.0f, -10.0f);
        glVertex3f((float)i, -1.0f,  10.0f);
        glVertex3f(-10.0f, -1.0f, (float)i);
        glVertex3f( 10.0f, -1.0f, (float)i);
    }
    glEnd();

    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': case 'W': 
            camZ -= velocidad;
            break;
        case 's': case 'S': 
            camZ += velocidad;
            break;
        case 'a': case 'A': 
            camX -= velocidad;
            break;
        case 'd': case 'D': 
            camX += velocidad;
            break;
        case 'r': case 'R': 
            camY += velocidad;
            break;
        case 'f': case 'F': 
            camY -= velocidad;
            break;
    }
    
    glutPostRedisplay();
}

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    
    GLfloat luz_pos[] = { 5.0f, 5.0f, 5.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, luz_pos);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Camara Interactiva - Lab 5");

    initLighting();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    
    glutMainLoop();
    return 0;
}