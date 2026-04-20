#include <GL/glut.h>
#include <math.h>

void init(void) {
    // Background color (Sky Blue)
    glClearColor(0.4, 0.7, 0.9, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 2D Coordinate System: Screen ke -100 theke +100 porjonto vag kora hoyeche
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

// Circle Drawing Algorithm
void drawCircle(float x, float y, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        // Algorithm: theta ke radian e niye cos/sin diye coordinate ber kora
        float theta = i * 3.14159 / 180;
        glVertex2f(x + cos(theta) * radius, y + sin(theta) * radius);
    }
    glEnd();
}

void display() {
    // Protibar frame clear kora hocche
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 1. Sun Drawing (Algorithm: Trigonometric Circle)
    drawCircle(70, 70, 12, 1.0, 0.9, 0.0);

    // 2. Road Drawing (Algorithm: Area Filling / Scan Conversion)
    glColor3f(0.2, 0.2, 0.2); // Road color (Dark Grey)
    glRectf(-100, -100, 100, -30);

    // Road Divider Lines (White dashes)
    glColor3f(1.0, 1.0, 1.0);
    for (float i = -100; i < 100; i += 20) {
        glRectf(i, -66, i + 10, -64);
    }

    // Graphics swap kora (Double buffering er jonno)
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    // Double buffer ebong RGB mode enable kora
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Day 1: Scenery Foundation");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
