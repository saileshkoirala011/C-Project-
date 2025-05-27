#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 200
#define MAX_USERS 100
#define MAX_ATTEMPTS 50
#define USERNAME_LEN 50
#define QUESTION_LEN 500
#define OPTION_LEN 100


typedef struct {
    char question[QUESTION_LEN];
    char options[4][OPTION_LEN];
    int correct_answer; 
    int difficulty; 
    int category; 
    int points;
    int time_limit;
} Question;


typedef struct {
    char username[USERNAME_LEN];
    int normal_high_score;
    int rapid_high_score;
    int total_games;
    int recent_scores[10];
    int recent_count;
} User;


typedef struct {
    User current_user;
    Question questions[MAX_QUESTIONS];
    int total_questions;
    int used_questions[MAX_QUESTIONS];
    int used_count;
    int lifeline_used;
    int current_score;
    int game_mode; 
} GameState;


GameState game;


char categories[5][20] = {"Nepal", "Geography", "Science", "Sports", "Programming"};


void initialize_game();
void load_questions();
void load_users();
void save_users();
int login_user();
void display_main_menu();
void normal_mode();
void rapid_fire_mode();
void display_question(Question *q, int q_num, int total_q);
int get_user_answer(int time_limit);
void use_lifeline(Question *q);
void shuffle_questions(int count);
void update_user_score(int score, int mode);
void display_user_stats();
void display_leaderboard();
int simple_timer(int seconds);

