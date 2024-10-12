#include "str_utils.h"

void appendString(char **dest, const char *src, size_t *currentSize)
{
    size_t srcLength = strlen(src);
    size_t destLength = *currentSize;

    // Realoca memória para o novo tamanho necessário (texto existente + novo bloco + 1 para o terminador nulo)
    *dest = (char *)realloc(*dest, destLength + srcLength + 1);
    if (*dest == NULL)
    {
        perror("Erro ao alocar memória");
        return;
    }

    // Concatena a nova string ao destino
    strcat(*dest, src);

    // Atualiza o tamanho atual
    *currentSize += srcLength;
}