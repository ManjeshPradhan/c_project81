#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define ROWS 10
#define COLS 4
#define MAX_SEATS 10

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"
#define HGRN "\e[0;92m"
#define URED "\e[4;31m"
#define WHITE "\e[1;37m"
#define BLUE "\e[0;34m"
#define BRED "\e[1;31m"
#define CYN "\e[0;36m"
#define BBLK "\e[1;30m"

char useremail[50];
char password[50];

int emailcheck();
int passwordcheck();
void displayBookingMenu(char seats[ROWS][COLS], int from, int to, int hour, int minute);
void fromto(char seats[ROWS][COLS], int *from, int *to, int *hour, int *minute);
void loadSeatsFromFile(char seats[ROWS][COLS]);
void saveSeatsToFile(char seats[ROWS][COLS]);
int processPayment(double amount);

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void typewriterEffect(const char *text, int delay)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%c", text[i]);
        fflush(stdout);
        Sleep(delay);
    }
    printf("\n");
}

void signup()
{
    int len;

    while (getchar() != '\n')
        ;
    clearScreen();
check1:
    printf(BLUE "Enter your email: " WHITE);
    fgets(useremail, sizeof(useremail), stdin);
    useremail[strcspn(useremail, "\n")] = 0;

    if (emailcheck() == 0)
    {
        goto check1;
    }
    else
    {
    check2:
        printf(BLUE "Enter the password:" RED);
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = 0;

        if (passwordcheck() == 0)
        {
            goto check2;
        }
        else
        {
            struct userdetails
            {
                char name[50];
                char address[50];
                char phone[50];
                int age;
                char bankaccount[50];
                char accountpassword[50];
            };

            struct userdetails user;

            printf(BLUE "Enter your Name: " WHITE);
            fgets(user.name, sizeof(user.name), stdin);
            user.name[strcspn(user.name, "\n")] = 0;

            printf(BLUE "Enter your Address: " WHITE);
            fgets(user.address, sizeof(user.address), stdin);
            user.address[strcspn(user.address, "\n")] = 0;

            printf(BLUE "Enter your Phone: " WHITE);
            fgets(user.phone, sizeof(user.phone), stdin);
            user.phone[strcspn(user.phone, "\n")] = 0;

            printf(BLUE "Enter your Age: " WHITE);
            scanf("%d", &user.age);
            while (getchar() != '\n')
                ;

            printf(BLUE "Enter your Bank account number: " WHITE);
            fgets(user.bankaccount, sizeof(user.bankaccount), stdin);
            user.bankaccount[strcspn(user.bankaccount, "\n")] = 0;

            printf(BLUE "Enter your Account password: " WHITE);
            fgets(user.accountpassword, sizeof(user.accountpassword), stdin);
            user.accountpassword[strcspn(user.accountpassword, "\n")] = 0;

            FILE *fp;
            fp = fopen("database.txt", "a");
            if (fp == NULL)
            {
                system("cls");
                printf("File not found\n");
                exit(1);
            }
            fprintf(fp, "Passenger Login Details\n");
            fprintf(fp, "%s  %s\n\n", useremail, password);

            fprintf(fp, "Passenger Other Details\n");
            fprintf(fp, "Name: %s\nAddress: %s\nPhone: %s\nAge: %d\n\n", user.name, user.address, user.phone, user.age);

            fprintf(fp, "Passenger Bank Details\n");
            fprintf(fp, "%s  %s\n", user.bankaccount, user.accountpassword);
            fprintf(fp, "-------------------------------------------------------------------------\n");
            fclose(fp);
            clearScreen();
            const char *message = "Sign UP Successful....";
            int delayInMillis = 100;
            typewriterEffect(message, delayInMillis);
        }
    }
}

