#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "algoritmos.h"

typedef struct {
    const char *nome;
    void (*fn)(int[], int, Metricas *);
} Algoritmo;

static const Algoritmo ALGS[] = {
    {"bubble",    bubbleSort},
    {"selection", selectionSort},
    {"insertion", insertionSort},
    {"merge",     mergeSort},
    {"quick",     quickSort},
    {"heap",      heapSort},
};
#define NUM_ALGS (sizeof ALGS / sizeof ALGS[0])

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "uso: %s <n> [bubble|selection|insertion|merge|quick|heap]\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "n deve ser um inteiro positivo\n");
        return 1;
    }
    const char *alvo = (argc >= 3) ? argv[2] : NULL;

    int *orig = malloc((size_t)n * sizeof(int));
    int *v    = malloc((size_t)n * sizeof(int));
    if (orig == NULL || v == NULL) {
        fprintf(stderr, "falta de memória\n");
        free(orig);
        free(v);
        return 1;
    }

    srand(42);                         /* semente fixa: execuções reprodutíveis */
    for (int i = 0; i < n; i++)
        orig[i] = rand() % 1000000;

    int encontrou = 0;
    for (size_t k = 0; k < NUM_ALGS; k++) {
        if (alvo != NULL && strcmp(alvo, ALGS[k].nome) != 0)
            continue;
        encontrou = 1;

        memcpy(v, orig, (size_t)n * sizeof(int));   /* cada algoritmo ordena uma cópia */
        Metricas m = {0, 0};

        clock_t ini = clock();                       /* cronometra só a ordenação */
        ALGS[k].fn(v, n, &m);
        clock_t fim = clock();

        double ms = 1000.0 * (double)(fim - ini) / CLOCKS_PER_SEC;
        printf("%-10s n=%d  tempo=%.3f ms  comparações=%lu  trocas=%lu\n",
               ALGS[k].nome, n, ms, m.comparacoes, m.trocas);
    }

    if (!encontrou)
        fprintf(stderr, "algoritmo desconhecido: %s\n", alvo);

    free(orig);
    free(v);
    return encontrou ? 0 : 1;
}