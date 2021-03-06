#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QDir>
#include "gsetting.h"
#include "./libs/qtplist/PListParser.h"
#include "./libs/qtplist/PListSerializer.h"
#include "./libs/fnt/fntserializer.h"

#define kPlistFileSuffix    ".plist"
#define kFntFileSuffix      ".fnt"

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

void Dialog::ShowMessage(const QString& msg)
{
    ui->textEdit->setText(msg);
}

void Dialog::selectFile()
{
    QString plistFilePath = GSetting::GetInstance()->ReadPlistFilePathSetting();
    m_fileFullPath = QFileDialog::getOpenFileName(this,
                                                  "Select Plist File",
                                                  plistFilePath,
                                                  tr("Plist (*.plist)"));

    if(m_fileFullPath.isEmpty())
    {
        m_message = "Please select plist file";

    }
    else
    {
        m_message = "You Selected File: \n\n";
        m_message += m_fileFullPath;
        GSetting::GetInstance()->WritePlistFilePathSetting(m_fileFullPath);
    }
    ShowMessage(m_message);
}

void Dialog::convertFile()
{
    QFile readFile(m_fileFullPath);
    if(!readFile.open(QFile::ReadOnly | QIODevice::Text))
    {
        ShowMessage("ERROR:\n Open plist file failed!\n Please Select Plist file.");
        return;
    }
    QVariant plistVar = PListParser::parsePList(&readFile);
    QString fntStr = FntSerializer::ConvertPlistVarToFntDataStr(plistVar);
    QString fntFileFullPath = m_fileFullPath.replace(kPlistFileSuffix,kFntFileSuffix);
    QFile writeFile(fntFileFullPath);
    writeFile.open(QFile::WriteOnly | QIODevice::Text);
    writeFile.write(fntStr.toStdString().c_str());
    ShowMessage("Convert Completed!\n Please Select Plist file.");
}
