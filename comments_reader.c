#include "comments_reader.h"
#include "file_preprocessor.h"
#include "utils/str_utils.h"
/*
@DOCSTART
@DOCEND
*/
const char *docExtractor(const char *input)
{

    const char *inputCharIndex_aux1 = input;
    int inputLength = strlen(input);
    printf("here%s", input);
    char *returnString = (char *)malloc(1);
    int indexaux = 0;

    returnString[0] = '\0';

    while (1)
    {
        char *end = NULL;
        // @ID Get the first occourrence by using the function
        // @ID Check if there no more occourrence of the Tokens
        const char *occourrenceAuxiliar = checkFirstOccurrence(inputCharIndex_aux1);
        if (occourrenceAuxiliar == NULL)
        {
            break;
        }

        // @ID Next Step is Jump to the start of next token occourrence
        inputCharIndex_aux1 = strstr(inputCharIndex_aux1, occourrenceAuxiliar);
        if (inputCharIndex_aux1 == NULL)
        {
            break;
        }

        inputCharIndex_aux1 += strlen(occourrenceAuxiliar);

        // @ID Do the token start Comparations and set the END variable
        if (strcmp(occourrenceAuxiliar, ID) == 0 || strcmp(occourrenceAuxiliar, INLINEDOC) == 0)
        {

            end = strstr(inputCharIndex_aux1, "\n");
            // printf("%s", end);
            if (end == NULL)
            {
                perror("Error: can't find '\\n'.\n");
                return "Error";
            }
        }
        else if (strcmp(occourrenceAuxiliar, DOCSTART) == 0)
        {

            end = strstr(inputCharIndex_aux1, DOCEND);
            if (end == NULL)
            {
                perror("Error: can't find '@DOCEND'.\n");
                return "Error";
            }
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

        if (strcmp(occourrenceAuxiliar, ID) || strcmp(occourrenceAuxiliar, INLINEDOC))
        {
            inputCharIndex_aux1 = end + 1;
        }
        else
        {
            inputCharIndex_aux1 = end + strlen(DOCEND);
        }
        // inputCharIndex_aux1 = end + strlen(DOCEND);
        //   printf("%d\n", indexaux);
        //   printf("%s\n", inputCharIndex_aux1);
    }

    return returnString;
    // input = returnString;
    // free(returnString);
}