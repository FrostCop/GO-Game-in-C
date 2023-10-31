#include "util.c"
#include <stdlib.h>

void InitializeBoard(int *board, int rows, int columns)
{    
    for(int i = 0; i < rows; i++) 
    {
        for(int j = 0; j < columns; j++) 
        {
            *(board + (columns * i) + j) = 0;
        }
    }
}

int OppositePiece(int piece)
{
    if(piece == 1)
    {
        return -1;
    }
    return 1;
}

void RemoveGroup(int *board, int rows, int columns, int i, int j, int value)
{
    int examinatedSquareValue = *(board + (columns * i) + j);

    *(board + (i * columns) + j) = 0;

    int newI, newJ;
    newI = i + 1;
    newJ = j;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && SameValue(board, rows, columns, newI, newJ, examinatedSquareValue))
    {
        RemoveGroup(board, rows, columns, newI, newJ, value);
    }
    newI = i - 1;
    newJ = j;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && SameValue(board, rows, columns, newI, newJ, examinatedSquareValue))
    {
        RemoveGroup(board, rows, columns, newI, newJ, value);
    }
    newI = i;
    newJ = j + 1;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && SameValue(board, rows, columns, newI, newJ, examinatedSquareValue))
    {
        RemoveGroup(board, rows, columns, newI, newJ, value);
    }
    newI = i;
    newJ = j - 1;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && SameValue(board, rows, columns, newI, newJ, examinatedSquareValue))
    {
        RemoveGroup(board, rows, columns, newI, newJ, value);
    }
}

int HasLiberties(int *board,  int rows, int columns, int i, int j, int **alreadyCheckedMatrix)
{
    alreadyCheckedMatrix[i][j] = 1;
    
    int newI, newJ;

    //Empty spaces
    newI = i + 1;
    newJ = j;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && EmptySpace(board, rows, columns, newI, newJ))
    {
        return 1;
    }
    newI = i - 1;
    newJ = j;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && EmptySpace(board, rows, columns, newI, newJ))
    {
        return 1;
    }
    newI = i;
    newJ = j + 1;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && EmptySpace(board, rows, columns, newI, newJ))
    {
        return 1;
    }
    newI = i;
    newJ = j - 1;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && EmptySpace(board, rows, columns, newI, newJ))
    {
        return 1;
    }
    
    //Stones of same color
    int examinatedSquareValue = *(board + (columns * i) + j);

    newI = i + 1;
    newJ = j;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && alreadyCheckedMatrix[newI][newJ] == 0 && SameValue(board, rows, columns, newI, newJ, examinatedSquareValue))
    {
        return HasLiberties(board, rows, columns, newI, newJ, alreadyCheckedMatrix);
    }
    newI = i - 1;
    newJ = j;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && alreadyCheckedMatrix[newI][newJ] == 0 && SameValue(board, rows, columns, newI, newJ, examinatedSquareValue))
    {
        return HasLiberties(board, rows, columns, newI, newJ, alreadyCheckedMatrix);
    }
    newI = i;
    newJ = j + 1;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && alreadyCheckedMatrix[newI][newJ] == 0 && SameValue(board, rows, columns, newI, newJ, examinatedSquareValue))
    {
        return HasLiberties(board, rows, columns, newI, newJ, alreadyCheckedMatrix);
    }
    newI = i;
    newJ = j - 1;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && alreadyCheckedMatrix[newI][newJ] == 0 && SameValue(board, rows, columns, newI, newJ, examinatedSquareValue))
    {
        return HasLiberties(board, rows, columns, newI, newJ, alreadyCheckedMatrix);
    }

    return 0;
}

void CheckLiberties(int *board, int rows, int columns, int i, int j)
{
    int **newAlreadyCheckedMatrix = NewAlreadyCheckedMatrix(rows, columns);

    if(!HasLiberties(board, rows, columns, i, j, newAlreadyCheckedMatrix))
    {
        RemoveGroup(board, rows, columns, i, j, *(board + (i * columns) + j));
    }

    //Freeing memory
    for(int k = 0; k < rows; k++)
    {
        free(newAlreadyCheckedMatrix[k]);
    }
    free(newAlreadyCheckedMatrix);
}

int MakeMove(int *board,  int rows, int columns, int i, int j, int blackTurn, int *previousBoardBlackTurn, int *previousBoardWhiteTurn)
{
    if(!InBounds(i, 0, rows) || !InBounds(j, 0, columns))
    {
        return 1;
    }
    if(*(board + (columns * i) + j) != 0)
    {
        return 2;
    }    

    *(board + (columns * i) + j) = (blackTurn ? 1 : -1);

    //Killing opposite groups. We do this before checking for suicide
    int oppositeSquareValue = *(board + (columns * i) + j) == 1 ? -1 : 1;
    int newI, newJ;
    newI = i + 1;
    newJ = j;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && SameValue(board, rows, columns, newI, newJ, oppositeSquareValue))
    {
        CheckLiberties(board, rows, columns, newI, newJ);
    }
    newI = i - 1;
    newJ = j;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && SameValue(board, rows, columns, newI, newJ, oppositeSquareValue))
    {
        CheckLiberties(board, rows, columns, newI, newJ);
    }
    newI = i;
    newJ = j + 1;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && SameValue(board, rows, columns, newI, newJ, oppositeSquareValue))
    {
        CheckLiberties(board, rows, columns, newI, newJ);
    }
    newI = i;
    newJ = j - 1;
    if(InBounds(newI, 0, rows) && InBounds(newJ, 0, columns) && SameValue(board, rows, columns, newI, newJ, oppositeSquareValue))
    {
        CheckLiberties(board, rows, columns, newI, newJ);
    }
    
    //Suicide check
    int **newAlreadyCheckedMatrix = NewAlreadyCheckedMatrix(rows, columns);
    if(!HasLiberties(board, rows, columns, i, j, newAlreadyCheckedMatrix))
    {
        *(board + (columns * i) + j) = 0; //Reversing the move
        return 3;
    }
        //Freeing memory
    for(int k = 0; k < rows; k++)
    {
        free(newAlreadyCheckedMatrix[k]);
    }
    free(newAlreadyCheckedMatrix);

    if(MatricesEqual(board, (blackTurn ? previousBoardBlackTurn : previousBoardWhiteTurn), rows, columns))
    {
        //Reversing the move
        CopyMatrix(blackTurn ? previousBoardWhiteTurn : previousBoardBlackTurn, board, rows, columns);

        return 4;
    }

    CopyMatrix(board, (blackTurn ? previousBoardBlackTurn : previousBoardWhiteTurn), rows, columns);

    return 0;
}