#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

#define MAX_PLAYERS 100

// MACROS for colour schemes
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

struct player
{
    int id;
    char name[50];
    int age;
    int points;
};

typedef struct
{
    char name[30];
    char desc[80];
} hang;

struct player player_list[MAX_PLAYERS]; // for accessing globally
int num_players = 0;
//Function inilialisations
int fetch_player_serial_no(int play_id);
//player management
void addplayer();
void editplayer();
void deleteplayer();
void displayAllplayers(struct player temp_player_list[]);
void searchplayer();
void generateReports();
void gamingzone();
//guess the number
void guessthenumber(int player_serial_no);
//find the mine
void findthemine(int player_serial_no);
void print_mine(char arr[][7][2]);
//hangman
void hangman(hang *a, int range, int player_serial_num);
bool letter_present(char arr[], int n, char c);
void print_man(int n);
void printavailableletters(bool arr[], int arrange[]);
int search_char_in_str(char x, char a[], int n);
void print_hearts(int n);
char *wrap(char *s);
//tictactoe
void tictactoe(int player_1_sno, int player_2_sno);
void printbox(char arr[]);
char tick(char arr[]);

int getint()
{
    char character = getch();
    int integer_value = character - '0';
    return integer_value;
}

int abs(int a)
{
    if (a > 0)
        return a;
    return (-a);
}

