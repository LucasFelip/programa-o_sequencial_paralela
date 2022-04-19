#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>

#define TOTALCIDADES 5

int distancias[TOTALCIDADES * TOTALCIDADES];
double custos[TOTALCIDADES];

void zeraDistancia(){
    for (int i = 0; i < TOTALCIDADES * TOTALCIDADES; i++)
        distancias[i] = -1;
    for (int i = 0; i < TOTALCIDADES; i++)
        custos[i] = 0;
}

void criaGrafo(){
    int origem, destino, totalLigacoes, i, ok, distancia;

    totalLigacoes = rand() % (TOTALCIDADES * 4);
    printf("TOTAL LIGACOES: %i \n\n", totalLigacoes);

    for (i = 0; i < totalLigacoes; i++){
        ok = 0;
        while (ok == 0){
            origem = rand() % TOTALCIDADES;
            destino = rand() % TOTALCIDADES;
            if (origem != destino){
                if (distancias[(origem)*TOTALCIDADES + destino] == -1){
                    distancia = (rand() % 20) + 1;
                    distancias[(origem)*TOTALCIDADES + destino] = distancia;
                    ok = 1;
                    printf("De %i e %i com distancia: %i\n", origem, destino, distancia);
                }
            }
        }
    }
}

void calculoDistancia(){
    int i, j;
    printf("\n\nDistancias de A até B com custo C \n");
    for (i = 0; i < TOTALCIDADES; i++){
        for (j = 0; j < TOTALCIDADES; j++)
            dijkstra(i, j);
    }
}

void dijkstra(int origem, int destino){
    int *anterior, i, aux, *verticesNoCaminho, calculo;
    double distMinima, auxDist;

    verticesNoCaminho = calloc(TOTALCIDADES, sizeof(int *));
    if (verticesNoCaminho == NULL){
        printf("Erro na alocacao\n");
        exit(-1);
    }

    for (i = 0; i < TOTALCIDADES; i++){
        verticesNoCaminho[i] = 0;
        if (distancias[(origem)*TOTALCIDADES + i] != -1)
            custos[i] = distancias[(origem)*TOTALCIDADES + i];
        else
            custos[i] = HUGE_VAL;
    }

    verticesNoCaminho[origem] = 1;
    custos[origem] = 0;
    do{
        distMinima = HUGE_VAL;
        for (i = 0; i < TOTALCIDADES; i++){
            if (!verticesNoCaminho[i]){
                if (custos[i] >= 0 && custos[i] < distMinima){
                    distMinima = custos[i];
                    aux = i;
                }
            }
        }
        if (distMinima != HUGE_VAL && aux != destino){
            verticesNoCaminho[aux] = 1;
            for (i = 0; i < TOTALCIDADES; i++){
                if (!verticesNoCaminho[i]){
                    if (distancias[aux * TOTALCIDADES + i] != -1 && custos[aux] + distancias[aux * TOTALCIDADES + i] < custos[i]){
                        custos[i] = custos[aux] + distancias[aux * TOTALCIDADES + i];
                    }
                }
            }
        }
    } while (aux != destino && distMinima != HUGE_VAL);

    printf("De %i ate %i, ", origem, destino);
    printf("custa: %.0f\n", custos[destino]);
}

int main(int argc, char *argv[]){
    setlocale(LC_ALL, "Portuguese");

    float tempo;
    time_t t_init, t_fim;

    printf("Algoritmo de Dijkstra Sequencial \n\n");
    srand((unsigned)TOTALCIDADES);
    zeraDistancia();
    criaGrafo();

    t_init = time(NULL);
    calculoDistancia();
    t_fim = time(NULL);

    tempo = difftime(t_fim, t_init);
    printf("\n\nTempo de execução do algoritmo de Dijstrika: %.2fs", tempo);

    return 0;
}