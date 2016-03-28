/*
 *  File:		rook.h
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public virtual Piece
{
public:
    Rook(PieceModel* model, bool isBlack = true);

    virtual bool canMove(const Piece* dest, bool checkKing = true) const;
};

#endif // ROOK_H
