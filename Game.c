// For input and output (contains printf and scanf)
#include <stdio.h>
// Includes NULL, malloc, abs, rand and srand definitions
#include <stdlib.h>
// time_t stores calendar time
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
void playGame(Player *head, int numberOfPlayers);

//Returns Winners with same score
Player **getWinners(Player *head, Player **winners, Player *winner, int *NoOfWinners);

int main()
{
    system("COLOR 0B");
    // Choice for first switch case
    int choice_1 = -1;

    int numberOfPlayers;

    // Head of the circular linked list
    Player *head = NULL;

    while (choice_1 != 3)
    {
        printf("\n\t\t\t============================================\n\t\t\t==============  Guessing Game  =============\n\t\t\t============================================");
        printf("\n\n\t1. Start Game\n\t2. All About rules of Game\n\t3. Quit Game\n\n\tEnter your choice : ");
        scanf("%d", &choice_1);
        switch (choice_1)
        {
        case 1:
            do
            {
                printf("\n\tEnter the number of players : ");
                scanf("%d", &numberOfPlayers);
                if (numberOfPlayers < 2) //checking for minimum no. of players
                {
                    printf("\n\n\tMinimum Number of players should be 2.\n\n");
                }
            } while (numberOfPlayers < 2);
            head = createCLL(numberOfPlayers);
            playGame(head, numberOfPlayers);
            break;
        case 2:
            // All About game !!
            printf("\n\tHey players..Nice to see u all !!\n\tThe rules of the game are quite simple:-\n");
            printf("\n\t* This game will generate number in range 1...10 in each round.");
            printf("\n\t* Every player should guess the number.");
            printf("\n\t* Any numbers of player can play the game(Atleat 2 players).");
            printf("\n\t* Each player will play 4 rounds in total.");
            printf("\n\t* In each round all players will get chance to guess \n\t  the random generated number one by one.");
            printf("\n\t* After every round, score board will be displayed.");
            printf("\n\t* At the end of game final leaderboard will be shown  \n\t  and the winner will be announced.");
            printf("\n\t* There can be more than one winner in case of \n\t  tie score between the players.\n");
            printf("\n\tALL THE BEST !! We Hope you will enjoy the game !!\n\n");
            break;
        case 3:
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

Player *acceptInfo(int playerNumber) // Get Player's Information
{
    // Allocating memory to a pointer of type Player
    Player *player = (Player *)malloc(sizeof(struct Player));

    printf("\n\tPlayer #%d : ", playerNumber + 1);
    player->name = (char *)malloc(100 * sizeof(char));
    scanf(" %[^\n]s", player->name); //includes space in input and removes stray \n from input buffer

    // Initializing the score to 0
    player->score = 0;

    player->next = NULL;

    return player;
}

Player *createCLL(int numberOfPlayers) // Create a circular linked list based on the number of players playing the game
{
    Player *head = NULL;
    Player *temp = NULL;
    Player *player = NULL;
    printf("\n\tEnter the name of all Players :-\n");
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

int generateRandomNumber(int lowerLimit, int upperLimit) // Returns the random number within the given range
{
    time_t t;
    /* Intializes random number generator */
    srand((unsigned)time(&t));
    return (rand() % (upperLimit - lowerLimit + 1)) + 1;
}

void showLeaderboard(Player *head) // To display the leaderboard after each roundNo
{
    printf("\n\tHere's what the leaderboard looks like : \n");
    printf("\n\tNo.\tName \tScore\n");
    Player *temp = head;
    int i = 0;
    do
    {
        printf("\n\t%d\t%s\t%d", ++i, temp->name, temp->score);
        temp = temp->next;
    } while (temp != head);
}

void playRound(Player *head, int roundNo) // Called on each round
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

Player *getWinner(Player *head) // Returns the winner at the end of the game
{
    // Score can't be negative, so assigning Maximum value initially
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

Player **getWinners(Player *head, Player **winners, Player *winner, int *NoOfWinners) //Returns Winners with same score
{
    Player *temp = head;
    do
    {
        if (winner->score == temp->score)
        {
            winners[(*NoOfWinners)++] = temp;
        }
        temp = temp->next;
    } while (temp != head);
    return winners;
}
void playGame(Player *head, int numberOfPlayers) // Root function to start the game
{
    Player *winner = NULL;
    Player **winners = (Player **)malloc(numberOfPlayers * sizeof(Player *));
    for (int i = 0; i < ROUNDS; ++i)
    {
        playRound(head, i);
        showLeaderboard(head);
    }
    winner = getWinner(head);
    int NoOfWinners = 0;
    winners = getWinners(head, winners, winner, &NoOfWinners);
    printf("\n\n\tNote :  Less the score ...more accurate was your guess !!");
    printf("\n\n\tTotal Winners are: %d\n\n", NoOfWinners);
    for (int w = 0; w < NoOfWinners; w++)
    {
        printf("\n\n\tCongrats %s !!!\n\tYou're the Winner with a score of %d\n\n", winners[w]->name, winners[w]->score);
    }
}
