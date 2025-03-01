#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h> // For generating random ticket numbers

#define ROWS 10
#define COLS 4
#define MAX_SEATS 10

// ANSI escape codes for colors
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

void clearScreen()
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux/macOS
#endif
}

void displaySeats(char seats[ROWS][COLS])
{
    printf("\nAeroplane Seat Layout:\n");
    printf("   --------------------------\n");
    for (int i = 0; i < ROWS; i++)
    {
        printf("%2d | ", i + 1);
        for (int j = 0; j < COLS; j++)
        {
            if (j == 2)
            {
                printf("  ");
            }
            if (seats[i][j] == 'X')
            {
                printf(RED "%c " RESET, seats[i][j]);
            }
            else if (seats[i][j] == 'O')
            {
                printf(GREEN "%c " RESET, seats[i][j]);
            }
            else
            {
                printf("%c ", seats[i][j]);
            }
        }
        printf("|\n");
    }
    printf("   --------------------------\n");
    printf("     A B   C D\n");
}

void saveSeatsToFile(char seats[ROWS][COLS])
{
    FILE *file = fopen("seats.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            fprintf(file, "%c", seats[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void loadSeatsFromFile(char seats[ROWS][COLS])
{
    FILE *file = fopen("seats.txt", "r");
    if (file == NULL)
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                seats[i][j] = 'O';
            }
        }
        return;
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            fscanf(file, " %c", &seats[i][j]);
        }
    }

    fclose(file);
}

int generateTicketNumber()
{
    srand(time(0));                  // Seed the random number generator
    return rand() % 900000 + 100000; // Generate a 6-digit ticket number
}

void displayTicket(int ticketNumber, char seats[ROWS][COLS], char *seatList)
{
    clearScreen();
    printf("\n\n=== Your Ticket ===\n");
    printf("Ticket Number: %d\n", ticketNumber);
    printf("Flight Number: AA123\n");
    printf("Departure: New York (JFK)\n");
    printf("Arrival: Los Angeles (LAX)\n");
    printf("Date: 2023-12-25\n");
    printf("Time: 10:00 AM\n");
    printf("Seats Booked: %s\n", seatList);
    printf("\nThank you for choosing our airline!\n");
}

int askToReturnToMenu()
{
    char choice;
    printf("\nDo you want to return to the menu? (y/n): ");
    scanf(" %c", &choice);
    return (tolower(choice) == 'y');
}

void bookSeats(char seats[ROWS][COLS])
{
    char input[100];
    printf("Enter the seats you want to book (e.g., 1A 2B 3C): ");
    getchar(); // Clear the input buffer
    fgets(input, sizeof(input), stdin);

    char *token = strtok(input, " ");
    int booked = 0;
    char seatList[100] = ""; // To store the list of booked seats

    while (token != NULL && booked < MAX_SEATS)
    {
        int row;
        char colChar;
        if (sscanf(token, "%d%c", &row, &colChar) == 2)
        {
            // Convert column character to index (A=0, B=1, C=2, D=3)
            int col = toupper(colChar) - 'A';

            if (row < 1 || row > ROWS || col < 0 || col >= COLS)
            {
                printf("Invalid seat selection: %s. Skipping.\n", token);
            }
            else if (seats[row - 1][col] == 'X')
            {
                printf("Seat %s is already booked. Skipping.\n", token);
            }
            else
            {
                seats[row - 1][col] = 'X';
                printf("Seat %s booked successfully!\n", token);
                strcat(seatList, token);
                strcat(seatList, " ");
                booked++;
            }
        }
        else
        {
            printf("Invalid input format: %s. Skipping.\n", token);
        }
        token = strtok(NULL, " ");
    }

    if (booked > 0)
    {
        saveSeatsToFile(seats);
        int ticketNumber = generateTicketNumber();
        displayTicket(ticketNumber, seats, seatList);

        if (askToReturnToMenu())
        {
            clearScreen();
        }
        else
        {
            printf("Exiting the program. Thank you!\n");
            exit(0);
        }
    }
    else
    {
        printf("No seats were booked.\n");
    }
}

int main()
{
    char seats[ROWS][COLS];

    loadSeatsFromFile(seats);

    while (1)
    {
        printf("\t               __\n");
        printf("\t  __________/ F\n");
        printf("\t c'____---__=_/ \n");
        printf("\t____o_____o________");
        printf("\n\nAeroplane Ticket Booking System\n");
        printf("-------------------------------\n");
        printf("1. View Seat Layout\n");
        printf("2. Book Multiple Seats\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            clearScreen();
            displaySeats(seats);
            if (!askToReturnToMenu())
            {
                printf("Exiting the program. Thank you!\n");
                exit(0);
            }
            clearScreen();
            break;

        case 2:
            clearScreen();
            displaySeats(seats);
            bookSeats(seats);
            break;

        case 3:
            printf("Exiting the program. Thank you!\n");
            exit(0);

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}