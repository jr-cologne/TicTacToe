#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>

char winner;

char hasAnyoneWonGame(char field[3][3]) {
    // check for diagonal win
    if ( (field[0][0] == 'X' && field[1][1] == 'X' && field[2][2] == 'X') || (field[0][2] == 'X' && field[1][1] == 'X' && field[2][0] == 'X') ) {
        return 'X';
    } else if ( (field[0][0] == 'O' && field[1][1] == 'O' && field[2][2] == 'O') || (field[0][2] == 'O' && field[1][1] == 'O' && field[2][0] == 'O') ) {
        return 'O';
    }

    int hitX_pX = 0;
    int hitX_pO = 0;
    int hitY_pX = 0;
    int hitY_pO = 0;
    int i, j;

    // check for vertical or horizontal win
    for (i = 0; i < 3; i++) {
        hitX_pX = hitX_pO = hitY_pX = hitY_pO = 0;

        for (j = 0; j < 3; j++) {
            if (field[i][j] == 'X') {
                hitX_pX++;
            } else if (field[i][j] == 'O') {
                hitX_pO++;
            }

            if (field[j][i] == 'X') {
                hitY_pX++;
            } else if (field[j][i] == 'O') {
                hitY_pO++;
            }
        }

        if (hitX_pX == 3 || hitY_pX == 3) {
            return 'X';
        } else if (hitX_pO == 3 || hitY_pO == 3) {
            return 'O';
        }
    }

    return false;
}

bool gameEnded(char field[3][3]) {
    int i, j;
    char playerWon;
    int fieldsTaken = 0;

    // check if anyone has won the game
    playerWon = hasAnyoneWonGame(field);

    if (playerWon == 'X' || playerWon == 'O') {
        winner = playerWon;
        return true;
    }

    // check if field is full
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (field[i][j] == 'X' || field[i][j] == 'O') {
                fieldsTaken++;
            }
        }
    }

    if (fieldsTaken == 9) {
        // field is full
        return true;
    }

    return false;
}

bool isTaken(int x, int y, char field[3][3]) {
    if (field[y-1][x-1] == 'X' || field[y-1][x-1] == 'O') {
        return true;
    }

    return false;
}

int askForXCoordinate(char playerName[21]) {
    int x;

    printf("%s, bitte setzen Sie einen Stein.\n", playerName);
    printf("%s, die x-Koordinate > ", playerName);
    scanf("%d", &x);
    fflush(stdin);
    printf("\n");

    while (x > 3 || x <= 0) {
        printf("Ihre Eingabe entspricht nicht dem erwarteten Format. Bitte korrigieren Sie dies.\n");
        printf("%s, die x-Koordinate > ", playerName);
        scanf("%d", &x);
        fflush(stdin);
        printf("\n");
    }

    return x;
}

int askForYCoordinate(char playerName[21]) {
    int y;

    printf("%s, die y-Koordinate > ", playerName);
    scanf("%d", &y);
    fflush(stdin);
    printf("\n");

    while (y > 3 || y <= 0) {
        printf("Ihre Eingabe entspricht nicht dem erwarteten Format. Bitte korrigieren Sie dies.\n");
        printf("%s, die x-Koordinate > ", playerName);
        scanf("%d", &y);
        fflush(stdin);
        printf("\n");
    }

    return y;
}

int main() {
    char playerX[21];       // name of player X
    char playerO[21];       // name of player O
    char player;            // current player symbol
    char playerName[21];    // current player name
    int i, j, x, y;
    char field[3][3];

    // get names of players
    printf("Spieler X, bitte Namen eingeben (max. 20 Zeichen) > ");
    scanf("%20s", playerX);

    printf("\n");

    printf("Spieler O, bitte Namen eingeben (max. 20 Zeichen) > ");
    scanf("%20s", playerO);

    printf("\n\n");

    // create field
    printf("  1 2 3\n");
    for (i = 1; i < 4; i++) {   // i = y
        printf("%d ", i);
        for (j = 1; j < 4; j++) {   // j = x
            field[i-1][j-1] = ' ';
            printf("%c ", field[i-1][j-1]);
        }
        printf("\n");
    }

    printf("\n");

    // set the player, who starts
    player = 'X';
    strcpy(playerName, playerX);

    while (!gameEnded(field)) {
        // ask player for coordinates
        x = askForXCoordinate(playerName);
        y = askForYCoordinate(playerName);

        // set stone for player
        while (isTaken(x, y, field)) {
            printf("Das Feld ist bereits belegt. Bitte waehlen Sie ein anderes.\n\n");

            // ask player for coordinates
            x = askForXCoordinate(playerName);
            y = askForYCoordinate(playerName);
        }

        // set stone
        field[y-1][x-1] = player;

        // display field
        printf("  1 2 3\n");
        for (i = 1; i < 4; i++) {   // i = y
            printf("%d ", i);
            for (j = 1; j < 4; j++) {   // j = x
                printf("%c ", field[i-1][j-1]);
            }
            printf("\n");
        }

        printf("\n");

        // swap player
        if (player == 'X') {
            player = 'O';
            strcpy(playerName, playerO);
        } else if (player == 'O') {
            player = 'X';
            strcpy(playerName, playerX);
        }
    }

    printf("\n");

    if (winner == 'X') {
        printf("%s hat gewonnen. Herzlichen Glueckwunsch!\n", playerX);
    } else if (winner == 'O') {
        printf("%s hat gewonnen. Herzlichen Glueckwunsch!\n", playerO);
    }

    printf("Niemand hat gewonnen.\n");
    printf("Das Spiel ist vorbei. Vielen Dank fuers Spielen!");

    return 0;
}
