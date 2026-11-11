#include <GL/glut.h>
#include <math.h>
#include "camera.h"

#define DEG2RAD 0.017453292519943295f

static float camX, camY, camZ;
static float yaw, pitch;

void inicializaCamera()
{
    camX = 0.0f; camY = 3.0f; camZ = 11.0f;
    yaw = -90.0f;
    pitch = -8.0f;
}

void aplicaCamera()
{
    float cy = cosf(yaw * DEG2RAD),   sy = sinf(yaw * DEG2RAD);
    float cp = cosf(pitch * DEG2RAD), sp = sinf(pitch * DEG2RAD);

    float dx = cy * cp, dy = sp, dz = sy * cp;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              camX + dx, camY + dy, camZ + dz,
              0.0f, 1.0f, 0.0f);
}

void configuraProjecao(int largura, int altura)
{
    float aspecto = (altura == 0) ? 1.0f : (float)largura / (float)altura;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspecto, 0.5, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
