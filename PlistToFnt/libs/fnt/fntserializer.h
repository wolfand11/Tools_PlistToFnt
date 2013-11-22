#ifndef FNTSERIALIZER_H
#define FNTSERIALIZER_H
#include <QColor>
#include <QString>
#include <QVector>
#include <QtCore>

class FntCharData
{
public:
    FntCharData()
        :m_charID(0)
        ,m_posX(0.0f)
        ,m_posY(0.0f)
        ,m_width(0.0f)
        ,m_height(0.0f)
        ,m_xoffset(0.0f)
        ,m_yoffset(0.0f)
        ,m_xadvance(0.0f)
    {}
    void InitWithData(int charID,QRectF frameRect,QSizeF offset)
    {
        m_charID = charID;
        m_posX = frameRect.x();
        m_posY = frameRect.y();
        m_width  = frameRect.width();
        m_height = frameRect.height();
        m_xoffset = offset.width();
        m_yoffset = offset.height();
    }
    QString toString(int pageId) const
    {
        QString temp;
        temp = QString("char id=%1   x=%2     y=%3     width=%4     height=%5     xoffset=%6     yoffset=%7    xadvance=%8     page=%9\n")
                .arg(QString::number(m_charID),
                     QString::number(m_posX),
                     QString::number(m_posY),
                     QString::number(m_width),
                     QString::number(m_height),
                     QString::number(m_xoffset),
                     QString::number(m_yoffset),
                     QString::number(m_xadvance),
                     QString::number(pageId)
                     );
        return temp;
    }

    char  m_charID;
    float m_posX;
    float m_posY;
    float m_width;
    float m_height;
    float m_xoffset;
    float m_yoffset;
    float m_xadvance;
};

class FntPageData
{
public:
    FntPageData()
        :m_pageId(0)
    {
    }

    QString toString() const
    {
        QString temp;
        temp = QString("page id=%1 file=\"%2\"\n")
                .arg(QString::number(m_pageId),
                     m_imagePath);
        temp += QString("chars count=%1\n").arg(QString::number(m_chars.count()));
        foreach (const FntCharData& charData, m_chars)
        {
            temp += charData.toString(m_pageId);
        }
        return temp;
    }

    int     m_pageId;
    QString m_imagePath;
    QVector<FntCharData> m_chars;
};

class FntData
{
public:
    FntData()
        :m_padding(0,0,0,0)
        ,m_lineHeight(0.0f)
    {
    }
    QString toString() const
    {
        QString temp;
        temp = QString("info face=\"GuoDong\" padding=%1,%2,%3,%4\n")
                .arg(QString::number(m_padding.red()),
                     QString::number(m_padding.green()),
                     QString::number(m_padding.blue()),
                     QString::number(m_padding.alpha())
                     );
        temp += QString("common lineHeight=%1 pages=%2\n")
                .arg(QString::number(m_lineHeight),
                     QString::number(m_pages.count()));
        foreach (const FntPageData& pageData, m_pages) {
            temp += pageData.toString();
        }
        return temp;
    }

    QColor  m_padding;
    float   m_lineHeight;
    QVector<FntPageData> m_pages;
};

class FntSerializer
{
public:
    static QString ConvertPlistVarToFntDataStr(QVariant& plistVar);
    static FntData ConvertPlistVarToFntData(QVariant& plistVar);

private:
    static QRectF ConvertStringToRectF(const QString& str);
    static QSizeF ConvertStringToSizeF(const QString& str);
    static unsigned short ConvertKeyToCharID(const QString& key);
};

#endif // FNTSERIALIZER_H
