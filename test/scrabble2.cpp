#include <conio.h>
#include <stdio.h>
#include <windows.h>

struct Player {
    char name[50];
};

void displayIdentityMenu(struct Player players[2]) {
    printf("+-------------------------------+\n");
    printf("|   Identity Player : P1 VS P2 |\n");
    printf("+-------------------------------+\n");
    printf("| P1  : %-25s |\n", players[0].name);
    printf("| P2  : %-25s |\n", players[1].name);
    printf("|                               |\n");
    printf("| [ ] Start Game               |\n");
    printf("| [ ] Back to Main menu        |\n");
    printf("+-------------------------------+\n");
}

void displaySetPlayersMenu(struct Player players[2]) {
    printf("+-------------------------------+\n");
    printf("|    New Game : Set Players     |\n");
    printf("+-------------------------------+\n");
    printf("| [%c] P1 VS P2                |\n", (players[0].name[0] != '\0' && players[1].name[0] != '\0') ? 'x' : ' ');
    printf("| [%c] P1 VS COM               |\n", (players[0].name[0] != '\0' && players[1].name[0] == '\0') ? 'x' : ' ');
    printf("| [%c] Back to Main menu        |\n", (players[0].name[0] == '\0' && players[1].name[0] == '\0') ? 'x' : ' ');
    printf("+-------------------------------+\n");
}

void inputPlayerNames(struct Player players[2], int numPlayers) {
    for (int i = 0; i < numPlayers; ++i) {
        printf("Enter name for Player %d: ", i + 1);
        scanf("%s", players[i].name);
    }
}

void displayGameModeMenu(struct Player players[2]) {
    printf("+-------------------------------+\n");
    printf("|           Game Mode           |\n");
    printf("+-------------------------------+\n");
    printf("| [ ] P1 VS P2                 |\n");
    printf("| [ ] P1 VS COM                |\n");
    printf("| [ ] Back to Main menu        |\n");
    printf("+-------------------------------+\n");
}

void displayKop() {
    printf(
        " ______   ______   ______   ______   ______   ______   __       ______    \n"
        "/\\  ___\\ /\\  ___\\ /\\  == \\ /\\  __ \\ /\\  == \\ /\\  == \\ /\\ \\     /\\  ___\\   \n"
        "\\ \\___  \\\\ \\ \\____\\ \\  __< \\ \\  __ \\\\ \\  __< \\ \\  __< \\ \\ \\____\\ \\  __\\   \n"
        " \\/\\_____\\\\ \\_____\\\\ \\_\\ \\_\\\\ \\_\\ \\_\\\\ \\_____\\\\ \\_____\\\\ \\_____\\ \\_____\\ \n"
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

void displayStartmenu(int selectedOption) {
    printf("                +---------------------------------------+\n");
    printf("                |               Start Game              |\n");
    printf("                +---------------------------------------+\n");
    printf("                |       [%c]New Game                     |\n", (selectedOption == 1) ? 'x' : ' ');
    printf("                |       [%c]Continue                     |\n", (selectedOption == 2) ? 'x' : ' ');
    printf("                |       [%c]Back to Main Menu            |\n", (selectedOption == 3) ? 'x' : ' ');
    printf("                +---------------------------------------+\n");
}

void displayScoremenu(int selectedOption) {
    printf("                +---------------------------------------+\n");
    printf("                |               Highscore               |\n");
    printf("                +---------------------------------------+\n");
    printf("                |       [%c]Back to Main Menu            |\n", (selectedOption == 3) ? 'x' : ' ');
    printf("                +---------------------------------------+\n");
}

void displayGuidemenu(int selectedOption) {
    printf("                +---------------------------------------+\n");
    printf("                |             Guide Page (!)            |\n");
    printf("                +---------------------------------------+\n");
    printf("                |       [%c]Back to Main Menu            |\n", (selectedOption == 3) ? 'x' : ' ');
    printf("                +---------------------------------------+\n");
}

void displayCreditmenu(int selectedOption) {
    printf("                +---------------------------------------+\n");
    printf("                |               Credits (!)             |\n");
    printf("                +---------------------------------------+\n");
    printf("                |       [%c]Back to Main Menu            |\n", (selectedOption == 3) ? 'x' : ' ');
    printf("                +---------------------------------------+\n");
}

int main() {
    system("cls");
    int key;
    int selectedOption = 1;
    int submenuOption = 0;
    struct Player players[2] = {{"P1"}, {"P2"}};

    do {
        if (submenuOption == 0) {
            // Display the main menu
            displayKop();
            displayMenu(selectedOption);
        } else if (submenuOption == 1) {
            // Display the set players menu
            displayKop();
            displaySetPlayersMenu(players);
        } else if (submenuOption == 2) {
            // Display the game mode menu
            displayKop();
            displayGameModeMenu(players);
        }

        // Wait for key press without Enter
        key = getch();

        if (submenuOption == 0) {
            // Handle arrow key input for the main menu
            switch (key) {
                case 72:  // Up arrow key
                    selectedOption = (selectedOption > 1) ? selectedOption - 1 : 5;
                    system("cls");
                    break;
                case 80:  // Down arrow key
                    selectedOption = (selectedOption < 5) ? selectedOption + 1 : 1;
                    system("cls");
                    break;
                case 13:  // Enter key
                    if (selectedOption == 1) {
                        submenuOption = 1;  // Enter submenu for Set Players
                        selectedOption = 1;
                        system("cls");
                        inputPlayerNames(players, 2);
                    } else if (selectedOption == 2) {
                        submenuOption = 2;  // Enter submenu for Game Mode
                        selectedOption = 1;
                        system("cls");
                    } else if (selectedOption == 3) {
                        submenuOption = 3;  // Enter submenu for Guide
                        selectedOption = 1;
                        system("cls");
                    } else if (selectedOption == 4) {
                        submenuOption = 4;  // Enter submenu for Credits
                        selectedOption = 1;
                        system("cls");
                    } else if (selectedOption == 5) {
                        key = 13;  // Exit if "Exit" is selected in the main menu
                    }
                    break;
                default:
                    // Ignore other keys
                    break;
            }
        } else {
            // Handle arrow key input for the submenu
            switch (key) {
                case 72:  // Up arrow key
                    selectedOption = (selectedOption > 1) ? selectedOption - 1 : 3;
                    system("cls");
                    break;
                case 80:  // Down arrow key
                    selectedOption = (selectedOption < 3) ? selectedOption + 1 : 1;
                    system("cls");
                    break;
                case 13:  // Enter key
                    // Perform action based on the selected submenu option
                    if (selectedOption == 1) {
                        // Add your logic for starting a new game here
                        system("cls");
                        displayIdentityMenu(players);
                    } else if (selectedOption == 2) {
                        // Add your logic for continuing the game here
                        system("cls");
                        displayIdentityMenu(players);
                    } else if (selectedOption == 3) {
                        selectedOption = 1;
                        submenuOption = 0;  // Go back to the main menu
                        system("cls");
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
