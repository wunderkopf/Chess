/*
 *  File:		piece.h
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#ifndef PIECE_H
#define PIECE_H

#include <QString>
#include <QMetaType>
#include <QDebug>

class PieceModel;

class Piece
{
public:
    Piece(PieceModel* model = NULL);
    Piece(PieceModel* model, const QString& name, bool isBlack);
    Piece(const Piece &other);
    virtual ~Piece();

    virtual bool canMove(const Piece* dest, bool checkKing = true) const;

public:
    bool isBlack() const;
    QString getName() const;
    QString getImageAlias() const;
    const PieceModel* getModel() const;
    void move(bool init = false);
    int getMovements() const;
    int row() const;
    int col() const;

private:
    bool m_Black;
    QString m_Name;
    PieceModel* m_Model;
    int m_movements;
};

Q_DECLARE_METATYPE(Piece)

typedef QSharedPointer<Piece> PiecePtr;
typedef QWeakPointer<const Piece> ConstPieceWPtr;

#endif // PIECE_H
