/* src/metricas.h */
#ifndef METRICAS_H
#define METRICAS_H

typedef struct {
    unsigned long comparacoes;  /* comparações entre dois valores do vetor */
    unsigned long trocas;       /* trocas de dois elementos, ou cópias/deslocamentos */
} Metricas;

#endif