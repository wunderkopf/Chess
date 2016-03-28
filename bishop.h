/*
 *  File:		bishop.h
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public virtual Piece
{
public:
    Bishop(PieceModel* model, bool isBlack = true);

    virtual bool canMove(const Piece* dest, bool checkKing = true) const;
};

#endif // BISHOP_H
