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
