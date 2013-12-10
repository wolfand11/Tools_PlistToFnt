#include "fntserializer.h"
#include <QDebug>

#define kPlistKey_frames                "frames"
#define kPlistKey_metadata              "metadata"
#define kPlistKey_realTextureFileName   "realTextureFileName"
#define kPlistKey_frame                 "frame"
#define kPlistKey_offset                "offset"
#define kPlistKey_sourceSize            "sourceSize"

FntData FntSerializer::ConvertPlistVarToFntData(QVariant &plistVar)
{
    FntData tempFntData;
    FntPageData tempFntPage;
    if(plistVar.type() != QVariant::Map)
    {
        qDebug() << "plist isn't map" << endl;
    }
    QVariantMap rootVar = plistVar.toMap();
    if(rootVar.count() != 2)
    {
        qDebug() << "plist map isn't two elements" << endl;
    }
    QVariantMap metadataVar = rootVar.value(kPlistKey_metadata).toMap();
    QVariant imagePathVar = metadataVar.value(kPlistKey_realTextureFileName);
    tempFntPage.m_imagePath = imagePathVar.toString();
    tempFntPage.m_pageId = 0;
    QVariantMap framesVar = rootVar.value(kPlistKey_frames).toMap();
    FntCharData tempCharData;
    unsigned short charUnicodeValue = 0;
    QRectF frame;
    QSizeF offset;
    QSizeF sourceSize;
    foreach (const QString& key, framesVar.keys()) {
        QVariantMap itemVar = framesVar.value(key).toMap();
        charUnicodeValue = ConvertKeyToCharID(key);
        QString frameStr = itemVar.value(kPlistKey_frame).toString();
        QString offsetStr = itemVar.value(kPlistKey_offset).toString();
        if(!sourceSize.isValid())
        {
            QString sourceSizeStr = itemVar.value(kPlistKey_sourceSize).toString();
            sourceSize = ConvertStringToSizeF(sourceSizeStr);
            tempFntData.m_lineHeight = sourceSize.height();
        }
        frame = ConvertStringToRectF(frameStr);
        offset = ConvertStringToSizeF(offsetStr);

        tempCharData.InitWithData(charUnicodeValue,
                                  frame,
                                  offset);
        tempFntPage.m_chars.push_back(tempCharData);
    }
    tempFntData.m_pages.push_back(tempFntPage);
    return tempFntData;
}

QString FntSerializer::ConvertPlistVarToFntDataStr(QVariant &plistVar)
{
    FntData fntData = ConvertPlistVarToFntData(plistVar);
    return fntData.toString();
}

QRectF FntSerializer::ConvertStringToRectF(const QString& str)
{
    //{{198,0},{18,30}}
    QRectF temp;
    int tempIndexBegin = 2;
    int tempIndexEnd = str.indexOf(',');
    QString xStr = str.mid(tempIndexBegin,tempIndexEnd-tempIndexBegin);
    tempIndexBegin = tempIndexEnd+1;
    tempIndexEnd = str.indexOf('}',tempIndexBegin);
    QString yStr = str.mid(tempIndexBegin,tempIndexEnd-tempIndexBegin);
    tempIndexBegin = tempIndexEnd+3;
    tempIndexEnd = str.indexOf(',',tempIndexBegin);
    QString wStr = str.mid(tempIndexBegin,tempIndexEnd-tempIndexBegin);
    tempIndexBegin = tempIndexEnd+1;
    tempIndexEnd = str.indexOf('}',tempIndexBegin);
    QString hStr = str.mid(tempIndexBegin,tempIndexEnd-tempIndexBegin);
    temp.setX(xStr.toFloat());
    temp.setY(yStr.toFloat());
    temp.setWidth(wStr.toFloat());
    temp.setHeight(hStr.toFloat());
    return temp;
}

QSizeF FntSerializer::ConvertStringToSizeF(const QString& str)
{
    // {18,30}
    QSizeF temp;
    int tempIndexBegin = 1;
    int tempIndexEnd = str.indexOf(',');
    QString wStr = str.mid(tempIndexBegin,tempIndexEnd-tempIndexBegin);
    tempIndexBegin = tempIndexEnd+1;
    tempIndexEnd = str.indexOf('}',tempIndexBegin);
    QString hStr = str.mid(tempIndexBegin,tempIndexEnd-tempIndexBegin);
    temp.setWidth(wStr.toFloat());
    temp.setHeight(hStr.toFloat());
    return temp;
}

unsigned short FntSerializer::ConvertKeyToCharID(const QString& key)
{
    int charStrIndexBegin = key.lastIndexOf('_');
    charStrIndexBegin++;
    int charStrIndexEnd = key.lastIndexOf('.');
    QString charStr = key.mid(charStrIndexBegin,charStrIndexEnd-charStrIndexBegin);
    return *(charStr.utf16());
}
