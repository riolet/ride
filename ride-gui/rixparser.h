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

extern Error** errors;

/**
 * @brief      { function_description }
 *
 * @param      err      The err
 * @param      err_num  The err num
 * @param      doc      The doc
 *
 * @return     { description_of_the_return_value }
 */
extern int Detect_errors(Error** err, int* err_num, char* doc);

/**
 * @brief      { function_description }
 *
 * @return     { description_of_the_return_value }
 */
extern int Return_errors();

#endif // ERROR_OBJECT_H
