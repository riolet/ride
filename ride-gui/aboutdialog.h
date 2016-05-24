/*===============================================================================
HEADER FILE:	aboutdialog.h 
					Custom QDialog dedicated to displaying large amount of
					information inside of a Dialog Form. 

PROGRAM:		Ride

FUNCTIONS:		explicit AboutDialog(const QString &title,
                         			 const QString &body,
                         			 QWidget *parent = 0);

PROGRAMMER(S):	Tyler Trepanier-Bracken

NOTES:
This custom class deals with displaying any large amount of text within a
managable window such as the GNU License Agreement, About Rix and About Ride.
===============================================================================*/

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:

    //Only this version of the constructor is allowed.
    explicit AboutDialog(const QString &title,
                         const QString &body,
                         QWidget *parent = 0);
    ~AboutDialog();

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
