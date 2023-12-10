#include <conio.h>
#include <stdio.h>
#include <windows.h>

typedef struct {
    char name[50];
    char rank[50];
    char date[50];
    int score;
    int total_poin;
} Player;

Player pl[100];
FILE *dataPlayer;
int counter;

void sortHighscores(Player (*pl)[100], int ascending) {
    int i, j, index;
    Player temp;
    for (i = 0; i < counter - 1; i++) {
        index = i;
        for (j = i + 1; j < counter; j++) {
            if ((ascending && (*pl)[j].total_poin < (*pl)[index].total_poin) ||
                (!ascending && (*pl)[j].total_poin > (*pl)[index].total_poin)) {
                index = j;
            }
        }
        // Swap mhs[i] and mhs[index]
        temp = (*pl)[i];
        (*pl)[i] = (*pl)[index];
        (*pl)[index] = temp;
    }
}

int get_total_poin(Player pl) {
    int total;
    total = pl.score + 99;
    return total;
}

void printDataPlayer(Player pl[100]) {
    printf("Sedang print data");

    if (counter == 0) {
        printf("|                       Ups! Nampaknya data masih kosong.                       |\n");
    } else {
        for (int i = 0; i < counter; i++) {
            // printf("| %s \t\t|\t %s \t|\t %d \t| %s \t\t|\n", pl[i].name, pl[i].rank, pl[i].total_poin, pl[i].date);
            // printf("|%s|", pl[i].name);
            // printf("|%s|", pl[i].rank);
            printf("|%d|", pl[i].score);
            // printf("|%s|", pl[i].date);
        }
    }
}

void readDataPlayer(Player (*pl)[100]) {
    dataPlayer = fopen("scores.txt", "r");
    int i = 0;

    // while (!feof(dataPlayer)) {
    //     fscanf(dataPlayer, "%d\n", (*pl)[i].score);
    //     fflush(stdin);
    //     i++;
    // }

    while ((fscanf(dataPlayer, "%d", &(*pl)[i].score) == 1) && (!feof(dataPlayer))) {
        fflush(stdin);
        i++;
    }

    printf("Berhasil read data");

    counter = i;

    fclose(dataPlayer);
}

void saveDataPlayer(Player pl[100]) {
    dataPlayer = fopen("scores.txt", "a");
    for (int i = 0; i < 2; i++) {
        fprintf(dataPlayer, "%s#%s#%d#%s#\n", pl[i].name, pl[i].rank, pl[i].score, pl[i].date);
    }
    fclose(dataPlayer);
    printf("Data input Berhasil Disimpan di scores.txt !\n");
}

void saveSortedData(Player pl[100], char *filename) {
    dataPlayer = fopen(filename, "w");
    for (int i = 0; i < counter; i++) {
        fprintf(dataPlayer, "%s#%s#%d#%s#\n", pl[i].name, pl[i].rank, pl[i].score, pl[i].date);
    }
    fclose(dataPlayer);
    printf("[!] Sementara data Sorting Disimpan di %s!\n", filename);
    printf("\n         [i] Press any Key ...");
}

void saveHighscoresDescending(Player pl[100]) {
    saveSortedData(pl, "top_score.txt");
}

void displayScoremenu(int selectedOption) {
    printf("+-------------------------------------------------------------------------------+\n");
    printf("|                                 HIGHSCORE                                     |\n");
    printf("+-------------------------------------------------------------------------------+\n");
    printf("|       PLAYER          |      RANK     |     SCORE     |        DATE           |\n");
    printf("+-------------------------------------------------------------------------------+\n");

    printf("+-------------------------------------------------------------------------------+\n");
    printf("|                [i] Press any Key for Back to Main menu ...                    |\n");
    printf("+-------------------------------------------------------------------------------+\n");
}

void inputPlayerhuman(Player pl[100]) {
    printf("+-------------------------------------------------------------------------------+\n");
    printf("|                                P1 VS P2                                       |\n");
    printf("+-------------------------------------------------------------------------------+\n");
    for (int i = 0; i < 2; i++) {
        printf("| [Data for Player %d]                                                           |\n", i + 1);
        printf("        >>> Username    :");
        scanf(" %[^\n]", &pl[i].name);
        printf("        >>> Rank        :");
        scanf(" %[^\n]", &pl[i].rank);
        printf("        >>> Score       :");
        scanf("%d", &pl[i].score);
        printf("        >>> Date        :");
        scanf(" %[^\n]", &pl[i].date);

        pl[i].total_poin = get_total_poin(pl[i]);
    }
}

