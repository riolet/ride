#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickView>
#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QFile>
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

private:    //Private Functions
    void setupScintilla();
    void setupFileTree();

private:    //Private Variables
    std::vector<ScintillaDoc> textEditList;   // Container of Scintilla widgets
    unsigned int                cur_index;      // Currently active document index
    Ui::MainWindow  *ui;                        // Central UI Widget Container
    QTreeView       *tree;                      // File Directory Tree

};

#endif // MAINWINDOW_H
