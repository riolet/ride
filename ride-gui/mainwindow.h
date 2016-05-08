#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickView>
#include <QAction>
#include <QApplication>
#include <QCloseEvent>

#include <QFileInfo>
#include <QFileDialog>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPoint>
#include <QSettings>
#include <QSize>
#include <QStatusBar>
#include <QTextStream>
#include <QToolBar>
#include <QDir>
#include <QFileSystemModel>
#include <QTreeView>
#include <string>
#include <vector>
#include "globals.h"
#include "scintilladoc.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:     //Public Functions
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_button_open_clicked();

private:    //Private Functions
    void setupScintilla();
    void setupFileTree();
    void loadFile(QString filename);

private:    //Private Variables
    Ui::MainWindow              *ui;            // Central UI Widget Container
    std::vector<ScintillaDoc>   textEditList;   // Container of Scintilla widgets
    int                         cur_index;      // Currently active document index
    QTreeView                   *tree;          // File Directory Tree
    ScintillaDoc                *cur_doc;       // Currently active document

};

#endif // MAINWINDOW_H
