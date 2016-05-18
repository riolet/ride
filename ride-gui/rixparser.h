#ifndef ERROR_OBJECT_H
#define ERROR_OBJECT_H

typedef struct error_object
{
    char *message;
    int message_length;
    int line_number;
    int column_start;
    int num_characters;
} Error;

Error** errors;

extern int Detect_errors(Error** err, int* err_num, char* doc);
extern int Return_errors();

#endif // ERROR_OBJECT_H
