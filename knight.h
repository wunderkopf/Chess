/*
 *  File:		knight.h
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
    Knight(PieceModel* model, bool isBlack = true);

    virtual bool canMove(const Piece* dest, bool checkKing = true) const;
};

#endif // KNIGHT_H
