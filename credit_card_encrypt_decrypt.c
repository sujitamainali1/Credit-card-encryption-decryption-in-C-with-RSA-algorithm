#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define RED "\033[0;31m"
#define MAGENTA "\033[0;35m"
#define PURPLE "\033[0;35m"
#define YELLOW "\033[0;33m"
#define PINK "\033[0;95m"
#define RESET "\033[0m"

// Global variables
int x, y, n, t, i, flag;
long int p, q, e[50], d[50], temp[50], j, m[50], cipher[50];

// Function Declaration
int prime(long int pr);
void generate_keys();
long int calculate_d(long int);
void encrypt();
void decrypt();

int main()
{
    printf(GREEN "\n========== Credit Card Encryption and Decryption ===========\n" RESET);
    printf(BLUE "**Note: This is a simulation. Do NOT enter real credit card information!**\n\n" RESET);

    // Prompt user to enter the first prime number (p)
    while (1)
    {
        printf(MAGENTA "Enter the first prime number (p): " RESET);
        scanf("%ld", &p);

        // Check if the entered number is prime
        flag = prime(p);
        if (flag == 0)
        {
            printf(RED "INVALID INPUT. Please enter a prime number.\n" RESET);
            continue; // Go back to the start of the loop
        }
        break; // Exit the loop if a prime number is entered
    }

    // Prompt user to enter the second prime number (q)
    while (1)
    {
        printf(MAGENTA "Enter the second prime number (q): " RESET);
        scanf("%ld", &q);

        // Check if the entered number is prime and different from p
        flag = prime(q);
        if (flag == 0 || p == q)
        {
            printf(RED "INVALID INPUT. Please enter a prime number different from the first one.\n" RESET);
            continue; // Go back to the start of the loop
        }
        break; // Exit the loop if a prime number is entered
    }

    // Generate RSA keys
    generate_keys();

    printf(PURPLE"\nPublic Key(s):\n"RESET);
    for (i = 0; e[i] != '\0'; i++)
        printf("e[%d]: %ld\n", i, e[i]);

    printf(PURPLE"\nPrivate Key(s):\n"RESET);
    for (i = 0; d[i] != '\0'; i++)
        printf("d[%d]: %ld\n", i, d[i]);

    // Program loop
    while (1)
    {
        int option;
        printf(PINK"\nChoose an option:\n"RESET);
        printf(YELLOW "1. Encrypt Credit Card Number\n"RESET);
        printf(YELLOW"2. Decrypt Credit Card Number\n"RESET);
        printf(YELLOW"0. Exit\n"RESET);
        printf(YELLOW "Enter your choice: " RESET);
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            encrypt();
            break;
        case 2:
            decrypt();
            break;
        case 0:
            printf(PURPLE"Exiting program...\n"RESET);
            exit(0);
        default:
            printf(RED "**Invalid option** Please try again!!.\n" RESET);
            break;
        }
    }

    return 0;
}

int prime(long int pr)
{
    int i;
    j = sqrt(pr);

    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }

    return 1;
}

void generate_keys()
{
    int k;
    k = 0;

    n = p * q;
    t = (p - 1) * (q - 1);

    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;

        flag = prime(i);
        if (flag == 1 && i != p && i != q)
        {
            e[k] = i;
            flag = calculate_d(e[k]);

            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }

            if (k == 99)
                break;
        }
    }
}

long int calculate_d(long int a)
{
    long int k = 1;
    while (1)
    {
        k = k + t;
        if (k % a == 0)
            return (k / a);
    }
}

void encrypt()
{
    int len;
    printf(PURPLE "\nEnter the length of the credit card number: " RESET);
    scanf("%d", &len);

    printf(PURPLE "Enter the credit card number: " RESET);
    char cardNumber[100];
    scanf("%s", cardNumber);

    len = strlen(cardNumber);
    for (int i = 0; i < len; i++)
    {
        m[i] = cardNumber[i] - '0';
    }

    printf("\n");

    long int key;
    printf(PINK "Enter the public key (e): " RESET);
    scanf("%ld", &key);

    int publicKeyValid = 0;
    for (int i = 0; e[i] != '\0'; i++)
    {
        if (e[i] == key)
        {
            publicKeyValid = 1;
            break;
        }
    }

    if (!publicKeyValid)
    {
        printf(RED "Invalid public key. Exiting...\n" RESET);
        exit(0);
    }

    printf(MAGENTA"Encrypted Credit Card Number: "RESET);
    for (int i = 0; i < len; i++)
    {
        long int pt, ct, k;

        pt = m[i];
        k = 1;

        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }

        temp[i] = k;
        ct = k;
        printf("%ld ", ct);
    }
    printf("\n");
}
void decrypt()
{  
    
    int len;
    printf(PURPLE "\nEnter the length of the cipher: " RESET);
    scanf("%d", &len);

    printf(PURPLE "Enter the cipher: " RESET);
    for (int i = 0; i < len; i++)
        scanf("%ld", &cipher[i]);

    long int privateKey;
            printf(PINK "Enter the private key (d): " RESET);
            scanf("%ld", &privateKey);
    // Check if the entered private key is correct
    int privateKeyValid = 0;
    for (i = 0; d[i] != '\0'; i++)
    {
        if (d[i] == privateKey)
        {
            privateKeyValid = 1;
            break;
        }
    }

    if (!privateKeyValid)
    {
        printf(RED "Invalid private key. Exiting...\n" RESET);
        exit(0);
    }    

    printf(MAGENTA"\nDecrypted Credit Card Number: "RESET);
    for (int i = 0; i < len; i++)
    {
        long int pt, ct, key = d[0], k;
        ct = cipher[i];
        k = 1;

        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }

        pt = k;
        printf("%ld ", pt);
    }
    printf("\n");
}
