# ride [![Build Status](https://drone.io/github.com/berong91/ride/status.png)](https://drone.io/github.com/berong91/ride/latest)
RIDE - An IDE for the Rix Language
==================================================================
Rix is an expressive and efficient language for the C ecosystem. Rix uses C libraries natively and generates easy to understand C code.

You can learn more about the Rix language by reading the README_rix.md located inside this same directory.

R-ix
I-ntegrated 
D-evelopment
E-nvironment

This program is built using the Qt Open Source and with the Text Editor QScintilla, a port of scintilla to Qt.

Features
========
RIDE is a prototype platform that has the basic text functionality of:
(Save / Save As)    -Saving a File 
(Open)              -Opening a File and displaying its contents onto 
                     the scintilla text surface 
(New File)          -Creation a new blank scintilla text surface.  
(Zoom In/Out)       -Zoom in and out functionality 
(Undo/Redo)         -Undo or Redo an action 
(License)           -Displaying the Open Source License Agreement 
(Copy/Cut/Paste)    -Able to cut, copy and paste text onto the 
                     scintilla text surface.

In additon, RIDE has been configured to have keyword highlighting 
and RIX error detection every time you hit the `enter` or `return` key.

Dependencies
============
-Qt 5.6       (built with Qt 5.6.0,)    
    [http://www.qt.io/]
    
-Qt Creator   (QtCreator v3 was used to build this project)
    [http://www.qt.io/] 

-QScintilla   (built with QScintilla2)  
    [https://www.riverbankcomputing.com/software/qscintilla/download]
    
-Rix Programming Language
    [https://github.com/riolet/rix]    

Get Started with Ubuntu
================================================================
1.  Download Qt 5.6 and follow their installation instructions
2.  Download Qt Creator and follow their installation instructions
3.  Download QScintilla
4.  Follow QScintilla's instructions up until you see any mention of
    the usage of qmake.
        Note: The standard installed version of qmake does not work,
              you have to use the Qt 5.6 version of qmake (refer to
              the known issues for instructions on how to do this).
5.  sudo apt-get install libgl1-mesa-dev
6.  clone from the git repository [https://github.com/riolet/rix]
7.  follow the Rix installation instructions
8.  Copy these files into your Rix folder
       `rix`      <-- Used to compile your Rix files.  
       `paths.sh` <-- Used to link the copied rix file and compile
9.  Execute the paths.sh file with the command:
        $. paths.sh

Team
====
Concept: 
[Rohana Rezel](https://github.com/rrezel) ([Riolet Corporation](https://github.com/riolet))

Design and implementation: 
[Phillip Hood](https://github.com/pvgh) 
[Dimitry Rakhlei](https://github.com/DimitryRakhlei) 
[Duy Pham](https://github.com/berong91)
[Tyler Trepanier](https://github.com/Tmanthegamer)
[Micah Willems](https://github.com/micahwillems)
(final year students at BCIT, Burnaby, BC, Canada)

Known Issues
============
Ubuntu 16.04 - May 2016 : Qt Version 5.6.0 installation
    When installing Qt5.6 Open source, the qmake that results from 
    your installation will always be the wrong version. Many of our 
    team has had issues where it pointed to a qmake for Qt4 which was 
    not installed at all. 
    
    The only work-around for this is for all terminal-based qmake 
    usage, it is recommended to ALWAYS use the qmake found in the '/
    path/to/Qt/5.6/gcc_64/qmake'. 
    
    If that doesn't work:
    1) Open an instance of Qt Creator
    2) Build a new Qt example program from their examples
    3) Open the menu bar Tools->Options->Build & Run-> Qt Versions
    4) Copy the file path that is pointing to the Qt 5.6.0
    
Ubuntu 16.04 - May 2016 : Qt 5.6 and Qt Creator3 installation via 
                          GitHub
    Was unable to install Qt 5.6 properly via their github via a 
    virtual machine and using drone.io so the only known way 
    currently of properly installing Qt is to go to 
    [http://www.qt.io/], download the proper version and install 
    using the GUI installation.
    
Ubuntu 16.04 - May 2016 : "/usr/bin/ld cannot find -lGL"
    On newly installed ubuntu or fedora machines, you may find 
    yourself missing an important package that Qt uses. 
    
    To solve this on ubuntu machines use: 
    `sudo apt-get install libgl1-mesa-dev`.
    
    On Fedora machines, type in the error inside Google and we wish 
    you the best of luck.

Unfinished Features
===================
Themehandler:
-using the colours obtained from this class and using it with the 
 rixlexer class

Mainwindow:
-Requires Rix information file
-Requires Ride information file 
-Multiple tabs: Foundation for many tabs (uses a cur_doc pointer for 
                the current document however adding in new tabs is 
                not done.)
