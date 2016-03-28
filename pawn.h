/*
 *  File:		pawn.h
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(PieceModel* model, bool isBlack = true);

    virtual bool canMove(const Piece* dest, bool checkKing = true) const;
};

#endif // PAWN_H
