#include "gsetting.h"
#include <QtGui>

#define kPlistFilePath  "PlistFilePath"

GSetting::GSetting()
{
    QCoreApplication::setOrganizationName("GuoDong");
    QCoreApplication::setOrganizationDomain("com.guodong.org");
    QCoreApplication::setApplicationName("PlistToFnt");
}

void GSetting::WritePlistFilePathSetting(QString plistFilePath)
{
    m_setting.setValue(kPlistFilePath,plistFilePath);
}

QString GSetting::ReadPlistFilePathSetting()
{
    return m_setting.value(kPlistFilePath,QDir::homePath()).toString();
    //return m_setting.value(kPlistFilePath,QDir::currentPath()).toString();
}
