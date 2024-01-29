#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MINE -1
#define UNREVEALED -2
#define FLAG -3
#define LEADERBOARD_FILE "leaderboard.txt"
#define MAX_LEADERBOARD_ENTRIES 10

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

typedef struct minesweeper{
    int width;
    int length;
    int mines;
    int **board;
    int **display;
}minesweeper;

typedef struct {
    double timeTaken;
    int mines;
    int rows;
    int columns;
} leaderboardEntry;

int compareEntries(const void *a, const void *b) {
    // Cast the void pointers to pointers of type leaderboardEntry
    leaderboardEntry *entryA = (leaderboardEntry *)a;
    leaderboardEntry *entryB = (leaderboardEntry *)b;

    // Compare the timeTaken fields of the two entries
    if (entryA->timeTaken > entryB->timeTaken) {
        
        return 1;
    } else if (entryA->timeTaken < entryB->timeTaken) {

        return -1;
    } else {
 
        return 0;
    }
}

void saveLeaderboardEntry(leaderboardEntry newEntry) {
    leaderboardEntry entries[MAX_LEADERBOARD_ENTRIES + 1];
    int count = 0;

    // Read existing entries
    FILE *file = fopen(LEADERBOARD_FILE, "r");
    if (file != NULL) {
        while (count < MAX_LEADERBOARD_ENTRIES && fscanf(file, "%lf %d %d %d", &entries[count].timeTaken, &entries[count].mines, &entries[count].rows, &entries[count].columns) == 4) {
            count++;
        }
        fclose(file);
    }

    // Add new entry
    entries[count++] = newEntry;

    // Sort entries
    qsort(entries, count, sizeof(leaderboardEntry), compareEntries);

    // Write entries back to file
    file = fopen(LEADERBOARD_FILE, "w");
    if (file != NULL) {
        for (int i = 0; i < count && i < MAX_LEADERBOARD_ENTRIES; i++) {
            fprintf(file, "%lf %d %d %d\n", entries[i].timeTaken, entries[i].mines, entries[i].rows, entries[i].columns);
        }
        fclose(file);
    }
}

void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void readLeaderboard() {
    FILE *file = fopen(LEADERBOARD_FILE, "r");
    if (file != NULL) {
        leaderboardEntry entry;
        printf("\nThe following is the leadboard data of the fastest times and their corresponding set mines, columns and rows:\n");
        printf("Time\tMines\tRows\tColumns\n\n");
        while (fscanf(file, "%lf %d %d %d", &entry.timeTaken, &entry.mines, &entry.rows, &entry.columns) == 4) {
            printf("%.2f\t%d\t%d\t%d\n\n\n\n", entry.timeTaken, entry.mines, entry.rows, entry.columns);
        }
        fclose(file);
    } else {
        printf("No leaderboard data found.\n");
    }
}

int openingDecision(){
    int choice;
    int readItems;

    printf("Welcome to Minesweeper!!\n\n");

    while (true) {
        printf("Start New Game (1)\nView Leaderboard(2)\nQuit Game(9)\n\nWhat is your choice: ");
        readItems = scanf(" %d", &choice);

        if (readItems != 1) {
            printf("\nInvalid input. Please enter a number.\n\n");
            clearInputBuffer(); // Clear the input buffer to remove invalid input
            continue; // Ask for input again
        }

        switch (choice) {
            case 1:
                printf("\n\n\n");
                return 1; // Start game
            case 2:
                readLeaderboard();
                break; // Show leaderboard and ask again
            case 9:
                printf("\n\nHave a nice day!!\n");
                return 9; // Quit game
            default:
                printf("This option is invalid. Try again!\n\n\n");
                break; // Invalid option, ask again
        }
    }
}

minesweeper* openingData(int l, int w, int m){
    
    int readItems; 

   
    do {
        printf("How many rows (3 or more): ");
        readItems = scanf("%d", &l); 
        
        if (readItems != 1 || l < 3) {
            printf("Not a valid number. Please enter a valid number of rows.\n");
            clearInputBuffer(); 
        }
    } while (readItems != 1 || l < 3);

    do {
        printf("How many columns (3 or more): ");
        readItems = scanf("%d", &w); 
      
        if (readItems != 1 || w < 3) {
            printf("Not a valid number. Please enter a valid number of columns.\n");
            clearInputBuffer(); 
        }
    } while (readItems != 1 || w < 3); 

   
    do {
        printf("How many mines: ");
        readItems = scanf("%d", &m); 
     
        if (readItems != 1 || m < 1 || m > w * l) {
            printf("Not a valid number. Please enter a valid number of mines.\n");
            clearInputBuffer(); 
        }
    } while (readItems != 1 || m < 1 || m > w * l); 
    printf("\n\n");
    
    // Allocate memory for the minesweeper game structure.
    minesweeper* game = (minesweeper*)malloc(sizeof(minesweeper));
    game->width = w; 
    game->length = l; 
    game->mines = m; 

    // Allocate memory for the game board and display arrays.
    game->board = (int**)malloc(l * sizeof(int*));
    game->display = (int**)malloc(l * sizeof(int*));

    // Initialize the game board and display arrays.
    for (int i = 0; i < l; i++) {
        game->board[i] = (int*)malloc(w * sizeof(int));
        game->display[i] = (int*)malloc(w * sizeof(int));
        for (int j = 0; j < w; j++){
            game->board[i][j] = 0; 
            game->display[i][j] = UNREVEALED; 
        }
    }

    return game; 
}

