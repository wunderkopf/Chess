/*
 *  File:		pawn.cpp
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#include "pawn.h"
#include <QtMath>

Pawn::Pawn(PieceModel* model, bool isBlack) : Piece(model, "pawn", isBlack)
{
    move(true);
}

bool Pawn::canMove(const Piece* dest, bool checkKing) const
{
    if (!Piece::canMove(dest, checkKing))
        return false;

    int sourceRow = row();
    int sourceCol = col();
    int destRow = dest->row();
    int destCol = dest->col();

    if (isBlack()) // prevent movements back
    {
        if (sourceRow >= destRow)
            return false;
    }
    else
    {
        if (sourceRow <= destRow)
            return false;
    }

    if ((qFabs(sourceCol - destCol) != 0)) // prevent moving left/right
    {
        if ((qFabs(sourceCol - destCol) == 1) && (qFabs(sourceRow - destRow) == 1)) // kill
        {
            if (dest->getName() != "")
                return true;
        }

        return false;
    }

    if (sourceCol == destCol) // moving
    {
        if (qFabs(sourceRow - destRow) > 2) // can not move more then two rows
            return false;

        if (qFabs(sourceRow - destRow) == 2 && getMovements() > 0)
            return false;
    }

    return true;
}
