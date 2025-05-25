#include "funciones.h"

void desbloquear(int fila, int col, int filas, int columnas, int** numeros, int** reveladas) {
    // Fuera de límites
    if (fila < 0 || fila >= filas || col < 0 || col >= columnas) return;

    // No revelar si ya está revelada o si tiene bandera
    if (reveladas[fila][col] == 1 || reveladas[fila][col] == 2) return;

    // Revelar la celda actual
    reveladas[fila][col] = 1;

    // Si el número no es 0, no se expande
    if (numeros[fila][col] != 0) return;

    // Expandir a vecinos
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Ignorar la celda actual
            int ni = fila + dx;
            int nj = col + dy;

            // Validar límites
            if (ni >= 0 && ni < filas && nj >= 0 && nj < columnas) {
                // Solo revelar vecinos que NO tengan bandera y NO estén revelados
                if (reveladas[ni][nj] == 0) {
                    if (numeros[ni][nj] == 0) {
                        desbloquear(ni, nj, filas, columnas, numeros, reveladas);
                    } else {
                        reveladas[ni][nj] = 1;
                    }
                }
                // Si reveladas[ni][nj] == 2 (bandera), NO hacer nada, no revelar
            }
        }
    }
}

int main(int argc, char* argv[])
{

    semilla();
    size_t filas = 10, columnas = 10;

    int cantidad=cantMinas(filas,columnas); //setea la cantidad d minas
    sMinas minubi[cantidad]; //struct donde cada "mina" tiene su posicion x,y



    int** minas = crearMatriz(filas,columnas); // crea la matriz fila representativa de las minas
    int** numeros = crearMatriz(filas,columnas); // crea la matriz representativa de los numeros
    int** reveladas = crearMatriz(filas, columnas);

    inicializarMatriz(minas,filas,columnas); // inicializa ambas matrices en cero
    inicializarMatriz(numeros,filas,columnas);
    inicializarMatriz(reveladas, filas, columnas);

    posMinas(minas,filas,columnas,minubi,cantidad);
    posNumeros(minas,numeros,filas,columnas,minubi,cantidad);
//
    mostrarMatriz(minas,filas,columnas);
    printf("\n/////////////////////////\n\n");
    mostrarMatriz(numeros,filas,columnas);



    // Inicializar SDL
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init(); // Inicializar SDL_ttf
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* ventana = SDL_CreateWindow("Matriz con SDL2",
                                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                           WINDOW_WIDTH, WINDOW_HEIGHT,
                                           SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* surfaceMina = IMG_Load("mina.png");
    SDL_Texture* texturaMina = SDL_CreateTextureFromSurface(renderer, surfaceMina);
    SDL_FreeSurface(surfaceMina);

    SDL_Surface* surfaceBandera = IMG_Load("bandera.png");
    SDL_Texture* texturaBandera = SDL_CreateTextureFromSurface(renderer, surfaceBandera);
    SDL_FreeSurface(surfaceBandera);


    TTF_Font* fuente = TTF_OpenFont("Arial.ttf", 20);

    // Dibujar la matriz
    dibujarMatriz(ventana, renderer, minas, fuente, numeros, reveladas, texturaBandera);

    // Esperar hasta que el usuario cierre la ventana
    SDL_Event evento;
    int ejecutando = 1;
    while (ejecutando) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                ejecutando = 0;
            }
            else if (evento.type == SDL_MOUSEBUTTONDOWN) {
                int x = evento.button.x;
                int y = evento.button.y;
//                printf("Hiciste click en la posicion (%d, %d)\n", x/CELL_SIZE,y/CELL_SIZE);
//                printf("Hiciste click en la posicion (%d, %d)\n", x,y);
                int col = x / CELL_SIZE;
                int fila = y / CELL_SIZE;
                int boton = evento.button.button;
                printf("Hiciste click en la posicion (%d, %d)\n", fila,col);

                int posx = cuadrante(fila);
                    int posy = cuadrante(col);
                    SDL_Rect celda = {
                                posy,
                                posx,
                                CELL_SIZE,
                                CELL_SIZE
                            };
                if (boton == SDL_BUTTON_RIGHT)
                {

                    if(reveladas[fila][col]==0){
                        reveladas[fila][col]=2;
                        SDL_RenderCopy(renderer, texturaBandera, NULL, &celda);
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // borde negro
                        SDL_RenderDrawRect(renderer, &celda);
                        SDL_RenderPresent(renderer);
                    }else{
                    if(reveladas[fila][col]==2){
                        reveladas[fila][col]=0;
                        if(minas[fila][col]!=1){
                            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // gris oscuro
                            SDL_RenderFillRect(renderer, &celda);
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // borde negro
                            SDL_RenderDrawRect(renderer, &celda);
                            SDL_RenderPresent(renderer);}
                        else{
                            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // rojo
                            SDL_RenderFillRect(renderer, &celda);
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // borde negro
                            SDL_RenderDrawRect(renderer, &celda);
                            SDL_RenderPresent(renderer);
                        }
                    }}


                }
                if (boton == SDL_BUTTON_LEFT) {
                    if (minas[fila][col] == 1) {
                        reveladas[fila][col]=3;
                        dibujarMatriz(ventana, renderer, minas, fuente, numeros, reveladas, texturaMina);
                        ejecutando = 0; // pisaste una mina
                    }
                     else {
                        if(reveladas[fila][col]==0){
                        desbloquear(fila, col, filas, columnas, numeros, reveladas);
                        dibujarMatriz(ventana, renderer, minas, fuente, numeros, reveladas, texturaBandera);}
                    }
                }

            }
        }
        SDL_Delay(10); // Pequeña espera para no consumir CPU

    }
    TTF_CloseFont(fuente);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    SDL_DestroyTexture(texturaMina);
    SDL_DestroyTexture(texturaBandera);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
    }
