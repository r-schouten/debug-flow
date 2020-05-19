#pragma once

#include <QObject>
#include <QFileDialog>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QJsonParseError>
class FileSystem
{
public:
    QUrl filePath = QUrl("");
    bool hasFileLocation = false;

    FileSystem();
    QString getFileName();
    bool openFile(QWidget *widget, QJsonObject &qjsonObject, QString &fileName);
    bool saveFile(QWidget *widget, QJsonObject *json, bool saveAs);

private:
    bool openFile(QUrl &path, QJsonObject &json);
    void saveFile(QJsonObject *json);
};

