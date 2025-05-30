# 🎮 Quiz Game Summary (C Project)
## 🧱 1. Core Structures
Question
Holds data for each quiz question:

- ```question```: question text
- ```options[4]```: multiple choice options
- ```correct_answer```: correct option index (0-3)
- ```difficulty```: Easy (0), Medium (1), Hard (2)
- ```category```: 0–4, based on topics
points: points awarded for correct answer
- ```time_limit```: seconds to answer

```User```

Stores player data:
- ```username```: current player's name
- ```normal_high_score```, ```rapid_high_score```: best scores in each mode
- ```total_games```: number of games played
- ```recent_scores[10]```: last 10 game scores
- ```recent_count```: number of recent scores tracked

```GameState```

- Tracks entire game session:
- current user
loaded questions
score
- game mode (normal/rapid)
lifeline usage, etc.

## 🛠️ 2. Main Functional Modules
- ```main()```

- Starts the game, logs in a user, shows the main menu.
- Based on user input, triggers different modes or views.
- ```initialize_game()```
- Resets game state and loads questions/users.
- ```load_questions()```
- Manually hardcodes 15+ quiz questions into memory.
- Categories include Nepal, Geography, Science, Sports, Programming.
- ```login_user()```
Prompts for username and initializes user data (no actual authentication or storage yet).
display_main_menu()
Shows 5 options: Normal Mode, Rapid Fire, Stats, Leaderboard, Exit.

### 🧩 3. Game Modes
- ```normal_mode()```
- User chooses number of questions (10–50).
- Lifeline: One "50-50" is available (eliminates 2 wrong options).
- Shuffles questions.
- Each question:
  - Displayed with difficulty, category, timer.
   - Player selects answer within time limit.
- Ends with score display and updates user's stats.
 
 ```rapid_fire_mode()```

- Timed challenge: 60 seconds to answer as many medium-difficulty questions as possible.
- One point per correct answer.
- No lifeline.
- Uses real-time countdown via ```time()```.

## 🎯 4. Helper Functions
```display_question()```

- Prints question, options, difficulty, and category.
- Optionally displays 50-50 lifeline hint.

```get_user_answer()```

- Takes timed input.
- Handles lifeline usage.
- Returns user’s answer or timeout.

```shuffle_questions()```

- Randomly rearranges questions.

 ```update_user_score()```

- Updates user’s best score and recent history.

```display_user_stats()```

- Shows the user's current high scores and recent performance.

```display_leaderboard()```
- Shows placeholder leaderboard with only current user (no persistent leaderboard implemented).

```save_users()```

- Placeholder that currently prints a save success message (no file saving logic yet).

## 🗂️ 5. Categories Used

char categories[5][20] = {
    "Nepal", "Geography", "Science", "Sports", "Programming"
};

### 📌 Features Implemented
- User login (in-memory only)
- Two game modes: normal & rapid fire
- 50-50 lifeline (normal mode only)
- Real-time countdown (rapid fire)
- Score tracking and history
- Static leaderboard (placeholder)
- Randomized questions
- Difficulty-based point system

## 🔴 Missing / Incomplete Features
 - No persistent user data storage (e.g., file-based ```load_users()``` / ```save_users()``` not implemented).
- No actual timer enforcement on answers (time is suggested, not strictly measured).
- 50-50 lifeline doesn’t actually eliminate two wrong options visually.
- Leaderboard is not multi-user; it shows only the current user’s scores.

## ✅ Summary
Your current implementation covers all key aspects up to implementation and partial testing. With a few additions (file I/O, better input handling, external data), it can be made robust enough for full deployment
