void ScanBoardSize(int *rows, int *columns)
{
    printf("Insert board size");
    printf("\nRows: ");
    scanf("%d", rows);
    printf("Columns: ");
    scanf("%d", columns);
}

int ScanRowIndex()
{    
    int i;
    printf("Insert row index: ");
    scanf("%d", &i);

    return i;
}

int ScanColumnIndex()
{    
    int j;
    printf("Insert column index: ");
    scanf("%d", &j);

    return j;
}

int ScanChoice()
{   
    int choice;
    scanf("%d", &choice);

    return choice;
}