void inputPlayercomp(Player pl[100]) {
    printf("+-------------------------------------------------------------------------------+\n");
    printf("|                                P1 VS COMP                                     |\n");
    printf("+-------------------------------------------------------------------------------+\n");
    for (int i = 0; i < 1; i++) {
        printf("| [Data for Player %d]                                                           |\n", i + 1);
        printf("        >>> Username  :");
        scanf(" %[^\n]", pl[i].name);
    }
}

void displayKop() {
    printf(
        " ______   ______   ______   ______   ______   ______   __       ______    \n"
        "/\\  ___\\ /\\  ___\\ /\\  == \\ /\\  __ \\ /\\  == \\ /\\  == \\ /\\ \\     /\\  ___\\   \n"
        "\\ \\___  \\\\ \\ \\____\\ \\  __< \\ \\  __ \\\\ \\  __< \\ \\  __< \\ \\ \\____\\ \\  __\\   \n"
        " \\/\\_____\\\\ \\_____\\\\ \\_\\ \\_\\\\ \\_\\ \\_\\\\ \\_____\\\\ \\_____\\\\ \\_____\\  \\_____\\ \n"
        "  \\/_____/ \\/_____/ \\/_/ /_/ \\/_/\\/_/ \\/_____/ \\/_____/ \\/_____/ \\/_____/ \n"
        "\n");
}

void displayMenu(int selectedOption) {
    printf("                +---------------------------------------+\n");
    printf("                |       Main Menu (Choose submenu)      |\n");
    printf("                +---------------------------------------+\n");
    printf("                |       [%c]Start Game                   |\n", (selectedOption == 1) ? 'x' : ' ');
    printf("                |       [%c]Highscores                   |\n", (selectedOption == 2) ? 'x' : ' ');
    printf("                |       [%c]Guide                        |\n", (selectedOption == 3) ? 'x' : ' ');
    printf("                |       [%c]Credits                      |\n", (selectedOption == 4) ? 'x' : ' ');
    printf("                |       [%c]Exit                         |\n", (selectedOption == 5) ? 'x' : ' ');
    printf("                +---------------------------------------+\n");
}

void displaySetPlayersMenu(int selectedOption) {
    printf("                +---------------------------------------+\n");
    printf("                |         New Game : Set Players        |\n");
    printf("                +---------------------------------------+\n");
    printf("                |       [%c]P1 VS P2                     |\n", (selectedOption == 1) ? 'x' : ' ');
    printf("                |       [%c]P1 VS COM                    |\n", (selectedOption == 2) ? 'x' : ' ');
    printf("                |       [%c]Back to Main menu            |\n", (selectedOption == 3) ? 'x' : ' ');
    printf("                +---------------------------------------+\n");
}

void displayStartmenu(int selectedOption) {
    printf("                +---------------------------------------+\n");
    printf("                |               Start Game              |\n");
    printf("                +---------------------------------------+\n");
    printf("                |       [%c]New Game                     |\n", (selectedOption == 1) ? 'x' : ' ');
    printf("                |       [%c]Continue                     |\n", (selectedOption == 2) ? 'x' : ' ');
    printf("                |       [%c]Back to Main Menu            |\n", (selectedOption == 3) ? 'x' : ' ');
    printf("                +---------------------------------------+\n");
}

