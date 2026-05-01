//coding project 10 submission for Brian Doyle

#include<stdio.h>
#include<stdbool.h>

#define wordLen 5
#define maxGuesses 6

void loadWord(char word[]);
int findLen(char guess[]);
bool isLetters(char guess[]);
void makeLower(char guess[]);
bool sameWord(char guess[], char word[]);
void copyGuess(char guesses[][wordLen + 1], char guess[], int guessNumber);
void showGuesses(char guesses[][wordLen + 1], int guessCount, char word[]);
void lenError();
void letterError();

int main(){

    char word[wordLen + 1];
    char guess[32];
    char guesses[maxGuesses][wordLen + 1];

    int guessLen = 0;
    int guessNumber = 0;
    bool won = false;

    loadWord(word);

    while (guessNumber < maxGuesses && won == false) {
        printf("GUESS %d! Enter your guess: ", guessNumber + 1);
        fgets(guess, 32, stdin);

        guessLen = findLen(guess);
        if (guessLen != wordLen && isLetters(guess) == false){
            lenError();
            letterError();
        }
        else if (guessLen != wordLen) {
            lenError();
        }
        else if (isLetters(guess) == false) {
            letterError();
        }
        else {
            makeLower(guess);

            copyGuess(guesses, guess, guessNumber);
            guessNumber++;

            showGuesses(guesses, guessNumber, word);

            if (sameWord(guess, word) == true) {
                won = true;
            }
        }
    }
    if (won == true) {
        printf("You guessed the word!\n");
    }
    else {
        printf("You lost, better luck next time!\n");
    }
    return 0;
}

void loadWord(char word[]){
    FILE *inFile;
    int i = 0;
    inFile = fopen("word.txt", "r");
    if (inFile == NULL) {
        printf("Could not open word.txt\n");
    }
    else {
        fgets(word, wordLen + 2, inFile);
        while (word[i] != '\n' && word[i] != '\0') {
            if (word[i] >= 'A' && word[i] <= 'Z') {
                word[i] = word[i] + 32;
            }
            i++;
        }
        word[i] = '\0';
        fclose(inFile);
    }
}

int findLen(char guess[]){
    int guessLen = 0;
    while (guess[guessLen] != '\n' && guess[guessLen] != '\0') {
        guessLen++;
    }
    return guessLen;
}

bool isLetters(char guess[]){
    int i = 0;
    while (guess[i] != '\n' && guess[i] != '\0') {
        if (!((guess[i] >= 'A' && guess[i] <= 'Z') || (guess[i] >= 'a' && guess[i] <= 'z'))) {
            return false;
        }
        i++;
    }
    return true;
}

void makeLower(char guess[]){
    int i = 0;

    while (guess[i] != '\n' && guess[i] != '\0') {
        if (guess[i] >= 'A' && guess[i] <= 'Z') {
            guess[i] = guess[i] + 32;
        }
        i++;
    }
    guess[i] = '\0';
}

bool sameWord(char guess[], char word[]){
    int i = 0;

    while (i < wordLen) {
        if (guess[i] != word[i]) {
            return false;
        }
        i++;
    }
    return true;
}

void copyGuess(char guesses[][wordLen + 1], char guess[], int guessNumber){
    int i = 0;
    while (i < wordLen) {
        guesses[guessNumber][i] = guess[i];
        i++;
    }
    guesses[guessNumber][i] = '\0';
}

void showGuesses(char guesses[][wordLen + 1], int guessCount, char word[]){
    int row;
    int col;
    int i;
    bool point;

    for (row = 0; row < guessCount; row++) {
        for (col = 0; col < wordLen; col++) {
            if (guesses[row][col] == word[col]) {
                printf("%c", guesses[row][col] - 32);
            }
            else {
                printf("%c", guesses[row][col]);
            }
        }
        printf("\n");

        for (col = 0; col < wordLen; col++) {
            point = false;

            if (guesses[row][col] != word[col]) {
                for (i = 0; i < wordLen; i++) {
                    if (guesses[row][col] == word[i] && guesses[row][i] != word[i]) {
                        point = true;
                    }
                }
            }
            if (point == true) {
                printf("^");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void lenError(){
    printf("Your guess must be 5 letters long.\n");
}

void letterError(){
    printf("Your guess must contain only letters.\n");
}