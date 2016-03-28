/*
 *  File:		queen.cpp
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#include "queen.h"

Queen::Queen(PieceModel* model, bool isBlack) : Piece(model, "queen", isBlack),
    Bishop(model, isBlack), Rook(model, isBlack)
{
    move(true);
}

bool Queen::canMove(const Piece* dest, bool checkKing) const
{
    if (Bishop::canMove(dest, checkKing))
        return true;

    return Rook::canMove(dest, checkKing);
}
