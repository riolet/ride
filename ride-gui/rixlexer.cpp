/******************************************************************************
** SOURCE FILE:     rixlexer.cpp
**
** PROGRAMMER(S):   Micah Willems, Tyler Trepanier-Bracken
**
** PROGRAM:         RixLexer
**
** FUNCTIONS:       void setScintilladoc(ScintillaDoc *sd);
**                  void styleText(unsigned int start, unsigned int end);
**                  void styleToken(unsigned int length, int style);
**                  void styleError(unsigned int line, unsigned int offset, unsigned int length);
**                  void setWordChars(char *chars);
**                  void setErrorStyle(unsigned int indic, unsigned int style, unsigned int hexColour);
**                  QString description(unsigned int style) const;
**                  const char* language() const;
**                  const char* lexer() const;
**                  void handleStyleNeeded(int pos);
**                  void handleCharAdded(int pos);
**                  void handleFoundErrors();
**
** NOTES:           This class handles the visual colouring and autocompletion
**                  of the QScintilla text editor component, effectively adding
**                  all the functionality that makes it a code editor.
*******************************************************************************/
#include "rixlexer.h"
#include "syntaxcolours.h"

/******************************************************************************
** FUNCTION: 		handleStyleNeeded
** ​
** PROGRAMMER(S):	Micah Willems
** ​
** PARAMETERS:		ScintillaDoc *sd
**                      pointer to the ScintillaDoc instance
​**
** RETURNS:         void
​**
** NOTES:           Sets the ScintillaDoc associated with this RixLexer instance
******************************************************************************/
void RixLexer::setScintilladoc(ScintillaDoc *sd)
{
    _scint = sd;
}

/******************************************************************************
** FUNCTION: 		handleStyleNeeded
** ​
** PROGRAMMER(S):	Micah Willems
** ​
** PARAMETERS:		int pos
**                      The position of the cursor at the time of a "Styling
**                      needed" signal
​**
** RETURNS:         void
​**
** NOTES:           The slot connected to the signal "StylingNeeded". When the
**                  signal is emitted, this function is called. It gets the
**                  first position on the line when the signal was emitted and
**                  calls styleText
******************************************************************************/
void RixLexer::handleStyleNeeded(int pos)
{
    if (!editor())
        return;

    int start   = editor()->SendScintilla(QsciScintillaBase::SCI_GETENDSTYLED);
    int line    = editor()->SendScintilla(QsciScintillaBase::SCI_LINEFROMPOSITION,
                                          start);
    start       = editor()->SendScintilla(QsciScintillaBase::SCI_POSITIONFROMLINE,
                                          line);

    if (start != pos)
        styleText(start, pos);
}

/******************************************************************************
** FUNCTION: 		styleText (abstract implementation)
** ​
** PROGRAMMER(S):	Micah Willems
** ​
** PARAMETERS:		int start
**                      The first unstyled character
**                  int end
**                      The position of the caret
​**
** RETURNS:         void
​**
** NOTES:           Starts the styling for a section of text and sends the line
**                  of text to flex to parse through the wrapper function
**                  scan_string
******************************************************************************/
void RixLexer::styleText(int start, int end)
{
    if(end < start || !editor())
        return;

    char chars[end - start];
    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, end,
                            chars);

    startStyling(start);
    scan_string(chars);
}

/******************************************************************************
** FUNCTION: 		styleToken
** ​
** PROGRAMMER(S):	Micah Willems
** ​
** PARAMETERS:		unsigned int length
**                      The length of the token to be styled
**                  int style
**                      The style to use
​**
** RETURNS:         void
​**
** NOTES:           Styles a token according to the Rix language syntax and
**                  chosen style colours.
******************************************************************************/
void RixLexer::styleToken(unsigned int length, int style)
{
    int totLen = editor()->SendScintilla(QsciScintilla::SCI_GETTEXTLENGTH);
    int cur = editor()->SendScintilla(QsciScintilla::SCI_GETENDSTYLED);
    if (cur == totLen) {
        return;
    }
    else if (style == SyntaxColours::Default)
    {
        setStyling(length, 32);
        return;
    }
    else if (length == -2)
    {
        length = totLen - cur;
    }

    setStyling(length, style);
}