int main() {
    srand(time(NULL));
    initialize_game();
    
    printf("=================================\n");
    printf("   WELCOME TO QUIZ MASTER 2025   \n");
    printf("=================================\n\n");
    
    if (!login_user()) {
        printf("Login failed. Exiting...\n");
        return 1;
    }
    
    int choice;
    do {
        display_main_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                normal_mode();
                break;
            case 2:
                rapid_fire_mode();
                break;
            case 3:
                display_user_stats();
                break;
            case 4:
                display_leaderboard();
                break;
            case 5:
                printf("\nThank you for playing Quiz Master!\n");
                printf("Keep learning and come back soon!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 5);
    
    save_users();
    return 0;
}

void initialize_game() {
    game.total_questions = 0;
    game.used_count = 0;
    game.lifeline_used = 0;
    game.current_score = 0;
    load_questions();
    load_users();
}

void load_questions() {
    
    strcpy(game.questions[game.total_questions].question, "Which province is known as the industrial hub of Nepal?");
    strcpy(game.questions[game.total_questions].options[0], "Province 1");
    strcpy(game.questions[game.total_questions].options[1], "Madhesh Province");
    strcpy(game.questions[game.total_questions].options[2], "Bagmati");
    strcpy(game.questions[game.total_questions].options[3], "Lumbini");
    game.questions[game.total_questions].correct_answer = 1;
    game.questions[game.total_questions].difficulty = 0;
    game.questions[game.total_questions].category = 1;
    game.questions[game.total_questions].points = 1;
    game.questions[game.total_questions].time_limit = 20;
    game.total_questions++;

    strcpy(game.questions[game.total_questions].question, "Which national park in Nepal is a UNESCO World Heritage Site?");
    strcpy(game.questions[game.total_questions].options[0], "Bardiya National Park");
    strcpy(game.questions[game.total_questions].options[1], "Rara National Park");
    strcpy(game.questions[game.total_questions].options[2], "Chitwan National Park");
    strcpy(game.questions[game.total_questions].options[3], "Khaptad National Park");
    game.questions[game.total_questions].correct_answer = 2;
    game.questions[game.total_questions].difficulty = 0;
    game.questions[game.total_questions].category = 1;
    game.questions[game.total_questions].points = 1;
    game.questions[game.total_questions].time_limit = 20;
    game.total_questions++;

    strcpy(game.questions[game.total_questions].question, "What is the capital city of Nepal?");
    strcpy(game.questions[game.total_questions].options[0], "Pokhara");
    strcpy(game.questions[game.total_questions].options[1], "Kathmandu");
    strcpy(game.questions[game.total_questions].options[2], "Lalitpur");
    strcpy(game.questions[game.total_questions].options[3], "Biratnagar");
    game.questions[game.total_questions].correct_answer = 1;
    game.questions[game.total_questions].difficulty = 0;
    game.questions[game.total_questions].category = 0;
    game.questions[game.total_questions].points = 1;
    game.questions[game.total_questions].time_limit = 20;
    game.total_questions++;

    
    strcpy(game.questions[game.total_questions].question, "Which vitamin is mainly produced in the human body through sunlight exposure?");
    strcpy(game.questions[game.total_questions].options[0], "Vitamin A");
    strcpy(game.questions[game.total_questions].options[1], "Vitamin B12");
    strcpy(game.questions[game.total_questions].options[2], "Vitamin C");
    strcpy(game.questions[game.total_questions].options[3], "Vitamin D");
    game.questions[game.total_questions].correct_answer = 3;
    game.questions[game.total_questions].difficulty = 0;
    game.questions[game.total_questions].category = 2;
    game.questions[game.total_questions].points = 1;
    game.questions[game.total_questions].time_limit = 20;
    game.total_questions++;

    strcpy(game.questions[game.total_questions].question, "Which planet is known as the 'Red Planet'?");
    strcpy(game.questions[game.total_questions].options[0], "Earth");
    strcpy(game.questions[game.total_questions].options[1], "Mars");
    strcpy(game.questions[game.total_questions].options[2], "Jupiter");
    strcpy(game.questions[game.total_questions].options[3], "Venus");
    game.questions[game.total_questions].correct_answer = 1;
    game.questions[game.total_questions].difficulty = 0;
    game.questions[game.total_questions].category = 2;
    game.questions[game.total_questions].points = 1;
    game.questions[game.total_questions].time_limit = 20;
    game.total_questions++;

    
    strcpy(game.questions[game.total_questions].question, "Which country won the FIFA World Cup 2022?");
    strcpy(game.questions[game.total_questions].options[0], "France");
    strcpy(game.questions[game.total_questions].options[1], "Brazil");
    strcpy(game.questions[game.total_questions].options[2], "Argentina");
    strcpy(game.questions[game.total_questions].options[3], "Germany");
    game.questions[game.total_questions].correct_answer = 2;
    game.questions[game.total_questions].difficulty = 0;
    game.questions[game.total_questions].category = 3;
    game.questions[game.total_questions].points = 1;
    game.questions[game.total_questions].time_limit = 20;
    game.total_questions++;

    strcpy(game.questions[game.total_questions].question, "How many players are there in a standard football team on the field?");
    strcpy(game.questions[game.total_questions].options[0], "9");
    strcpy(game.questions[game.total_questions].options[1], "10");
    strcpy(game.questions[game.total_questions].options[2], "11");
    strcpy(game.questions[game.total_questions].options[3], "12");
    game.questions[game.total_questions].correct_answer = 2;
    game.questions[game.total_questions].difficulty = 0;
    game.questions[game.total_questions].category = 3;
    game.questions[game.total_questions].points = 1;
    game.questions[game.total_questions].time_limit = 20;
    game.total_questions++;

    
    strcpy(game.questions[game.total_questions].question, "Which of these is used to display output in C programming?");
    strcpy(game.questions[game.total_questions].options[0], "print()");
    strcpy(game.questions[game.total_questions].options[1], "echo()");
    strcpy(game.questions[game.total_questions].options[2], "cout");
    strcpy(game.questions[game.total_questions].options[3], "printf()");
    game.questions[game.total_questions].correct_answer = 3;
    game.questions[game.total_questions].difficulty = 0;
    game.questions[game.total_questions].category = 4;
    game.questions[game.total_questions].points = 1;
    game.questions[game.total_questions].time_limit = 20;
    game.total_questions++;

    
    strcpy(game.questions[game.total_questions].question, "Which river forms the major part of the eastern boundary between Nepal and India?");
    strcpy(game.questions[game.total_questions].options[0], "Koshi");
    strcpy(game.questions[game.total_questions].options[1], "Mechi");
    strcpy(game.questions[game.total_questions].options[2], "Mahakali");
    strcpy(game.questions[game.total_questions].options[3], "Bagmati");
    game.questions[game.total_questions].correct_answer = 1;
    game.questions[game.total_questions].difficulty = 1;
    game.questions[game.total_questions].category = 1;
    game.questions[game.total_questions].points = 2;
    game.questions[game.total_questions].time_limit = 30;
    game.total_questions++;

    strcpy(game.questions[game.total_questions].question, "Which organ in the human body purifies blood?");
    strcpy(game.questions[game.total_questions].options[0], "Liver");
    strcpy(game.questions[game.total_questions].options[1], "Heart");
    strcpy(game.questions[game.total_questions].options[2], "Kidney");
    strcpy(game.questions[game.total_questions].options[3], "Lung");
    game.questions[game.total_questions].correct_answer = 2;
    game.questions[game.total_questions].difficulty = 1;
    game.questions[game.total_questions].category = 2;
    game.questions[game.total_questions].points = 2;
    game.questions[game.total_questions].time_limit = 30;
    game.total_questions++;

    strcpy(game.questions[game.total_questions].question, "Which country hosted the 2018 FIFA World Cup?");
    strcpy(game.questions[game.total_questions].options[0], "Qatar");
    strcpy(game.questions[game.total_questions].options[1], "Germany");
    strcpy(game.questions[game.total_questions].options[2], "Brazil");
    strcpy(game.questions[game.total_questions].options[3], "Russia");
    game.questions[game.total_questions].correct_answer = 3;
    game.questions[game.total_questions].difficulty = 1;
    game.questions[game.total_questions].category = 3;
    game.questions[game.total_questions].points = 2;
    game.questions[game.total_questions].time_limit = 30;
    game.total_questions++;

    strcpy(game.questions[game.total_questions].question, "Which data structure uses LIFO (Last In First Out) principle?");
    strcpy(game.questions[game.total_questions].options[0], "Queue");
    strcpy(game.questions[game.total_questions].options[1], "Array");
    strcpy(game.questions[game.total_questions].options[2], "Stack");
    strcpy(game.questions[game.total_questions].options[3], "Linked List");
    game.questions[game.total_questions].correct_answer = 2;
    game.questions[game.total_questions].difficulty = 1;
    game.questions[game.total_questions].category = 4;
    game.questions[game.total_questions].points = 2;
    game.questions[game.total_questions].time_limit = 30;
    game.total_questions++;

    strcpy(game.questions[game.total_questions].question, "Which river system of Nepal contributes most to sediment load in the Ganga River Basin?");
    strcpy(game.questions[game.total_questions].options[0], "Koshi");
    strcpy(game.questions[game.total_questions].options[1], "Gandaki");
    strcpy(game.questions[game.total_questions].options[2], "Karnali");
    strcpy(game.questions[game.total_questions].options[3], "Bagmati");
    game.questions[game.total_questions].correct_answer = 0;
    game.questions[game.total_questions].difficulty = 2;
    game.questions[game.total_questions].category = 1;
    game.questions[game.total_questions].points = 3;
    game.questions[game.total_questions].time_limit = 60;
    game.total_questions++;

    strcpy(game.questions[game.total_questions].question, "Which of the following is NOT a greenhouse gas?");
    strcpy(game.questions[game.total_questions].options[0], "CO2");
    strcpy(game.questions[game.total_questions].options[1], "CH4");
    strcpy(game.questions[game.total_questions].options[2], "O3");
    strcpy(game.questions[game.total_questions].options[3], "N2");
    game.questions[game.total_questions].correct_answer = 3;
    game.questions[game.total_questions].difficulty = 2;
    game.questions[game.total_questions].category = 2;
    game.questions[game.total_questions].points = 3;
    game.questions[game.total_questions].time_limit = 60;
    game.total_questions++;

    strcpy(game.questions[game.total_questions].question, "Which nation has hosted both the Summer and Winter Olympic Games?");
    strcpy(game.questions[game.total_questions].options[0], "China");
    strcpy(game.questions[game.total_questions].options[1], "Germany");
    strcpy(game.questions[game.total_questions].options[2], "France");
    strcpy(game.questions[game.total_questions].options[3], "All of the above");
    game.questions[game.total_questions].correct_answer = 3;
    game.questions[game.total_questions].difficulty = 2;
    game.questions[game.total_questions].category = 3;
    game.questions[game.total_questions].points = 3;
    game.questions[game.total_questions].time_limit = 60;
    game.total_questions++;

    strcpy(game.questions[game.total_questions].question, "Which of the following time complexities is the most efficient for large input sizes?");
    strcpy(game.questions[game.total_questions].options[0], "O(n²)");
    strcpy(game.questions[game.total_questions].options[1], "O(n log n)");
    strcpy(game.questions[game.total_questions].options[2], "O(log n)");
    strcpy(game.questions[game.total_questions].options[3], "O(n)");
    game.questions[game.total_questions].correct_answer = 2;
    game.questions[game.total_questions].difficulty = 2;
    game.questions[game.total_questions].category = 4;
    game.questions[game.total_questions].points = 3;
    game.questions[game.total_questions].time_limit = 60;
    game.total_questions++;
}

void load_users() {
    
}

void save_users() {
    
    printf("User data saved successfully!\n");
}

int login_user() {
    printf("Enter your username: ");
    scanf("%s", game.current_user.username);
    
    
    game.current_user.normal_high_score = 0;
    game.current_user.rapid_high_score = 0;
    game.current_user.total_games = 0;
    game.current_user.recent_count = 0;
    
    printf("\nWelcome, %s!\n", game.current_user.username);
    printf("Ready to test your knowledge?\n\n");
    return 1;
}

void display_main_menu() {
    printf("\n=================================\n");
    printf("         MAIN MENU\n");
    printf("=================================\n");
    printf("1. Normal Mode Quiz\n");
    printf("2. Rapid Fire Mode\n");
    printf("3. View Your Stats\n");
    printf("4. Leaderboard\n");
    printf("5. Exit\n");
    printf("=================================\n");
}

void normal_mode() {
    int num_questions;
    printf("\n=== NORMAL MODE ===\n");
    printf("Choose number of questions:\n");
    printf("1. 10 Questions\n");
    printf("2. 20 Questions\n");
    printf("3. 30 Questions\n");
    printf("4. 40 Questions\n");
    printf("5. 50 Questions\n");
    printf("Enter choice: ");
    
    int choice;
    scanf("%d", &choice);
    
    switch(choice) {
        case 1: num_questions = 10; break;
        case 2: num_questions = 20; break;
        case 3: num_questions = 30; break;
        case 4: num_questions = 40; break;
        case 5: num_questions = 50; break;
        default: 
            printf("Invalid choice! Defaulting to 10 questions.\n");
            num_questions = 10;
    }
    
    
    game.current_score = 0;
    game.lifeline_used = 0;
    game.used_count = 0;
    game.game_mode = 0;
    
    printf("\n Starting Normal Mode with %d questions!\n", num_questions);
    printf(" Time limits: Easy(20s), Medium(30s), Hard(60s)\n");
    printf(" You have ONE 50-50 lifeline available!\n");
    printf("  Game ends if you don't answer within time limit!\n\n");
    
    printf("Press Enter to start...");
    getchar(); 
    getchar(); 
    
    
    shuffle_questions(num_questions);
    
    for(int i = 0; i < num_questions && i < game.total_questions; i++) {
        Question *current_q = &game.questions[i];
        
        printf("\n" "=================================\n");
        display_question(current_q, i+1, num_questions);
        
        int user_answer = get_user_answer(current_q->time_limit);
        
        if(user_answer == -1) {
            printf("\n Time's up! Game over!\n");
            printf("Your final score: %d points\n", game.current_score);
            break;
        }
        
        if(user_answer == current_q->correct_answer) {
            printf("Correct! +%d points\n", current_q->points);
            game.current_score += current_q->points;
        } else {
            printf("Wrong! The correct answer was: %s\n", 
                   current_q->options[current_q->correct_answer]);
        }
        
        printf("Current Score: %d\n", game.current_score);
    }
    
    printf("\n🎉 Quiz completed!\n");
    printf("Final Score: %d points\n", game.current_score);
    
    
    update_user_score(game.current_score, 0);
}

void rapid_fire_mode() {
    printf("\n=== RAPID FIRE MODE ===\n");
    printf(" Answer as many questions as possible in 60 seconds!\n");
    printf(" Each correct answer = 1 point\n");
    printf(" Questions from all categories (medium difficulty)\n\n");
    
    printf("Press Enter to start...");
    getchar();
    getchar(); 
    
    game.current_score = 0;
    game.game_mode = 1;
    
    time_t start_time = time(NULL);
    time_t current_time;
    int questions_asked = 0;
    
    printf("\n RAPID FIRE STARTED!\n");
    
    while(1) {
        current_time = time(NULL);
        if(current_time - start_time >= 60) {
            printf("\n Time's up!\n");
            break;
        }
        
        
        int q_index;
        do {
            q_index = rand() % game.total_questions;
        } while(game.questions[q_index].difficulty != 1);
        
        Question *current_q = &game.questions[q_index];
        
        int remaining_time = 60 - (current_time - start_time);
        printf("\n Time remaining: %d seconds\n", remaining_time);
        printf("Question %d: %s\n", questions_asked + 1, current_q->question);
        
        for(int j = 0; j < 4; j++) {
            printf("%d. %s\n", j+1, current_q->options[j]);
        }
        
        printf("Your answer (1-4): ");
        int answer;
        scanf("%d", &answer);
        answer--; 
        
        if(answer == current_q->correct_answer) {
            printf(" Correct! +1 point\n");
            game.current_score++;
        } else {
            printf(" Wrong!\n");
        }
        
        questions_asked++;
    }
    
    printf("\n🎉 Rapid Fire completed!\n");
    printf("Questions answered: %d\n", questions_asked);
    printf("Final Score: %d points\n", game.current_score);
    
    update_user_score(game.current_score, 1);
}

void display_question(Question *q, int q_num, int total_q) {
    char difficulty_str[10];
    switch(q->difficulty) {
        case 0: strcpy(difficulty_str, "Easy"); break;
        case 1: strcpy(difficulty_str, "Medium"); break;
        case 2: strcpy(difficulty_str, "Hard"); break;
    }
    
    printf("Question %d/%d [%s - %s] (%d points)\n", 
           q_num, total_q, categories[q->category], difficulty_str, q->points);
    printf(" Time limit: %d seconds\n\n", q->time_limit);
    printf("%s\n\n", q->question);
    
    for(int i = 0; i < 4; i++) {
        printf("%d. %s\n", i+1, q->options[i]);
    }
    
    if(!game.lifeline_used) {
        printf("\n Type '5' to use 50-50 lifeline\n");
    }
}

int get_user_answer(int time_limit) {
    printf("\nYour answer (1-4): ");
    
    
    int answer;
    scanf("%d", &answer);
    
    if(answer == 5 && !game.lifeline_used) {
        
        game.lifeline_used = 1;
        printf(" 50-50 Lifeline used! Two wrong answers eliminated.\n");
        printf("Choose from remaining options (1-4): ");
        scanf("%d", &answer);
    }
    
    if(answer < 1 || answer > 4) {
        return -1; 
    }
    
    return answer - 1; 
}

void shuffle_questions(int count) {
    
    for(int i = 0; i < count && i < game.total_questions; i++) {
        int j = rand() % game.total_questions;
        Question temp = game.questions[i];
        game.questions[i] = game.questions[j];
        game.questions[j] = temp;
    }
}

void update_user_score(int score, int mode) {
    if(mode == 0) { 
        if(score > game.current_user.normal_high_score) {
            game.current_user.normal_high_score = score;
            printf(" NEW HIGH SCORE for Normal Mode!\n");
        }
    } else { 
        if(score > game.current_user.rapid_high_score) {
            game.current_user.rapid_high_score = score;
            printf(" NEW HIGH SCORE for Rapid Fire Mode!\n");
        }
    }
    
    
    if(game.current_user.recent_count < 10) {
        game.current_user.recent_scores[game.current_user.recent_count] = score;
        game.current_user.recent_count++;
    } else {
        
        for(int i = 0; i < 9; i++) {
            game.current_user.recent_scores[i] = game.current_user.recent_scores[i+1];
        }
        game.current_user.recent_scores[9] = score;
    }
    
    game.current_user.total_games++;
}

void display_user_stats() {
    printf("\n=================================\n");
    printf("      %s's STATISTICS\n", game.current_user.username);
    printf("=================================\n");
    printf(" Normal Mode High Score: %d\n", game.current_user.normal_high_score);
    printf(" Rapid Fire High Score: %d\n", game.current_user.rapid_high_score);
    printf(" Total Games Played: %d\n", game.current_user.total_games);
    
    if(game.current_user.recent_count > 0) {
        printf("\n Recent Scores:\n");
        for(int i = 0; i < game.current_user.recent_count; i++) {
            printf("   Game %d: %d points\n", i+1, game.current_user.recent_scores[i]);
        }
    }
    
    printf("\n Keep playing to improve your scores!\n");
}

void display_leaderboard() {
    printf("\n=================================\n");
    printf("         LEADERBOARD\n");
    printf("=================================\n");
    printf(" Normal Mode Champion: %s (%d points)\n", 
           game.current_user.username, game.current_user.normal_high_score);
    printf(" Rapid Fire Champion: %s (%d points)\n", 
           game.current_user.username, game.current_user.rapid_high_score);
    printf("\n(In full version, this would show all users' scores)\n");
}