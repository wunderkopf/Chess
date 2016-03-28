TEMPLATE = app

QT += qml quick widgets

QT += core-private
QT += gui-private


SOURCES += main.cpp \
    piece.cpp \
    piecemodel.cpp \
    rook.cpp \
    king.cpp \
    bishop.cpp \
    pawn.cpp \
    knight.cpp \
    queen.cpp \
    3dParty/fileopendialog.cpp \
    3dParty/filesavedialog.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    piece.h \
    piecemodel.h \
    rook.h \
    king.h \
    bishop.h \
    pawn.h \
    knight.h \
    queen.h \
    3dParty/fileopendialog.h \
    3dParty/filesavedialog.h

DISTFILES +=
