#ifndef ERROR_OBJECT_H
#define ERROR_OBJECT_H

/*-------------------------------------------------------------------------*//**
 * @brief      Type define of an error object
 * @details    This object indicates an error message that can be returned to
 *             the GUI.
 * @author     Duy Pham
 * @version    1.0
 */
struct error_object
{
    char *message;
    int message_length;
    int line_number;
    int column_start;
    int num_characters;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief      { function_description }
 *
 * @param      err      The err
 * @param      err_num  The err num
 * @param      doc      The doc
 *
 * @return     { description_of_the_return_value }
 */
    int Detect_errors(struct error_object** err, int* err_num, char* doc);

#ifdef __cplusplus
}
#endif
#endif  // ERROR_OBJECT_H
