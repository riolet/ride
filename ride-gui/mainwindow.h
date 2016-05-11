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
#include <QFileSystemModel>
#include <QTreeView>
#include <string>
#include "globals.h"
#include "scintilladoc.h"
#include "aboutdialog.h"

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

    void on_button_save_clicked();

    void on_button_new_file_clicked();

    void documentWasModified();

    void tabChanged(int index);

    void on_button_zoom_in_clicked();

    void on_button_zoom_out_clicked();

    void on_button_saveall_clicked();

    void displayAboutRix();

    void displayAboutRide();

    void displayLicense();

    bool displayUnsavedChanges();

    bool saveAs();

    bool save();

    void open();

    void newFile();

    void closeEvent(QCloseEvent *event);

private:    //Private Functions
    void setupScintilla();
    void setupFileTree();
    void setupShortcuts(); // Not done yet.
    void setupMenuActions();
    void setDocumentModified(bool modified);



    // Combined MainWindow and Scintilla methods
    void loadFile(QString filename);

private:    //Private Variables
    Ui::MainWindow              *ui;            // Central UI Widget Container
    std::vector<ScintillaDoc*>  textEditList;   // Container of Scintilla widgets
    int                         cur_index;      // Currently active document index
    QFileSystemModel            *model;         // File Directory View
    QTreeView                   *tree;          // File Directory Tree
    ScintillaDoc                *cur_doc;       // Currently active document

};

#endif // MAINWINDOW_H
