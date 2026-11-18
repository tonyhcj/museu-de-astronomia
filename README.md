# Museu 3D - Computação Gráfica

Projeto desenvolvido para a disciplina de Computação Gráfica. O programa é uma cena interativa em 3D que simula a sala de um museu de astronomia, utilizando **C**, **OpenGL** e **GLUT**.

## Estrutura do Projeto

O código-fonte está dividido em módulos para facilitar a manutenção e a organização:

* **`main.c`**: Inicializa a janela GLUT, configura os parâmetros globais do OpenGL (teste de profundidade, normalização, material por cor), registra os callbacks de desenho, redimensionamento, teclado e teclas especiais, e inicia o loop principal.
* **`camera.c` / `camera.h`**: Controla a projeção em perspectiva (`gluPerspective`), o posicionamento da câmera (`gluLookAt`), a movimentação horizontal (frente/trás e lateral), a rotação (yaw e pitch) e os limites de colisão com as paredes da sala.
* **`scene.c` / `scene.h`**: Responsável pela iluminação da cena (`GL_LIGHT0`) e pela modelagem geométrica do ambiente e das exposições do museu.

## Objetos Modelados na Cena

* **Ambiente**: Piso e três paredes (fundo, esquerda e direita) formando a galeria. As superfícies são geradas pela função `superficie`, que subdivide cada plano em uma grade de quadrados para melhorar a iluminação.
* **Sistema Solar**: Sol com emissão de luz (`GL_EMISSION`) e Terra posicionada a partir dele por transformações aninhadas, sobre um pedestal.
* **Saturno**: Esfera inclinada com anel feito de `glutSolidTorus` achatado, sobre um pedestal.
* **Telescópio**: Tripé de três pernas (rotacionadas em 120°) e tubo feito com `gluCylinder`, apontado para o alto.

Os pedestais são cubos unitários escalados com `glScalef`.

## Transformações Utilizadas

* `glTranslatef`: posiciona cada peça na sala.
* `glRotatef`: inclina Saturno, distribui as pernas do tripé e aponta o telescópio.
* `glScalef`: achata o anel de Saturno e forma os pedestais.
* `glPushMatrix` / `glPopMatrix`: isolam as transformações de cada peça.

## Câmera e Projeção

* **Projeção em perspectiva**: `gluPerspective(60, aspecto, 0.5, 100)`, com campo de visão de 60° e aspecto ajustado ao tamanho da janela.
* **Câmera em primeira pessoa**: a direção do olhar é calculada a partir de `yaw` e `pitch` e passada ao `gluLookAt`.
* **Colisão**: a câmera é limitada às dimensões da sala e não atravessa as paredes.

## Controles

| Tecla | Ação |
|-------|------|
| `W` / `S` | Andar para frente / para trás |
| `A` / `D` | Andar para a esquerda / para a direita |
| `←` / `→` | Girar a câmera horizontalmente |
| `↑` / `↓` | Olhar para cima / para baixo |
| `ESC` | Sair do programa |

## Pré-requisitos e Compilação (Linux)

Para compilar em sistemas baseados em Debian/Ubuntu, instale o compilador `gcc` e as bibliotecas de desenvolvimento do OpenGL/GLUT:

```bash
sudo apt update
sudo apt install build-essential freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
```

### Como Compilar

Dentro da pasta do projeto, execute:

```bash
gcc *.c -o museu -lGL -lGLU -lglut -lm
```

### Como Executar

```bash
./museu
```