/******************************************************************************
** FUNCTION: 		styleError
** ​
** PROGRAMMER(S):	Micah Willems
** ​
** PARAMETERS:		unsigned int line
**                      The starting line
**                  unsigned int offset
**                      The offset on the line
**                  unsigned int length
**                      The length of characters to be styled
​**
** RETURNS:         void
​**
** NOTES:           Styles syntax errors.
******************************************************************************/
void RixLexer::styleError(unsigned int line, unsigned int offset, unsigned int length)
{
    if (!editor())
        return;

    int start = editor()->SendScintilla(QsciScintilla::SCI_POSITIONFROMLINE,
                                        (int) line);
    if (start > -1)
    {
        int begin = start + offset;
        editor()->SendScintilla(QsciScintilla::SCI_INDICATORFILLRANGE,
                                begin, length);
    }
}

/******************************************************************************
** FUNCTION: 		handleCharAdded
** ​
** PROGRAMMER(S):	Micah Willems
** ​
** PARAMETERS:		int pos
**                      Unknown (Scintilla signal gives unpredictable values)
​**
** RETURNS:         void
​**
** NOTES:           Slot connected to the "CharAdded" signal. Checks if the
**                  last char typed was a period. If so, gets the preceding
**                  word (if any) and calls the parser to get that variable's
**                  functions and members (if a class) and fills the
**                  autocomplete box with them.
**                  If the last char typed was a newline, it initiates error
**                  checking.
******************************************************************************/
void RixLexer::handleCharAdded(int pos)
{
    if (pos <= 0)
        return;

    char currentChar[1];
    int wordEnd = editor()->SendScintilla(QsciScintilla::SCI_GETCURRENTPOS) - 1;
    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, wordEnd,
                            wordEnd + 1, currentChar);

    if (currentChar[0] == '.')
    {
        bool onlyWordCharacters = true;
        int wordStart = editor()->SendScintilla(QsciScintillaBase::SCI_WORDSTARTPOSITION,
                                                wordEnd, onlyWordCharacters);

        if (wordEnd != wordStart)
        {
            char word[wordEnd - wordStart + 1];
            editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE,
                                    wordStart, wordEnd, word);

            activateAutocomplete(word);
        }
    }
    else if(currentChar[0] == '\n')
    {
        _scint->parseError();
        handleFoundErrors();
    }
}

/******************************************************************************
** FUNCTION: 		autoCompleteShortcut
** ​
** PROGRAMMER(S):	Micah Willems
​**
** RETURNS:         void
​**
** NOTES:           Slot connected to activateAutocomplete - autocomplete can
**                  occur both on a shortcut key and by typing a '.' following
**                  an identifier.
******************************************************************************/
void RixLexer::autoCompleteShortcut()
{
    activateAutocomplete();
}

/******************************************************************************
** FUNCTION: 		activateAutocomplete
** ​
** PROGRAMMER(S):	Dimitry Rakhlei, Micah Willems
** ​
** PARAMETERS:      std::string caller (optional text that preceded autocomp
**                      character '.')
**
** RETURNS:         void
​**
** NOTES:           This is a method that interfaces with the Autocompletion
**                  class. It calls methods that parse the current code and
**                  returns formatted strings for the widget that will display
**                  them.
******************************************************************************/
void RixLexer::activateAutocomplete(std::string caller)
{
    Q_UNUSED(caller)

    if (!editor())
        return;

    int length = editor()->SendScintilla(QsciScintilla::SCI_GETTEXTLENGTH);
    char contents[length + 1];
    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE,
                            0, length, contents);

    Autocompletion autocomp;
    autocomp.Detect(contents);
    std::vector<Class> classes = autocomp.GetClasses();
    std::vector<Function> functions = autocomp.GetFunctions();
    std::vector<std::string> formatted_functions;
    std::vector<std::string> formatted_classes;
    std::vector<std::string> insertable_class_code;
    std::vector<std::string> insertable_function_code;
    for(auto it : classes)
        formatted_classes.push_back(autocomp.FormatClass(it));
    for(auto it : functions)
        formatted_functions.push_back(autocomp.FormatFunction(it));
    for(auto it : classes)
        insertable_class_code.push_back(autocomp.AutocompleteClass(it));
    for(auto it : functions)
        insertable_function_code.push_back(autocomp.AutocompleteFunction(it));

    std::string oneLine;
    for (auto string : insertable_function_code) {
        oneLine += string + " ";
        std::cout << string << std::endl;
    }


    editor()->SendScintilla(QsciScintilla::SCI_AUTOCSHOW, (size_t)0, oneLine.c_str());
}