void displayGuidemenu(int selectedOption) {
    printf("+---------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                                           GUIDE PAGE                                                                              |\n");
    printf("+---------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("| BRAND SCRABBLE                                        W o R                                                                                       |\n");
    printf("| GAME RULES FOR 2 TO 4 PLAYERS / AGES 8 TO ADULT                                                                                                   |\n");
    printf("|                                                                                                                                                   |\n");
    printf("| CONTENTS:                                                                                                                                         |\n");
    printf("| Gameboard, 100 letter tiles, letter pouch, 4 tile racks.                                                                                          |\n");
    printf("+---------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("| Object:                                                                                                                                           |\n");
    printf("| In the SCRABBLE@ game, players form interlocking words, crossword fashion, on the board using letter tiles of different values.                   |\n");
    printf("| Each player competes for high score by taking advantage of the letter tiles, as well as the premium squares on the board.                         |\n");
    printf("| In a 2-player game, a good player scores in the 300-400 point range.                                                                              |\n");
    printf("|                                                                                                                                                   |\n");
    printf("| Setup:                                                                                                                                            |\n");
    printf("| Place all letter tiles in the pouch or facedown beside the board and mix them up.                                                                 |\n");
    printf("| Draw for first play. The player with the letter closest to 'A' plays first. A blank tile beats any letter.                                        |\n");
    printf("| Return the letters to the pool and remix. All players draw seven new letters each and place them in their racks.                                  |\n");
    printf("+---------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("| Gameplay:                                                                                                                                         |\n");
    printf("| (1) The first player combines two or more of his or her letters to form a word and places the word on the board to read either across or down with|\n");
    printf("|     one letter on the center * square. Diagonal words are not allowed.                                                                            |\n");
    printf("| (2) Complete your turn by counting and announcing the score for that turn. Then draw as many new letters as you played, always keeping seven      |\n");
    printf("|     letters on your rack, as long as there are enough left in the pouch.                                                                          |\n");
    printf("| (3) Play passes to the left. The second player, and then each in turn, adds one or more letters to those already played to form new words. All    |\n");
    printf("|     letters played on a turn must be placed in one row across or down the board to form at least one complete word. If, at the same time, they    |\n");
    printf("|     touch other letters in adjacent rows, those must form complete words, crossword fashion, with all such letters. The player gets full credit   |\n");
    printf("|     for all words formed or modified on his or her turn.                                                                                          |\n");
    printf("| (4) New words may be formed by:                                                                                                                   |\n");
    printf("|     a. Adding one or more letters to a word or letters already on the board.                                                                      |\n");
    printf("|     b. Placing a word at right angles to a word already on the board. The new word must use one of the letters already on the board or must add a |\n");
    printf("|        letter to it.                                                                                                                              |\n");
    printf("|     c. Placing a complete word parallel to a word already played so the adjacent letters also form complete words.                                |\n");
    printf("| (5) No tile may be shifted or replaced after it has been played and scored.                                                                       |\n");
    printf("| (6) Blanks: The two blank tiles may be used as any letters. When playing a blank, you must state which letter it represents. It remains that      |\n");
    printf("|     letter for the rest of the game.                                                                                                              |\n");
    printf("| (7) You may use a turn to exchange all, some, or none of your letters. To do this, place your discarded letter(s) facedown. Draw the same number  |\n");
    printf("|      of letters from the pool, then mix your discarded letter(s) into the pool. This ends your turn.                                              |\n");
    printf("| (8) Before the game begins, players should agree on which dictionary they will use in case of a challenge. All words labeled as a part of speech  |\n");
    printf("|     including those listed of foreign origin, and as archaic, obsolete, colloquial, slang, etc.) are permitted with the exception of the following|\n");
    printf("|     : words always capitalized, abbreviations, prefixes and suffixes standing alone, words requiring a hyphen or an apostrophe. Any play may be   |\n");
    printf("|     challenged before the next player starts a turn. If the play challenged is unacceptable, the challenged player takes back his or her tiles and|\n");
    printf("|     loses that turn. If the play challenged is acceptable, the challenger loses his or her next turn. All words (not just one) made in one play   |\n");
    printf("|     challenged simultaneously. If any word is unacceptable, the entire play is unacceptable. Only one turn is lost on any challenge. Consult the  |\n");
    printf("|     dictionary for challenges only.                                                                                                               |\n");
    printf("| (9) Ending the Game: The game ends when all letters have been drawn, and one player uses his or her last letter, or when all possible plays have  |\n");
    printf("|     been made.                                                                                                                                    |\n");
    printf("+---------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("| Scoring:                                                                                                                                          |\n");
    printf("| (1) The scorekeeper tallies each player's score, entering it after each turn. The score value of each letter is indicated by a number at the      |\n");
    printf("      bottom of the tile. The score value of a blank is zero.                                                                                       |\n");
    printf("| (2) The score for each turn is the sum of the letter values in each word(s) formed or modified on that turn, plus the additional points obtained  |\n");
    printf("|     from placing letters on premium squares.                                                                                                      |\n");
    printf("| (3) Premium Letter Squares: A light blue square doubles the score of a letter placed on it; a dark blue square triples the letter score.          |\n");
    printf("| (4) Premium Word Squares: The score for an entire word is doubled when one of its letters is placed on a pink square; it is tripled when one of   |\n");
    printf("|     its letters is placed on a red square. Include premiums for double or triple letter values, if any, before doubling or tripling the word      |\n");
    printf("|     score. If a word covers two premium word squares, the score is doubled and then re-doubled (4 times the letter count) or tripled and then     |\n");
    printf("|     re-tripled (9 times the letter count). NOTE: The center * square is a pink square, which doubles the score for the first word.                |\n");
    printf("| (5) Letter and word premiums count only on the turn in which they are played. On later turns, letters already played on premium squares count at  |\n");
    printf("|     face value.                                                                                                                                   |\n");
    printf("| (6) When a blank tile is played on a pink or red square, the value of the word is doubled or tripled, even though the blank itself has no score   |\n");
    printf("|    value.                                                                                                                                         |\n");
    printf("| (7) When two or more words are formed in the same play, each is scored. The common letter is counted (with full premium value, if any) for each   |\n");
    printf("|     word.                                                                                                                                         |\n");
    printf("| (8) BINGO! - If you play seven tiles on a turn, it's a Bingo. You earn a premium of 50 points after totaling your score for the turn.             |\n");
    printf("| (9) Unplayed Letters: When the game ends, each player's score is reduced by the sum of his or her unplayed letters. If a player used all his or   |\n");
    printf("|     her letters, the sum of the other players' unplayed letters is added to that player's score.                                                  |\n");
    printf("|                                                                                                                                                   |\n");
    printf("| How to Win:                                                                                                                                       |\n");
    printf("| The player with the highest final score wins the game. In case of a tie, the player with the highest score before adding or deducting unplayed    |\n");
    printf("| letters wins.                                                                                                                                     |\n");
    printf("+---------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("| Finish Line Scrabble Game:                                                                                                                        |\n");
    printf("| In this variant, the game is over when one player reaches a pre-decided score, no matter how many tiles are left. This variant allows mixed play- |\n");
    printf("| level groups, as the score needed to win depends on the level of the player (Beginner, Intermediate, or Expert). Here are the points needed to    |\n");
    printf("| win the game:                                                                                                                                     |\n");
    printf("|                                                                                                                                                   |\n");
    printf("|                      Beginner      Intermediate     Expert                                                                                        |\n");
    printf("| Three Players        60             100               180                                                                                         |\n");
    printf("| Two Players          70             120               200                                                                                         |\n");
    printf("| Four Players         50             90                160                                                                                         |\n");
    printf("|                                                                                                                                                   |\n");
    printf("| If players of the same level are playing, each needs to reach the same score. For example, two Intermediate players would be playing to 120, and  |\n");
    printf("| four Beginners would each be playing to 50.                                                                                                       |\n");
    printf("+---------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("| 10 Ways to Become an Instant SCRABBLE Game Expert:                                                                                                |\n");
    printf("| (1) Learn the 2-letter and 3-letter words. They are the building blocks of expert play and can boost your average score by as much as 50 points   |\n");
    printf("|    per game.                                                                                                                                      |\n");
    printf("| (2) Use an S to form two words at once. Pluralize one word while forming another at the same time. Use your S wisely; don't add it unless you can |\n");
    printf("|    fearn at least 8 points by doing so.                                                                                                           |\n");
    printf("| (3) Shuffle the tiles on your rack frequently. Look for common ways that letters go together.                                                     |\n");
    printf("| (4) Always look for ways to play across premium squares, especially those next to vowels.                                                         |\n");
    printf("| (5) Make your play with an eye toward your next play. Save good tiles on your rack for future turns.                                              |\n");
    printf("| (6) Always look for Bingos (using all 7 tiles at once). Learn common word beginnings and endings.                                                 |\n");
    printf("| (7) Learn the Q-without-U words. The Official SCRABBLE Players Dictionary lists these: QAT(S), QAID(S), QOPH(S), FAQIR(S), QANAT(S), TRANQ(S),    |\n");
    printf("|    QWERTY(S), SHEQEL, QINDARKA, and SHEQALIM.                                                                                                     |\n");
    printf("| (8) Look for 'hooks' - single letters that can be added to existing words to form other words.                                                    |\n");
    printf("| (9) After finding a good play, if you have time, look for a better one. Give yourself a choice of plays.                                          |\n");
    printf("| (10) Maintain a positive attitude and enjoy playing. Learn from your mistakes and focus on having fun!                                            |\n");
    printf("+---------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                                               [%c] Back to Main Menu                                                               |\n", (selectedOption == 1) ? 'x' : ' ');
    printf("+---------------------------------------------------------------------------------------------------------------------------------------------------+\n");
}

void displayCreditmenu(int selectedOption) {
    printf("+-------------------------------------------------------------------------------+\n");
    printf("|                                CREDITS                                        |\n");
    printf("+-------------------------------------------------------------------------------+\n");
    printf("|  BACKGROUND:                                                                  |\n");
    printf("|  Scrabble is a classic word game that has been enjoyed by people of all ages  |\n");
    printf("|  for decades. It provides a challenging and entertaining way to expand your   |\n");
    printf("|  vocabulary while having fun with friends and family.                         |\n");
    printf("|                                                                               |\n");
    printf("|  CREATOR:                                                                     |\n");
    printf("|                                                                               |\n");
    printf("|  $$$$$$\\  $$\\   $$\\ $$$$$$$$\\ $$\\       $$$$$$\\ $$\\   $$\\  $$$$$$\\  $$$$$$\\   |\n");
    printf("| $$  __$$\\ $$ | $$  |$$  _____|$$ |      \\_$$  _|$$$\\  $$ |$$  __$$\\ \\_$$  _|  |\n");
    printf("| \\__/  $$ |$$ |$$  / $$ |      $$ |        $$ |  $$$$\\ $$ |$$ /  \\__|  $$ |    |\n");
    printf("|  $$$$$$  |$$$$$  /  $$$$$\\    $$ |        $$ |  $$ $$\\$$ |$$ |        $$ |    |\n");
    printf("| $$  ____/ $$  $$<   $$  __|   $$ |        $$ |  $$ \\$$$$ |$$ |        $$ |    |\n");
    printf("| $$ |      $$ |\\$$\\  $$ |      $$ |        $$ |  $$ |\\$$$ |$$ |  $$\\   $$ |    |\n");
    printf("| $$$$$$$$\\ $$ | \\$$\\ $$$$$$$$\ $$$$$$$\\ $$$$$$\\ $$ | \\$$ | \\$$$$$$  |$$$$$$\\    |\n");
    printf("| \\________|\\__|  \\__|\\_______|\\________|\\______|\\__|  \\__| \\______/ \\______|   |\n");
    printf("|                                                                               |\n");
    printf("|  MEMBER(S) :                                                                  |\n");
    printf("|  FARRAS AHMAD RASYID  | FAR | 231524006                                       |\n");
    printf("|  NIETO SALIM MAULA    | NSM | 231524019                                       |\n");
    printf("|                                                                               |\n");
    printf("|  SOURCE CODE:                                                                 |\n");
    printf("|  The source code for this Scrabble game is created by [Your Name].            |\n");
    printf("|  It is an original implementation in the C programming language.              |\n");
    printf("|                                                                               |\n");
    printf("|  SPECIAL THANKS:                                                              |\n");
    printf("|  - [Name of contributor/source for specific code]                             |\n");
    printf("|  - [Name of contributor/source for specific code]                             |\n");
    printf("|  - [Name of contributor/source for specific code]                             |\n");
    printf("|                                                                               |\n");
    printf("|  ADDITIONAL INFO:                                                             |\n");
    printf("|  - This game is inspired by the classic Scrabble board game.                  |\n");
    printf("|  - All rights to the Scrabble game concept and trademarks belong to           |\n");
    printf("|    their respective owners.                                                   |\n");
    printf("+-------------------------------------------------------------------------------+\n");
    printf("|                          [%c] Back to Main Menu                                |\n", (selectedOption == 1) ? 'x' : ' ');
    printf("+-------------------------------------------------------------------------------+\n");
}

int main() {
    int key;
    int selectedOption = 1;
    int submenuOption = 0;

    do {
        system("cls");
        if (submenuOption == 0) {
            // Display the main menu
            displayKop();
            displayMenu(selectedOption);
        } else if (submenuOption == 1) {
            // Display the submenu
            displayKop();
            displayStartmenu(selectedOption);
        } else if (submenuOption == 2) {
            // Display the submenu
            displayKop();
            displayScoremenu(selectedOption);
            printf("sudah tampil menu");
            readDataPlayer(&pl);
            printf("sudah read data");
            sortHighscores(&pl, 0);
            printDataPlayer(pl);
            // saveHighscoresDescending(pl);
        } else if (submenuOption == 3) {
            // Display the submenu
            displayKop();
            displayGuidemenu(selectedOption);
        } else if (submenuOption == 4) {
            // Display the submenu
            displayKop();
            displayCreditmenu(selectedOption);
        } else if (submenuOption == 5) {
            displayKop();
            displaySetPlayersMenu(selectedOption);
        }

        // Wait for key press without Enter
        key = getch();

        if (submenuOption == 0) {
            // Handle arrow key input for the main menu
            switch (key) {
                case 72:  // Up arrow key
                    selectedOption = (selectedOption > 1) ? selectedOption - 1 : 5;
                    break;
                case 80:  // Down arrow key
                    selectedOption = (selectedOption < 5) ? selectedOption + 1 : 1;
                    break;
                case 13:  // Enter key
                    if (selectedOption == 1) {
                        submenuOption = 1;  // Enter submenu for Start Game
                        selectedOption = 1;
                        key = 0;
                        // Note: Removed clearing the console screen here
                    } else if (selectedOption == 2) {
                        submenuOption = 2;  // Enter submenu for Score Game
                        selectedOption = 1;

                        key = 0;
                        // Note: Removed clearing the console screen here
                    } else if (selectedOption == 3) {
                        submenuOption = 3;  // Enter submenu for Guide Game
                        selectedOption = 1;
                        key = 0;
                        // Note: Removed clearing the console screen here
                    } else if (selectedOption == 4) {
                        submenuOption = 4;  // Enter submenu for Credit Game
                        selectedOption = 1;
                        key = 0;
                        // Note: Removed clearing the console screen here
                    } else if (selectedOption == 5) {
                        key = 13;  // Exit if "Exit" is selected in the main menu
                    }
                    break;
                default:
                    // Ignore other keys
                    break;
            }
        } else if (submenuOption == 1) {
            // Handle arrow key input for the submenu
            switch (key) {
                case 72:  // Up arrow key
                    selectedOption = (selectedOption > 1) ? selectedOption - 1 : 3;
                    break;
                case 80:  // Down arrow key
                    selectedOption = (selectedOption < 3) ? selectedOption + 1 : 1;
                    break;
                case 13:  // Enter key
                    // Perform action based on the selected submenu option
                    if (selectedOption == 1) {
                        printf("New Game selected...\n");
                        // Add your logic for starting a new game here
                        submenuOption = 5;  // Enter submenu for set Players
                        selectedOption = 1;
                        key = 0;
                    } else if (selectedOption == 2) {
                        printf("Continue selected...\n");
                        // Add your logic for continuing the game here
                    } else if (selectedOption == 3) {
                        selectedOption = 1;
                        submenuOption = 0;  // Go back to the main menu
                        key = 0;
                    }
                    break;
            }
        } else if (submenuOption >= 2 && submenuOption <= 4) {
            // Handle arrow key input for the submenu
            if (key == 13) {
                if (selectedOption == 1) {
                    selectedOption = 1;
                    submenuOption = 0;  // Go back to the main menu
                    key = 0;
                }
            }
            // Clear the console screen (for Windows) - Moved outside of the submenu loop
            //
        } else if (submenuOption == 5) {
            // Handle arrow key input for the submenu
            switch (key) {
                case 72:  // Up arrow key
                    selectedOption = (selectedOption > 1) ? selectedOption - 1 : 3;
                    break;
                case 80:  // Down arrow key
                    selectedOption = (selectedOption < 3) ? selectedOption + 1 : 1;
                    break;
                case 13:                        // Enter key and Perform action based on the selected submenu option
                    if (selectedOption == 1) {  // Add your logic for continuing the game here
                        system("cls");
                        displayKop();
                        printf("P1 VS P2 selected...\n");
                        inputPlayerhuman(pl);
                        saveDataPlayer(pl);
                        readDataPlayer(&pl);
                    } else if (selectedOption == 2) {  // Add your logic for continuing the game here
                        system("cls");
                        displayKop();
                        printf("P1 VS COM selected...\n");
                        inputPlayercomp(pl);
                    } else if (selectedOption == 3) {
                        selectedOption = 1;
                        submenuOption = 0;  // Go back to the main menu
                        key = 0;
                    }
                    break;
            }
        }
    } while (key != 13);  // 13 is the ASCII code for Enter key

    if (submenuOption == 0) {
        printf("Exiting...\n");
    }

    return 0;
}