/*
 *  File:		main.qml
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *  Images: https://commons.wikimedia.org/wiki/Category:SVG_chess_pieces/Maurizio_Monge
 *  Kullo file dialogs: https://github.com/kullo/qml-file-dialog-demo
 *
 */
import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import KulloFileDialogs 1.0
import QtQuick.Dialogs 1.1

ApplicationWindow {
    id: mainWindow
    title: qsTr("Chess")
    width: 640
    height: 480
    visible: true

    toolBar: ToolBar {
        id: chessToolBar
        RowLayout {
            anchors.fill: parent
            Button {
                id: startButton
                text: qsTr("Start")
                Layout.alignment: Qt.AlignLeft
                onClicked: {
                    viewsContainer.state = "chess"
                    boardModel.reset()
                    chessContainer.reloadAll()
                }
            }
            Button {
                id: stopButton
                text: qsTr("Stop")
                Layout.alignment: Qt.AlignLeft
                onClicked: {
                    viewsContainer.state = "start"
                    boardModel.reset()
                }
            }
            Button {
                id: saveButton
                text: qsTr("Save")
                Layout.alignment: Qt.AlignLeft
                onClicked: { saveFile.open() }
            }
            Button {
                id: loadButton
                text: qsTr("Load")
                Layout.alignment: Qt.AlignLeft
                onClicked: { openFile.open() }
            }
            Item { Layout.fillWidth: true }
            Button {
                id: prevButton
                text: qsTr("Previous")
                Layout.alignment: Qt.AlignLeft
                onClicked: {
                    boardModel.prev()
                    chessContainer.reloadAll()
                }
            }
            Button {
                id: nextButton
                text: qsTr("Next")
                Layout.alignment: Qt.AlignLeft
                onClicked: {
                    boardModel.next()
                    chessContainer.reloadAll()
                }
            }
        }
    }

    Item {
        width: parent.width
        height: parent.height
        id: viewsContainer
        state: "start"

        states: [
            State {
                name: ""
            },
            State {
                name: "start"
                PropertyChanges { target: startButton; visible: true }
                PropertyChanges { target: stopButton; visible: false }
                PropertyChanges { target: saveButton; visible: false }
                PropertyChanges { target: loadButton; visible: true }
                PropertyChanges { target: prevButton; visible: false }
                PropertyChanges { target: nextButton; visible: false }
                PropertyChanges { target: chessContainer; model: 64 }
            },
            State {
                name: "chess"
                PropertyChanges { target: startButton; visible: false }
                PropertyChanges { target: stopButton; visible: true }
                PropertyChanges { target: saveButton; visible: true }
                PropertyChanges { target: loadButton; visible: false }
                PropertyChanges { target: prevButton; visible: false }
                PropertyChanges { target: nextButton; visible: false }
                PropertyChanges { target: chessContainer; model: boardModel }
            },
            State {
                name: "history"
                PropertyChanges { target: startButton; visible: true }
                PropertyChanges { target: stopButton; visible: false }
                PropertyChanges { target: saveButton; visible: false }
                PropertyChanges { target: loadButton; visible: true }
                PropertyChanges { target: prevButton; visible: true }
                PropertyChanges { target: nextButton; visible: true }
                PropertyChanges { target: chessContainer; model: boardModel }
            }
        ]

        Item {
            id: chessView
            width: parent.width
            height: parent.height

            Grid {
                id: chessGrid
                columns: 8
                spacing: 0
                x: 0
                y: 0
                width: parent.width
                height: parent.height
                rows: 8

                Repeater {
                    id: chessContainer
                    objectName: "chessContainer"
                    //model: boardModel
                    width: parent.width
                    height: parent.height
                    state: "white"

                    states: [
                        State {
                            name: "white"
                        },
                        State {
                            name: "black"
                        }
                    ]

                    function reloadAll() {
                        var i = 0
                        for (i = 0; i < count; ++i) {
                            reloadData(i)
                        }
                    }

                    function reloadData(i) {
                        chessContainer.itemAt(i).reloadImage(i)
                        resetStates()
                    }

                    function resetStates() {
                        var i = 0
                        for (i = 0; i < count; ++i) {
                            chessContainer.itemAt(i).state = "normal"
                        }
                    }

                    function isOneSelected() {
                        var i = 0
                        for (i = 0; i < count; ++i) {
                            if (chessContainer.itemAt(i).state === "selected")
                                return i;
                        }
                        return -1;
                    }

                    Rectangle {
                        id: chessCell
                        objectName: "chessCell"
                        //width: parent.width / 8
                        //height: parent.height / 8
                        width: viewsContainer.width / 8
                        height: viewsContainer.height / 8
                        state: "normal"


                        function reloadImage(i){
                            chessImage.source = picture
                        }

                        states: [
                            State {
                                name: "normal"
                                PropertyChanges {
                                    target: chessCell;
                                    color: ((Math.floor(index / 8) % 2) === 0) ?
                                               (index % 2  === 1 ? "#D18B47" : "#FFCE9E") :
                                               (index % 2  === 0 ? "#D18B47" : "#FFCE9E")
                                }
                            },
                            State {
                                name: "selected"
                                PropertyChanges { target: chessCell; color: "red" }
                            }
                        ]

                        Image {
                            id: chessImage
                            anchors.fill: parent
                            //source: picture
                        }
                        Component.onCompleted: {
                            if (viewsContainer.state === "chess"  && picture != null)
                                chessImage.source = picture
                        }

                        MouseArea {
                            id: mouseSquareArea
                            anchors.fill: parent

                            onPressed: {
                                if (viewsContainer.state != "chess")
                                    return;

                                var i = chessContainer.isOneSelected()
                                if (i >= 0) {
                                    if (i === index) { // reset self selection
                                        chessCell.state = "normal"
                                    }
                                    else {
                                        if (boardModel.move(i, index, chessContainer.state === "black")) {
                                            if (chessContainer.state === "white")
                                                chessContainer.state = "black"
                                            else
                                                chessContainer.state = "white"
                                        }

                                        chessContainer.resetStates()
                                    }
                                }
                                else {
                                    if (name != "" && pcolor === chessContainer.state)
                                        chessCell.state = "selected"
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    FileSaveDialog {
        id: saveFile
        title: "Save file"
        filename: "game.chess"
        nameFilters: ["Chess files (*.chess)", "All files (*)"]

        onAccepted: { boardModel.save(saveFile.fileUrl) }
        //onRejected: { }
    }

    FileOpenDialog {
        id: openFile
        title: "Open file"
        nameFilters: ["Chess files (*.chess)", "All files (*)"]

        onAccepted: {
            if (boardModel.load(openFile.fileUrl)) {
                viewsContainer.state = "history"
                chessContainer.reloadAll()
            }
            else {
                messageDialog.text = "Can not open " + openFile.fileUrl
                messageDialog.open()
                viewsContainer.state = "start"
                boardModel.reset()
            }
        }
        //onRejected: { }
    }

    MessageDialog {
        id: messageDialog
        title: "Error"
    }
}
