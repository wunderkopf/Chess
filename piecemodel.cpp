/*
 *  File:		piecemodel.cpp
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#include "piecemodel.h"

#include <QtMath>
#include <QApplication>
#include <QFile>
#include <QDataStream>

#include "bishop.h"
#include "king.h"
#include "rook.h"
#include "pawn.h"
#include "knight.h"
#include "queen.h"

PieceModel::PieceModel(QObject *parent) : QAbstractListModel(parent)
{
    reset();
}

void PieceModel::init()
{
    m_model.append(PiecePtr(new Rook(this))); // rook
    m_model.append(PiecePtr(new Knight(this))); // knight
    m_model.append(PiecePtr(new Bishop(this))); // bishop
    m_model.append(PiecePtr(new Queen(this))); // queen
    m_model.append(PiecePtr(new King(this))); // king
    m_BlackKing = m_model.last();
    m_model.append(PiecePtr(new Bishop(this))); // bishop
    m_model.append(PiecePtr(new Knight(this))); // knight
    m_model.append(PiecePtr(new Rook(this))); // rook

    for (int i = 0; i < 8; ++i)
        m_model.append(PiecePtr(new Pawn(this))); // pawn

    for (int n = 0; n < 4; ++n)
    {
        for (int i = 0; i < 8; ++i)
            m_model.append(PiecePtr(new Piece(this))); // space
    }

    for (int i = 0; i < 8; ++i)
        m_model.append(PiecePtr(new Pawn(this, false))); // pawn

    m_model.append(PiecePtr(new Rook(this, false))); // rook
    m_model.append(PiecePtr(new Knight(this, false))); // knight
    m_model.append(PiecePtr(new Bishop(this, false))); // bishop
    m_model.append(PiecePtr(new Queen(this, false))); // queen
    m_model.append(PiecePtr(new King(this, false))); // king
    m_WhiteKing = m_model.last();
    m_model.append(PiecePtr(new Bishop(this, false))); // bishop
    m_model.append(PiecePtr(new Knight(this, false))); // knight
    m_model.append(PiecePtr(new Rook(this, false))); // rook

    makeSnapshot();
}

int PieceModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    int count = m_model.count();
    Q_ASSERT(count == 64);

    return count;
}

QVariant PieceModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_model.count() )
        return QVariant();

    PiecePtr modelEntry = m_model[index.row()];

    if (role == NameRole)
        return modelEntry->getName();

    if (role == ColorRole)
    {
        if (modelEntry->isBlack())
            return "black";

        return "white";
    }

    if (role == PictureRole)
        return modelEntry->getImageAlias();

    return QVariant();
}

QHash<int, QByteArray> PieceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ColorRole] = "pcolor";
    roles[PictureRole] = "picture";

    return roles;
}

int PieceModel::indexToRow(int index) const
{
    return qFloor(index / 8);
}

int PieceModel::indexToCol(int index) const
{
    return index % 8;
}

int PieceModel::pieceRow(const Piece* piece) const
{
    int index = 0;
    for (QList<PiecePtr>::const_iterator iter = m_model.begin(); iter != m_model.end(); ++iter)
    {
        if (iter->data() == piece)
            return indexToRow(index);

        ++index;
    }
    return -1;
}

int PieceModel::pieceCol(const Piece* piece) const
{
    int index = 0;
    for (QList<PiecePtr>::const_iterator iter = m_model.begin(); iter != m_model.end(); ++iter)
    {
        if (iter->data() == piece)
            return indexToCol(index);

        ++index;
    }
    return -1;
}

ConstPieceWPtr PieceModel::getPiece(int row, int col) const
{
    int index = row * 8 + (col + 1);
    Q_ASSERT(index < m_model.size());
    return m_model[index - 1].toWeakRef();
}

ConstPieceWPtr PieceModel::meetRight(int sRow, int sCol, int dRow, int dCol) const
{
    if (sCol < dCol && sRow == dRow)
    {
        int col = sCol + 1;
        for (; col < dCol; ++col)
        {
            ConstPieceWPtr piece = getPiece(sRow, col);
            Q_ASSERT(!piece.isNull());
            if (piece.data()->getName() != "")
                return piece;
        }
        return getPiece(sRow, col);
    }
    return ConstPieceWPtr();
}

ConstPieceWPtr PieceModel::meetTopRight(int sRow, int sCol, int dRow, int dCol) const
{
    if (sCol < dCol && sRow > dRow)
    {
        int col = sCol + 1;
        int row = sRow - 1;
        for (; col < dCol && row > dRow; ++col, --row)
        {
            ConstPieceWPtr piece = getPiece(row, col);
            Q_ASSERT(!piece.isNull());
            if (piece.data()->getName() != "")
                return piece;
        }
        return getPiece(row, col);
    }
    return ConstPieceWPtr();
}

ConstPieceWPtr PieceModel::meetBottomRight(int sRow, int sCol, int dRow, int dCol) const
{
    if (sCol < dCol && sRow < dRow)
    {
        int col = sCol + 1;
        int row = sRow + 1;
        for (; col < dCol && row < dRow; ++col, ++row)
        {
            ConstPieceWPtr piece = getPiece(row, col);
            Q_ASSERT(!piece.isNull());
            if (piece.data()->getName() != "")
                return piece;
        }
        return getPiece(row, col);
    }
    return ConstPieceWPtr();
}

ConstPieceWPtr PieceModel::meetLeft(int sRow, int sCol, int dRow, int dCol) const
{
    if (sCol > dCol && sRow == dRow)
    {
        int col = sCol - 1;
        for (; col > dCol; --col)
        {
            ConstPieceWPtr piece = getPiece(sRow, col);
            Q_ASSERT(!piece.isNull());
            if (piece.data()->getName() != "")
                return piece;
        }
        return getPiece(sRow, col);
    }
    return ConstPieceWPtr();
}

ConstPieceWPtr PieceModel::meetTopLeft(int sRow, int sCol, int dRow, int dCol) const
{
    if (sCol > dCol && sRow > dRow)
    {
        int col = sCol - 1;
        int row = sRow - 1;
        for (; col > dCol && row > dRow; --col, --row)
        {
            ConstPieceWPtr piece = getPiece(row, col);
            Q_ASSERT(!piece.isNull());
            if (piece.data()->getName() != "")
                return piece;
        }
        return getPiece(row, col);
    }
    return ConstPieceWPtr();
}

ConstPieceWPtr PieceModel::meetBottomLeft(int sRow, int sCol, int dRow, int dCol) const
{
    if (sCol > dCol && sRow < dRow)
    {
        int col = sCol - 1;
        int row = sRow + 1;
        for (; col > dCol && row < dRow; --col, ++row)
        {
            ConstPieceWPtr piece = getPiece(row, col);
            Q_ASSERT(!piece.isNull());
            if (piece.data()->getName() != "")
                return piece;
        }
        return getPiece(row, col);
    }
    return ConstPieceWPtr();
}

ConstPieceWPtr PieceModel::meetTop(int sRow, int sCol, int dRow, int dCol) const
{
    if (sCol == dCol && sRow > dRow)
    {
        int row = sRow - 1;
        for (; row > dRow; --row)
        {
            ConstPieceWPtr piece = getPiece(row, sCol);
            Q_ASSERT(!piece.isNull());
            if (piece.data()->getName() != "")
                return piece;
        }
        return getPiece(row, sCol);
    }
    return ConstPieceWPtr();
}

ConstPieceWPtr PieceModel::meetBottom(int sRow, int sCol, int dRow, int dCol) const
{
    if (sCol == dCol && sRow < dRow)
    {
        int row = sRow + 1;
        for (; row < dRow; ++row)
        {
            ConstPieceWPtr piece = getPiece(row, sCol);
            Q_ASSERT(!piece.isNull());
            if (piece.data()->getName() != "")
                return piece;
        }
        return getPiece(row, sCol);
    }
    return ConstPieceWPtr();
}

void PieceModel::reset(bool initBoard)
{
    m_model.clear();
    m_Snapshots.clear();

    if (initBoard)
        init();
}

bool PieceModel::move(int source, int dest, bool isBlack)
{
    Q_ASSERT(source < m_model.size());
    Q_ASSERT(dest < m_model.size());

    if (isCheckMate(isBlack) != OkState)
    {
        if (isBlack)
        {
            if (m_model[source].data() != m_BlackKing.data())
                return false;
        }
        else
        {
            if (m_model[source].data() != m_WhiteKing.data())
                return false;
        }
    }

    bool canMove = m_model[source]->canMove(m_model[dest].data());

    if (canMove)
    {
        qDebug() << "Can move from (" << indexToRow(source) << ";" << indexToCol(source) << ") to ("
                 << indexToRow(dest) << ";" << indexToCol(dest) << ")";

        PiecePtr sourcePiece = m_model[source];
        m_model[source].reset(new Piece(this));
        emit reloadData(source);
        m_model[source]->move();
        m_model[dest] = sourcePiece;
        emit reloadData(dest);
        m_model[dest]->move();
        makeSnapshot();

        return true;
    }
    else
    {
        qDebug() << "Can not move from (" << indexToRow(source) << ";" << indexToCol(source) << ") to ("
                 << indexToRow(dest) << ";" << indexToCol(dest) << ")";
    }

    QApplication::beep();
    return false;
}

void PieceModel::save(const QUrl& fileUrl)
{
    QFile file(fileUrl.toLocalFile());
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Can not open file" << fileUrl;
        return;
    }

    QDataStream stream(&file);
    try
    {
        stream << m_Snapshots;
    }
    catch (...)
    {
        qDebug() << fileUrl << "has not been saved";
    }

    file.close();
}

void PieceModel::makeSnapshot()
{
    Snapshot snapshot(64);
    int index = 0;
    for (QList<PiecePtr>::const_iterator iter = m_model.begin(); iter != m_model.end(); ++iter)
    {
        snapshot[index] = qMakePair((*iter)->getName(), (*iter)->isBlack());
        ++index;
    }
    Q_ASSERT(index <= 64);
    m_Snapshots << snapshot;
}

bool PieceModel::loadSnapshot(QList<Snapshot>::const_iterator& iter)
{
    Q_ASSERT(iter != m_Snapshots.end());

    m_model.clear();
    const Snapshot& snapshot = *iter;

    for (Snapshot::const_iterator iter = snapshot.begin(); iter != snapshot.end(); ++iter)
        m_model << createPiece(*iter);

    return true;
}

PiecePtr PieceModel::createPiece(const Snapshot::value_type& pieceData)
{
    if (pieceData.first == "bishop")
        return PiecePtr(new Bishop(this, pieceData.second));

    if (pieceData.first == "king")
        return PiecePtr(new King(this, pieceData.second));

    if (pieceData.first == "knight")
        return PiecePtr(new Knight(this, pieceData.second));

    if (pieceData.first == "pawn")
        return PiecePtr(new Pawn(this, pieceData.second));

    if (pieceData.first == "queen")
        return PiecePtr(new Queen(this, pieceData.second));

    if (pieceData.first == "rook")
        return PiecePtr(new Rook(this, pieceData.second));

    return PiecePtr(new Piece(this));
}

bool PieceModel::load(const QUrl& fileUrl)
{
    reset(false);

    QFile file(fileUrl.toLocalFile());
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can not open file" << fileUrl;
        return false;
    }

    QDataStream stream(&file);
    try
    {
        stream >> m_Snapshots;
    }
    catch (...)
    {
        qDebug() << "Something evil has happened while loading data from" << fileUrl;
        file.close();
        return false;
    }

    file.close();

    if (m_Snapshots.empty())
    {
        qDebug() << "Has not read anything from" << fileUrl;
        return false;
    }

    m_CurrentSnapshot = m_Snapshots.cbegin();

    return loadSnapshot(m_CurrentSnapshot);
}

bool PieceModel::prev()
{
    if (m_CurrentSnapshot != m_Snapshots.cbegin())
        --m_CurrentSnapshot;

    return loadSnapshot(m_CurrentSnapshot);
}

bool PieceModel::next()
{
    if (m_CurrentSnapshot + 1 != m_Snapshots.cend())
        ++m_CurrentSnapshot;

    if (m_CurrentSnapshot != m_Snapshots.cend())
        return loadSnapshot(m_CurrentSnapshot);

    return false;
}

States PieceModel::isCheckMate(bool isBlack) const
{
    if (isBlack)
    {
        for (QList<PiecePtr>::const_iterator iter = m_model.begin(); iter != m_model.end(); ++iter)
        {
            if (!(*iter)->isBlack() && (*iter)->getName() != "")
            {
                if ((*iter)->canMove(m_BlackKing.data(), false))
                    return CheckState;
            }
        }
    }
    else
    {
        for (QList<PiecePtr>::const_iterator iter = m_model.begin(); iter != m_model.end(); ++iter)
        {
            if ((*iter)->isBlack() && (*iter)->getName() != "")
            {
                if ((*iter)->canMove(m_WhiteKing.data(), false))
                    return CheckState;
            }
        }
    }

    return OkState;
}
