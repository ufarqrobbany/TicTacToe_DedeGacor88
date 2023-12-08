#include <conio.h>
#include <stdio.h>
#include <windows.h>

struct Player {
    char name[50];
};

void displayKop() {
    printf(
        " ______   ______   ______   ______   ______   ______   __       ______    \n"
        "/\\  ___\\ /\\  ___\\ /\\  == \\ /\\  __ \\ /\\  == \\ /\\  == \\ /\\ \\     /\\  ___\\   \n"
        "\\ \\___  \\\\ \\ \\____\\ \\  __< \\ \\  __ \\\\ \\  __< \\ \\  __< \\ \\ \\____\\ \\  __\\   \n"
        " \\/\\_____\\\\ \\_____\\\\ \\_\\ \\_\\\\ \\_\\ \\_\\\\ \\_____\\\\ \\_____\\\\ \\_____\\ \\_____\\ \n"
        "  \\/_____/ \\/_____/ \\/_/ /_/ \\/_/\\/_/ \\/_____/ \\/_____/ \\/_____/ \\/_____/ \n"
        "\n");
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
    printf("                |       [%c]Back to Main Menu            |\n", (selectedOption == 1) ? 'x' : ' ');
    printf("                +---------------------------------------+\n");
}

void displayGuidemenu(int selectedOption) {
    printf("                +---------------------------------------+\n");
    printf("                |             Guide Page (!)            |\n");
    printf("                +---------------------------------------+\n");
    printf("                |       [%c]Back to Main Menu            |\n", (selectedOption == 1) ? 'x' : ' ');
    printf("                +---------------------------------------+\n");
}

void displayCreditmenu(int selectedOption) {
    printf("                +---------------------------------------+\n");
    printf("                |               Credits (!)             |\n");
    printf("                +---------------------------------------+\n");
    printf("                |       [%c]Back to Main Menu            |\n", (selectedOption == 1) ? 'x' : ' ');
    printf("                +---------------------------------------+\n");
}

int main() {
    system("cls");
    int key;
    int selectedOption = 1;
    int submenuOption = 0;

    do {
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
                    system("cls");
                    break;
                case 80:  // Down arrow key
                    selectedOption = (selectedOption < 5) ? selectedOption + 1 : 1;
                    system("cls");
                    break;
                case 13:  // Enter key
                    if (selectedOption == 1) {
                        submenuOption = 1;  // Enter submenu for Start Game
                        selectedOption = 1;
                        system("cls");
                        key = 0;
                        // Note: Removed clearing the console screen here
                    } else if (selectedOption == 2) {
                        submenuOption = 2;  // Enter submenu for Score Game
                        selectedOption = 1;
                        system("cls");
                        key = 0;
                        // Note: Removed clearing the console screen here
                    } else if (selectedOption == 3) {
                        submenuOption = 3;  // Enter submenu for Guide Game
                        selectedOption = 1;
                        system("cls");
                        key = 0;
                        // Note: Removed clearing the console screen here
                    } else if (selectedOption == 4) {
                        submenuOption = 4;  // Enter submenu for Credit Game
                        selectedOption = 1;
                        system("cls");
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
                    system("cls");
                    break;
                case 80:  // Down arrow key
                    selectedOption = (selectedOption < 3) ? selectedOption + 1 : 1;
                    system("cls");
                    break;
                case 13:  // Enter key
                    // Perform action based on the selected submenu option
                    if (selectedOption == 1) {
                        printf("New Game selected...\n");
                        // Add your logic for starting a new game here
                        submenuOption = 5;  // Enter submenu for set Players
                        selectedOption = 1;
                        system("cls");
                        key = 0;
                    } else if (selectedOption == 2) {
                        printf("Continue selected...\n");
                        // Add your logic for continuing the game here
                    } else if (selectedOption == 3) {
                        selectedOption = 1;
                        submenuOption = 0;  // Go back to the main menu
                        system("cls");
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
                    system("cls");
                    key = 0;
                }
            }
            // Clear the console screen (for Windows) - Moved outside of the submenu loop
            // system("cls");
        } else if (submenuOption == 5) {
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
                        printf("P1 VS P2 selected...\n");
                        // Add your logic for starting a new game here
                    } else if (selectedOption == 2) {
                        printf("P1 VS COM selected...\n");
                        // Add your logic for continuing the game here
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