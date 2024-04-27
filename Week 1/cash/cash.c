#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for change owed, in cents.
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0); // Only accepts positive integers.

    int quarters = cents / 25;     // Calculate how many quarters you should give customer.
    cents = cents - quarters * 25; // Subtract the value of those quarters from cents.

    int dimes = cents / 10;     // Calculate how many dimes you should give customer.
    cents = cents - dimes * 10; // Subtract the value of those dimes from remaining cents.

    int nickels = cents / 5;     // Calculate how many nickels you should give customer.
    cents = cents - nickels * 5; // Subtract the value of those nickels from remaining cents.

    int pennies = cents; // Calculate how many pennies you should give customer.

    int total = quarters + dimes + nickels + pennies;   // Sum the number of quarters, dimes, nickels, and pennies used.
    printf("%i\n", total); // Print that sum.
}
