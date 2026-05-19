#include <GL/glut.h>

// Variables de la ventana
int winWidth = 800;
int winHeight = 400;
float angulo = 0.0f; // Para rotar la tetera y verla mejor

// Función que dibuja nuestro objeto (la tetera)
void dibujarEscena() {
    glPushMatrix();
        glRotatef(angulo, 0.5f, 1.0f, 0.0f); // Le puse un poco de rotación en X también para que se vea mejor
        
        // Cambiamos la tetera por un cubo de alambre
        glutWireCube(1.5); 
        
    glPopMatrix();
}

void display() {
    // Limpiamos la pantalla UNA sola vez
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculamos el aspecto (relación de aspecto) de la MITAD de la pantalla
    float aspecto = (float)(winWidth / 2) / (float)winHeight;

    // ========================================================
    // LADO IZQUIERDO: Proyección Ortográfica
    // ========================================================
    // 1. Definimos el Viewport a la mitad izquierda de la ventana
    glViewport(0, 0, winWidth / 2, winHeight);

    // 2. Configuramos la Proyección Ortográfica
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // (izquierda, derecha, abajo, arriba, cerca, lejos)
    glOrtho(-3.0 * aspecto, 3.0 * aspecto, -3.0, 3.0, 1.0, 10.0);

    // 3. Configuramos la Cámara
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 2.0, 6.0,  // Ojo
              0.0, 0.0, 0.0,  // Centro
              0.0, 1.0, 0.0); // Arriba

    // 4. Dibujamos en naranja
    glColor3f(1.0f, 0.5f, 0.0f); 
    dibujarEscena();


    // ========================================================
    // LADO DERECHO: Proyección en Perspectiva
    // ========================================================
    // 1. Definimos el Viewport a la mitad derecha de la ventana
    glViewport(winWidth / 2, 0, winWidth / 2, winHeight);

    // 2. Configuramos la Proyección en Perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // (angulo_vision, aspecto, cerca, lejos)
    gluPerspective(45.0, aspecto, 1.0, 10.0);

    // 3. Configuramos la Cámara (Exactamente en la misma posición)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 2.0, 6.0,  // Ojo
              0.0, 0.0, 0.0,  // Centro
              0.0, 1.0, 0.0); // Arriba

    // 4. Dibujamos en azul celeste
    glColor3f(0.0f, 0.8f, 1.0f); 
    dibujarEscena();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    // Evitamos división por cero
    if (h == 0) h = 1;
    winWidth = w;
    winHeight = h;
}

void idle() {
    angulo += 0.02f; // Animación suave
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // Ventana más ancha que alta para acomodar las dos vistas
    glutInitWindowSize(800, 400); 
    glutCreateWindow("Izquierda: Ortografica  |  Derecha: Perspectiva");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape); // Importante para recalcular la división
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}