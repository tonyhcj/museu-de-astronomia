#include <stdlib.h>
#include <GL/glut.h>
#include "camera.h"
#include "scene.h"

int largura = 1000;
int altura = 700;

static int mx, my, arrastando = 0;

void teclado(unsigned char k, int x, int y)
{
    switch (k) {
        case 'w': movimentaCamera( 0.3f, 0); break;
        case 's': movimentaCamera(-0.3f, 0); break;
        case 'a': movimentaCamera(0, -0.3f); break;
        case 'd': movimentaCamera(0,  0.3f); break;
        case 'p': alternaProjecao();         break;
        case 'l': alternaLuz();              break;
        case ' ': alternaAnimacao();         break;
        case 27:  exit(0);
    }
    glutPostRedisplay();
}

void especial(int k, int x, int y)
{
    switch (k) {
        case GLUT_KEY_LEFT:  giraCamera(-3, 0); break;
        case GLUT_KEY_RIGHT: giraCamera( 3, 0); break;
        case GLUT_KEY_UP:    giraCamera(0,  2); break;
        case GLUT_KEY_DOWN:  giraCamera(0, -2); break;
    }
    glutPostRedisplay();
}

void mouse(int botao, int estado, int x, int y)
{
    if (botao == GLUT_LEFT_BUTTON)
    {
        arrastando = (estado == GLUT_DOWN);
        mx = x;
        my = y;
    }
}

void movimentoMouse(int x, int y)
{
    if (!arrastando) return;
    giraCamera((x - mx) * 0.3f, -(y - my) * 0.3f);
    mx = x;
    my = y;
    glutPostRedisplay();
}

void timer(int valor)
{
    atualizaAnimacao();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);   /* ~60 quadros por segundo */
}

void desenho()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    configuraProjecao(largura, altura);
    aplicaCamera();
    desenhaCena();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    largura = (w > 0) ? w : 1;
    altura  = (h > 0) ? h : 1;
    glViewport(0, 0, largura, altura);
}

void inicializa()
{
    glClearColor(0.04f, 0.04f, 0.04f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    inicializaCamera();
    inicializaCena();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(largura, altura);
    glutCreateWindow("Museu de Astronomia - Computacao Grafica");

    inicializa();

    glutDisplayFunc(desenho);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(especial);
    glutMouseFunc(mouse);
    glutMotionFunc(movimentoMouse);
    glutTimerFunc(16, timer, 0);

    glutMainLoop();
    return 0;
}
