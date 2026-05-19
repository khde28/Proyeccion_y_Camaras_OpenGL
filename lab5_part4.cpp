#include <GL/glut.h>
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846
#endif

float angulo_rotacion_sol = 0.0f;
float angulo_orbita_tierra = 0.0f;
float angulo_rotacion_tierra = 0.0f;
float angulo_orbita_luna = 0.0f;
float angulo_rotacion_luna = 0.0f;
float angulo_orbita_marte = 0.0f;
float angulo_rotacion_marte = 0.0f;

float Vs = 0.025f;
float Vt = 0.015f;

float radio_sol = 4.0f;
float radio_tierra = 2.0f;
float radio_luna = 0.8f;
float radio_marte = 1.5f;

float distancia_tierra = 10.0f;
float distancia_luna = 4.0f;
float distancia_marte = 18.0f;

float escala_global = 0.3f;

void circulo(float x, float y, float radio, int segmentos) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segmentos; i++) {
        float theta = 2.0f * PI * i / segmentos;
        glVertex3f(x + radio * cos(theta), y + radio * sin(theta), 0.0f);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float radTierra = angulo_orbita_tierra * PI / 180.0f;
    
    float tierraX = escala_global * distancia_tierra * cos(radTierra);
    float tierraY = escala_global * distancia_tierra * sin(radTierra);
    float tierraZ = 0.0f;

    float camX = tierraX;
    float camY = tierraY - 15.0f;
    float camZ = 12.0f;

    gluLookAt(camX, camY, camZ,
              tierraX, tierraY, tierraZ,
              0.0, 0.0, 1.0);

    glScalef(escala_global, escala_global, escala_global);

    glDisable(GL_LIGHTING);
    glColor3f(0.5f, 0.5f, 0.5f);
    circulo(0.0f, 0.0f, distancia_tierra, 100);
    circulo(0.0f, 0.0f, distancia_marte, 100);
    glEnable(GL_LIGHTING);
    
    glPushMatrix();
        glRotatef(angulo_rotacion_sol, 0.0f, 1.0f, 0.0f);
        GLfloat amarillo[] = {1.0f, 1.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, amarillo);
        glMaterialfv(GL_FRONT, GL_AMBIENT, amarillo);
        glutSolidSphere(radio_sol, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glRotatef(angulo_orbita_tierra, 0.0f, 0.0f, 1.0f);
        glTranslatef(distancia_tierra, 0.0f, 0.0f);
        
        glPushMatrix();
            glRotatef(angulo_rotacion_tierra, 0.0f, 1.0f, 0.0f);
            GLfloat azul[] = {0.2f, 0.6f, 1.0f, 1.0f};
            glMaterialfv(GL_FRONT, GL_DIFFUSE, azul);
            glMaterialfv(GL_FRONT, GL_AMBIENT, azul);
            glutSolidSphere(radio_tierra, 16, 16);
        glPopMatrix();
        
        glPushMatrix();
            glRotatef(angulo_orbita_luna, 0.0f, 0.0f, 1.0f);
            glTranslatef(distancia_luna, 0.0f, 0.0f);
            
            glPushMatrix();
                glRotatef(angulo_rotacion_luna, 0.0f, 1.0f, 0.0f);
                GLfloat gris[] = {0.8f, 0.8f, 0.8f, 1.0f};
                glMaterialfv(GL_FRONT, GL_DIFFUSE, gris);
                glMaterialfv(GL_FRONT, GL_AMBIENT, gris);
                glutSolidSphere(radio_luna, 12, 12);
            glPopMatrix();
        glPopMatrix();
        
    glPopMatrix();

    glPushMatrix();
        glRotatef(angulo_orbita_marte, 0.0f, 0.0f, 1.0f);
        glTranslatef(distancia_marte, 0.0f, 0.0f);
        
        glPushMatrix();
            glRotatef(angulo_rotacion_marte, 0.0f, 1.0f, 0.0f);
            GLfloat rojo[] = {1.0f, 0.3f, 0.0f, 1.0f};
            glMaterialfv(GL_FRONT, GL_DIFFUSE, rojo);
            glMaterialfv(GL_FRONT, GL_AMBIENT, rojo);
            glutSolidSphere(radio_marte, 16, 16);
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers(); 
}

void idle() {
    angulo_rotacion_sol += Vs;
    if (angulo_rotacion_sol > 360.0f) angulo_rotacion_sol -= 360.0f;
    
    angulo_orbita_tierra += Vt;
    if (angulo_orbita_tierra > 360.0f) angulo_orbita_tierra -= 360.0f;
    
    angulo_rotacion_tierra += 3.0f * Vs;
    if (angulo_rotacion_tierra > 360.0f) angulo_rotacion_tierra -= 360.0f;
    
    angulo_orbita_luna += 2.0f * Vt;
    if (angulo_orbita_luna > 360.0f) angulo_orbita_luna -= 360.0f;
    
    angulo_rotacion_luna += 1.5f * Vs;
    if (angulo_rotacion_luna > 360.0f) angulo_rotacion_luna -= 360.0f;
    
    angulo_orbita_marte += Vt;
    if (angulo_orbita_marte > 360.0f) angulo_orbita_marte -= 360.0f;
    
    angulo_rotacion_marte += Vs;
    if (angulo_rotacion_marte > 360.0f) angulo_rotacion_marte -= 360.0f;
    
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutCreateWindow("Lab 5: Camara Siguiendo a la Tierra");

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}