#include "comments_reader.h"
#include "file_preprocessor.h"
#include "utils/str_utils.h"

const char *docExtractor(const char *input)
{
    const char *inputCharIndex_aux1 = input;
    int inputLength = strlen(input);
    char *returnString = (char *)malloc(1);

    returnString[0] = '\0';

    while ((inputCharIndex_aux1 = strstr(inputCharIndex_aux1, DOCSTART)) != NULL)
    {
        inputCharIndex_aux1 += strlen(DOCSTART);
        const char *end = strstr(inputCharIndex_aux1, DOCEND);
        if (end == NULL)
        {
            perror("Error: can't find '@DOCEND'.\n");
            return "Error";
        }

        size_t length = end - inputCharIndex_aux1;
        char *auxText = (char *)malloc(length + 1);
        if (auxText == NULL)
        {
            perror("mem error");
            free(returnString);
            return "mem error";
        }

        strncpy(auxText, inputCharIndex_aux1, length);
        auxText[length] = '\0';

        appendString(&returnString, auxText, &length);

        free(auxText);

        inputCharIndex_aux1 = end + strlen(DOCEND);
    }

    return returnString;
    // input = returnString;
    // free(returnString);
}