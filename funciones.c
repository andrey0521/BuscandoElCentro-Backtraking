//Diego Andrey Lopez Camal - 1298580
#include "cabezeras.h"
int** cargarLaberinto()
{
    int laberinto1[MAX][MAX]={
        {3,5,4,4,7,3,4,6,3},
        {6,7,5,6,6,2,6,6,2},
        {3,3,4,3,2,5,4,7,2},
        {6,5,5,1,2,3,6,5,6},
        {3,3,4,3,0,1,4,3,4},
        {3,5,4,3,2,2,3,3,5},
        {3,5,4,3,2,6,4,4,3},
        {3,5,1,3,7,5,3,6,4},
        {6,2,4,3,4,5,4,5,1}
    };
    
    int** laberinto=(int**)calloc(MAX,sizeof(int*));
    for(int i=0; i<MAX; i++){
        laberinto[i]=(int*)calloc(MAX,sizeof(int));
    }

    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            laberinto[i][j]=laberinto1[i][j];
        }
    }
    
    return laberinto;
}

Nodo crearNodo(int x, int y, int** laberinto, int n){
    Nodo nodo;
    nodo.pos[0]=x;
    nodo.pos[1]=y;
    nodo.val=laberinto[x][y];
    
    for(int i=0; i<4; i++){
        nodo.dir[i]=0;
    }

    //Posibles movimientos
    if(x-nodo.val>=0) 
        nodo.dir[0]=1;
    if(y+nodo.val<n) 
        nodo.dir[1]=1;
    if(x+nodo.val<n) 
        nodo.dir[2]=1;
    if(y-nodo.val>=0) 
        nodo.dir[3]=1;
    
    return nodo;
}

int existeMovimiento(Nodo* nodo){
    if(nodo->dir[0]==1) 
        return 1;
    if(nodo->dir[1]==1) 
        return 2;
    if(nodo->dir[2]==1) 
        return 3;
    if(nodo->dir[3]==1) 
        return 4;
    return 0;
}

void resolverLaberinto(int** laberinto, int n, Nodo** pilaDePilas, int m, int inicio_x, int inicio_y, int delay){
    if(n<=1 || m<=1) return;

    int solu=0, cont=0, x=inicio_x, y=inicio_y;
    int centro_x = n/2;
    int centro_y = n/2;
    int pasos = 0;
    
    Nodo* pila = calloc(m, sizeof(Nodo));
    int** visitados=(int**)calloc(n,sizeof(int*));

    for(int i=0; i<n; i++)
    {
        visitados[i]=(int*)calloc(n,sizeof(int));
        for(int j=0; j<n; j++){
            visitados[i][j]=0;    
        }
    }

    pila[cont]=crearNodo(x,y,laberinto,n);
    visitados[x][y]=1;

    while(1){
        // Visualizar cada paso 
        imprimirLaberinto(laberinto, n, pila, cont, visitados, x, y, solu);
        usleep(delay * 3000); 
        pasos++;
        
        // Si llegamos al centro
        if(x == centro_x && y == centro_y){
            solu++;
            
            // Guardar solución
            for(int i=0; i<m; i++)
            {
                pilaDePilas[solu-1][i].val = -1;
            }
            for(int i=0; i<=cont; i++)
            {
                pilaDePilas[solu-1][i].val = pila[i].val;
                pilaDePilas[solu-1][i].pos[0] = pila[i].pos[0];
                pilaDePilas[solu-1][i].pos[1] = pila[i].pos[1];
            }
            // Mostrar solución encontrada
            system(CLEAR);
            printf("\n*** BUSQUEDA COMPLETA ***\n");
            imprimirSolucion(laberinto,n,pilaDePilas[solu-1],m,solu);
            printf("\n\nPresiona ENTER para continuar...");
            getchar();
            
            // Hacer backtrack
            visitados[pila[cont].pos[0]][pila[cont].pos[1]] = 0;
            cont--;
            x = pila[cont].pos[0];
            y = pila[cont].pos[1];
            return;
        }
        
        int existeMov=existeMovimiento(&pila[cont]);
        
        switch (existeMov)
        {
        case 1: x-=pila[cont].val; break;
        case 2: y+=pila[cont].val; break;
        case 3: x+=pila[cont].val; break;
        case 4: y-=pila[cont].val; break;
        default:
            if(cont == 0){
                system(CLEAR);
                printf("\n*** BUSQUEDA COMPLETA ***\n");
                printf("No se encontro solucion\n");
                for(int i=0; i<solu; i++){
                    printf("\n");
                     imprimirSolucion(laberinto,n,pilaDePilas[i],m,i+1);
                }
                
                for(int i=0; i<n; i++){
                    free(visitados[i]);
                }
                free(visitados);
                return;
            }
                
            visitados[pila[cont].pos[0]][pila[cont].pos[1]] = 2;
            pila[cont].val=-1;
            
            cont--;  
            x=pila[cont].pos[0];
            y=pila[cont].pos[1];

            continue;
        }
        
        pila[cont].dir[existeMov-1]=0;

        if(visitados[x][y]==0){
            visitados[x][y]=1;
            pila[++cont]=crearNodo(x,y,laberinto,n);
        } else {
            x = pila[cont].pos[0];
            y = pila[cont].pos[1];
        }
    }

    for(int i=0; i<n; i++){
        free(visitados[i]);
    }
    free(visitados);
}

