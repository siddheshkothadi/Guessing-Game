#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// No. of rounds in the game
#define ROUNDS 4

// Lower and upper limit of the random number generated
#define LOWER_LIMIT 1
#define UPPER_LIMIT 10

// A structure defining a Player in the game
typedef struct Player
{
    char *name;
    int guess;
    int score;
    struct Player *next;
} Player;

// Get Player's Information
Player *acceptInfo(int playerNumber);
// Create a circular linked list based on the number of players playing the game
Player *createCLL(int numberOfPlayers);

/** GAME RELATED FUNCTIONS **/

// Returns the random number within the given range
int generateRandomNumber(int lowerLimit, int upperLimit);

// To display the leaderboard after each roundNo
void showLeaderboard(Player *head);

// Called on each round
void playRound(Player *head, int roundNo);

// Returns the winner at the end of the game
Player *getWinner(Player *head);

// Root function to start the game
void playGame(Player *head);

int main()
{
    // Choice for first switch case
    int choice_1 = -1;

    int numberOfPlayers;
    int lowerLimit, upperLimit;

    // Head of the circular linked list
    Player *head = NULL;

    while (choice_1 != 2)
    {
        printf("\n\t\t\t============================================\n\t\t\t==============  Guessing Game  =============\n\t\t\t============================================");
        printf("\n\n\t1. Start Game\n\t2. Quit Game\n\n\tEnter your choice : ");
        scanf("%d", &choice_1);
        switch (choice_1)
        {
        case 1:
            printf("\n\tEnter the number of players : ");
            scanf("%d", &numberOfPlayers);
            head = createCLL(numberOfPlayers);
            playGame(head);
            break;

        case 2:
            // Exit
            printf("\n\tThank you for playing the game!\n\tQuitting the game...");
            break;

        default:
            printf("\n\tPlease enter a valid choice_1!");
            break;
        }
    }
    return 0;
}

Player *acceptInfo(int playerNumber)
{
    // Allocating memory to a pointer of type Player
    Player *player = (Player *)malloc(sizeof(struct Player));

    printf("\n\tEnter the name of the Player #%d : ", playerNumber + 1);
    player->name = (char *)malloc(100);
    scanf(" %[^\n]s", player->name); //includes space in input and removes stray \n from input buffer

    // Initializing the score to 0
    player->score = 0;

    player->next = NULL;

    return player;
}

Player *createCLL(int numberOfPlayers)
{
    Player *head = NULL;
    Player *temp = NULL;
    Player *player = NULL;
    for (int i = 0; i < numberOfPlayers; ++i)
    {
        player = acceptInfo(i);
        if (head == NULL)
        {
            head = player;
            temp = head;
        }
        else
        {
            temp->next = player;
            temp = temp->next;
        }
    }
    temp->next = head; //Circular linked list
    return head;
}

int generateRandomNumber(int lowerLimit, int upperLimit)
{
    time_t t;
    /* Intializes random number generator */
    srand((unsigned)time(&t));
    return (rand() % (upperLimit - lowerLimit + 1)) + 1;
}

void showLeaderboard(Player *head)
{
    printf("\n\tHere's what the leaderboard looks like : \n");
    printf("\n\tNo.\tName\tScore\n");
    Player *temp = head;
    int i = 0;
    do
    {
        printf("\n\t%d\t%s\t%d", ++i, temp->name, temp->score);
        temp = temp->next;
    } while (temp != head);
}

void playRound(Player *head, int roundNo)
{
    int randomNumber = generateRandomNumber(LOWER_LIMIT, UPPER_LIMIT);
    Player *temp = head;
    printf("\n\n\t\t\t================  Round #%d  ================", roundNo + 1);
    do
    {
        printf("\n\n\tIt\'s %s\'s turn : ", temp->name);
        printf("\n\t\tGuess a number between %d and %d : ", LOWER_LIMIT, UPPER_LIMIT);
        scanf("%d", &temp->guess);
        printf("\tNoted your guess %s!", temp->name);
        temp->score += abs(randomNumber - temp->guess);
        temp = temp->next;
    } while (temp != head);
    printf("\n\n\tDrum Rolls......\n\tThe number was : %d", randomNumber);
    printf("\n\n\t\t\t============= End of the Round ==============\n\n");
}

Player *getWinner(Player *head)
{
    // Score can't be negative, so assigning -1 initially
    int min_score = __INT_MAX__;
    Player *winner = NULL;
    Player *temp = head;

    do
    {
        if (temp->score < min_score)
        {
            min_score = temp->score;
            winner = temp;
        }
        temp = temp->next;
    } while (temp != head);

    return winner;
}

void playGame(Player *head)
{
    Player *winner = NULL;
    for (int i = 0; i < ROUNDS; ++i)
    {
        playRound(head, i);
        showLeaderboard(head);
    }
    winner = getWinner(head);
    printf("\n\n\tCongrats %s!!!\n\tYou've won the game with a score of %d\n\n", winner->name, winner->score);
}