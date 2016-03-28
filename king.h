/*
 *  File:		king.h
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece
{
public:
    King(PieceModel* model, bool isBlack = true);

    virtual bool canMove(const Piece* dest, bool checkKing = true) const;
};

#endif // KING_H
