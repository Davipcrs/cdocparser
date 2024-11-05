This is the code for garantee the output (-o) file 
``` c
        else if(ch == 'i'){
           menu();
           return;
       }
       
```
## main.c 
 #### Using the project 
 To use the project you need to use anotations "@SOMETHING" inside comments (WITH THE "@")to generate docs. Substitute the "SOMETHING" with this anotations: 
 
 - DOCSTART (For starting a doc block) 
 
 - DOCEND (For ending a doc block) 
 
 - ID or INLINEDOC (For inline doc - No need to create a doc block) 
 
 - NL (For new Line) 
 
 - CODEBLOCKSTART or CBS (For creating a Code Block [Include no Commentary in the doc]) 
 
 - CODEBLOCKEND or CBE (For Ending a code block) 
 More on Code Blocks later in the doc 
 ###### Code Blocks 
 Here you can include code blocks in the documentation Its Better to use CBS and CBE and with this structure: 
 
 - DOCSTART 
 
 - CBS [Language, in this case c] 
 
 - "CODE" 
 
 - CBE 
 
 - NL 
 
 - DOCEND 
## dir_utils.c 
 This file contains the implementation for the directory utils 
 @ID This is a Linux only lib 
 
```
#include <dirent.h>
// 
```
## consts_def.h 
 this file is responsible for defining the constants of the application via macros see that the TOKENS are implemented here 
## str_utils.c 
 This file contains the implementation for the String utils 
 Get the number os occourrencies of the search string 
 Allocate memory for the new string 
## dir_utils.h 
 This is the Header file for the Dir Utils 
## str_utils.h 
 This is the Header file for the Str Utils. 
 
 Functions defined: 
``` c
void appendString(char **dest, const char *src, size_t *currentSize);
const char *removeSpaces(const char *str);
const char *checkFirstOccurrence(const char *str);
const char *formatString(const char *str, int exportType);
const char *formatCB(const char *str, int exportType);
// 
```
## file_preprocessor.c 
 This function is the function responsible to implement the file loading.
 In the input is a char point (A string) for the path of the file. 
 
``` c
bool isSingleLine = false;
bool isInMultiLine = false;
bool isCodeBlock = false;
int saveIndexOfStartComment_aux1 = 0;
int saveIndexOfStartComment_aux2 = 0;
int readIndex = 0;
int inputLength = strlen(input);
int returnStringWriteIndex = 0;
// char returnString[inputLength + 1];
char *returnString = realloc(input, (inputLength + 1) * sizeof(char));
// 
```
## file_preprocessor.h 
## comments_reader.c 
 Get the first occourrence by using the function Check if there no more occourrence of the Tokens Next Step is Jump to the start of next token occourrence Do the token start Comparations and set the END variable 
## comments_reader.h 
