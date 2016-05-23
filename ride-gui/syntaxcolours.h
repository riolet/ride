#ifndef SYNTAXCOLOURS_H
#define SYNTAXCOLOURS_H

namespace SyntaxColours {

    static int Default          = -1;
    static int Noncoloured      = 0;
    static int Integer          = 1;
    static int Float            = 2;
    static int Int              = 3;
    static int String           = 4;
    static int Char             = 5;
    static int Class            = 6;
    static int Scope            = 7;
    static int Keyword          = 8;
    static int Return           = 9;
    static int Identifier       = 10;
    static int Comm             = 11;
    static int MultiComm        = 12;
    static int UnterMultiComm   = 13;
    static int FunctionDecl     = 14;
    static int ReturnType       = 15;
    static int FunctionCall     = 16;

    static int colourValues[17] = {
        (0 | (0 << 8) | (0 << 16)),     // Noncoloured
        (0 | (0 << 8) | (255 << 16)),   // Integer
        (0 | (0 << 8) | (255 << 16)),   // Float
        (0 | (0 << 8) | (255 << 16)),   // Int
        (255 | (0 << 8) | (0 << 16)),   // String
        (255 | (0 << 8) | (0 << 16)),   // Char
        (0 | (0 << 8) | (255 << 16)),   // Class
        (0 | (0 << 8) | (0 << 16)),     // Scope
        (0 | (0 << 8) | (255 << 16)),   // Keyword
        (0 | (0 << 8) | (255 << 16)),   // Return
        (0 | (0 << 8) | (0 << 16)),     // Identifier
        (0 | (180 << 8) | (0 << 16)),   // Comm
        (0 | (180 << 8) | (0 << 16)),     // MultiComm
        (0 | (180 << 8) | (0 << 16)),     // UnterMultiComm
        (0 | (255 << 8) | (255 << 16)), // FunctionDecl
        (255 | (0 << 8) | (255 << 16)), // ReturnType
        (0 | (255 << 8) | (255 << 16))  // FunctionCall
    };
}

#endif
