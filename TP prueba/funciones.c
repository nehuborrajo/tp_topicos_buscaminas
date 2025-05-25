#include "funciones.h"

void semilla()
{
    srand(time(NULL));
}

void mostrarMatriz(int** m, size_t filas, size_t columnas)
{

    for(int i=0;i<filas;i++)
    {
        for(int j=0;j<columnas;j++)

            printf("%d ",m[i][j]);
        printf("\n");
    }
}

int sumarDiago(int m[][COL])
{
    int acum=0;
    for(int i=0;i<FIL;i++)
        acum+=m[i][i];
    return acum;
}

int** crearMatriz(size_t filas, size_t columnas) //size_t tamElem
{
    int **m=(int**) malloc(filas * sizeof(void*));
    if(!m)
        return SIN_MEM;

    int **ult=m+filas-1;

    for(int **i=m;i<=ult;i++)
    {
        *i=(int*) malloc(sizeof(int)*columnas);
        if(!*i)
        {
            destruirMatriz(m,i-m);
            return NULL;
        }
    }
    return m;
}

void destruirMatriz (int **m,size_t filas)
{
    int **ult=m+filas-1;
    for(int **i=m;i<=ult;i++)
        free(*i);
    free(m);
}

void inicializarMatriz(int** m, size_t f, size_t c)
{
    for (int i = 0; i < f; i++)
        for (int j = 0; j < c; j++)
            m[i][j] = 0;
}


int cantMinas(size_t filas,size_t columnas)
{
    int cant=0;
    cant=(filas*columnas*0.15); //pos totales * factor dificultad
    return cant;
}

void posMinas(int** m,size_t filas,size_t columnas, sMinas minas[], int cantidad)
{
 int x,y;

 int mc = 0;

while (mc < cantidad) {
    x = rand() % filas;
    y = rand() % columnas;

    if (m[x][y] == 0)
    {
        m[x][y] = 1;
        minas[mc].x=x;
        minas[mc].y=y;
        mc++;
    }

        //printf("[%d,%d]\n",x,y);
    }
}

void posNumeros(int** m,int** n,size_t filas,size_t columnas,sMinas pos[],int cantidad)
{
    for(int i=0;i<cantidad;i++)
    {
        int x,y;
        x=pos[i].x;
        y=pos[i].y;
        for(int o=-1;o<=1;o++)
        {
            for(int p=-1;p<=1;p++)
            {

              if ((x+o) >= 0 && (x+o) < filas && (y+p) >= 0 && (y+p) < columnas)
        {
                if(m[x+o][y+p]!=1)
                {
                    n[x+o][y+p]++;
            }
                }


        }


    }
    }
    }

///////////////////////////////////////////////////////////////////

void dibujarMatriz(SDL_Window* ventana, SDL_Renderer* renderer, int** minas, TTF_Font* fuente, int** numeros, int** reveladas, SDL_Texture* textura) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fondo blanco
    SDL_RenderClear(renderer);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            SDL_Rect celda = {
                j * CELL_SIZE,
                i * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE
            };

            if(minas[i][j]==1) //si es una mina lo pinta de rojo
            {
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // gris oscuro
                SDL_RenderFillRect(renderer, &celda);
            }
            else if(reveladas[i][j]==0){ //si no es celda revelada la pinta de gris oscuro
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // gris oscuro
                SDL_RenderFillRect(renderer, &celda);
            }
            else{ //cuando se revela la pinta de gris claro
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // gris claro
                SDL_RenderFillRect(renderer, &celda);
                if (numeros[i][j] > 0) {
                        dibujarNumero(i, j, fuente, renderer, numeros);
                    }
            }
            if(reveladas[i][j]==2)
            {
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // gris oscuro
                SDL_RenderFillRect(renderer, &celda);
                SDL_RenderCopy(renderer, textura, NULL, &celda);
            }
            if(minas[i][j]==1 && reveladas[i][j]==3)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // rojo
                SDL_RenderFillRect(renderer, &celda);
                SDL_RenderCopy(renderer, textura, NULL, &celda);
            }


            //dibuja los bordes de la celda
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // borde negro
            SDL_RenderDrawRect(renderer, &celda);
        }
    }

    SDL_RenderPresent(renderer);
}

int cuadrante(int num)
{
    int pos = num * CELL_SIZE;
    return pos;
}

void dibujarNumero(int i, int j, TTF_Font* fuente, SDL_Renderer* renderer, int** numeros)
{
    char texto[2];
    sprintf(texto, "%d", numeros[i][j]);

    SDL_Color colorTexto = {0, 0, 0, 255};
    SDL_Surface* surfaceTexto = TTF_RenderText_Blended(fuente, texto, colorTexto);
    SDL_Texture* texturaTexto = SDL_CreateTextureFromSurface(renderer, surfaceTexto);

    SDL_Rect destino = {
        j * CELL_SIZE + (CELL_SIZE - surfaceTexto->w) / 2,
        i * CELL_SIZE + (CELL_SIZE - surfaceTexto->h) / 2,
        surfaceTexto->w,
        surfaceTexto->h
    };
    SDL_RenderCopy(renderer, texturaTexto, NULL, &destino);
    SDL_FreeSurface(surfaceTexto);
    SDL_DestroyTexture(texturaTexto);
    SDL_RenderPresent(renderer); // actualiza la pantalla
}




