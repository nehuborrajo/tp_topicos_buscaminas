#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define COL 10
#define FIL 10
#define SIN_MEM NULL
////////////////////
#define N 10              // tamaño de la matriz (N x N)
#define CELL_SIZE 50      // tamaño de cada celda en     píxeles
#define WINDOW_WIDTH  (N * CELL_SIZE)
#define WINDOW_HEIGHT (N * CELL_SIZE)

typedef struct
{
    int x;
    int y;
}sMinas;

void mostrarMatriz(int** m,size_t,size_t);
int sumarDiago(int m[][COL]);
int** crearMatriz (size_t ,size_t );
void destruirMatriz (int **m,size_t filas);
void inicializarMatriz(int** m, size_t f, size_t c);
void semilla();
int cantMinas(size_t,size_t);
void posMinas(int** m,size_t filas,size_t columnas, sMinas minas[],int);
void posNumeros(int**,int** n,size_t ,size_t ,sMinas pos[],int );
void dibujarMatriz(SDL_Window*, SDL_Renderer*, int**,TTF_Font*, int**, int**, SDL_Texture*);
void dibujarNumero(int, int, TTF_Font*, SDL_Renderer*, int**);
int cuadrante(int);
#endif // FUNCIONES_H_INCLUDED
