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
#endif  // ERROR_OBJECT_H

#ifdef __cplusplus
/**
 * @brief      Trigger the parser to parse the source code and find errors.
 *
 * @param      err      The array of errors
 * @param      err_num  The number of found errors
 * @param      doc      The source document
 *
 * @return     { description_of_the_return_value }
 */
int Initialize_error_detect_thread(struct error_object **err, int *err_num, char *doc);

extern "C" int errorDetect(struct error_object **err, int *err_num, char *doc);
#endif
