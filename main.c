#include <stdio.h>
#include <string.h>
#define MAX_USERS 20
#define ADMIN_PASSWORD "ADMIN123"

typedef struct
 {
    char username[20];
    char password[20];
    float balance;
    float loan;
}
User;
User users[MAX_USERS];
int num_users = 0;
void create_user();
void login();
void request_loan(User* user);
void approve_loan(User* user);
void deposit(User* user);
void withdraw(User* user);

int main()
{
    int choice;
    char admin_password[20];
    printf("\n                    Welcome to ClintoneBank. \n          Enter administrator password(ADMIN123) : ");
    scanf("%s", admin_password);
    if (strcmp(admin_password, ADMIN_PASSWORD) == 0)
        {
        while (1)
         {
            printf("\nWelcome, Administrator.\n");
            printf("1. Create user\n");
            printf("2. View user account\n");
            printf("3. Approve loan\n");
            printf("4. Log out\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
            case 1:
                create_user();
                break;
            case 2:
                login();
                break;
            case 3:
                approve_loan(NULL);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    }
    else
     {
        printf("Incorrect password. Exiting program.\n");
        return 0;
     }
}

void create_user()
 {
    if (num_users == MAX_USERS)
    {
        printf("Maximum number of users reached.\n");
        return;
    }
    printf("Enter a username: ");
    scanf("%s", users[num_users].username);
    printf("Enter a password: ");
    scanf("%s", users[num_users].password);
    users[num_users].balance = 0;
    users[num_users].loan = 0;
    num_users++;
    printf("User account created successfully.\n");
}

void login()
 {
    char username[20], password[20];
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);
    int i;
    for (i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0) {
            User* user = &users[i];
            int choice;
            while (1)
                {
                printf("\nWelcome, %s.\n", user->username);
                printf("1. View account balance\n");
                printf("2. Deposit\n");
                printf("3. Request loan\n");
                printf("4. Withdraw\n");
                printf("5. Log out\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                switch (choice)
                 {
                case 1:
                    printf("Your balance is %.2f.\n", user->balance);
                    break;
                case 2:
                    deposit(user);
                    break;
                case 3:
                    request_loan(user);
                    break;
                case 4:
                    withdraw(user);
                    break;
                case 5:
                    return;
                default:
                    printf("Invalid choice. Please try again.\n");
                    break;
                }
            }
        }
    }
    printf("Invalid username or password.\n");
}

void request_loan(User* user)
 {
    if (user->loan > 0)
        {
        printf("You already have a pending loan request of %.2f.\n");
    }
    else
    {
        float amount;
        printf("Enter the amount you would like to borrow: ");
        scanf("%f", &amount);
        if (amount <= user->balance * 3)
        {
            printf("Loan request approved. %.2f has been added to your account balance.\n", amount);
            user->balance += amount;
            user->loan += amount;
        }
        else
        {
            printf("Loan request denied. You cannot borrow more than three times your account balance.\n");
        }
    }
}

void approve_loan(User* user)
{
    printf("Enter the username of the user whose loan request you would like to approve: ");
    char username[20];
    scanf("%s", username);
    int i;
    for (i = 0; i < num_users; i++)
        {
        if (strcmp(username, users[i].username) == 0)
         {
            if (users[i].loan == 0)
             {
                printf("There are no pending loan requests for this user.\n");
            } else
            {
                float amount = users[i].loan;
                printf("Loan request approved. %.2f has been added to %s's account balance.\n", amount, users[i].username);
                users[i].balance += amount;
                users[i].loan = 0;
            }
            return;
        }
    }
    printf("Invalid username.\n");
}

void deposit(User* user)
 {
    float amount;
    printf("Enter the amount you would like to deposit: ");
    scanf("%f", &amount);
    user->balance += amount;
    printf("%.2f has been added to your account balance.\n", amount);
}

void withdraw(User* user)
{
    float amount;
    printf("Enter the amount you would like to withdraw: ");
    scanf("%f", &amount);

    if (amount > user->balance)
    {
        printf("Insufficient funds.\n");
    }
    else
    {
        user->balance -= amount;
        printf("%.2f has been deducted from your account balance.\n", amount);
    }
}
