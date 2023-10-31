int NumberOfDigits(int number)
{
    if(number == 0)
    {
        return 1;
    }
    if(number < 0)
    {
        number *= -1;
    }

    int c = 0;
    while(number > 0)
    {
        number /= 10;
        c++;
    }

    return c;
}

void PrintSpaces(int spaces)
{
    for(int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
}

void PrintBoard(int *board, int rows, int columns)
{
    PrintSpaces(NumberOfDigits(rows - 1) + 1);
    for(int j = 0; j < columns; j++)
    {
        printf("%d", j);
        PrintSpaces(NumberOfDigits(columns - 1) + 1 - NumberOfDigits(j));
    }    
    printf("\n");

    for(int i = 0; i < rows; i++) 
    {   
        printf("%d", i);
        PrintSpaces(NumberOfDigits(rows - 1) + 1 - NumberOfDigits(i));
        for(int j = 0; j < columns; j++) 
        {
            int value = *(board + (columns * i) + j);

            switch(value)
            {
                case 0:
                    printf("-");
                    break;
                case 1:
                    printf("X");
                    break;
                case -1:
                    printf("O");
                    break;
            };
            PrintSpaces(NumberOfDigits(columns - 1));
        }
        printf("\n");
    }
}

void PrintMoveOutcome(int moveOutcome)
{
    switch(moveOutcome)
    {
        case 1:
            printf("The indexes are not valid\n");
            break;
        case 2:
            printf("That space is already occupied\n");
            break;
        case 3:
            printf("You can't play a suicide move\n");
            break;
    }
}

void PrintInvalidChoice()
{
    printf("Choice not valid\n");
}

void PrintTurn(int blackTurn)
{    
    printf(blackTurn ? "Black Turn\n" : "White Turn\n");
}

void PrintChoiceOption()
{    
    printf("Choose:\n1 = Play a move\n2 = Pass\n");
}