#include <stdio.h>
#include "input.c"
#include "output.c"
#include "board.c"

//TODO: Insert Ko and Score counting

int main(int argc, int *argv[]) 
{
    int rows, columns;
    ScanBoardSize(&rows, &columns);

    int board[rows][columns]; //1 is black, 0 is empty, -1 is white
    InitializeBoard(&(board[0][0]), rows, columns);
    
    int previousBoardBlackTurn[rows][columns];
    CopyMatrix(&(board[0][0]), &(previousBoardBlackTurn[0][0]), rows, columns);
    int previousBoardWhiteTurn[rows][columns];
    CopyMatrix(&(board[0][0]), &(previousBoardWhiteTurn[0][0]), rows, columns);

    int blackTurn = 1;
    
    for(;;)
    {
        printf("\n\n");

        PrintBoard(&(board[0][0]), rows, columns);

        int choice;
        printf("\n");
        PrintTurn(blackTurn);

        PrintChoiceOption();
        choice = ScanChoice();

        if(choice == 1)
        {
            int moveOutCome;
            do
            {
                int i = ScanRowIndex();
                int j = ScanColumnIndex();
                moveOutCome = MakeMove(&(board[0][0]), rows, columns, i, j, blackTurn, &(previousBoardBlackTurn[0][0]), &(previousBoardWhiteTurn[0][0]));

                PrintMoveOutcome(moveOutCome);
            }
            while(moveOutCome != 0);
            
            blackTurn = !blackTurn;
        }
        if(choice == 2)
        {
            blackTurn = !blackTurn;
        }
        else
        {
            PrintInvalidChoice();
        }
    }
}