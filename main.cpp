/*
 *  File:		main.cpp
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "piecemodel.h"
#include "3dParty/filesavedialog.h"
#include "3dParty/fileopendialog.h"

int main(int argc, char *argv[])
{
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // 3d Party controls
    qmlRegisterType<FileOpenDialog>("KulloFileDialogs", 1, 0, "FileOpenDialog");
    qmlRegisterType<FileSaveDialog>("KulloFileDialogs", 1, 0, "FileSaveDialog");
    //

    PieceModel model;
    engine.rootContext()->setContextProperty("boardModel", &model);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *chessContainer = (engine.rootObjects().value(0))->findChild<QObject*>("chessContainer");
    Q_ASSERT(chessContainer != NULL);
    QObject::connect(&model, SIGNAL(reloadData(QVariant)), chessContainer, SLOT(reloadData(QVariant)));

    return app.exec();
}
