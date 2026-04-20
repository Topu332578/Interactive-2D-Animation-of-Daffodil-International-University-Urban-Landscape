#include <GL/glut.h>
#include <math.h>
#include <string.h>


float cloudX = -100.0; // cloud movement er jonno base logic

void init(void) {
    // Background color: Sky Blue
    glClearColor(0.4, 0.7, 0.9, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Coordinate System: -100 to 100
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

// Algorithm:Circle Drawing
void drawCircle(float x, float y, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(x + cos(theta) * radius, y + sin(theta) * radius);
    }
    glEnd();
}

//  Cloud
void drawCloud(float x, float y) {
    drawCircle(x, y, 5, 1.0, 1.0, 1.0);
    drawCircle(x + 4, y + 2, 6, 1.0, 1.0, 1.0);
    drawCircle(x - 4, y + 1, 5, 1.0, 1.0, 1.0);
}

//  Basic Building Structure
void drawBuilding(float x, float y, float width, float height, float r, float g, float b) {
    // Building Body
    glColor3f(r, g, b);
    glRectf(x, y, x + width, y + height);

    // Windows
    glColor3f(0.8, 0.9, 1.0);
    for (float i = x + 2; i < x + width - 2; i += 5) {
        for (float j = y + 5; j < y + height - 5; j += 8) {
            glRectf(i, j, i + 3, j + 5);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    // 1. Sun
    drawCircle(70, 70, 12, 1.0, 0.9, 0.0);

    // 2. Road
    glColor3f(0.2, 0.2, 0.2);
    glRectf(-100, -100, 100, -30);

    // Road Lines
    glColor3f(1.0, 1.0, 1.0);
    for (float i = -100; i < 100; i += 25) {
        glRectf(i, -66, i + 12, -64);
    }


    // 3.Buildings
    drawBuilding(-90, -30, 20, 60, 0.3, 0.3, 0.3); // Gray building
    drawBuilding(-60, -30, 25, 80, 0.2, 0.2, 0.3); // Dark building
    drawBuilding(40, -30, 22, 50, 0.4, 0.3, 0.2);  // Brown building
    drawBuilding(70, -30, 20, 75, 0.3, 0.4, 0.3);  // Greenish building

    // 4. Clouds
    drawCloud(-50, 70);
    drawCloud(10, 80);
    drawCloud(-80, 85);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("Day 1 & 2: Environment and Infrastructure");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
