/*
 *  File:		rook.cpp
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#include "rook.h"
#include "piecemodel.h"

Rook::Rook(PieceModel* model, bool isBlack) : Piece(model, "rook", isBlack)
{
    move(true);
}

bool Rook::canMove(const Piece* dest, bool checkKing) const
{
    if (!Piece::canMove(dest, checkKing))
        return false;

    int sourceRow = row();
    int sourceCol = col();
    int destRow = dest->row();
    int destCol = dest->col();

    ConstPieceWPtr piece = getModel()->meetRight(sourceRow, sourceCol, destRow, destCol);
    if (piece == NULL)
    {
        piece = getModel()->meetLeft(sourceRow, sourceCol, destRow, destCol);
        if (piece == NULL)
        {
            piece = getModel()->meetBottom(sourceRow, sourceCol, destRow, destCol);
            if (piece == NULL)
            {
                piece = getModel()->meetTop(sourceRow, sourceCol, destRow, destCol);
                if (piece == NULL)
                    return false;
            }
        }
    }

    if (piece != NULL)
    {
        int pr = piece.data()->row();
        int pc = piece.data()->col();
        if (pr != destRow || pc != destCol)
            return false;
        return true;
    }

    return true;
}