int emailcheck()
{
    int len;
    len = strlen(useremail);

    if (len < 12)
    {
        system("cls");
        printf(BRED "Email is too short. Minimum length 12\n" RESET);
        return 0;
    }

    int i = 0;
    while (useremail[i] != '\0')
    {
        if (useremail[i] == ' ')
        {
            system("cls");
            printf(BRED "Invalid email. Space is not allowed\n");
            return 0;
        }
        i++;
    }

    char tempchar[] = "moc.liamg@";

    int j = 0;
    while (tempchar[j] != '\0')
    {
        if (tempchar[j] != useremail[len - 1 - j])
        {
            system("cls");
            printf(BRED "Invalid email. Email must end with @gmail.com\n" RESET);
            return 0;
        }
        j++;
    }

    FILE *fp;
    fp = fopen("database.txt", "r");
    if (fp == NULL)
    {
        system("cls");
        printf(BRED "File not found\n" RESET);
        exit(1);
    }
    char tempemail[50];
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strcmp(useremail, tempemail) == 0)
        {
            system("cls");
            printf(BRED "Email already exists. Please Enter a unique email\n" RESET);
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);
    return 1;
}

int passwordcheck()
{
    int len;
    len = strlen(password);

    if (len < 8)
    {
        system("cls");
        printf("Password is too short. Minimum length 8\n");
        return 0;
    }

    int i = 0;
    while (password[i] != '\0')
    {
        if (password[i] == ' ')
        {
            system("cls");
            printf(BRED "Invalid password. Space is not allowed\n" RESET);
            return 0;
        }
        i++;
    }

    return 1;
}

void login(char seats[ROWS][COLS])
{
    char tempemail[50];
    char temppassword[50];
    char line[256];

    while (getchar() != '\n')
        ; // Clear the input buffer
    printf(BLUE "Enter your email: " WHITE);
    fgets(useremail, sizeof(useremail), stdin);
    useremail[strcspn(useremail, "\n")] = 0;

    printf(BLUE "Enter your password: " BRED);
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    FILE *fp;
    fp = fopen("database.txt", "r");
    if (fp == NULL)
    {
        system("cls");
        printf("File not found\n");
        exit(1);
    }

    int found = 0;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strstr(line, "Passenger Login Details") != NULL)
        {
            if (fgets(line, sizeof(line), fp))
            {
                sscanf(line, "%s %s", tempemail, temppassword);
                if (strcmp(useremail, tempemail) == 0 && strcmp(password, temppassword) == 0)
                {
                    found = 1;
                    break;
                }
            }
        }
    }

    fclose(fp);

    if (found == 1)
    {
        system("cls");
        const char *message = "Login Successful....";
        int delayInMillis = 100;
        typewriterEffect(message, delayInMillis);
        int from, to, hour, minute;
        fromto(seats, &from, &to, &hour, &minute);
    }
    else
    {
        system("cls");
        printf(BRED "Invalid email or password. Please try again\n" RESET);
    }
}

void displaySeats(char seats[ROWS][COLS])
{
    loadSeatsFromFile(seats);

    printf(HGRN "\nAeroplane Seat Layout:\n" RESET);
    printf("   -------------------\n");
    printf("     A B   C D\n");
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
    printf("   -------------------\n");
}

