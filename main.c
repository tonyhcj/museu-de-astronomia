#include <GL/glut.h>
#include "camera.h"
#include "scene.h"

int largura = 1000;
int altura = 700;

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

    glutMainLoop();
    return 0;
}
