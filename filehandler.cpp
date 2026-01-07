#include "filehandler.h"
#include <QDir>
#include <QDebug>

void FileHandler::writeString(QDataStream& out, const QString& str) {
    out << str;
}

void FileHandler::writeStringMap(QDataStream& out, const QMap<QString, QString>& map) {
    out << (qint32)map.size();
    for (auto it = map.begin(); it != map.end(); ++it) {
        out << it.key() << it.value();
    }
}

void FileHandler::writeDoubleMap(QDataStream& out, const QMap<QString, double>& map) {
    out << (qint32)map.size();
    for (auto it = map.begin(); it != map.end(); ++it) {
        out << it.key() << it.value();
    }
}

void FileHandler::writeStringVector(QDataStream& out, const QVector<QString>& vector) {
    out << (qint32)vector.size();
    for (const QString& str : vector) {
        out << str;
    }
}

QString FileHandler::readString(QDataStream& in) {
    QString str;
    in >> str;
    return str;
}

QMap<QString, QString> FileHandler::readStringMap(QDataStream& in) {
    QMap<QString, QString> map;
    qint32 size;
    in >> size;
    for (int i = 0; i < size; ++i) {
        QString key, value;
        in >> key >> value;
        map[key] = value;
    }
    return map;
}

QMap<QString, double> FileHandler::readDoubleMap(QDataStream& in) {
    QMap<QString, double> map;
    qint32 size;
    in >> size;
    for (int i = 0; i < size; ++i) {
        QString key;
        double value;
        in >> key >> value;
        map[key] = value;
    }
    return map;
}

QVector<QString> FileHandler::readStringVector(QDataStream& in) {
    QVector<QString> vector;
    qint32 size;
    in >> size;
    for (int i = 0; i < size; ++i) {
        QString str;
        in >> str;
        vector.append(str);
    }
    return vector;
}

bool FileHandler::fileExists(const QString& filePath) {
    return QFile::exists(filePath);
}

void FileHandler::ensureDirectoryExists(const QString& dirPath) {
    QDir dir(dirPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
}
