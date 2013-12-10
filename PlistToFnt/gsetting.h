#ifndef GSETTING_H
#define GSETTING_H

#include <QString>
#include <QSettings>

class GSetting
{
public:
    static GSetting* GetInstance()
    {
        static GSetting* setting = NULL;
        if(setting==NULL)
        {
            setting = new GSetting;
        }
        return setting;
    }
    GSetting();

    void WritePlistFilePathSetting(QString plistFilePath);
    QString ReadPlistFilePathSetting();
private:
    QSettings m_setting;
};

#endif // GSETTING_H
