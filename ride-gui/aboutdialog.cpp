/*===============================================================================
HEADER FILE:	aboutdialog.cpp 
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

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(const QString &title, const QString &body, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->title->setText(title);
    ui->textbody->setText(body);
    show();
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
