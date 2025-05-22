#include <stdio.h>

int main() {
    int score = 0, answer;

    // Question 1
    printf("1. What is the capital of France?\n");
    printf("1) Berlin\n2) Paris\n3) Rome\n4) Madrid\n");
    printf("Enter your answer (1-4): ");
    scanf("%d", &answer);
    if (answer == 2) score++;

    // Question 2
    printf("\n2. Which language is used for system programming?\n");
    printf("1) Python\n2) Java\n3) C\n4) HTML\n");
    printf("Enter your answer (1-4): ");
    scanf("%d", &answer);
    if (answer == 3) score++;

    // Question 3
    printf("\n3. What does CPU stand for?\n");
    printf("1) Central Processing Unit\n2) Computer Personal Unit\n3) Central Print Unit\n4) Control Processing Unit\n");
    printf("Enter your answer (1-4): ");
    scanf("%d", &answer);
    if (answer == 1) score++;

    // Result
    printf("\nQuiz finished! You scored %d out of 3.\n", score);

    return 0;
}