void delay(int n_milliseconds)
{
    for (int i = 0; i < 4000000; i++)
        for (int j = 0; j < n_milliseconds; j++)
        {
        }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int fetch_player_serial_no(int play_id)
{
    for (int i = 0; i < num_players; i++)
    {
        if (player_list[i].id == play_id)
            return i;
    }
    return -1;
}
void addplayer()
{
    if (num_players == MAX_PLAYERS)
    {
        printf("Cannot add more players. Maximum capacity reached.\n");
        return;
    }
    struct player newplayer;
    printf("Enter player ID:");
    scanf("%d", &newplayer.id);
    if (fetch_player_serial_no(newplayer.id) == -1)
    {
        printf("Enter player name:");
        scanf("\n%50[^\n]", newplayer.name);
        printf("Enter player age:");
        scanf("%d", &newplayer.age);
        newplayer.points = 0;
        player_list[num_players++] = newplayer;
        printf("Player added successfully!\n");
    }
    else
    {
        printf("Player ID already exist.");
        printf("Try Again.\n");
        addplayer();
    }
}

void editplayer()
{
    int id;
    printf("Enter player ID to edit: ");
    scanf("%d", &id);
    for (int i = 0; i < num_players; i++)
    {
        if (player_list[i].id == id)
        {
            printf("Enter new player name: ");
            scanf("\n%50[^\n]", player_list[i].name);

            printf("Enter new player age: ");
            scanf("%d", &player_list[i].age);

            printf("Enter new player points: ");
            scanf("%d", &player_list[i].points);

            printf("Player information updated successfully!\n");
            return;
        }
    }
    printf("player with ID %d not found.\n", id);
}

void deleteplayer()
{
    int id;
    printf("Enter player ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < num_players; i++)
    {
        if (player_list[i].id == id)
        {
            for (int j = i; j < num_players - 1; j++)
            {
                player_list[j] = player_list[j + 1];
            }
            num_players--;
            printf("player deleted successfully!\n");
            return;
        }
    }
    printf("player with ID %d not found.\n", id);
}

void searchplayer()
{
    int choice;
    printf("Search player by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        int id;
        printf("Enter player ID to search: ");
        scanf("%d", &id);

        for (int i = 0; i < num_players; i++)
        {
            if (player_list[i].id == id)
            {
               
                printf("ID    : %d\n", player_list[i].id);
                printf("Name  : %s\n", player_list[i].name);
                printf("Age   : %d\n", player_list[i].age);
                printf("points: %d\n", player_list[i].points);
                printf(ANSI_COLOR_RESET);
                return;
            }
        }
        printf(ANSI_COLOR_RED);
        printf("player with ID %d not found.\n", id);
        printf(ANSI_COLOR_RESET);
    }
    else if (choice == 2)
    {
        char name[50];
        printf("Enter player name to search: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

        for (int i = 0; i < num_players; i++)
        {
            if (strcmp(player_list[i].name, name) == 0)
            {
                printf(ANSI_COLOR_GREEN);
                printf("player found!\n");
                printf("ID    : %d\n", player_list[i].id);
                printf("Name  : %s\n", player_list[i].name);
                printf("Age   : %d\n", player_list[i].age);
                printf("points: %d\n", player_list[i].points);
                printf(ANSI_COLOR_RESET);
                return;
            }
        }
        printf(ANSI_COLOR_RED);
        printf("player with name '%s' not found.\n", name);
        printf(ANSI_COLOR_RESET);
    }
    else
    {
        printf("Invalid choice.\n");
    }
}

void displayAllplayers(struct player temp_player_list[])
{
    if (num_players == 0)
    {
        printf("No players found.\n");
        return;
    }
    printf("+------+------------------------+-----+--------+\n");
    printf("|  ID  |          Name          | Age | Points |\n");
    printf("+------+------------------------+-----+--------+\n");
    for (int i = 0; i < num_players; i++)
    {
        printf("|%5d |", temp_player_list[i].id);
        printf("%23s |", temp_player_list[i].name);
        printf("%4d |", temp_player_list[i].age);
        printf("%7d |", temp_player_list[i].points);
        printf("\n+------+------------------------+-----+--------+\n");
    }
}

void generateReports()
{
    int choice;
    printf("Generate report for:\n");
    printf("1. Leaderboard\n");
    printf("2. Average points of all players\n");
    printf("3. Number of players in each points level\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        struct player player_lst[num_players];
        for (int i = 0; i < num_players; i++)
        {
            player_lst[i] = player_list[i];
        }
        for (int i = 0; i < num_players; i++)
        {
            for (int j = (num_players - i - 1); j > 0; j--)
            {
                if (player_lst[j].points > player_lst[j - 1].points)
                {
                    struct player temp = player_lst[j];
                    player_lst[j] = player_lst[j - 1];
                    player_lst[j - 1] = temp;
                }
            }
        }
        displayAllplayers(player_lst);
    }
    else if (choice == 2)
    {
        if (num_players == 0)
        {
            printf("No players found.\n");
            return;
        }
        float totalpoints = 0.0;
        for (int i = 0; i < num_players; i++)
        {
            totalpoints += player_list[i].points;
        }
        float averagepoints = totalpoints / num_players;
        printf("Average points of all players: %.2f\n", averagepoints);
    }
    else if (choice == 3)
    {
        if (num_players == 0)
        {
            printf("No players found.\n");
            return;
        }
        int pointsCount[10] = {0};
        for (int i = 0; i < num_players; i++)
        {
            int pointsLevel = (int)player_list[i].points / 10;
            if (pointsLevel >= 0 && pointsLevel < 10)
            {
                pointsCount[pointsLevel]++;
            }
        }
        printf("Number of players in each points level:\n");
        for (int i = 0; i < 10; i++)
        {
            printf("%2d-%2d: %d\n", i * 10, (i * 10) + 9, pointsCount[i]);
        }
    }
    else
    {
        printf("Invalid choice.\n");
    }
}

void printbox(char arr[])
{
    printf(ANSI_COLOR_CYAN);
    printf("     %c | %c | %c \n    ---+---+---\n     %c | %c | %c \n    ---+---+---\n     %c | %c | %c \n", arr[7], arr[8], arr[9], arr[4], arr[5], arr[6], arr[1], arr[2], arr[3]);
    printf(ANSI_COLOR_RESET);
}

char tick(char arr[])
{
    for (int i = 0; i < 3; i++)
    {
        if (arr[3 * i + 1] == arr[3 * i + 2] && arr[3 * i + 2] == arr[3 * i + 3] && arr[3 * i + 1] == 'X')
            return 'X';
        if (arr[3 * i + 1] == arr[3 * i + 2] && arr[3 * i + 2] == arr[3 * i + 3] && arr[3 * i + 1] == 'O')
            return 'O';
        if (arr[i + 1] == arr[i + 4] && arr[i + 4] == arr[i + 7] && arr[i + 1] == 'X')
            return 'X';
        if (arr[i + 1] == arr[i + 4] && arr[i + 4] == arr[i + 7] && arr[i + 1] == 'O')
            return 'O';
        if ((arr[1] == arr[5] && arr[5] == arr[9]) || (arr[3] == arr[5] && arr[5] == arr[7]))
        {
            if (arr[5] == 'X')
                return 'X';
            else if (arr[5] == 'O')
                return 'O';
        }
    }
    return ('a' - 'A');
}

char *wrap(char *s)
{
    int l = strlen(s);
    char *wr;
    wr = (char *)malloc((l + 1) * sizeof(char));
    for (int i = 0; i < l; i++)
    {
        if (s[i] == ' ')
            wr[i] = ' ';
        else
            wr[i] = '-';
    }
    wr[l] = '\0';
    return wr;
}

int search_char_in_str(char x, char a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] == x)
            return i;
    }
    return -1;
}

