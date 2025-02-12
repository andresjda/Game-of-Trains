// Extra Credit: Personalized names, Graphics
// Names: Alex Beck & Andres August
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define HAND_SIZE 7

int drawTracker = 0;

typedef struct {
    int value;
    char action[15];
    bool protect;
} card;

typedef struct Node {
    card card;
    struct Node* next;
} Node;

Node* head = NULL; 

void printCard(card c);

void printFaceUp(Node* head);

void descending(card* hand);

void printPlayerCards(card* player);

void initializeGame(card* player1, char* p1Name, card* player2, char* p2Name, card* drawPile) ;

bool inOrder(card* player);

void addToFaceUp(card* add);

void swapAdjacent(card* player);

void move2Right(card* player, int index);

void move2Left(card* player, int index);

void swapOneBetween(card* player);

void protectCard(card* player);

void removeLeft(card* player, card* drawPile);

void removeRight(card* player, card* drawPile);

void removeMiddle(card* player, card* drawPile);

card drawCard(card* drawPile);

int main() {
    card player1[7], player2[7], faceUp[9],drawPile[84];
    char p1Name[50], p2Name[50];
    int drawTracker = 0, choiceCard;
    card tempCard1,tempCard2;

    // Initialize the cards for each player

    initializeGame(player1, p1Name, player2, p2Name, drawPile);

    // player 1 draws 1 card and replaces one card in their train with it. replaced card discarded
    printf("\n%s your hand is:\n", p1Name);
    printPlayerCards(player1);
    printf("\nDrawn card:\n");
    tempCard1 = drawCard(drawPile);
    printCard(tempCard1);
    printf("Which card would you like to replace with this one? (1-7) ");
    scanf(" %d", &choiceCard);
    addToFaceUp(&player1[choiceCard - 1]);
    player1[choiceCard - 1] = tempCard1;
    
    // player 2 draws 2 cards, discards 1 card and replaces one card in train with it
    printf("\n%s your hand is:\n", p2Name);
    printPlayerCards(player2);

    printf("\nDrawn cards:\n");
    tempCard1 = drawCard(drawPile);
    tempCard2 = drawCard(drawPile);
    printCard(tempCard1);
    printCard(tempCard2);
    printf("Which card would you like to add to your hand (1 or 2)? ");
    int kept;
    card p2kept;
    scanf("%d", &kept);
    if (kept == 1) {
        p2kept = tempCard1;
    } else {
        p2kept = tempCard2;
    }
    printCard(p2kept);
    printf("\nWhich card would you like to replace with this one (1-7)? ");
    scanf("%d", &choiceCard);
    addToFaceUp(&player2[choiceCard - 1]);
    player2[choiceCard - 1] = (kept == 1) ? tempCard1 : tempCard2;
    

    int playersTurn = 0;
    int action;
    // if a player has all their cards in order the game ends
    while (!inOrder(player1) && !inOrder(player2)) {
        if (playersTurn % 2 == 0) {
            printf("%s hand\n", p1Name);
            printPlayerCards(player1);
        } else {
            printf("%s hand\n", p2Name);
            printPlayerCards(player2);
        }
        
        // each loops represents one players turn
        while(!(action == 1 || action == 2)) {
            printFaceUp(head);
            if (playersTurn%2 == 0) {
                printf("%s would you like to draw a card (1) or use an ability (2)? ", p1Name);
            } else {
                printf("%s would you like to draw a card (1) or use an ability (2)? ", p2Name);
            }
            scanf(" %d", &action);
        }

        if (action == 1) {
            // if player draws a card they must replace a card in train
            if (playersTurn%2 == 0) {
                printf("\nDrawn card:\n");
                tempCard1 = drawCard(drawPile);
                printCard(tempCard1);
                printf("Which card would you like to replace with this one? (1-7) ");
                scanf(" %d", &choiceCard);
                addToFaceUp(&player1[choiceCard - 1]);
                player1[choiceCard - 1] = tempCard1;
            } else {
                tempCard1 = drawCard(drawPile);
                printCard(tempCard1);
                printf("Which card would you like to replace with this one? (1-7) ");
                scanf(" %d", &choiceCard);
                addToFaceUp(&player2[choiceCard - 1]);
                player2[choiceCard - 1] = tempCard1;
            }


        } else {
            // if a player uses a cards ability
            printf("Which face up card would you like to use the ability of?");
            scanf(" %d", &choiceCard);

            char ability[15];
            int count = 0;
            Node* current = head;
            while (current != NULL) {
                if (count == choiceCard-1) {
                    strcpy(ability, current->card.action);
                    addToFaceUp(&current->card);
                }
                count++;
                current = current->next;
                
            }
            if (playersTurn%2 == 0) {
                if (strcmp(ability, "shift2Right") == 0) {
                    move2Right(player1, choiceCard);
                } else if (strcmp(ability, "shift2Left") == 0) {
                    move2Left(player1, choiceCard);
                } else if (strcmp(ability, "swapAdjacent") == 0) {
                    swapAdjacent(player1);
                } else if (strcmp(ability, "removeMiddle") == 0) {
                    removeMiddle(player1, drawPile);
                } else if (strcmp(ability, "removeRight") == 0) {
                    removeRight(player1, drawPile);
                } else if (strcmp(ability, "removeLeft") == 0) {
                    removeLeft(player1, drawPile);
                } else if (strcmp(ability, "swapSkip1Card") == 0) {
                    swapOneBetween(player1);
                } else if (strcmp(ability, "protect") == 0) {
                    protectCard(player1);
                }
            } else {
                if (strcmp(ability, "shift2Right") == 0) {
                    move2Right(player2, choiceCard);
                } else if (strcmp(ability, "shift2Left") == 0) {
                    move2Left(player2, choiceCard);
                } else if (strcmp(ability, "swapAdjacent") == 0) {
                    swapAdjacent(player2);
                } else if (strcmp(ability, "removeMiddle") == 0) {
                    removeMiddle(player2, drawPile);
                } else if (strcmp(ability, "removeRight") == 0) {
                    removeRight(player2, drawPile);
                } else if (strcmp(ability, "removeLeft") == 0) {
                    removeLeft(player2, drawPile);
                } else if (strcmp(ability, "swapSkip1Card") == 0) {
                    swapOneBetween(player2);
                } else if (strcmp(ability, "protect") == 0) {
                    protectCard(player2);
                }
            }
            
        }
        playersTurn ++;
        action = 0;
    }

    return 1;
}

