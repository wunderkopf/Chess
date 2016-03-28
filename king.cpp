/*
 *  File:		king.cpp
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#include "king.h"
#include <QtMath>

King::King(PieceModel* model, bool isBlack) : Piece(model, "king", isBlack)
{
    move(true);
}

bool King::canMove(const Piece* dest, bool checkKing) const
{
    if (!Piece::canMove(dest, checkKing))
        return false;

    int sourceRow = row();
    int sourceCol = col();
    int destRow = dest->row();
    int destCol = dest->col();

    if ((qFabs(sourceCol - destCol) > 1) || (qFabs(sourceRow - destRow) > 1)) // move/kill
        return false;

    return true;
}