void saveSeatsToFile(char seats[ROWS][COLS])
{
    FILE *file = fopen("seats.txt", "w");
    if (file == NULL)
    {
        printf(BRED "Error opening file for writing.\n" RESET);
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
    srand(time(0));
    return rand() % 900000 + 100000;
}

void displayTicket(int ticketNumber, char *seatList, int from, int to, int hour, int minute)
{
    clearScreen();
    char departure[100];
    char arrival[100];

    if (from == 1)
    {
        strcpy(departure, "Tribhuvan International Airport (TIA)");
    }
    else if (from == 2)
    {
        strcpy(departure, "Pokhara International Airport (PIA)");
    }
    else if (from == 3)
    {
        strcpy(departure, "Gautam Buddha International Airport (GBIA)");
    }
    else if (from == 4)
    {
        strcpy(departure, "Janakpur Airport (JNA)");
    }
    else if (from == 5)
    {
        strcpy(departure, "Biratnagar Airport (BIR)");
    }
    else if (from == 6)
    {
        strcpy(departure, "Nepalgunj Airport (KEP)");
    }
    else if (from == 7)
    {
        strcpy(departure, "Dhangadhi Airport (DHI)");
    }
    else if (from == 8)
    {
        strcpy(departure, "Simara Airport (SIF)");
    }
    else if (from == 9)
    {
        strcpy(departure, "Bharatpur Airport (BHR)");
    }
    else if (from == 10)
    {
        strcpy(departure, "Bhadrapur Airport (BDP)");
    }

    if (to == 1)
    {
        strcpy(arrival, "Tribhuvan International Airport (TIA)");
    }
    else if (to == 2)
    {
        strcpy(arrival, "Pokhara International Airport (PIA)");
    }
    else if (to == 3)
    {
        strcpy(arrival, "Gautam Buddha International Airport (GBIA)");
    }
    else if (to == 4)
    {
        strcpy(arrival, "Janakpur Airport (JNA)");
    }
    else if (to == 5)
    {
        strcpy(arrival, "Biratnagar Airport (BIR)");
    }
    else if (to == 6)
    {
        strcpy(arrival, "Nepalgunj Airport (KEP)");
    }
    else if (to == 7)
    {
        strcpy(arrival, "Dhangadhi Airport (DHI)");
    }
    else if (to == 8)
    {
        strcpy(arrival, "Simara Airport (SIF)");
    }
    else if (to == 9)
    {
        strcpy(arrival, "Bharatpur Airport (BHR)");
    }
    else if (to == 10)
    {
        strcpy(arrival, "Bhadrapur Airport (BDP)");
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char currentDate[20];
    snprintf(currentDate, sizeof(currentDate), "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    printf(BLUE "******************************************************************************************************************************************************************\n");
    printf("\t\t\t\t\t\t\t\t\t      ");
    printf(RED "Your Ticket" BLUE);
    printf("  \t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t\t\t            \t\t\t\t\t\t\t\t\t        \n");
    printf(BLUE "\t\t\t\t\t\t\t\t\t   Ticket Number:" WHITE);
    printf("%d\n", ticketNumber);
    printf(BLUE "\t\t\t\t\t\t\t\t\t   Flight Number: AA123\n");
    printf("\t\t\t\t\t\t\t\t\t   Departure: ");
    printf(WHITE "%s\n", departure);
    printf(BLUE "\t\t\t\t\t\t\t\t\t   Arrival: ");
    printf(WHITE "%s\n", arrival);
    printf(BLUE "\t\t\t\t\t\t\t\t\t   Time: ");
    printf(WHITE "%02d:%02d\n", hour, minute);
    printf(BLUE "\t\t\t\t\t\t\t\t\t   Date: ");
    printf(WHITE "%s\n", currentDate);
    printf(BLUE "\t\t\t\t\t\t\t\t\t   Seats Booked: ");
    printf(WHITE "%s\n", seatList);
    printf(BLUE "******************************************************************************************************************************************************************\n\n");
    printf(HGRN "\nThank you for choosing our airline!\n");
}

int askToReturnToMenu()
{
    char choice;
    printf(BLUE "Do you want to return to the menu? (y/n): " WHITE);
    scanf(" %c", &choice);
    return (tolower(choice) == 'y');
}

void bookSeats(char seats[ROWS][COLS], int from, int to, int hour, int minute)
{
    char input[100];
    char seatList[100] = "";
    displaySeats(seats);
    printf(BLUE "Enter the seats you want to book (e.g., 1A 2B 3C): " WHITE);
    getchar();
    fgets(input, sizeof(input), stdin);

    int booked = 0;
    double seatPrice = 1000.0;
    double totalAmount = 0.0;

    char *token = input;
    while (*token && booked < MAX_SEATS)
    {
        int row;
        char colChar;
        if (sscanf(token, "%d%c", &row, &colChar) == 2)
        {
            int col = toupper(colChar) - 'A';

            if (row < 1 || row > ROWS || col < 0 || col >= COLS)
            {
                printf(BRED "Invalid seat selection: %d%c. Please select another seat.\n", row, colChar);
                printf(RESET "");
            }
            else if (seats[row - 1][col] == 'X')
            {
                printf(BRED "Seat %d%c is already booked. Please select another seat.\n", row, colChar);
                printf(RESET "");
            }
            else
            {
                char seat[10];
                snprintf(seat, sizeof(seat), "%d%c", row, colChar);
                strcat(seatList, seat);
                strcat(seatList, " ");
                booked++;
                totalAmount += seatPrice;
                seats[row - 1][col] = 'X';
            }
            while (*token && *token != ' ')
                token++;
            while (*token && *token == ' ')
                token++;
        }
        else
        {
            printf(BRED "Invalid input format: %s. Skipping.\n", token);
            printf(RESET "");
            break;
        }
    }

    if (booked > 0)
    {
        printf(HGRN "Total amount to be paid: Rs.%.2f\n", totalAmount);
        printf("" RESET);
        if (processPayment(totalAmount))
        {
            printf(HGRN "Seats booked successfully!\n" WHITE);
            saveSeatsToFile(seats);
            int ticketNumber = generateTicketNumber();
            Sleep(5000);
            displayTicket(ticketNumber, seatList, from, to, hour, minute);
        }
        else
        {
            printf(BRED "Payment failed. Booking not confirmed.\n");
            printf(RESET "");
        }
    }
    else
    {
        printf(BRED "No seats were booked.\n");
        printf(RESET "");
    }

    if (askToReturnToMenu())
    {
        clearScreen();
    }
    else
    {
        clearScreen();
        printf(HGRN "Exiting the program. Thank you!\n" RESET);
        exit(0);
    }
}

int processPayment(double amount)
{
    char choice;
    printf("Do you want to use your default account for payment? (y/n): ");
    scanf(" %c", &choice);
    getchar();

    if (tolower(choice) == 'y')
    {
        char accountNumber[50];
        char accountPassword[50];

        FILE *fp = fopen("database.txt", "r");
        if (fp == NULL)
        {
            printf(BRED "File not found\n" RESET);
            return 0;
        }

        char line[256];
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            if (strstr(line, useremail) != NULL)
            {
                while (fgets(line, sizeof(line), fp) != NULL)
                {
                    if (strstr(line, "Passenger Bank Details") != NULL)
                    {
                        fgets(line, sizeof(line), fp);
                        sscanf(line, "%s %s", accountNumber, accountPassword);
                        break;
                    }
                }
                break;
            }
        }
        fclose(fp);

        printf(HGRN "Processing payment of Rs.%.2f using default account...\n", amount);
        printf("" RESET);
        Sleep(2000);

        clearScreen();
        printf(HGRN "Payment successful!\n");
        const char *message = "Loding Ticket....";
        int delayInMillis = 150;
        return 1;
    }
    else
    {
        char accountNumber[50];
        char accountPassword[50];
        char paymentMethod[20];

        printf(BLUE "Choose a payment method (e.g., esewa, khalti): " WHITE);
        fgets(paymentMethod, sizeof(paymentMethod), stdin);
        paymentMethod[strcspn(paymentMethod, "\n")] = 0;

        printf(BLUE "Enter your account number: " WHITE);
        fgets(accountNumber, sizeof(accountNumber), stdin);
        accountNumber[strcspn(accountNumber, "\n")] = 0;

        printf(BLUE "Enter your account password: " WHITE);
        fgets(accountPassword, sizeof(accountPassword), stdin);
        accountPassword[strcspn(accountPassword, "\n")] = 0;

        printf(BLUE "Processing payment of Rs.%.2f using %s...\n", amount, paymentMethod);
        printf(RESET "");
        Sleep(2000);

        printf(HGRN "Payment successful!\n" RESET);
        return 1;
    }
}

void displayMenu(char seats[ROWS][COLS])
{
    int choice_menu;

    do
    {
        printf("\n\n\n\n\n\n");
        printf(HGRN "***************************************************************************************************************************************************************\n");
        printf("||\t\t\t\t\t\t\t\t\t            \t\t\t\t\t\t\t\t\t     ||\n");
        printf("||\t\t\t\t\t\t\t\t\t      ");
        printf(URED "Menu" HGRN);
        printf("  \t\t\t\t\t\t\t\t\t     ||\n");
        printf("||\t\t\t\t\t\t\t\t\t            \t\t\t\t\t\t\t\t\t     ||\n");
        printf("||\t\t\t\t\t\t\t\t\t            \t\t\t\t\t\t\t\t\t     ||\n");
        printf("||\t\t\t\t\t\t\t\t\t            \t\t\t\t\t\t\t\t\t     ||\n");
        printf("||\t\t\t\t\t\t\t\t\t            \t\t\t\t\t\t\t\t\t     ||\n");
        printf("||\t\t\t\t\t\t\t\t\t   1. Signup\t\t\t\t\t\t\t\t\t     ||\n");
        printf("||\t\t\t\t\t\t\t\t\t   2. Login \t\t\t\t\t\t\t\t\t     ||\n");
        printf("||\t\t\t\t\t\t\t\t\t   3. Exit  \t\t\t\t\t\t\t\t\t     ||\n");
        printf("||\t\t\t\t\t\t\t\t\t            \t\t\t\t\t\t\t\t\t     ||\n");
        printf("||\t\t\t\t\t\t\t\t\t            \t\t\t\t\t\t\t\t\t     ||\n");
        printf("||\t\t\t\t\t\t\t\t\t            \t\t\t\t\t\t\t\t\t     ||\n");
        printf("||\t\t\t\t\t\t\t\t\t            \t\t\t\t\t\t\t\t\t     ||\n");
        printf("||\t\t\t\t\t\t\t\t\t            \t\t\t\t\t\t\t\t\t     ||\n");
        printf("***************************************************************************************************************************************************************\n\n" RESET);

        printf(BLUE "Enter your choice: " WHITE);
        scanf("%d", &choice_menu);
        while (getchar() != '\n')
            ;

        switch (choice_menu)
        {
        case 1:
            signup();
            break;

        case 2:
            login(seats);
            break;

        case 3:
            printf("Exit\n");
            break;

        default:
            printf(BRED "Invalid choice\n" RESET);
            break;
        }
    } while (choice_menu != 3);
}

void displayBookingMenu(char seats[ROWS][COLS], int from, int to, int hour, int minute)
{
    int exitMenu = 0;
    while (!exitMenu)
    {
        printf(WHITE "\t               __\n");
        printf("\t   __________/ F\n");
        printf("\t c");
        printf(CYN "'---");
        printf(WHITE "__=_/ \n");
        printf(BBLK "\t___o_____o________");
        printf(HGRN "\n\nAeroplane Ticket Booking System\n");
        printf("-------------------------------\n");
        printf("1. View Seat Layout\n");
        printf("2. Book Seats\n");
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
                printf(BRED "Exiting the program. Thank you!\n");
                exit(0);
            }
            clearScreen();
            break;

        case 2:
            clearScreen();
            bookSeats(seats, from, to, hour, minute);
            break;

        case 3:
            printf(BRED "Exiting the program. Thank you!\n");
            exitMenu = 1;
            break;

        default:
            printf(BRED "Invalid choice. Please try again.\n" RESET);
        }
    }
}

