#ifndef CONSTS_DEF_H
#define CONSTS_DEF_H
//@DOCSTART
// ##consts_def.h
// this file is responsible for defining the constants of the application via macros
// see that the TOKENS are implemented here
//@DOCEND

#ifndef FILE_CHUNK_SIZE
#define FILE_CHUNK_SIZE 4096
#endif

#define DOCSTART "@DOCSTART"
#define DOCEND "@DOCEND"
#define FUNCNAME "@FUNCNAME"
#define NL "@NL"
#define IGNORESPACINGCORRECTIONSTART "@IGNORESPACINGCORRETIONSTART"
#define ISCS "@ISCS" // IGNORESPACINGCORRETION
#define IGNORESPACINGCORRECTIONEND "@IGNORESPACINGCORRETIONEND"
#define ISCE "@ISCE" // IGNORESPACINGCORRETION
#define INLINEDOC "@INLINEDOC"
#define ID "@ID" // INLINEDOC

#endif