void placeMines(minesweeper* game, int firstX, int firstY) {
    int minesPlaced = 0;
    while (minesPlaced < game->mines) {
        int x = rand() % game->length;
        int y = rand() % game->width;

        // Check if the randomly chosen cell is not the first clicked cell or its adjacent cells
        bool isSafeZone = (x == firstX && y == firstY);
        for (int i = 0; i < 8 && !isSafeZone; i++) {
            int adjX = firstX + dx[i];
            int adjY = firstY + dy[i];
            if (x == adjX && y == adjY) {
                isSafeZone = true;
            }
        }

        if (!isSafeZone && game->board[x][y] != MINE) {
            game->board[x][y] = MINE;
            minesPlaced++;

            // Update numbers around the mine
            for (int j = 0; j < 8; j++) {
                int nx = x + dx[j];
                int ny = y + dy[j];
                if (nx >= 0 && nx < game->length && ny >= 0 && ny < game->width && game->board[nx][ny] != MINE) {
                    game->board[nx][ny]++;
                }
            }
        }
    }
}

void printBoard(minesweeper* game){
    // Print Y-axis
    printf("    "); 
    for (int j = 0; j < game->width; j++) {
        printf("%3d", j + 1); 
    }
    printf("   Y\n");

    // Print X-axis
    for (int i = 0; i < game->length; i++) {
        printf("%3d ", i + 1); 
        for (int j = 0; j < game->width; j++) {
            
            if (game->display[i][j] == UNREVEALED) {
                printf("  ."); // Unrevealed cell
            } else if (game->display[i][j] == FLAG) {
                printf("  F"); // Flagged cell
            } else if (game->display[i][j] == MINE) {
                printf("  *"); // Mine cell
            } else {
                printf("%3d", game->display[i][j]); // Numbered cell
            }
        }
        printf("\n");
    }
    printf("\n  X\n");
    printf("\n");
}

bool areValidNums(minesweeper* game, int x, int y) {
    return x >= 0 && x < game->length && y >= 0 && y < game->width;
} 

void reveal(minesweeper* game, int x, int y) {

    if (x < 0 || x >= game->length || y < 0 || y >= game->width || game->display[x][y] != UNREVEALED) {
        return;
    }
    game->display[x][y] = game->board[x][y];
    if (game->board[x][y] == 0) {
        for (int i = 0; i < 8; i++) {
            reveal(game, x + dx[i], y + dy[i]);
        }
    }
}

bool checkWin(minesweeper* game) {
    for (int i = 0; i < game->length; i++) {
        for (int j = 0; j < game->width; j++) {
            if (game->display[i][j] == UNREVEALED && game->board[i][j] != MINE) {
                return false;
            }
        }
    }
    return true;
}

int main(){
    int decision = openingDecision();
    if (decision == 9) {
        return 0;
    }
    

    int w, l, m;
    minesweeper* game = openingData(w, l, m);
    bool gameOver = false;
    bool firstMove = true;
    time_t startTime = time(NULL);

    while (!gameOver){
        printBoard(game);
        int x, y;
        char action;
        int readItems;
        printf("\nType in coordinates (X Y): ");
        readItems = scanf("%d %d", &x, &y);
        if (readItems != 2) {
            printf("Invalid input. Please enter numbers.\n");
            clearInputBuffer(); 
            continue;
        }
        x--; 
        y--; 
        if (!areValidNums(game, x, y)) { 
            printf("Invalid coordinates. Please try again.\n");
            continue;
        }
        if (firstMove) {
            placeMines(game, x, y); 
            firstMove = false;
        }
        printf("Enter action (R for reveal, F for flag, U for unflag): ");
        scanf(" %c", &action);
        switch (action) {
            case 'R':
            case 'r':
                if (game->board[x][y] == MINE) {
                    printf("You stepped on a mine! Game over.\n");
                    time_t endTime = time(NULL);
                double elapsed = difftime(endTime, startTime);
                printf("Time taken: %.2f seconds\n", elapsed);
                    gameOver = true;
                } else {
                    reveal(game, x, y);
                    if (checkWin(game)) { 
                        printf("Congratulations! You've cleared the minefield!\n");
                        time_t endTime = time(NULL);
                        double elapsed = difftime(endTime, startTime);
                        printf("Time taken: %.2f seconds\n", elapsed);
                        gameOver = true;

                        leaderboardEntry entry;
                        entry.timeTaken = elapsed;
                        entry.mines = game->mines;
                        entry.rows = game->length;
                        entry.columns = game->width;
                        saveLeaderboardEntry(entry);

                    }
                }
                break;
            case 'F':
            case 'f':
                game->display[x][y] = FLAG;
                break;
            case 'U':
            case 'u':   
                if (game->display[x][y] == FLAG) {
                    game->display[x][y] = UNREVEALED;
                }
                break;
            default:
                printf("Invalid action. Please try again.\n");
        }
    }
    // Free each row of the board and display arrays
    for (int i = 0; i < game->length; i++) {
        free(game->board[i]);
        free(game->display[i]);
    }

    // Free the board and display pointers
    free(game->board);
    free(game->display);

    // Free the game structure
    free(game);

    return 0;
}