void printavailableletters(bool arr[], int arrange[])
{
    printf("      Available Letters\n");
    printf("[");
    for (int i = 0; i < 26; i++)
    {
        if (arr[arrange[i]])
        {
            printf(" _ ");
        }
        else
        {
            printf(" %c ", arrange[i] + 'a');
        }
        if (i == 9)
            printf("]\n  [");
        if (i == 18)
            printf("]\n     [");
    }
    printf("]\n");
}

void print_man(int n)
{
    printf(ANSI_COLOR_RED);
    if (n == 0)
        printf("\n\n\n\n\n\n        ___/|\\___\n");
    if (n == 1)
        printf("\n            |\n            |\n            |\n            |\n            |\n        ___/|\\___\n");
    else if (n == 2)
        printf("            ________\n            |/\n            |\n            |\n            |\n            |\n        ___/|\\___\n");
    else if (n == 3)
        printf("            ________\n            |/     |\n            |      O\n            |\n            |\n            |\n        ___/|\\___\n");
    else if (n == 4)
        printf("            ________\n            |/     |\n            |      O\n            |     /|\\\n            |\n            |\n        ___/|\\___\n");
    else if (n == 5)
        printf("            ________\n            |/     |\n            |      O\n            |     /|\\\n            |     / \\\n            |\n        ___/|\\___\n");
    printf(ANSI_COLOR_RESET);
}

bool letter_present(char arr[], int n, char c)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == c)
            return true;
    }
    return false;
}

void print_hearts(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c ", 3);
    }
    printf("\n");
}

void print_mine(char arr[][7][2])
{
    printf("     1    2    3    4    5    6    7\n");
    printf("  +----+----+----+----+----+----+----+\n");
    for (int i = 0; i < 7; i++)
    {
        printf("%d |", (i + 1));
        for (int j = 0; j < 7; j++)
        {
            printf(" %c%c |", arr[i][j][0], arr[i][j][1]);
        }
        printf("\n  +----+----+----+----+----+----+----+\n");
    }
}

