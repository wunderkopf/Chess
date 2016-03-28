/*
 *  File:		knight.cpp
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#include "knight.h"
#include <QtMath>

Knight::Knight(PieceModel* model, bool isBlack) : Piece(model, "knight", isBlack)
{
    move(true);
}

bool Knight::canMove(const Piece* dest, bool checkKing) const
{
    if (!Piece::canMove(dest, checkKing))
        return false;

    int sourceRow = row();
    int sourceCol = col();
    int destRow = dest->row();
    int destCol = dest->col();

    if ((qFabs(sourceRow - destRow) != 2) || (qFabs(sourceCol - destCol) != 1))
    {
        if ((qFabs(sourceRow - destRow) != 1) || (qFabs(sourceCol - destCol) != 2))
            return false;
    }

    return true;
}

