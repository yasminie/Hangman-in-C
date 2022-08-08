
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define WORDS 20
#define STRIKES 6

void rules(void); //display rules of the game
void maskWord (char starword[], int size); //mask the word with stars to display
int playRound(char starword[], char answer[]); //play a round of hangman
int occurancesInWord(char userguess, char answer[]); //number of times letter occurs in word
void updateStarWord(char starword[], char answer[], char userguess); //replace respective *
void playAgain(int *play); //ask user if to play again. 1 is yes 2 is no

int main() {

    // Declare and assign variables, strings, file
    FILE *inp;

    char answer[WORDS];
    char starword[WORDS];

    int size;
    char userguess;
    int check = 1;
    int play = 0;

    // Opening file
    inp = fopen("words.txt", "r");

    rules(); // Function call

    while(check)
    {
      // Reading line from text file
      fscanf(inp, "%s", answer);

      // Finding string length of each word
      size = strlen(answer);

      // Function calls
      maskWord(starword, size);

      if(playRound(starword, answer) == 1)
      {
        printf("Congratulations! You won! The word was %s.\n", answer);
        printf("\n");
      }
      else
      {
        printf("Sorry, you did not win the round. The word was %s.\n", answer);
        printf("\n");
      }

      playAgain(&play);

      // If the user enters 2 the loop ends
      if (play == 2)
      {
        check = 0;
      }
    }
    // Closing the file
    fclose(inp);

    return 0;
}

void rules(void)
{
    // Displays game rules
    printf("Welcome to the Hangman Game!\n");
    printf("\n");
    printf("************************************************************************\n");
    printf("Here are the rules.\n");
    printf("I will provide you a set of * characters for each round.\n");
    printf("Each * represents a letter in the English Alphabet.\n");
    printf("You must figure out each letter of the missing word.\n");
    printf("For every correct letter guessed, I will reveal its place in the word.\n");
    printf("Each mistake will result in a strike.\n");
    printf("6 strikes will result in a loss that round.\n");
    printf("Are you ready? Here we go!\n");
    printf("\n");
}

void maskWord (char starword[], int size)
{
    // Adds a star for every index
    // and a null character at the end
    for(int i = 0; i < size; ++i)
    {
        starword[i] = '*';
        starword[size] = '\0';
    }
}

int playRound(char starword[], char answer[])
{
    // Declaration and assignment of variables and strings
    int strike = 0;
    int size = strlen(answer);
    char guesses[WORDS] = {0};
    char userguess;
    int win = 0;

    // Starting round
    printf("************************************************************************\n");
    printf("Welcome to the Round!\n");
    printf("The size of the word has %d letters.\n", size);
    printf("\n");

    while(strike != STRIKES)
    {
      // States strikes, guesses, and starword
      printf("You currently have %d strike(s).\n", strike);

      printf("Letter(s) you have guessed: %s\n", guesses);
      printf("\n");

      printf("%s\n", starword);
      printf("\n");

      // Collects user's guess in lowercase
      printf("Enter your guess: ");
      scanf(" %c", &userguess);
      userguess = tolower(userguess);
      printf("\n");

      // There is at least one occurance, starword will update.
      if(occurancesInWord(userguess, answer) > 0)
      {
        updateStarWord(starword, answer, userguess); // Function call
        printf("The letter %c is in the word.\n", userguess);
        printf("\n");
        strncat(guesses, &userguess, 1);

        // If fully guessed, win is true.
        if(strcmp(starword, answer) == 0)
        {
          win = 1;
          break;
        }
      }

      // If the user's guess isn't a letter it's rejected.
      else if(!(isalpha(userguess)))
      {
        printf("You did not enter a letter from the alphabet.\n");
        printf("\n");
      }
      // If letter isn't in the word it's a strike.
      else
      {
        printf("The letter %c is NOT in the word.\n", userguess);
        printf("\n");
        strncat(guesses, &userguess, 1);
        strike += 1;
      }
    }

    // If strikes reach 6 the round ends and win is false.
    if (strike == STRIKES)
    {
      win = 0;
    }
    // Returns 1 or 0
    return win;
}

int occurancesInWord(char userguess, char answer[])
{
    // Declaration of variable
    int count = 0;

    // Counts how many times a user's guess is
    // present in the answer
    for(int i = 0; answer[i] != '\0'; ++i)
    {
      if(answer[i] == userguess)
      {
        count++;
      }
    }
    // Returns number of times guess occurs
    return count;
}

void updateStarWord(char starword[], char answer[], char userguess)
{
    // Declaration and assignment of variables
    int size = strlen(answer);
    int i;

    // If the user's guess matches a letter in the answer
    // starword will replace the letter
    for(int i = 0; i < size; ++i)
    {
      if(userguess == answer[i])
      {
        starword[i] = userguess;
      }
    }
}

void playAgain(int *play)
{
    // Asks user to continue or stop
    printf("************************************************************************\n");
    printf("Would you like to play another round?\n");
    printf("1: Yes\n");
    printf("2: No\n");

    printf("Choice: ");
    scanf("%d", play);

    printf("\n");

    // If 1 selcted, rounds will continue in main function.
    // If 2 selected, game ends.
    switch(*play)
    {
      case 1:
        *play = 1;
        break;
      case 2:
        printf("************************************************************************\n");
        printf("Thank you for playing today!\n");
        *play = 2;
        break;
      default:
        printf("Invalid input. Try again!\n");
      }
}