void printCard(card c) {
    if (c.protect) {
        printf("\n.---------------.\n|%d             |\n| Protected     |\n| %s\t|\n`---------------'", c.value, c.action);

    /*
    .---------------.
    |10             |
    | Protected     |
    |swapOneBetween |
    `---------------'
    */

    } else {
        printf(".---------------.\n|%d             |\n|               |\n| %s\t|\n`---------------'", c.value, c.action);
    }
    printf("\n");
}

void printFaceUp(Node* head) {
    Node* current = head;
    int count = 1;
    printf("Face up cards:\n");
    while (current != NULL) {
        printCard(current->card);
        current = current->next;
        count++;
    }
    printf("\n");
}

void descending(card* hand) {
    int i, j; 
    card temp;
    
    // iterates the array elements 
    for (i = 0; i < 6; i++) { 
        
        // iterates the array elements from index 1 
        for (j = i + 1; j < 7; j++) { 
            
            // comparing the array elements, to set array 
            // elements in descending order 
            if (hand[i].value < hand[j].value) { 
                temp = hand[i]; 
                hand[i] = hand[j]; 
                hand[j] = temp; 
            } 
        } 
    } 
}

void printPlayerCards(card* player) {
    printf("         _______\n  _||____|______||_\n |     Locomotive    |\n |___________________|\n( )                 ( )\n");
    /*
         _______
  _||____|______||_
 |     Locomotive    |
 |___________________|
( )                 ( )
*/
    for (int i = 0; i < HAND_SIZE; i++) {
        printCard(player[i]);
    }
    printf("\n");
}

void initializeGame(card* player1, char* p1Name, card* player2, char* p2Name, card* drawPile) { //B
    char choice;
    FILE* deckFile;
    char presetDeck[50];

    printf("Enter the name of player 1: ");
    scanf("%s", p1Name);

    printf("Enter the name of player 2: ");
    scanf("%s", p2Name);

    
    printf("Would you like to enter a preset deck of cards? (y/n)");
    scanf("%c", &choice);

    if (choice =='y' || choice == "Y") {

        printf("Enter the name of your deck file: ");
        scanf("%s", &presetDeck);
        deckFile = fopen(presetDeck, "r");
        
        while(deckFile == NULL) {
        printf("File %s does not exist. Enter the name of your deck file: ", presetDeck);
        scanf("%s", &presetDeck);
        deckFile = fopen(presetDeck, "r");
        }
    } else {
        // generate the deck of cards
        int index = 0;
        for (int i = 1; i <= 84; i++) {
            card newCard;
            newCard.value = i;
            strcpy(newCard.action, "");
            newCard.protect = false;
            
            // assign actions
            switch (index % 8) {
                case 0:
                    strcpy(newCard.action, "shift2Right");
                    break;
                case 1:
                    strcpy(newCard.action, "protect");
                    break;
                case 2:
                    strcpy(newCard.action, "shift2Left");
                    break;
                case 3:
                    strcpy(newCard.action, "swapAdjacent");
                    break;
                case 4:
                    strcpy(newCard.action, "removeMiddle");
                    break;
                case 5:
                    strcpy(newCard.action, "removeRight");
                    break;
                case 6:
                    strcpy(newCard.action, "removeLeft");
                    break;
                case 7:
                    strcpy(newCard.action, "swapSkip1Card");
                    break;
            }
            
            drawPile[index] = newCard;
            index++;
        }
        
        // shuffle the deck
        srand((unsigned int) time(NULL));
        
        for (int i = 0; i < 84; i++) {
            int j = rand() % 84;
            card temp = drawPile[i];
            drawPile[i] = drawPile[j];
            drawPile[j] = temp;
        }
    }

    for(int i = 0; i < 7*2; i ++) {
        if(i < 7) {
            player1[i] = drawPile[i];
            drawTracker++;
        } else {
            player2[i-7]= drawPile[i];
            drawTracker++;
        }
    }

    descending(player1);
    descending(player2);
}

