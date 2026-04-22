#include <GL/glut.h>
#include <math.h>
#include <string.h>

// --- Global Variables (Day 5 & 6) ---
float carX = -100.0;
float cloudX = -100.0;
float wheelAngle = 0.0;

void init(void) {
    // Background color: Sky Blue
    glClearColor(0.4, 0.7, 0.9, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Coordinate system setup (-100 to 100)
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

// --- Text Rendering (Day 3) ---
void drawText(const char* text, float x, float y, void* font) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    for (int i = 0; i < (int)strlen(text); i++) {
        glutBitmapCharacter(font, text[i]);
    }
}

// --- Circle Algorithm (Day 1) ---
void drawCircle(float x, float y, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159 / 180.0;
        glVertex2f(x + cos(theta) * radius, y + sin(theta) * radius);
    }
    glEnd();
}

// --- Ferris Wheel (Day 6) ---
void drawFerrisWheel(float x, float y) {
    // Stand
    glColor3f(0.2, 0.2, 0.2);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(x, y); glVertex2f(x - 12, y - 35);
    glVertex2f(x, y); glVertex2f(x + 12, y - 35);
    glEnd();

    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(wheelAngle, 0, 0, 1); // Rotation Transformation

    // Wheel Ring
    glColor3f(0.5, 0.2, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159 / 180.0;
        glVertex2f(cos(theta) * 20, sin(theta) * 20);
    }
    glEnd();

    // Spokes
    glBegin(GL_LINES);
    for (int i = 0; i < 8; i++) {
        float theta = i * 45 * 3.14159 / 180.0;
        glVertex2f(0, 0); glVertex2f(cos(theta) * 20, sin(theta) * 20);
    }
    glEnd();

    // Cabins with Counter-Rotation
    for (int i = 0; i < 8; i++) {
        float theta = i * 45 * 3.14159 / 180.0;
        glPushMatrix();
        glTranslatef(cos(theta) * 20, sin(theta) * 20, 0);
        glRotatef(-wheelAngle, 0, 0, 1);
        glColor3f(1.0, 0.2, 0.2); glRectf(-4, -4, 4, 1);
        glPopMatrix();
    }
    glPopMatrix();
}

// --- DIU Building (Day 3) ---
void drawDIUBuilding(float x, float y) {
    glColor3f(0.1, 0.1, 0.1); glRectf(x, y, x + 55, y + 85); // Body
    glColor3f(0.0, 0.4, 0.2); glRectf(x + 2, y + 70, x + 53, y + 80); // Green Belt
    drawText("DIU MAIN CAMPUS", x + 5, y + 73, GLUT_BITMAP_HELVETICA_12);

    // Windows
    glColor3f(0.3, 0.5, 0.8);
    for(float j=y+5; j<y+65; j+=12)
        for(float i=x+5; i<x+50; i+=12) glRectf(i, j, i+8, j+8);
}

// --- Standard Building (Day 2) ---
void drawBuilding(float x, float y, float w, float h, float r, float g, float b) {
    glColor3f(r, g, b); glRectf(x, y, x + w, y + h);
    glColor3f(0.8, 0.9, 1.0);
    for (float i = x + 2; i < x + w - 2; i += 6)
        for (float j = y + 5; j < y + h - 5; j += 10) glRectf(i, j, i + 3, j + 6);
}

// --- Cloud (Day 2) ---
void drawCloud(float x, float y) {
    drawCircle(x, y, 7, 1.0, 1.0, 1.0);
    drawCircle(x + 5, y + 2, 8, 1.0, 1.0, 1.0);
    drawCircle(x - 5, y + 1, 7, 1.0, 1.0, 1.0);
}

// --- DIU Bus (Day 4) ---
void drawDIUBus(float x, float y) {
    glPushMatrix(); glTranslatef(x, y, 0);
    glColor3f(0.0, 0.4, 0.2); glRectf(0, 0, 45, 18); // Bus Body
    glColor3f(1.0, 1.0, 1.0); glRectf(0, 10, 45, 18); // Top part
    drawCircle(10, 0, 4, 0.1, 0.1, 0.1); drawCircle(35, 0, 4, 0.1, 0.1, 0.1); // Wheels
    drawText("DIU TRANSPORT", 5, 3, GLUT_BITMAP_HELVETICA_10);
    glPopMatrix();
}

// --- Private Car (Day 4) ---
void drawCar(float x, float y, float r, float g, float b) {
    glPushMatrix(); glTranslatef(x, y, 0);
    glColor3f(r, g, b); glRectf(0, 0, 20, 8); glRectf(4, 8, 16, 14);
    drawCircle(5, 0, 3, 0.1, 0.1, 0.1); drawCircle(15, 0, 3, 0.1, 0.1, 0.1);
    glPopMatrix();
}

// --- Animation Update Logic (Day 5) ---
void update(int value) {
    carX += 1.2; if (carX > 150) carX = -200;
    cloudX += 0.15; if (cloudX > 250) cloudX = -250;
    wheelAngle += 1.5; if (wheelAngle > 360) wheelAngle -= 360;

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // 1. Sun (Day 1)
    drawCircle(75, 75, 12, 1.0, 0.9, 0.0);

    // 2. Animated Clouds (Day 2 & 5)
    glPushMatrix(); glTranslatef(cloudX, 0, 0);
    drawCloud(-120, 85); drawCloud(-40, 75); drawCloud(60, 88); drawCloud(140, 80);
    glPopMatrix();

    // 3. Buildings (Day 2 & 3)
    drawBuilding(-95, -30, 20, 60, 0.3, 0.3, 0.3);
    drawDIUBuilding(-70, -30);
    drawBuilding(45, -30, 20, 50, 0.4, 0.3, 0.2);
    drawBuilding(70, -30, 25, 80, 0.2, 0.2, 0.3);

    // 4. Ferris Wheel (Day 6)
    drawFerrisWheel(15, 10);

    // 5. Road (Day 1)
    glColor3f(0.15, 0.15, 0.15); glRectf(-100, -100, 100, -30);
    glColor3f(1.0, 1.0, 1.0);
    for (float i = -100; i < 100; i += 30) glRectf(i, -66, i + 15, -63);

    // 6. Animated Traffic (Day 4 & 5)
    drawDIUBus(carX, -58);
    drawCar(carX + 80, -92, 0.8, 0.1, 0.1); // Red Car
    drawCar(carX - 80, -92, 0.1, 0.1, 0.8); // Blue Car

    drawText("DIU Endless Cityscape - Complete Project", -40, 95, GLUT_BITMAP_HELVETICA_18);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1300, 750);
    glutCreateWindow("DIU Cityscape - Day 1 to 6 Full Integration");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
