#include <stdio.h>

int main() {
    int n;
    int num;
    int sum = 0;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &num);

        if (num % 2 == 0) {
            sum += num;
        }
    }

    printf("Sum of all even numbers = %d\n", sum);

    return 0;
}
