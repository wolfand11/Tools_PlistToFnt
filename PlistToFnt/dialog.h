#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
public slots:
    void selectFile();
    void convertFile();
private:
    void ShowMessage(const QString& msg);

    Ui::Dialog *ui;

    QString m_fileFullPath;
    QString m_message;
};

#endif // DIALOG_H