void hangman(hang *a, int range, int player_serial_num)
{
    bool typed_letters[26] = {false};
    int letter_arrangement[26] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm'};
    for (int i = 0; i < 26; i++)
        letter_arrangement[i] -= 'a';
    printf(ANSI_COLOR_YELLOW);
    printf("============WELCOME TO HANGMAN GAME============\n\n");
    printf(ANSI_COLOR_RESET);
    printf("Correct guess will give you 5 points.\n");
    printf("Press any key to continue...");
    getch();

    time_t t1;
    srand((unsigned)time(&t1));
    int x = (rand()) % range;
    char *name_wrap = wrap(a[x].name);
    char name_copy[20];
    strcpy(name_copy, a[x].name);
    int wrong_guess = 0;
    int correct_guess = 0;

    while (wrong_guess != 5 && strcmp(a[x].name, name_wrap) != 0)
    {
        if (wrong_guess == 0)
        {
            system("cls");
            print_man(wrong_guess);
            print_hearts(5 - wrong_guess);
        }
        printf("\n%s      %s\n\n", name_wrap, a[x].desc);
        printavailableletters(typed_letters, letter_arrangement);
        char c = 'a';
        printf("Enter a character:");
        fflush(stdin);
        c = getch();
        while (typed_letters[c - 'a'])
        {
            printf("Enter valid character:");
            fflush(stdin);
            c = getch();
        }
        typed_letters[c - 'a'] = true;
        system("cls");
        int isguesses = 0;
        if (search_char_in_str(c, name_copy, strlen(a[x].name)) != -1)
        {
            do
            {
                int ind = search_char_in_str(c, name_copy, strlen(a[x].name));
                name_wrap[ind] = c;
                name_copy[ind] = '-';
                correct_guess++;
            } while (search_char_in_str(c, name_copy, strlen(a[x].name)) != -1);
            print_man(wrong_guess);
            print_hearts(5 - wrong_guess);
            if (strcmp(a[x].name, name_wrap) == 0)
            {
                isguesses = 1;
                printf(ANSI_COLOR_GREEN);
                printf("#Congratulations, you have guessed the word.\n");
                printf("#The word was %s.\n", a[x].name);
                printf("You have earned 5 points.\n");
                printf(ANSI_COLOR_RESET);
                player_list[player_serial_num].points += 5;
            }
        }
        else
        {
            wrong_guess++;
            printf(ANSI_COLOR_RED);
            print_man(wrong_guess);
            if (wrong_guess == 5)
            {
                printf("You are hanged.\n");
                printf(ANSI_COLOR_YELLOW);
                printf("The correct word was %s.\n", a[x].name);
                printf("You lost 2 points.\n");
                printf(ANSI_COLOR_RESET);
                player_list[player_serial_num].points -= 2;
                continue;
            }
            print_hearts(5 - wrong_guess);
            printf(ANSI_COLOR_RESET);
        }
    }
    printf(ANSI_COLOR_BLUE);
    printf("==========================\n");
    printf("    0 - exit this game\n");
    printf("    1 - play again\n");
    printf("==========================\n");
    printf(ANSI_COLOR_RESET);
    printf("Your response:");
    int response = 0;
    scanf("%d", &response);
    system("cls");
    if (response == 1)
        hangman(a, range, player_serial_num);
    return;
}

