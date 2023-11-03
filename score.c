void CountEmptySpaces(int *board, int rows, int columns, int i, int j, int* emptySpacesCount, int *touchedBlack, int *touchedWhite, int **alreadyCheckedMatrix)
{
    if(!InBounds(i, 0, rows) || !InBounds(j, 0, columns))
    {
        return;
    }

    if(*(board + (columns * i) + j) == 1)
    {
        *touchedBlack = 1;
        return;
    }
    else if(*(board + (columns * i) + j) == -1)
    {
        *touchedWhite = 1;
        return;
    }

    if(alreadyCheckedMatrix[i][j])
    {
        return;
    }
    alreadyCheckedMatrix[i][j] = 1;

    (*emptySpacesCount) += 1;

    int newI, newJ;

    newI = i + 1;
    newJ = j;
    CountEmptySpaces(board, rows, columns, newI, newJ, emptySpacesCount, touchedBlack, touchedWhite, alreadyCheckedMatrix);

    newI = i - 1;
    newJ = j;
    CountEmptySpaces(board, rows, columns, newI, newJ, emptySpacesCount, touchedBlack, touchedWhite, alreadyCheckedMatrix);
    
    newI = i;
    newJ = j + 1;
    CountEmptySpaces(board, rows, columns, newI, newJ, emptySpacesCount, touchedBlack, touchedWhite, alreadyCheckedMatrix);
    
    newI = i;
    newJ = j - 1;
    CountEmptySpaces(board, rows, columns, newI, newJ, emptySpacesCount, touchedBlack, touchedWhite, alreadyCheckedMatrix);
}

void CheckSquare(int *board, int rows, int columns, int i, int j, int **alreadyCheckedMatrix, int *sumBlack, int *sumWhite)
{
    if(alreadyCheckedMatrix[i][j])
    {
        return;
    }

    if(*(board + (columns * i) + j) == 1)
    {
        (*sumBlack)++;
    }
    else if(*(board + (columns * i) + j) == -1)
    {
        (*sumWhite)++;
    }
    else if(*(board + (columns * i) + j) == 0) //We delegate to CountEmptySpaces. Keep in mind that alreadyCheckedMatrix will be also changed to true by CountEmptySpaces
    {

        int emptySpacesCount = 0;
        int touchedBlack = 0;
        int touchedWhite = 0;
        CountEmptySpaces(board, rows, columns, i, j, &emptySpacesCount, &touchedBlack, &touchedWhite, alreadyCheckedMatrix);

        if(touchedBlack && touchedWhite)
        {
            //Nothing
        }
        else if(touchedBlack)
        {
            (*sumBlack) += emptySpacesCount;
        }
        else if(touchedWhite)
        {
            (*sumWhite) += emptySpacesCount;
        }
    }
    
    alreadyCheckedMatrix[i][j] = 1;
}

void CountScore(int *board, int rows, int columns)
{    
    int **newAlreadyCheckedMatrix = NewAlreadyCheckedMatrix(rows, columns);
    int sumBlack = 0;
    int sumWhite = 0;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            CheckSquare(board, rows, columns, i, j, newAlreadyCheckedMatrix, &sumBlack, &sumWhite);
        }
    }

    //Freeing memory
    for(int k = 0; k < rows; k++)
    {
        free(newAlreadyCheckedMatrix[k]);
    }
    free(newAlreadyCheckedMatrix);

    PrintScore(sumBlack, sumWhite);
}