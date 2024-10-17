#include "str_utils.h"

void appendString(char **dest, const char *src, size_t *currentSize)
{
    size_t srcLength = strlen(src);
    size_t destLength = *currentSize;
    /*
    printf("strlen %ld\n", srcLength);
    printf("dlen %ld\n", destLength);
    printf("realloclen %ld\n", (srcLength + destLength + 1));
    */
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

const char *removeSpaces(const char *str)
{
    int i = 0, j = 0;
    int len = strlen(str);
    int space_found = 0;

    // Allocate memory for the result string (same size as the original)
    char *result = (char *)malloc(len + 1);
    if (result == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // Skip leading spaces
    while (isspace(str[i]))
    {
        i = i + 1;
    }

    for (i; i < len; i++)
    {
        // If current character is not a space, copy it
        if (!isspace(str[i]))
        {
            result[j] = str[i];
            space_found = 0;
            j = j + 1;
        }
        // If current character is a space and the last character was not a space, copy a single space
        else if (!space_found)
        {
            result[j] = ' ';
            space_found = 1;
            j = j + 1;
        }
    }

    // Remove trailing space if any
    if (j > 0 && result[j - 1] == ' ')
    {
        j = j - 1;
    }

    // Null-terminate the resulting string
    result[j] = '\0';

    return result;
}

const char *formatString(const char *str, int exportType)
{

    const char *searchString = "@NL";
    int searchLen = strlen(searchString);
    const char *replaceString;
    int replaceLen = 0;

    int count = 0;
    const char *tmp = str;

    // Check for @NL
    if (exportType == 1)
    {
        // exportType == 1 is .txt output
        // @NL ==> \n
        replaceString = "\n";
        replaceLen = strlen(replaceString);
    }
    else if (exportType == 2)
    {
        // exportType == 2 is .md output
        // @NL ==> "  "
        replaceString = "  \n";
        replaceLen = strlen(replaceString);
    }
    else
    {
        return str;
    }

    // @ID Get the number os occourrencies of the search string @NL
    while ((tmp = strstr(tmp, searchString)) != NULL)
    {
        count = count + 1;
        tmp = tmp + searchLen;
    }

    // @ID Allocate memory for the new string
    size_t new_len = strlen(str) + count * (replaceLen - searchLen) + 1;
    char *formatted_str = (char *)malloc(new_len);
    if (formatted_str == NULL)
    {
        return NULL; // Memory allocation failed
    }

    const char *src = str;
    char *dst = formatted_str;
    while (*src)
    {
        const char *next = strstr(src, searchString);
        if (next)
        {
            // Copy part of the string before the @NL
            strncpy(dst, src, next - src);
            dst += next - src;

            // Copy the replacement (either \n or "  ")
            strcpy(dst, replaceString);
            dst += replaceLen;

            // Skip the @NL in the source string
            src = next + searchLen;
        }
        else
        {
            // No more occurrences, copy the rest of the string
            strcpy(dst, src);
            break;
        }
    }

    return formatted_str; // Return the new formatted strin
}