void tictactoe(int player_1_sno, int player_2_sno)
{
    int random_start = rand() % 2 + 1;
    system("cls");
    printf(ANSI_COLOR_YELLOW);
    printf("======Welcome to TicTacToe game======\n\n");
    printf(ANSI_COLOR_RESET);
    printf("Follow these coordinates to enter values:\n");
    printf(ANSI_COLOR_GREEN);
    printf("     7 | 8 | 9 \n    ---+---+---\n     4 | 5 | 6 \n    ---+---+---\n     1 | 2 | 3 \n");
    printf(ANSI_COLOR_RESET);
    char tic[10] = {32, 32, 32, 32, 32, 32, 32, 32, 32, 32};
    char player1[20], player2[20], player1_sign, player2_sign;
    printf(ANSI_COLOR_YELLOW);
    if (random_start == 1)
    {
        strcpy(player1, player_list[player_1_sno].name);
        strcpy(player2, player_list[player_2_sno].name);
    }
    else if (random_start == 2)
    {
        swap(&player_1_sno, &player_2_sno);
        strcpy(player2, player_list[player_2_sno].name);
        strcpy(player1, player_list[player_1_sno].name);
    }
    printf("%s choose your sign (X/O):", player1);
    fflush(stdin);
    player1_sign = getch();
    printf(ANSI_COLOR_RESET);
    if (player1_sign == 'O' || player1_sign == 'o')
    {
        player1_sign = 'O';
        player2_sign = 'X';
    }
    else
    {
        player1_sign = 'X';
        player2_sign = 'O';
    }
    int outcome = 0;
    int position_number = 0;
    for (int i = 1; i <= 9; i++)
    {
        system("cls");
        printf(ANSI_COLOR_GREEN);
        printf("Follow these references and avoid filling filled boxes:\n");
        printf("     7 | 8 | 9 \n    ---+---+---\n     4 | 5 | 6 \n    ---+---+---\n     1 | 2 | 3 \n");
        printf(ANSI_COLOR_RESET);
        printf("Game Board condition:\n");
        printbox(tic);
        if (i % 2 == 1)
        {
            printf("%s's (%c) turn, enter the box number:", player1, player1_sign);
            position_number = getint();
            printf("\n");
            while (true)
            {
                if (tic[position_number] == ' ')
                {
                    tic[position_number] = player1_sign;
                    break;
                }
                else
                {
                    printf("Enter valid move.\n");
                    printf("%s's (%c) turn, enter the box number:", player1, player1_sign);
                    position_number = getint();
                    printf("\n");
                }
            }
            printbox(tic);
        }
        else
        {
            printf("%s's (%c) turn, enter the box number:", player2, player2_sign);
            position_number = getint();
            printf("\n");
            while (true)
            {
                if (tic[position_number] == ' ')
                {
                    tic[position_number] = player2_sign;
                    break;
                }
                else
                {
                    printf("Enter valid move.\n");
                    printf("%s's (%c) turn, enter the box number:", player2, player2_sign);
                    position_number = getint();
                    printf("\n");
                }
            }
            printbox(tic);
        }
        char res = tick(tic);
        if (res == player1_sign)
        {
            outcome = 1;
            printf(ANSI_COLOR_GREEN);
            printf("Congratulations, %s won.\n", player1);
            player_list[player_1_sno].points += 5;
            printf(ANSI_COLOR_RESET);
            break;
        }
        else if (res == player2_sign)
        {
            outcome = 1;
            printf(ANSI_COLOR_GREEN);
            printf("Congratulations, %s won.\n", player2);
            player_list[player_2_sno].points += 5;
            printf(ANSI_COLOR_RESET);
            break;
        }
    }
    if (outcome == 0)
    {
        printf(ANSI_COLOR_BLUE);
        printf("Unfortunately, it's a DRAW.\n");
        printf(ANSI_COLOR_RESET);
    }
    printf(ANSI_COLOR_YELLOW);
    printf("==========================\n");
    printf("    0 - exit this game\n");
    printf("    1 - play again\n");
    printf("==========================\n");
    printf(ANSI_COLOR_RESET);
    printf("Your response:");
    int response = 0;
    scanf("%d", &response);
    if (response == 1)
        tictactoe(player_1_sno, player_2_sno);
    return;
}

void guessthenumber(int player_serial_no)
{
    int x;
    time_t t1;
    srand((unsigned)time(&t1));
    x = rand() % 1000 + 1;
    int number_of_guesses = 0;
    printf("General Instructions:\n");
    printf("    The number lies ranges between 1 and 1000.\n");
    printf("    You give a number and system tells whether input number is higher/lower than the actual number.\n");
    while (true)
    {
        int y = -1;
        printf("Guess a number:");
        scanf("%d", &y);
        number_of_guesses++;
        if (y == -1)
        {
            printf("Oops, the number was: %d.\n", x);
            break;
        }
        else if (y > x)
            printf("Guess lower.\n");
        else if (y < x)
            printf("Guess higher.\n");
        else
        {
            printf(ANSI_COLOR_GREEN);
            printf("Congratulations, you have guessed the number in %d guesses which is: %d.\n", number_of_guesses, x);
            if (number_of_guesses < 10)
            {
                printf("You earned 5 points.\n");
                player_list[player_serial_no].points += 5;
            }
            else if (number_of_guesses < 15)
            {
                printf("You earned 4 points.\n");
                player_list[player_serial_no].points += 4;
            }
            else
            {
                printf("You earned 3 points.\n");
                player_list[player_serial_no].points += 3;
            }
            printf(ANSI_COLOR_RESET);
            break;
        }
    }
    printf("==========================\n");
    printf("    0 - exit this game\n");
    printf("    1 - play again\n");
    printf("==========================\n");
    printf("Your response:");
    int response = 0;
    scanf("%d", &response);
    system("cls");
    if (response == 1)
        guessthenumber(player_serial_no);
    return;
}

