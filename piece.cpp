/*
 *  File:		piece.cpp
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#include "piece.h"
#include "piecemodel.h"

Piece::Piece(PieceModel* model) : m_Model(model), m_movements(-1)
{
    Q_ASSERT(model != NULL);
}

Piece::Piece(PieceModel* model, const QString& name, bool isBlack) : m_Black(isBlack), m_Name(name), m_Model(model),
    m_movements(-1)
{
    Q_ASSERT(model != NULL);
}

Piece::Piece(const Piece &other)
{
    m_Black = other.m_Black;
    m_Name = other.m_Name;
    m_Model = other.m_Model;
}

Piece::~Piece()
{
}

bool Piece::isBlack() const
{
    return m_Black;
}

QString Piece::getName() const
{
    return m_Name;
}

QString Piece::getImageAlias() const
{
    if (getName().isEmpty())
        return QString();

    QString color = isBlack() ? QString("black_") : QString("white_");
    return  color + getName();
}

const PieceModel* Piece::getModel() const
{
    return m_Model;
}

int Piece::row() const
{
    return getModel()->pieceRow(this);
}

int Piece::col() const
{
    return getModel()->pieceCol(this);
}

void Piece::move(bool init)
{
    if (init)
        m_movements = 0;
    else
    {
        if (m_movements != -1)
            ++m_movements;
    }
}

int Piece::getMovements() const
{
    return m_movements;
}

bool Piece::canMove(const Piece* dest, bool checkKing) const
{
    if (dest->getName() != "" && ((isBlack() == dest->isBlack()) || (checkKing && dest->getName() == "king")))
        return false;

    return true;
}
