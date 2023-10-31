#include <stdlib.h>

int InBounds(int n, int lowerBound, int upperBound) // [ , )
{
    return n >= lowerBound && n < upperBound; 
}

int **NewAlreadyCheckedMatrix(int rows, int columns)
{
    int **newAlreadyCheckedMatrix;
    newAlreadyCheckedMatrix = malloc(sizeof(int*) * rows);
    
    for(int i = 0; i < rows; i++)
    {
        newAlreadyCheckedMatrix[i] = malloc(sizeof(int*) * columns);
    }

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            newAlreadyCheckedMatrix[i][j] = 0;
        }
    }

    return newAlreadyCheckedMatrix;
}

int EmptySpace(int *board, int rows, int columns, int i, int j)
{
    return (*(board + (columns * i) + j) == 0);
}

int SameValue(int *board, int rows, int columns, int i, int j, int value)
{
    return (*(board + (columns * i) + j) == value);
}

void CopyMatrix(int *matrixSrc, int *matrixDst, int rows, int columns)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            *(matrixDst + (columns * i) + j) = *(matrixSrc + (columns * i) + j);
        }
    }
}

int MatricesEqual(int *matrix1, int *matrix2, int rows, int columns)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            if(*(matrix1 + (columns * i) + j) != *(matrix2 + (columns * i) + j))
            {
                return 0;
            }
        }
    }

    return 1;
}