void findthemine(int player_serial_no)
{
    char arr[7][7][2];
    time_t t1;
    srand((unsigned)time(&t1));
    printf("Note: 1. The system gives you the distance (horizontal + vertical) of the mine from that coordinate.\n");
    printf("      2. You have 4 guesses to find the mine hidden somewhere.\n");
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            arr[i][j][0] = ' ';
            arr[i][j][1] = ' ';
        }
    }
    int xa, ya;
    int guess = 0;
    ya = rand() % 7;
    xa = rand() % 7;
    int count = 0;
    while (true)
    {
        guess++;
        system("cls");
        print_mine(arr);
        int a, b;
        printf("Enter X and Y values (x y) of box to check:");
        scanf("%d", &a);
        scanf("%d", &b);
        a--;
        b--;
        int distance = abs(a - xa) + abs(b - ya);
        if (distance == 0)
        {
            system("cls");
            arr[xa][ya][0] = '*';
            arr[xa][ya][1] = '*';
            print_mine(arr);
            printf(ANSI_COLOR_GREEN);
            printf("Congratulations, you have successfully found the mine and saved the city.\n");
            printf("You earned 5 points.\n");
            printf(ANSI_COLOR_RESET);
            player_list[player_serial_no].points += 5;
            break;
        }
        else
        {
            arr[a][b][0] = distance / 10 + '0';
            arr[a][b][1] = distance % 10 + '0';
            print_mine(arr);
        }
        if (guess == 4)
        {
            system("cls");
            printf(ANSI_COLOR_RED);
            printf("You couldn't find the mine.\n");
            printf("You lost 2 points.\n");
            printf(ANSI_COLOR_RESET);
            player_list[player_serial_no].points -= 2;
            break;
        }
    }
    printf(ANSI_COLOR_BLUE);
    printf("==========================\n");
    printf("    0 - exit this game\n");
    printf("    1 - play again\n");
    printf("==========================\n");
    printf(ANSI_COLOR_RESET);
    printf("Your response:");
    int response = 0;
    scanf("%d", &response);
    system("cls");
    if (response == 1)
        findthemine(player_serial_no);
    return;
}

