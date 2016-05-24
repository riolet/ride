#ifndef SYNTAXCOLOURS_H
#define SYNTAXCOLOURS_H

namespace SyntaxColours {

    const int Default          = -1;
    const int Noncoloured      = 0;
    const int Integer          = 1;
    const int Float            = 2;
    const int Int              = 3;
    const int String           = 4;
    const int Char             = 5;
    const int Class            = 6;
    const int Scope            = 7;
    const int Keyword          = 8;
    const int Return           = 9;
    const int Identifier       = 10;
    const int Comm             = 11;
    const int MultiComm        = 12;
    const int UnterMultiComm   = 13;
    const int FunctionDecl     = 14;
    const int ReturnType       = 15;
    const int FunctionCall     = 16;

    const int colourValues[17] = {
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