bool inOrder(card* player) {
    for (int i = 0; i < HAND_SIZE - 1; i++) {
        if (player[i].value > player[i + 1].value) {
            return false;
        }
    }
    return true;
}

void addToFaceUp(card* add) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->card = *add;
    newNode->next = NULL;

    Node* curr = head;
    Node* prev = NULL;
    bool duplicate = false;

    // check for duplicate action
    while (curr != NULL) {
        if (strcmp(curr->card.action, add->action) == 0) {
            if (prev == NULL) {
                head = curr->next;
                free(curr);
                curr = head;
            } else {
                prev->next = curr->next;
                free(curr);
                curr = prev->next;
            }
            duplicate = true;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

// if card is no duplicate add to face up
    if (!duplicate) {
        if (head == NULL) {
            head = newNode;
        } else {
            Node* last = head;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = newNode;
        }
    }
}

void swapAdjacent(card* player) {
    int index = 0;

    printf("Enter the index of the leftmost card you want to swap: ");
    scanf("%d", &index);

    while (index < 0 || index > 5){
        printf("No card available to swap with the selected card. Select a new card: ");
        scanf("%d", &index);
    }
    
    card temp = player[index];
    player[index] = player[index+1];
    player[index+1] = temp;

    
}

void move2Right(card* player, int index) {
    // moves card at index 2 spaces right
    int goodIndex = 0; //track if the index is valid

    while (!goodIndex) { // Loop until a valid index is entered
        printf("Enter the index of the card you want to move 2 spaces to the right: ");
        scanf("%d", &index);

        if (index >= 0 && index <= 5) { 
            goodIndex = 1; // Set true
            card temp = player[index];
            player[index] = player[index + 2];
            player[index + 2] = temp;
        } else {
            printf("Card you selected is unable to move right 2 spaces. Enter a different card index: ");
        }
    }
}

void move2Left(card* player, int index) {
    // moves card at index 2 spaces left
    int goodIndex = 0; //track if the index is valid

    while (!goodIndex) { // Loop until a valid index is entered
        printf("Enter the index of the card you want to move 2 spaces to the left: ");
        scanf("%d", &index);

        if (index >= 2 && index <= 7) { 
            goodIndex = 1; // Set true
            card temp = player[index];
            player[index] = player[index - 2];
            player[index - 2] = temp;
        } else {
            printf("Card you selected is unable to move left 2 spaces. Enter a different card index: ");
        }
    }
}

void swapOneBetween(card* player) {
    int index1, index2;
    // swap the card at index1 with the card at index2
    printf("Enter the indexes of the cards you want to swap from left to right"); 
    scanf("%d %d", &index1, &index2);

if (0 <= index1 && index1 <= 7 &&  0 <= index2 && index2 <= 7){
        card temp;
    temp = player[index1];
    player[index1] = player[index2];
    player[index2] = temp;
    } else {
        printf("Please enter 2 valid indexes to swap: ");
        scanf("%d %d", &index1, &index2);
}}

void protectCard(card* player) {
    // protect card at index
    int index;
    printf("Which card from your hand would you like to protect? ");
    scanf("%d", &index);
    player[index-1].protect = true;
}

void removeLeft(card* player, card* drawPile) {
    // removes leftmost card
    player[0] = drawCard(drawPile);
}

void removeRight(card* player, card* drawPile) {
    // removes rightmost card
    player[6] = drawCard(drawPile);
}

void removeMiddle(card* player, card* drawPile) {
    // removes middle card
    player[4] = drawCard(drawPile);
}

card drawCard(card* drawPile) { // draw a card from the draw pile
    int replace;

    drawTracker++;
    return drawPile[drawTracker];
    
}