# Museu 3D - Computação Gráfica

Projeto desenvolvido para a disciplina de Computação Gráfica. O programa consiste em uma cena interativa em 3D que simula a sala de um museu espacial utilizando **C**, **OpenGL** e **GLUT**.

##  Estrutura do Projeto

O código-fonte está dividido em módulos para facilitar a manutenção e organização:

* **`main.c`**: Inicializa a janela GLUT, configura os parâmetros globais do OpenGL (teste de profundidade, normalização, materiais) e gerencia o loop principal de renderização.
* **`camera.c` / `camera.h`**: Controla a projeção em perspectiva (`gluPerspective`), o posicionamento (`gluLookAt`), a movimentação horizontal (frente/trás e lateral), a rotação da câmera e os limites de colisão com as paredes da sala.
* **`scene.c` / `scene.h`**: Responsável pela iluminação da cena (`GL_LIGHT0`) e pela modelagem geométrica do ambiente e das exposições do museu.

##  Objetos Modelados na Cena

* **Ambiente**: Piso e três paredes (fundo, esquerda e direita) formando a galeria.
* **Saturno**: Esfera central com anéis inclinados feitos com `glutSolidTorus` sobre um pedestal.
* **Foguete**: Estrutura composta por base, corpo cilíndrico (`gluCylinder`), bico cônico (`glutSolidCone`), três aletas estabilizadoras e escotilha.
* **Sistema Solar**: Exposição suspensa alinhada próxima à parede do fundo contendo o Sol e os planetas representados por esferas de diferentes raios e cores.

## Pré-requisitos e Compilação (Linux)

Para compilar o projeto em sistemas baseados em Debian/Ubuntu, certifique-se de ter o compilador `gcc` e as bibliotecas de desenvolvimento do OpenGL/GLUT instaladas:

```bash
sudo apt update
sudo apt install build-essential freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
```

### Como Compilar

Dentro da pasta do projeto, execute o comando abaixo para compilar todos os arquivos `.c` e vincular as bibliotecas gráficas:

```bash
gcc *.c -o museu -lGL -lGLU -lglut -lm
```

### Como Executar

```bash
./museu
```
