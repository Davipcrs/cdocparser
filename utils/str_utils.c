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

const char *checkFirstOccurrence(const char *str)
// Adicionar Checagem até o proximo espaço
// necessário para puder desobrir o primeiro.
{
    char *inlinePos = strstr(str, INLINEDOC);
    char *nlPos = strstr(str, ID);
    char *docstartPos = strstr(str, DOCSTART);
    char *minPos = NULL;
    int auxiliar_idx = 0;

    if (inlinePos != NULL)
    {
        minPos = inlinePos;
    }
    if (nlPos != NULL && (minPos == NULL || nlPos < minPos))
    {
        minPos = nlPos;
    }
    if (docstartPos != NULL && (minPos == NULL || docstartPos < minPos))
    {
        minPos = docstartPos;
    }
    if (minPos == NULL)
    {
        return NULL;
    }

    while (minPos[auxiliar_idx] && !isspace(minPos[auxiliar_idx]))
    {
        auxiliar_idx = auxiliar_idx + 1;
    }

    char *auxiliar = (char *)malloc(auxiliar_idx + 1);
    if (auxiliar == NULL)
    {
        return NULL;
    }

    strncpy(auxiliar, minPos, auxiliar_idx);
    auxiliar[auxiliar_idx] = '\0';

    return auxiliar;
}