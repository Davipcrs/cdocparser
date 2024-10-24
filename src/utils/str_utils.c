// @ID ## str_utils.c @NL
// @ID This file contains the implementation for the String utils @NL

#include "str_utils.h"

void appendString(char **dest, const char *src, size_t *currentSize)
{
    int srcLength = strlen(src);
    int destLength = *currentSize;
    /*
    printf("strlen %ld\n", srcLength);
    printf("dlen %ld\n", destLength);
    printf("realloclen %ld\n", (srcLength + destLength + 1));
    */
    // Realoca memória para o novo tamanho necessário (texto existente + novo bloco + 1 para o terminador nulo)
    *dest = (char *)realloc(*dest, (destLength + srcLength + 1) * sizeof(char));
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
    bool isCodeBlock = false;

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

    for (; i < len; i++)
    {

        // Detect the start of a code block (@CBS)
        if (strncmp(&str[i], CBS, 4) == 0)
        {
            isCodeBlock = true;
            // Copy @CBS and move index forward
            strncpy(&result[j], CBS, 4);
            j += 4;
            i += 3; // Move past @CBS (since the loop will increment i by 1)
            continue;
        }

        if (strncmp(&str[i], CODEBLOCKSTART, 14) == 0)
        {
            isCodeBlock = true;
            // Copy @CBS and move index forward
            strncpy(&result[j], CODEBLOCKSTART, 14);
            j += 14;
            i += 13; // Move past @CBS (since the loop will increment i by 1)
            continue;
        }

        if (strncmp(&str[i], CODEBLOCKEND, 13) == 0)
        {
            isCodeBlock = false;
            // Copy @CBS and move index forward
            strncpy(&result[j], CODEBLOCKEND, 13);
            j += 13;
            i += 12; // Move past @CBS (since the loop will increment i by 1)
            continue;
        }

        // Detect the end of a code block (@CBE)
        if (strncmp(&str[i], CBE, 4) == 0)
        {
            isCodeBlock = false;
            // Copy @CBE and move index forward
            strncpy(&result[j], CBE, 4);
            j += 4;
            i += 3; // Move past @CBE (since the loop will increment i by 1)
            continue;
        }
        if (isCodeBlock)
        {
            // printf("%s, %d\n", str[i], isspace(str[i + 1]));
            if (str[i] == '\n' && isspace(str[i + 1]))
            {
                result[j] = str[i];
                i = i + 2;
                j = j + 1;
            }
            result[j] = str[i];
            j = j + 1;
        }
        else
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

    // @ID Allocate memory for the new string @NL
    int new_len = strlen(str) + (count * (replaceLen - searchLen));
    char *formatted_str = malloc((new_len + 1) * sizeof(char));
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
    formatted_str[new_len] = '\0';
    return formatted_str; // Return the new formatted strin
}

const char *formatCB(const char *str, int exportType)
{
    const char *searchString[] = {CODEBLOCKSTART, CBS, CODEBLOCKEND, CBE};
    int searchLen[4];
    searchLen[0] = strlen(searchString[0]);
    searchLen[1] = strlen(searchString[1]);
    searchLen[2] = strlen(searchString[2]);
    searchLen[3] = strlen(searchString[3]);
    int count[4];
    count[0] = 0;
    count[1] = 0;
    count[2] = 0;
    count[3] = 0;

    const char *replaceString;
    int replaceLen = 0;

    const char *tmp = str;

    // Check for @NL
    if (exportType == 1)
    {
        // exportType == 1 is .txt output
        // @NL ==> \n
        replaceString = "\n===";
        replaceLen = strlen(replaceString);
    }
    else if (exportType == 2)
    {
        // exportType == 2 is .md output
        // @NL ==> "  "
        replaceString = "\n```";
        replaceLen = strlen(replaceString);
    }
    else
    {
        return str;
    }

    for (int i = 0; i < 4; i++)
    {

        tmp = str;

        while ((tmp = strstr(tmp, searchString[i])) != NULL)
        {
            count[i] = count[i] + 1;
            tmp = tmp + searchLen[i];
        }
    }

    int newLen = strlen(str) + (count[0] * (replaceLen - searchLen[0])) + (count[1] * (replaceLen - searchLen[1])) + (count[2] * (replaceLen - searchLen[2])) + (count[3] * (replaceLen - searchLen[3]));
    char *formatted_str = malloc((newLen + 1) * sizeof(char));
    if (formatted_str == NULL)
    {
        return NULL; // Memory allocation failed
    }

    const char *src = str;
    char *dst = formatted_str;

    while (*src)
    {
        const char *next = NULL;
        int matchedIndex = -1;

        // Find the next occurrence of any search string
        for (int i = 0; i < 4; i++)
        {
            const char *pos = strstr(src, searchString[i]);
            if (pos != NULL && (next == NULL || pos < next))
            {
                next = pos;
                matchedIndex = i;
            }
        }

        if (next)
        {
            // Copy part of the string before the found search string
            size_t len = next - src;
            strncpy(dst, src, len);
            dst += len;

            // Copy the replacement string
            strcpy(dst, replaceString);
            dst += replaceLen;

            // Move the source pointer past the search string
            src = next + searchLen[matchedIndex];
        }
        else
        {
            // No more occurrences, copy the rest of the string
            strcpy(dst, src);
            break;
        }
    }
    // printf("%d\n", newLen);
    formatted_str[newLen] = '\0';

    // printf("%s\n", formatted_str);
    return formatted_str;
}
