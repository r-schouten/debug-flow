#include "filesystem.h"

FileSystem::FileSystem()
{
}

bool FileSystem::openFile(QWidget *widget, QJsonObject &json, QString& fileName)
{
    QUrl openFilePath = QFileDialog::getOpenFileUrl(widget, "open flow", QUrl(""), "Debug Flow(*.dflow)");
    fileName = openFilePath.fileName();

    if(openFilePath.isEmpty())
    {
        //user pressed cancel
        return false;
    }
    else
    {
        qDebug("open directory %s",openFilePath.toString().toStdString().c_str());

        if(!openFile(openFilePath, json))
        {
            return false;
        }
        filePath = openFilePath;
        hasFileLocation = true;
    }
}
bool FileSystem::openFile(QUrl &path, QJsonObject &json)
{
    QFile file(path.toLocalFile());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox msgBox;
        msgBox.setText(QString("Error can't open file\n%1").arg(file.errorString().toStdString().c_str()));
        msgBox.exec();
        return false;
    }

    QTextStream in(&file);
    QByteArray raw = in.readAll().toUtf8();

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(raw,&parseError);
    if(document.isNull())
    {
        QMessageBox msgBox;
        msgBox.setText(QString("Error parsing file\n%1").arg(parseError.errorString()));
        msgBox.exec();
        return false;
    }
    json = document.object();
    return true;
}
void FileSystem::saveFile(QJsonObject *json)
{
     if(!hasFileLocation)qFatal("[fatal][FileSystem]no file location set");

     QFile file(filePath.toLocalFile());

     if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
         QMessageBox msgBox;
         msgBox.setText(QString("Error saving file\n%1").arg(file.errorString().toStdString().c_str()));
         msgBox.exec();
         return;
     }
     QJsonDocument document(*json);
     QByteArray rawData = document.toJson();
     QTextStream out(&file);
     out << rawData;
     file.close();
}
void FileSystem::saveFile(QWidget *widget, QJsonObject *json, bool saveAs)
{
    if((hasFileLocation) && (!saveAs))
    {
        saveFile(json);
    }
    else
    {
        QUrl saveFilePath = QFileDialog::getSaveFileUrl(widget, "save flow", QUrl(""), "Debug Flow(*.dflow)");

        if(saveFilePath.isEmpty())
        {
            //user pressed cancel
            return;
        }
        else
        {
            qDebug("save directory %s",saveFilePath.toString().toStdString().c_str());
            filePath = saveFilePath;
            hasFileLocation = true;
            saveFile(json);

        }
    }
}
