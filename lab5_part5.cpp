#include <GL/glut.h>

float camDistancia = 5.0f;
float rotX = 0.0f;
float rotY = 0.0f;

int lastMouseX = 0;
int lastMouseY = 0;
bool isDragging = false;

void dibujarGizmo() {
    glDisable(GL_LIGHTING);
    glLineWidth(2.5f);

    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(2.0f, 0.0f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 2.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 2.0f);
    glEnd();

    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -camDistancia);
    
    glRotatef(rotY, 1.0f, 0.0f, 0.0f);
    glRotatef(rotX, 0.0f, 1.0f, 0.0f);

    dibujarGizmo();

    glColor3f(0.8f, 0.8f, 0.8f);
    glutWireTeapot(1.0);

    glutSwapBuffers();
}

void raton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            lastMouseX = x;
            lastMouseY = y;
        } else {
            isDragging = false;
        }
    }
    
    if (state == GLUT_DOWN) {
        if (button == 3) {
            camDistancia -= 0.5f;
        } else if (button == 4) {
            camDistancia += 0.5f;
        }
    }
    
    glutPostRedisplay();
}

void ratonMovimiento(int x, int y) {
    if (isDragging) {
        int deltaX = x - lastMouseX;
        int deltaY = y - lastMouseY;

        rotX += (float)deltaX * 0.5f;
        rotY += (float)deltaY * 0.5f;

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Camara Trackball - Ejercicio 5");

    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    GLfloat luz_pos[] = { 5.0f, 5.0f, 5.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, luz_pos);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    
    glutMouseFunc(raton);
    glutMotionFunc(ratonMovimiento);
    
    glutMainLoop();
    return 0;
}