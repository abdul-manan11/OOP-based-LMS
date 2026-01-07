#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QString>
#include <QFile>
#include <QDataStream>
#include <QMap>

class FileHandler {
public:
    // Write methods
    static void writeString(QDataStream& out, const QString& str);
    static void writeStringMap(QDataStream& out, const QMap<QString, QString>& map);
    static void writeDoubleMap(QDataStream& out, const QMap<QString, double>& map);
    static void writeStringVector(QDataStream& out, const QVector<QString>& vector);

    // Read methods
    static QString readString(QDataStream& in);
    static QMap<QString, QString> readStringMap(QDataStream& in);
    static QMap<QString, double> readDoubleMap(QDataStream& in);
    static QVector<QString> readStringVector(QDataStream& in);

    // File operations
    static bool fileExists(const QString& filePath);
    static void ensureDirectoryExists(const QString& dirPath);
};

#endif // FILEHANDLER_H
