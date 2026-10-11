/*
 * ============================================================================
 * Program: Sum of All Even Numbers
 * Description: Reads n integers (n > 0) and calculates the sum of the even
 *              numbers among them, with robust input validation.
 *
 * Features:
 *   - Validates that n is a positive integer
 *   - Handles positive, negative, and zero values (0 is considered even)
 *   - Robust input validation: rejects text, empty lines, trailing junk
 *     (e.g., "5abc"), and values outside int range
 *   - Uses long long to prevent sum overflow with large numbers
 *   - Gracefully handles EOF (Ctrl+D on Unix, Ctrl+Z on Windows)
 *   - Detailed error messages guide users to correct input
 *
 * Input Format: Enter ONE integer per line
 *
 * Sample Execution:
 *   Input:  n = 5, numbers = 1 2 3 4 5 (each on separate line)
 *   Output: Sum of all even numbers = 6 (from 2 + 4)
 *           Count of even numbers = 2
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

/* Constants for buffer sizes and line input */
#define INPUT_LINE_BUFFER_SIZE 128

/* Return codes for input reading function */
#define INPUT_READ_SUCCESS   1   /* Successfully read a valid integer */
#define INPUT_READ_END_OF_FILE 0 /* End of input stream reached (EOF) */
#define INPUT_READ_INVALID  -1   /* Invalid input (text, junk, overflow, etc.) */

/*
 * ============================================================================
 * Function: read_integer_from_input
 * 
 * Purpose: Reads a single integer from standard input with robust validation
 * 
 * Parameters:
 *   - prompt_message: String to display before reading input
 *   - integer_output: Pointer to store the successfully read integer
 * 
 * Returns:
 *   INPUT_READ_SUCCESS    : Successfully read and stored a valid integer
 *   INPUT_READ_INVALID    : Input was invalid (non-numeric, too large, junk)
 *   INPUT_READ_END_OF_FILE: Input stream ended (EOF encountered)
 * 
 * Behavior:
 *   - Handles lines longer than buffer (discards excess)
 *   - Validates range: ensures value fits in a 32-bit integer
 *   - Strips trailing whitespace but rejects trailing junk characters
 *   - Clears errno before attempting conversion
 * ============================================================================
 */
static int read_integer_from_input(const char *prompt_message, int *integer_output) {
    /* Buffer to hold one line of user input */
    char input_line[INPUT_LINE_BUFFER_SIZE];
    
    /* Pointer to track position after number conversion */
    char *conversion_end_pointer;
    
    /* Temporary storage for converted value (long for range checking) */
    long converted_value;

    /* Display the prompt and ensure it appears immediately */
    printf("%s", prompt_message);
    fflush(stdout);

    /* Read one line from input */
    if (fgets(input_line, sizeof input_line, stdin) == NULL) {
        /* No more input available (EOF reached) */
        return INPUT_READ_END_OF_FILE;
    }

    /* 
     * Check if the entire line was read successfully.
     * If newline is missing and we're not at EOF, the input line was too long.
     */
    if (strchr(input_line, '\n') == NULL && !feof(stdin)) {
        /* Discard the remaining characters from this line */
        int character;
        while ((character = getchar()) != '\n' && character != EOF) {
            ;
        }
        /* Report input as invalid */
        return INPUT_READ_INVALID;
    }

    /* Clear errno before conversion to detect true errors */
    errno = 0;
    
    /* Convert string to long integer (base 10) */
    converted_value = strtol(input_line, &conversion_end_pointer, 10);

    /* Check if any digits were found at all */
    if (conversion_end_pointer == input_line) {
        return INPUT_READ_INVALID;
    }
    
    /* Check for range errors (value too large or too small for int) */
    if (errno == ERANGE || converted_value < INT_MIN || converted_value > INT_MAX) {
        return INPUT_READ_INVALID;
    }
    
    /* Skip any trailing whitespace after the number */
    while (isspace((unsigned char)*conversion_end_pointer)) {
        conversion_end_pointer++;
    }
    
    /* Check that we've reached the end of the string (no junk after number) */
    if (*conversion_end_pointer != '\0') {
        return INPUT_READ_INVALID;
    }

    /* Store the successfully converted integer */
    *integer_output = (int)converted_value;
    return INPUT_READ_SUCCESS;
}

