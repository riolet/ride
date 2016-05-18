typedef struct error_object
{
    char *message;
    int message_length;
    int line_number;
    int column_start;
    int num_characters;
} Error;

#ifndef ERROR_OBJECT_H
#define ERROR_OBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

    int Detect_errors(Error** err, int* err_num, char* doc);
    //int Return_errors();

#ifdef __cplusplus
}
#endif
#endif  // ERROR_OBJECT_H


