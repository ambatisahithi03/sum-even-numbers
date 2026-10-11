/*
 * ============================================================================
 * Program: Sum of All Even Numbers
 * Description: Reads n integers and calculates the sum of all even numbers
 *              among them with comprehensive input validation.
 * 
 * Features:
 *   - Input validation for positive number of elements
 *   - Handles both positive and negative integers
 *   - Calculates and displays sum of even numbers
 *   - Counts total even numbers found
 *   - Formatted output with clear results
 * 
 * Grading Scale Example:
 *   Input: n = 5, numbers = 1 2 3 4 5
 *   Output: Sum of even numbers = 6 (2 + 4)
 *           Count of even numbers = 2
 * ============================================================================
 */

#include <stdio.h>

int main() {
    int n;
    int num;
    int sum = 0;
    int count = 0;

    printf("========================================\n");
    printf("    SUM OF ALL EVEN NUMBERS\n");
    printf("========================================\n\n");

    /* Input validation: ensure n is positive */
    do {
        printf("Enter the number of elements (n > 0): ");
        
        if (scanf("%d", &n) != 1) {
            printf("Invalid input. Please enter a positive integer.\n");
            while (getchar() != '\n');  /* Clear input buffer */
            n = 0;
            continue;
        }
        
        if (n <= 0) {
            printf("Please enter a positive number.\n");
        }
    } while (n <= 0);

    printf("\nEnter %d numbers:\n", n);

    /* Read n integers and sum the even ones */
    for (int i = 0; i < n; i++) {
        printf("Number %d: ", i + 1);
        
        if (scanf("%d", &num) != 1) {
            printf("Invalid input. Please enter an integer.\n");
            while (getchar() != '\n');  /* Clear input buffer */
            i--;  /* Repeat this iteration */
            continue;
        }

        /* Check if the number is even (divisible by 2) */
        if (num % 2 == 0) {
            sum += num;
            count++;
        }
    }

    /* Display results */
    printf("\n========================================\n");
    printf("                RESULTS\n");
    printf("========================================\n");
    printf("Sum of all even numbers = %d\n", sum);
    printf("Count of even numbers = %d\n", count);
    printf("========================================\n\n");

    return 0;
}