void gamingzone()
{
    system("cls");
    printf(ANSI_COLOR_YELLOW);
    printf("===========================================================================\n");
    printf("                     WELCOME TO GROUP 24 GAMING ZONE\n");
    printf("===========================================================================\n");
    printf("Please follow the instructions carefully to have a smooth gaming experience.\n");
    printf(ANSI_COLOR_RESET);
    int game = 1;
    while (game != 0)
    {
        system("cls");
        printf(ANSI_COLOR_BLUE);
        printf("=======================================\n");
        printf("Choose a game to play \n");
        printf("    1 - Hangman Game \n");
        printf("    2 - TicTacToe\n");
        printf("    3 - Guess the number\n");
        printf("    4 - Find the mine.\n");
        printf("=======================================\n");
        printf(ANSI_COLOR_RESET);
        printf("Your response:");
        scanf("%d", &game);
        if (game == 1)
        {
            displayAllplayers(player_list);
            printf("If player ID not available, generate new by entering a new ID.\n");
            int player_id = 0;
            printf("Enter player id:");
            scanf("%d", &player_id);
            int player_ser_no = fetch_player_serial_no(player_id);
            if (player_ser_no == -1)
            {
                printf("Player not found.\n");
                printf("Generating new id.\n");
                struct player newplayer;
                newplayer.id = player_id;
                printf("Enter player name:");
                scanf("\n%50[^\n]", newplayer.name);
                printf("Enter player age:");
                scanf("%d", &newplayer.age);
                newplayer.points = 0;
                player_list[num_players++] = newplayer;
                printf("Player added successfully!\n");
                player_ser_no = num_players - 1;
            }
            printf("Press any key to continue...");
            getch();
            hang *wordbank;
            wordbank = (hang *)malloc(50 * sizeof(hang));
            FILE *f_input;
            f_input = fopen("hangman_database.txt", "r");
            int count = 0;
            char naam[31], descrip[81];
            do
            {
                fscanf(f_input, "%30[^,], %80[^\n]\n", wordbank[count].name, wordbank[count].desc);
                count++;
            } while (!feof(f_input));
            fclose(f_input);
            system("cls");
            hangman(wordbank, count, player_ser_no);
        }
        if (game == 2)
        {
            system("cls");
            displayAllplayers(player_list);
            printf("If player ID not available, generate new by entering a new ID.\n");
            int player_1_id = 0;
            int player_2_id = 0;
            printf("Enter player 1 ID:");
            scanf("%d", &player_1_id);
            int player_1_ser_no = fetch_player_serial_no(player_1_id);
            if (player_1_ser_no == -1)
            {
                printf("Player not found.\n");
                printf("Generating new id.\n");
                struct player newplayer;
                newplayer.id = player_1_id;
                printf("Enter player name:");
                scanf("\n%50[^\n]", newplayer.name);
                printf("Enter player age:");
                scanf("%d", &newplayer.age);
                newplayer.points = 0;
                player_list[num_players++] = newplayer;
                printf("Player added successfully!\n");
                player_1_ser_no = num_players - 1;
            }
            printf("Enter player 2 ID:");
            scanf("%d", &player_2_id);
            int player_2_ser_no = fetch_player_serial_no(player_2_id);
            if (player_2_ser_no == -1)
            {
                printf("Player not found.\n");
                printf("Generating new id.\n");
                struct player newplayer;
                newplayer.id = player_2_id;
                printf("Enter player 2 name:");
                scanf("\n%50[^\n]", newplayer.name);
                printf("Enter player 2 age:");
                scanf("%d", &newplayer.age);
                newplayer.points = 0;
                player_list[num_players++] = newplayer;
                printf("Player added successfully!\n");
                player_2_ser_no = num_players - 1;
            }
            printf("Press any key to continue...");
            getch();
            tictactoe(player_1_ser_no, player_2_ser_no);
        }
        if (game == 3)
        {
            displayAllplayers(player_list);
            printf("If player ID not available, generate new by entering a new ID.\n");
            int player_id = 0;
            printf("Enter player id:");
            scanf("%d", &player_id);
            int player_ser_no = fetch_player_serial_no(player_id);
            if (player_ser_no == -1)
            {
                printf("Player not found.\n");
                printf("Generating new id.\n");
                struct player newplayer;
                newplayer.id = player_id;
                printf("Enter player name:");
                scanf("\n%50[^\n]", newplayer.name);
                printf("Enter player age:");
                scanf("%d", &newplayer.age);
                newplayer.points = 0;
                player_list[num_players++] = newplayer;
                printf("Player added successfully!\n");
                player_ser_no = num_players - 1;
            }
            printf("Press any key to continue...");
            getch();
            system("cls");
            guessthenumber(player_ser_no);
        }
        if (game == 4)
        {
            displayAllplayers(player_list);
            printf("If player ID not available, generate new by entering a new ID.\n");
            int player_id = 0;
            printf("Enter player id:");
            scanf("%d", &player_id);
            int player_ser_no = fetch_player_serial_no(player_id);
            if (player_ser_no == -1)
            {
                printf("Player not found.\n");
                printf("Generating new id.\n");
                struct player newplayer;
                newplayer.id = player_id;
                printf("Enter player name:");
                scanf("\n%50[^\n]", newplayer.name);
                printf("Enter player age:");
                scanf("%d", &newplayer.age);
                newplayer.points = 0;
                player_list[num_players++] = newplayer;
                printf("Player added successfully!\n");
                player_ser_no = num_players - 1;
            }
            printf("Press any key to continue...");
            getch();
            system("cls");
            findthemine(player_ser_no);
        }
        printf(ANSI_COLOR_BLUE);
        printf("=======================================\n");
        printf("    0 - exit GAMING ZONE \n");
        printf("    1 - play other games \n");
        printf("=======================================\n");
        printf(ANSI_COLOR_RESET);
        printf("Your response:");
        game = getint();
    }
    if (game == 0)
    {
        printf(ANSI_COLOR_GREEN);
        printf("\nThankyou for joining us in this amazing gaming journey.\n");
        printf(ANSI_COLOR_RESET);
        delay(2000);
    }
}

