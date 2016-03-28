/*
 *  File:		queen.h
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#ifndef QUEEN_H
#define QUEEN_H

#include "bishop.h"
#include "rook.h"

class Queen : public Bishop, public Rook
{
public:
    Queen(PieceModel* model, bool isBlack = true);

    virtual bool canMove(const Piece* dest, bool checkKing = true) const;
};

#endif // QUEEN_H
