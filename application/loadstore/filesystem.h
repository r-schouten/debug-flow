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
    bool openFile(QWidget *widget, QJsonObject &qjsonObject, QString &fileName);

    void saveFile(QWidget *widget, QJsonObject *json, bool saveAs);
private:
    bool openFile(QUrl &path, QJsonObject &json);
    void saveFile(QJsonObject *json);
};

