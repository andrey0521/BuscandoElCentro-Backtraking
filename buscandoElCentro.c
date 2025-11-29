//Diego Andrey Lopez Camal - 1298580
#include "cabezeras.h"

int main(int argc, char *argv[])
{

    if (argc < 3) {
        return 1;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);  

    int **laberinto=cargarLaberinto();
    int m=MAX*MAX;
    Nodo** pilaDePilas=(Nodo**)calloc(m,sizeof(Nodo*));
    
    for(int i=0; i<m; i++)
    {
        pilaDePilas[i]=(Nodo*)calloc(m,sizeof(Nodo));
        for(int j=0; j<m; j++){
            pilaDePilas[i][j].val=-1;    
        }
    }

    printf("*** BUSCANDO EL CENTRO  - LABERINTO ***\n");
    printf("Glosario de colores:\n");
    printf("%s[X]%s = Posición actual\n", RED, RESET);
    printf("%s[X]%s = Camino en la pila\n", GREEN, RESET);
    printf("%s[0]%s = Centro (objetivo)\n", YELLOW, RESET);
    printf("%s[X]%s = Solución encontrada\n\n", BLUE, RESET);
    printf("Presiona ENTER para comenzar...");
    getchar();
    
    int inicio_x = a;
    int inicio_y = b;
    int delay = 100;
    
    resolverLaberinto(laberinto, MAX, pilaDePilas, m, inicio_x, inicio_y, delay);
    
    // Liberar memoria
    for(int i=0; i<m; i++){
        free(pilaDePilas[i]);
    }
    for(int i=0; i<MAX; i++){
        free(laberinto[i]);
    }
    free(laberinto);
    free(pilaDePilas);
    
    return 0;
}