int main()
{
    system("cls");
    printf(ANSI_COLOR_CYAN);
    printf("%c %c WELCOME TO GROUP 24 PROJECT %c %c \n", 3, 3, 3, 3);
    printf(ANSI_COLOR_RESET);
    FILE *f_player;
    f_player = fopen("player_database.txt", "r");
    int count = 0;
    do
    {
        fscanf(f_player, "%d,", &player_list[count].id);
        fscanf(f_player, " %50[^,],", player_list[count].name);
        fscanf(f_player, "%d,", &player_list[count].age);
        fscanf(f_player, "%d,", &player_list[count].points);
        count++;
    } while (!feof(f_player));
    fclose(f_player);
    num_players = count;
    int choice = 0;
    while (true)
    {
        printf(ANSI_COLOR_GREEN);
        printf("%c-----------------------------------------------------%c\n", 4, 4);
        printf("|    GameSphere: Where players connect and compete    |\n");
        printf("%c-----------------------------------------------------%c\n", 4, 4);
        printf(ANSI_COLOR_MAGENTA);
        printf("    1. Add a new player\n");
        printf("    2. Edit player information\n");
        printf("    3. Delete a player\n");
        printf("    4. Search for a player\n");
        printf("    5. Display all player records\n");
        printf("    6. Leaderboards / Generate reports\n");
        printf("    7. Enter Game Zone\n");
        printf("    8. Exit\n\n");
        printf(ANSI_COLOR_RESET);
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addplayer();
            break;
        case 2:
            editplayer();
            break;
        case 3:
            deleteplayer();
            break;
        case 4:
            searchplayer();
            break;
        case 5:
            displayAllplayers(player_list);
            break;
        case 6:
            generateReports();
            break;
        case 7:
            gamingzone();
            break;
        case 8:
            // reflect all changes back intno the database in ascending order of ID.
            for (int i = 0; i < num_players; i++)
            {
                for (int j = 0; j < (num_players - i - 1); j++)
                {
                    if (player_list[j].id > player_list[j + 1].id)
                    {
                        struct player temp = player_list[j];
                        player_list[j] = player_list[j + 1];
                        player_list[j + 1] = temp;
                    }
                }
            }
            printf("Exiting program. Goodbye!\n");
            FILE *f_output;
            f_output = fopen("player_database.txt", "w");
            for (int i = 0; i < num_players; i++)
            {
                fprintf(f_output, "%d, %s, %d, %d", player_list[i].id, player_list[i].name, player_list[i].age, player_list[i].points);
                if (i != num_players - 1)
                    fprintf(f_output, ",\n");
            }
            fclose(f_output);
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
        printf("Press any key to continue...");
        getch();
        system("cls");
        printf("\n");
    }
    return 0;
}