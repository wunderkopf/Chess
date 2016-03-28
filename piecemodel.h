/*
 *  File:		piecemodel.h
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#ifndef PIECEMODEL_H
#define PIECEMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include <QUrl>

#include "piece.h"

enum States {
    OkState = 0,
    CheckState,
    MateState
};

class PieceModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PieceModel(QObject *parent = 0);

    enum DataRoles {
        NameRole = Qt::UserRole + 1,
        ColorRole,
        PictureRole
    };

    //
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
    //

    int pieceRow(const Piece* piece) const;
    int pieceCol(const Piece* piece) const;
    inline int indexToRow(int index) const;
    inline int indexToCol(int index) const;

    ConstPieceWPtr getPiece(int row, int col) const;

    ConstPieceWPtr meetRight(int sRow, int sCol, int dRow, int dCol) const;
    ConstPieceWPtr meetTopRight(int sRow, int sCol, int dRow, int dCol) const;
    ConstPieceWPtr meetBottomRight(int sRow, int sCol, int dRow, int dCol) const;
    ConstPieceWPtr meetLeft(int sRow, int sCol, int dRow, int dCol) const;
    ConstPieceWPtr meetTopLeft(int sRow, int sCol, int dRow, int dCol) const;
    ConstPieceWPtr meetBottomLeft(int sRow, int sCol, int dRow, int dCol) const;
    ConstPieceWPtr meetTop(int sRow, int sCol, int dRow, int dCol) const;
    ConstPieceWPtr meetBottom(int sRow, int sCol, int dRow, int dCol) const;

signals:
    void reloadData(const QVariant& i);

public slots:
    void reset(bool initBoard = true);
    bool move(int source, int dest, bool isBlack);
    void save(const QUrl& fileUrl);
    bool load(const QUrl& fileUrl);
    bool prev();
    bool next();

private:
    typedef QVector<QPair<QString, bool> > Snapshot;
    void init();
    void makeSnapshot();
    bool loadSnapshot(QList<Snapshot>::const_iterator& iter);
    PiecePtr createPiece(const Snapshot::value_type& pieceData);
    States isCheckMate(bool isBlack) const;

    QList<PiecePtr> m_model;
    QList<Snapshot> m_Snapshots;
    QList<Snapshot>::const_iterator m_CurrentSnapshot;

    ConstPieceWPtr m_BlackKing;
    ConstPieceWPtr m_WhiteKing;
};

#endif // PIECEMODEL_H
