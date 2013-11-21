#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QDir>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::selectFile()
{
    m_fileFullPath = QFileDialog::getOpenFileName(this,
                                                  "Select Plist File",
                                                  QDir::homePath(),
                                                  tr("Plist (*.plist)"));

    if(m_fileFullPath.isEmpty())
    {
        m_message = "Please select plist file";

    }
    else
    {
        m_message = "You Selected File: \n\n";
        m_message += m_fileFullPath;
    }
    ui->textEdit->setText(m_message);
}

void Dialog::convertFile()
{
}