void fromto(char seats[ROWS][COLS], int *from, int *to, int *hour, int *minute)
{
check3:
    clearScreen();
    printf(CYN "Here is the list of airports:\n");
    printf("1. Tribhuvan International Airport (TIA), Kathmandu\n");
    printf("2. Pokhara International Airport (PIA), Pokhara\n");
    printf("3. Gautam Buddha International Airport (GBIA), Bhairahawa\n");
    printf("4. Janakpur Airport (JNA), Janakpur\n");
    printf("5. Biratnagar Airport (BIR), Biratnagar\n");
    printf("6. Nepalgunj Airport (KEP), Nepalgunj\n");
    printf("7. Dhangadhi Airport (DHI), Dhangadhi\n");
    printf("8. Simara Airport (SIF), Simara\n");
    printf("9. Bharatpur Airport (BHR), Bharatpur\n");
    printf("10. Bhadrapur Airport (BDP), Jhapa\n" RESET);

    printf(BLUE "\nEnter your Departure airport:\n" WHITE);
    scanf("%d", from);
    printf(BLUE "Enter your Arrival airport:\n" WHITE);
    scanf("%d", to);
    printf(BLUE "Enter your time of departure in 00:00 format (24Hr cycle):\n" WHITE);
    scanf("%d:%d", hour, minute);
    char departure[100], arrival[100];

    char *airports[] = {
        "Invalid",
        "Tribhuvan International Airport (TIA), Kathmandu",
        "Pokhara International Airport (PIA), Pokhara",
        "Gautam Buddha International Airport (GBIA), Bhairahawa",
        "Janakpur Airport (JNA), Janakpur",
        "Biratnagar Airport (BIR), Biratnagar",
        "Nepalgunj Airport (KEP), Nepalgunj",
        "Dhangadhi Airport (DHI), Dhangadhi",
        "Simara Airport (SIF), Simara",
        "Bharatpur Airport (BHR), Bharatpur",
        "Bhadrapur Airport (BDP), Jhapa"};

    if (*from >= 1 && *from <= 10)
    {
        strcpy(departure, airports[*from]);
    }
    else
    {
        strcpy(departure, "Unknown Airport");
    }

    if (*to >= 1 && *to <= 10)
    {
        strcpy(arrival, airports[*to]);
    }
    else
    {
        strcpy(arrival, "Unknown Airport");
    }

    if (*from == 1 || *from == 2)
    {
        clearScreen();
        printf("We found a flight from %s to %s at %02d:%02d\n", departure, arrival, *hour, *minute);
        printf("Redirecting to Flight Booking Menu");
        const char *message = "........";
        int delayInMillis = 500;
        typewriterEffect(message, delayInMillis);
        displayBookingMenu(seats, *from, *to, *hour, *minute);
    }

    else
    {
        if (*to == 1 || *to == 2)
        {
            clearScreen();
            printf("We found a flight from %s to %s at %02d:%02d\n", departure, arrival, *hour, *minute);
            printf("Redirecting to Flight Booking Menu");
            const char *message = "........";
            int delayInMillis = 500;
            typewriterEffect(message, delayInMillis);
            displayBookingMenu(seats, *from, *to, *hour, *minute);
        }
        else
        {
            clearScreen();
            printf(BRED "No flights available\n");
            printf(BLUE "Please try alternative routes\n");
            printf("Available routes are:\n");
            printf("\n%s to Tribhuvan International Airport (TIA) and Tribhuvan International Airport (TIA) to %s\n", departure, arrival);
            printf("\n\n");
            char choice;
            printf("Do you want to try again? (press y/n) ");
            scanf(" %c", &choice);
            if (tolower(choice) == 'y')
            {
                goto check3;
            }
            else
            {
                clearScreen();
                printf(HGRN "Exiting the program. Thank you!\n" RESET);
                exit(0);
            }

            fromto(seats, from, to, hour, minute);
        }
    }
}

int main()
{
    clearScreen();
    char seats[ROWS][COLS];
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            seats[i][j] = 'O';
        }
    }
    displayMenu(seats);

    return 0;
}