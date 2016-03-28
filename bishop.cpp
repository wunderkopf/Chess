/*
 *  File:		bishop.cpp
 *
 *  Created by Oleksandr Kurylenko for job interview.
 *
 */
#include "bishop.h"
#include "piecemodel.h"

Bishop::Bishop(PieceModel* model, bool isBlack) : Piece(model, "bishop", isBlack)
{
    move(true);
}

bool Bishop::canMove(const Piece* dest, bool checkKing) const
{
    if (!Piece::canMove(dest, checkKing))
        return false;

    int sourceRow = row();
    int sourceCol = col();
    int destRow = dest->row();
    int destCol = dest->col();

    ConstPieceWPtr piece = getModel()->meetTopRight(sourceRow, sourceCol, destRow, destCol);
    if (piece.isNull())
    {
        piece = getModel()->meetBottomRight(sourceRow, sourceCol, destRow, destCol);
        if (piece.isNull())
        {
            piece = getModel()->meetBottomLeft(sourceRow, sourceCol, destRow, destCol);
            if (piece.isNull())
            {
                piece = getModel()->meetTopLeft(sourceRow, sourceCol, destRow, destCol);
                if (piece.isNull())
                    return false;
            }
        }
    }

    if (!piece.isNull())
    {
        int pr = piece.data()->row();
        int pc = piece.data()->col();
        if (pr != destRow || pc != destCol)
            return false;

        return true;
    }

    return true;
}
