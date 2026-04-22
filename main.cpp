#include <GL/glut.h>
#include <math.h>
#include <string.h>

// --- Day 5 Global Variables for Animation ---
float carX = -100.0;    // garir movement er jonno
float cloudX = -100.0;  // megh er movement er jonno

void init(void) {
    glClearColor(0.4, 0.7, 0.9, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

// --- Text Rendering
void drawText(const char* text, float x, float y, void* font) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    for (int i = 0; i < (int)strlen(text); i++) {
        glutBitmapCharacter(font, text[i]);
    }
}

// --- Circle Algorithm
void drawCircle(float x, float y, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(x + cos(theta) * radius, y + sin(theta) * radius);
    }
    glEnd();
}

// --- Building Design
void drawBuilding(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glRectf(x, y, x + width, y + height);
    glColor3f(0.8, 0.9, 1.0); // Windows
    for (float i = x + 2; i < x + width - 2; i += 5) {
        for (float j = y + 5; j < y + height - 5; j += 8) {
            glRectf(i, j, i + 3, j + 5);
        }
    }
}

// --- DIU Building
void drawDIUBuilding(float x, float y) {
    glColor3f(0.1, 0.1, 0.1); glRectf(x, y, x + 50, y + 80);
    glColor3f(0.0, 0.4, 0.2); glRectf(x + 2, y + 65, x + 48, y + 75);
    drawText("DIU MAIN CAMPUS", x + 5, y + 68, GLUT_BITMAP_HELVETICA_12);
}

// --- Cloud Design
void drawCloud(float x, float y) {
    drawCircle(x, y, 6, 1.0, 1.0, 1.0);
    drawCircle(x + 4, y + 3, 7, 1.0, 1.0, 1.0);
    drawCircle(x - 4, y + 2, 6, 1.0, 1.0, 1.0);
}

// --- Vehicles
void drawDIUBus(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0.0, 0.4, 0.2); glRectf(0, 0, 40, 15);
    glColor3f(1.0, 1.0, 1.0); glRectf(0, 8, 40, 15);
    drawCircle(8, 0, 3, 0.1, 0.1, 0.1); drawCircle(32, 0, 3, 0.1, 0.1, 0.1);
    drawText("DIU TRANSPORT", 5, 3, GLUT_BITMAP_HELVETICA_10);
    glPopMatrix();
}

void drawCar(float x, float y, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(r, g, b); glRectf(0, 0, 18, 7); glRectf(3, 7, 15, 12);
    drawCircle(4, 0, 2.5, 0.1, 0.1, 0.1); drawCircle(14, 0, 2.5, 0.1, 0.1, 0.1);
    glPopMatrix();
}

// Animation U
void update(int value) {
    // Car movement and boundary reset
    carX += 1.0;
    if (carX > 150) carX = -180;

    // Cloud movement
    cloudX += 0.1;
    if (cloudX > 200) cloudX = -200;

    glutPostRedisplay();
    glutTimerFunc(20, update, 0); // 20ms por por frame update hobe
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 1. Static Scenery
    drawCircle(75, 75, 12, 1.0, 0.9, 0.0);

    // 2. Animated Clouds
    glPushMatrix();
    glTranslatef(cloudX, 0, 0);
    drawCloud(-80, 85); drawCloud(10, 80); drawCloud(80, 85);
    glPopMatrix();

    // 3. Buildings
    drawBuilding(-98, -30, 15, 65, 0.3, 0.3, 0.3);
    drawDIUBuilding(-75, -30);
    drawBuilding(-18, -30, 20, 90, 0.4, 0.4, 0.4);
    drawBuilding(45, -30, 22, 70, 0.4, 0.3, 0.2);

    // 4. Road
    glColor3f(0.15, 0.15, 0.15); glRectf(-100, -100, 100, -30);
    glColor3f(1.0, 1.0, 1.0);
    for (float i = -100; i < 100; i += 25) glRectf(i, -66, i + 12, -64);

    // 5. Animated Traffic
    drawDIUBus(carX, -55);
    drawCar(carX + 70, -90, 0.8, 0.1, 0.1);
    drawCar(carX - 60, -90, 0.1, 0.1, 0.8);

    drawText("DIU Cityscape - Animation Integrated", -35, 95, GLUT_BITMAP_HELVETICA_18);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 750);
    glutCreateWindow("Day 5: Traffic and Cloud Animation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0); // Animation start call
    glutMainLoop();
    return 0;
}