/******************************************************************************
** FUNCTION: 		handleFoundErrors
** ​
** PROGRAMMER(S):	Tyler Trepanier
​**
** RETURNS:         void
​**
** NOTES:           Retrieves error information from shared memory and parses
**                  and displays error highlights for each one.
******************************************************************************/
void RixLexer::handleFoundErrors()
{
    char    *cur_error;
    char    msg[1024];
    int     len;
    int     line;
    int     start;
    int     num;

    int errors = *sem_error.errNumber;
    cur_error  = sem_error.content;

    while(errors > 0)
    {
        if(sscanf(cur_error, "%d,%d,%d,%d,", &len, &line, &start, &num) == 4)
        {
            //Skip the four commas
            char* travel = cur_error;
            for(int i = 0; i < 4; i++)
            {
                travel = strstr(travel, ",") + 1;
            }
            strncpy(msg, travel, len);
            //qDebug() << "[MSG:" << msg
            //         << "] LEN:" << len
            //         << "LINE:" << line
            //         << "START:" << start
            //         << "NUM:" << num;
        }

        styleError(line, start, num);

        cur_error = strstr(cur_error, "\n") +1;
        if(cur_error == 0)
        {
            break;
        }

        errors--; // Decrement errors here.
    }
}

/******************************************************************************
** FUNCTION: 		setWordChars
** ​
** PROGRAMMER(S):	Micah Willems
** ​
** PARAMETERS:		char *chars
**                      The characters that comprise a word in Rix
​**
** RETURNS:         void
​**
** NOTES:           Sets the characters that comprise a word in Rix
******************************************************************************/
void RixLexer::setWordChars(char *chars)
{
    if (!editor())
        return;

    editor()->SendScintilla(QsciScintillaBase::SCI_SETWORDCHARS,
                            chars);
}

/******************************************************************************
** FUNCTION: 		setErrorStyle
** ​
** PROGRAMMER(S):	Micah Willems
** ​
** PARAMETERS:		unsigned int indic
**                      The indicator number (error style number) to change
**                  unsigned int style
**                      The type of style to assign
**                  unsigned int hexColour
**                      The color of the style
​**
** RETURNS:         void
​**
** NOTES:           Sets the appearance of an error indicator.
******************************************************************************/
void RixLexer::setErrorStyle(unsigned int indic, unsigned int style, unsigned int hexColour)
{
    if (!editor())
        return;

    editor()->SendScintilla(QsciScintillaBase::SCI_INDICSETSTYLE,
                            0, style);
    editor()->SendScintilla(QsciScintillaBase::SCI_INDICSETFORE,
                            0, hexColour);
    editor()->SendScintilla(QsciScintillaBase::SCI_SETINDICATORCURRENT,
                            0, indic);
}

/******************************************************************************
** FUNCTION: 		description (abstract implementation)
** ​
** PROGRAMMER(S):	Micah Willems
** ​
** PARAMETERS:		int style
**                      The style to get a descriptor for
​**
** RETURNS:         QString
**                      The description of the style
​**
** NOTES:           Returns a descriptor for a style number.
******************************************************************************/
QString RixLexer::description(int style) const
{
    switch (style)
    {
    case 1:
        return "Integer";
    case 2:
        return "Float";
    case 3:
        return "Int";
    case 4:
        return "String";
    case 5:
        return "Char";
    case 6:
        return "Class";
    case 7:
        return "Scope";
    case 8:
        return "Keyword";
    case 9:
        return "Return";
    case 10:
        return "Identifier";
    case 11:
        return "Single-line comment";
    case 12:
        return "Terminated multi-line comment";
    case 13:
        return "Unterminated multi-line comment";
    case 14:
        return "Function declaration";
    case 15:
        return "Return type";
    case 16:
        return "Function call";
    default:
        return "Unknown";
    }

    return NULL;
}

/******************************************************************************
** FUNCTION: 		language (abstract implementation)
** ​
** PROGRAMMER(S):	Micah Willems
** ​
** RETURNS:		const char*
**                      The name of the language
**
** NOTES:           Returns a descriptor of this lexer's language.
******************************************************************************/
const char* RixLexer::language() const
{
    return "Rix";
}

/******************************************************************************
** FUNCTION: 		lexer (abstract implementation)
** ​
** PROGRAMMER(S):	Micah Willems
** ​
** RETURNS:		const char*
**                      The name of the lexer
**
** NOTES:           Returns a descriptor of this lexer.
******************************************************************************/
const char* RixLexer::lexer() const
{
    return "RixLexer";
}