/*
 * ============================================================================
 * Function: main
 * 
 * Purpose: Main program logic for calculating sum of even numbers
 * 
 * Returns:
 *   0 : Program completed successfully (read all requested numbers)
 *   1 : Program terminated early (EOF or other error condition)
 * ============================================================================
 */
int main(void) {
    /* Number of integers the user wants to input */
    int target_number_count = 0;
    
    /* Current number being processed */
    int current_number = 0;
    
    /* Status code from input reading function */
    int input_read_status;
    
    /* Counter for how many numbers have been successfully read */
    int numbers_successfully_read = 0;
    
    /* Sum of all even numbers found (using long long to prevent overflow) */
    long long sum_of_even_numbers = 0;
    
    /* Count of how many even numbers were found */
    int count_of_even_numbers = 0;

    /* ====================================================================
     * PROGRAM HEADER
     * ==================================================================== */
    printf("========================================\n");
    printf("    SUM OF ALL EVEN NUMBERS\n");
    printf("========================================\n\n");

    /* ====================================================================
     * PHASE 1: Get the count of numbers to input
     * ==================================================================== */
    do {
        /* Attempt to read the count of numbers */
        input_read_status = read_integer_from_input(
            "Enter the number of elements (n > 0): ",
            &target_number_count
        );

        /* Check if input ended unexpectedly */
        if (input_read_status == INPUT_READ_END_OF_FILE) {
            printf("\nInput ended unexpectedly. Exiting.\n");
            return 1;
        }
        
        /* Check if input was invalid */
        if (input_read_status == INPUT_READ_INVALID) {
            printf("Invalid input. Please enter a positive integer.\n");
            target_number_count = 0;  /* Reset to force re-entry */
            continue;
        }
        
        /* Validate that the count is positive */
        if (target_number_count <= 0) {
            printf("Please enter a positive number.\n");
        }
    } while (target_number_count <= 0);

    /* ====================================================================
     * PHASE 2: Read and process the specified number of integers
     * ==================================================================== */
    printf("\nEnter %d numbers (one per line):\n", target_number_count);

    /* Continue until we've read the requested number of integers */
    while (numbers_successfully_read < target_number_count) {
        /* Create a dynamic prompt showing current progress */
        char current_prompt[32];
        snprintf(
            current_prompt,
            sizeof current_prompt,
            "Number %d: ",
            numbers_successfully_read + 1
        );

        /* Attempt to read one integer */
        input_read_status = read_integer_from_input(current_prompt, &current_number);

        /* Handle end of input (EOF) */
        if (input_read_status == INPUT_READ_END_OF_FILE) {
            printf(
                "\nInput ended after %d of %d numbers.\n",
                numbers_successfully_read,
                target_number_count
            );
            break;  /* Exit the loop and display partial results */
        }
        
        /* Handle invalid input */
        if (input_read_status == INPUT_READ_INVALID) {
            printf("Invalid input. Please enter an integer.\n");
            continue;  /* Ask for the same number again without counting */
        }

        /* Increment counter only after successful read */
        numbers_successfully_read++;

        /* ================================================================
         * Check if the current number is even
         * Note: Works correctly for negative numbers too
         *       (e.g., -4 % 2 == 0 is true, -3 % 2 != 0)
         * ================================================================ */
        if (current_number % 2 == 0) {
            sum_of_even_numbers += current_number;
            count_of_even_numbers++;
        }
    }

    /* ====================================================================
     * PHASE 3: Display results
     * ==================================================================== */
    printf("\n========================================\n");
    printf("                RESULTS\n");
    printf("========================================\n");
    printf("Sum of all even numbers = %lld\n", sum_of_even_numbers);
    printf("Count of even numbers = %d\n", count_of_even_numbers);
    printf("========================================\n\n");

    /* Return appropriate exit code */
    return (numbers_successfully_read == target_number_count) ? 0 : 1;
}
