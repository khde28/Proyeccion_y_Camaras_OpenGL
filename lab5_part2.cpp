#include <GL/glut.h>

bool usarPerspectiva = false; 

void configurarProyeccion(int w, int h) {
    if (h == 0) h = 1;
    float aspecto = (float)w / (float)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (usarPerspectiva) {
        gluPerspective(45.0, aspecto, 1.0, 20.0);
    } else {
        glOrtho(-4.0 * aspecto, 4.0 * aspecto, -4.0, 4.0, 1.0, 20.0);
    }

    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 3.0, 10.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
        glTranslatef(-3.0f, 0.0f, -3.0f);
        glutWireCube(1.5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glutWireSphere(1.0, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(3.0f, 0.0f, 3.0f);
        glutWireTorus(0.3, 0.8, 16, 16); 
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    configurarProyeccion(w, h);
}

void teclado(unsigned char key, int x, int y) {
    if (key == 'p' || key == 'P') {
        usarPerspectiva = true;
    } else if (key == 'o' || key == 'O') {
        usarPerspectiva = false;
    }
    
    configurarProyeccion(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lab 5: Ortografica vs Perspectiva (Presiona 'P' u 'O')");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    
    glutMainLoop();
    return 0;
}