void imprimirLaberinto(int** laberinto, int n, Nodo* pila, int cont, int** visitados, int x_actual, int y_actual, int soluciones)
{
    system(CLEAR);
    
    printf("******************************************\n");
    printf("***   BUSCANDO EL CENTRO - LABERINTO   ***\n");
    printf("******************************************\n\n");
    
    // Marcar qué celdas están en la pila actual
    
    int centro_x = n/2;
    int centro_y = n/2;
    
    // Imprimir laberinto con colores
    for(int i=0; i<n ; i++)
    {
        printf("  ");
        for(int j=0; j<n; j++)
        {
            int val = laberinto[i][j];
            
            if(i == x_actual && j == y_actual){
                // Posición actual - ROJO
                printf("%s[%d]%s", RED, val, RESET);
            }
            else if(i == centro_x && j == centro_y){
                // Centro - AMARILLO
                printf("%s[%d]%s", YELLOW, val, RESET);
            }
            else if(visitados[i][j]==2){
                // En la pila actual - VERDE
                printf("%s[%d]%s", BLUE, val, RESET);
            }
            else if(visitados[i][j]==1){
                // En la pila actual - VERDE
                printf("%s[%d]%s", GREEN, val, RESET);
            }
            else{
                // Normal
                printf("[%d]", val);
            }
        }
        printf("\n");
    }
    
    printf("\n");
    printf("Estadísticas:\n");
    printf("    -Profundidad actual: %d pasos\n", cont);
    printf("    -Soluciones encontradas: %d\n", soluciones);
    printf("    -Posición: [%d][%d] = %d\n", x_actual, y_actual, laberinto[x_actual][y_actual]);
    
    printf("\nCamino actual: ");
    for(int i=0; i<=cont; i++){
        printf("[%d,%d]", pila[i].pos[0], pila[i].pos[1]);
    }
    printf("\n");
}

void imprimirSolucion(int**laberinto,int n, Nodo* pila,int m, int solu)
{
    int pasos=0;
    for(int i=0; i<m && pila[i].val!=-1; i++){
        pasos++;
    }
    printf("\nSOLUCIÓN #%d ENCONTRADA (%d pasos)\n\n",solu,pasos);
    
    int solucion[n][n];
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++){
            solucion[i][j]=0;    
        }
    }

    for(int i=0; i<m && pila[i].val!=-1; i++){
        solucion[pila[i].pos[0]][pila[i].pos[1]] = 1;
    }
    

    
    for(int i=0; i<n; i++)
    {
        printf("  ");
        for(int j=0; j<n; j++)
        {
            if(solucion[i][j]){
                printf("%s[%d]%s", GREEN, laberinto[i][j], RESET);
            } else {
                printf("[%d]", laberinto[i][j]);
            }
        }
        printf("\n");
    }
    
    printf("\nCamino: ");
    for(int i=0; i<m && pila[i].val!=-1; i++){
        printf("[%d,%d]", pila[i].pos[0], pila[i].pos[1]);
        if(!pila->pos[i]==n/2 || !pila->pos[i]==n/2 )
            printf("→");
    }
} 