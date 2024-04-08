#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#if defined(_WIN32) || defined(__CYGWIN__)
// Windows (x86 or x64)
#include <windows.h>
void clearScreen(){
    system("cls");
}
#else
// linux or unix based OS
#include <unistd.h>
void clearScreen() {
    system("clear");
}
#endif


struct shotgun {
    int shells[8];
    int length;
};


void spyGlass(struct shotgun *gun, int currRound) {
    printf("You pick up the shotgun and rack the slide a little, just to see that...\n");
    sleep(2);
    printf("The next round is");
    if (gun->shells[currRound] == 1) {
        printf(" LIVE!\n");
    } else {
        printf(" BLANK!\n");
    }
    sleep(2);
    clearScreen();
}


void drinkBeer(struct shotgun *gun, int *currRound) {
    printf("GLUGGLUGGLUGGLUGGLUG\n");
    printf("You snatch the gun off of the table and \n");
    sleep(2);
    printf("CHICKA CHICKA\n");
    printf("Pump the action!\n");
    sleep(2);
    if (gun->shells[*currRound] == 1) {
        printf("A live");
    } else {
        printf("A blank");
    }
    printf(" round goes flying out onto the ground!\n");
    sleep(2);
    clearScreen();
    *currRound += 1;
}

void smokeCig(int *health) {
    printf("You grab your carton of cigarrettes and pull one out\n");
    printf("CLICK, CLICK, CLI-FWOOSH\n");
    printf("You bring your lighter to the cigarette and inhale deep!\n");
    if(*health < 4){
        *health += 1;
        printf("Your health is now %d\n", *health);
    }else{
        printf("You are already at max health, no change!");
    }
    sleep(2);
    clearScreen();
}


int dealerLogic(struct shotgun gun, int *currentShell, int *enemyHealth, int itemArray[]){
    // should know what the final shell is
    // should use the spyglass immediately and make the right choice unless its the last shell
    // should heal when possible
    // should use cuffs when possible
    // should drink beer unless spyglass is available
    // no using the same thing twice
    // put the stuff that wouldn't result in an action being made first

    // handling cigarettes
    while(itemArray[2] > 0 && *enemyHealth < 4){
        itemArray[2] -= 1;
        *enemyHealth += 1;
        printf("The dealer smokes a cigarette\n");
        printf("His health is now %d\n", *enemyHealth);
        sleep(2);
        clearScreen();
    }


    // beer logic
    // if you have a beer and you do not have a spyglass or there are 2 shells left (you can have a spyglass in this case)
    // oh yeah also if its the last round in the gun, don't drink a beer
    if(itemArray[0] > 0 && (itemArray[1] < 1 || (*currentShell + 2) == gun.length) || *currentShell == (gun.length -1)){
        itemArray[0] -= 1;
        printf("The dealer drinks a beer!, he ejects a ");
        sleep(2);
        if(gun.shells[*currentShell] == 0){
            printf("BLANK round!\n");
        }else{
            printf("LIVE round!\n");
        }
        *currentShell += 1;
        printf("he has %d beers left!\n", itemArray[0]);
    }


    // return item uses (basically the dealer's logic

    // normal logic for last shell in the gun
    if(*currentShell == (gun.length - 1)){
        if(gun.shells[*currentShell] == 0){
            // dealer shoots himself
            return 1;
        }else{
            // shoots you
            return 0;
        }
    }
        
    
    // spyglass logic
    if(itemArray[1] > 0){
        itemArray[1] -= 1;
        printf("The dealer uses a spyglass!\nHe has %d spyglasses left!\n", itemArray[1]);
        sleep(2);
        clearScreen();
        if(gun.shells[*currentShell] == 0){
            // dealer shoots himself
            return 1;
        }else{
            // shoots you
            return 0;
        }
    }

    // finally, if this dude has no items that will effect his decision
    return rand()%2;


} 


// for setting items, have an items array, add 1 to a total num items counter and then random number generate until you get
// a number that isnt associated with any items or you have hit like 4 items i think it should max out at 4
void setItems(int arrayItems[]) {
    int itemToAdd;
    int addedItems;
    arrayItems[0] = 0;
    arrayItems[1] = 0;
    arrayItems[2] = 0;
    arrayItems[3] = 0;

    addedItems = 0;
    itemToAdd = rand() % 5;
    while (itemToAdd != 4 && addedItems < 4) {
        if(itemToAdd == 0){
            printf("Beer!\n");
        }else if(itemToAdd == 1){
            printf("Spyglass!\n");
        }else if(itemToAdd == 2){
            printf("cigarette!\n");
        }else if(itemToAdd == 3){
            printf("cuffs!\n");
        }
        arrayItems[itemToAdd] += 1;
        itemToAdd = rand() % 4;
        addedItems += 1;
    }
}



void loadGun(struct shotgun *gun) {
    int loader, arrSize, live, blank;
    // loading the first 2 shells (should always have at least 2 shells) 
    gun->shells[0] = rand() % 2;
    gun->shells[1] = rand() % 2;
    arrSize = 2;

    live = 0;
    blank = 0;
    if (gun->shells[0] == 1) {
        live += 1;
    } else {
        blank += 1;
    }
    if (gun->shells[1] == 1) {
        live += 1;
    } else {
        blank += 1;
    }

    // initializing loader
    loader = 0;
    while (loader != 2) {
        loader = rand() % 3;
        if (loader == 2) {
            continue;
        } else if (arrSize == 8) {
            break;
        } else {
            if (loader == 1) {
                live += 1;
            } else {
                blank += 1;
            }
            gun->shells[arrSize] = loader;
            arrSize += 1;
        }
    }
    // if no live rounds, add 1 in a random spot and take away a blank or vice versa for no blanks
    if (live < 1) {
        live += 1;
        blank -= 1;
        gun->shells[rand() % arrSize] = 1;
    } else if (blank < 1) {
        live -= 1;
        blank += 1;
        gun->shells[rand() % arrSize] = 0;
    }


    gun->length = arrSize;
    printf("%d live rounds loaded\n", live);
    printf("%d blank rounds loaded\n", blank);
    sleep(2);
}


int main() {
    int playerLife, 
        enemyLife, 
        currShell, 
        input, 
        dealerChoice, 
        playerItemArray[4], 
        enemyItemArray[4],
        score, 
        enemyCuffed, 
        skipTurn;
    char doubleRNothin;
    struct shotgun gameGun;

    score = 0;
    doubleRNothin = 'n';

    srand(time(NULL));
    clearScreen();
    do {
        playerLife = 4;
        enemyLife = 4;

        while (playerLife > 0 && enemyLife > 0) {
            skipTurn = 0;
            enemyCuffed = 0;
            currShell = 0;
            loadGun(&gameGun);
            setItems(playerItemArray);
            setItems(enemyItemArray);
            while (playerLife > 0 && enemyLife > 0 && gameGun.length > currShell) {
                sleep(2);
                clearScreen();
                // PLAYER TURN
                // resetting input
                input = 0;
                //TODO: really need to make this a function, this looks awful
                if (skipTurn == 0) {
                    while (input > 2 || input < 1) {
                        printf("You have %d beers, %d spyglasses, %d ciggies and %d handcuffs\n", playerItemArray[0],
                               playerItemArray[1], playerItemArray[2], playerItemArray[3]);
                        printf("there are %d shells\n", (gameGun.length - currShell));
                        printf("you have %d life\n", playerLife);
                        printf("the dealer has %d life\n", enemyLife);
                        printf("what would you like to do?\n");
                        printf("1. shoot the enemy\n");
                        printf("2. shoot yourself\n");
                        if (playerItemArray[0] > 0) {
                            printf("3. drink a beer\n");
                        }
                        if (playerItemArray[1] > 0) {
                            printf("4. use a spyglass\n");
                        }
                        if (playerItemArray[2] > 0) {
                            printf("5. smoke a marlboro\n");
                        }
                        if (playerItemArray[3] > 0 && enemyCuffed == 0) {
                            printf("6. cuff the dealer\n");
                        }

                        // using items
                        scanf("%d", &input);
                        if (input == 3 && playerItemArray[0] > 0) {
                            playerItemArray[0] -= 1;
                            drinkBeer(&gameGun, &currShell);
                        } else if (input == 4 && playerItemArray[1] > 0) {
                            playerItemArray[1] -= 1;
                            spyGlass(&gameGun, currShell);
                        } else if (input == 5 && playerItemArray[2] > 0) {
                            playerItemArray[2] -= 1;
                            smokeCig(&playerLife);
                        } else if (input == 6 && playerItemArray[3] > 0 && enemyCuffed == 0) {
                            // maybe will make this into a function later, but for now this works
                            playerItemArray[3] -= 1;
                            // cuff him for 2 turns
                            enemyCuffed = 2;
                            printf("You put the enemy into handcuffs!, he can't move for a few turns!\n");
                            sleep(2);
                            clearScreen();
                        }
                    }

                    // have to check if drinking a beer has ejected the last shell
                    if (currShell == gameGun.length) {
                        continue;
                    }

                    clearScreen();
                    printf("you nervously squeeze the trigger...\n");
                    sleep(2);
                    switch (input) {
                        case 1: {
                            enemyLife -= gameGun.shells[currShell];
                            currShell += 1;
                            if (gameGun.shells[currShell - 1] == 1) {
                                printf("BANG! The shotgun blows a massive hole in the dealers face\n");
                                score += 100;
                            } else {
                                printf("CLICK...\n");
                            }
                            break;
                        }
                        case 2: {
                            playerLife -= gameGun.shells[currShell];
                            currShell += 1;
                            if (gameGun.shells[currShell - 1] == 1) {
                                printf("BANG! You see a flash and then nothing...\n");
                            } else {
                                printf("CLICK...\n");
                                score += 200;
                                continue;
                            }
                            break;
                        }
                        default:
                            continue;
                    }

                } else {
                    // if your turn is being skipped
                    printf("Your turn is skipped!\n");
                    skipTurn -= 1;
                }




                // handling if you kill yourself or the enemy or use all the shells
                if (currShell == gameGun.length || playerLife < 1 || enemyLife < 1) {
                    break;
                }
                sleep(2);

                clearScreen();
                // DEALER TURN
                // TODO: make the dealer skip your turn if he manages to not kill himself
                // if the enemy is still cuffed, skip the enemy turn
                if (enemyCuffed > 0) {
                    printf("The dealer is cuffed, his turn is skipped\n");
                    enemyCuffed -= 1;
                    sleep(2);
                    clearScreen();
                    continue;
                }
                dealerChoice = dealerLogic(gameGun, &enemyLife, &currShell, enemyItemArray);
                printf("the dealer picks up the gun...\n");
                sleep(2);
                clearScreen();
                switch (dealerChoice) {
                    case 0: {
                        printf("and turns it on you!\n");
                        sleep(2);
                        clearScreen();
                        printf("You watch, paralyzed in fear as his arms tense up and...\n");
                        sleep(4);
                        clearScreen();
                        playerLife -= gameGun.shells[currShell];
                        currShell += 1;
                        if (gameGun.shells[currShell - 1] == 1) {
                            printf("BANG! you see a flash, and then nothing!\n");
                        } else {
                            printf("CLICK...\n");
                        }
                        break;
                    }
                    case 1: {
                        printf("and turns it on himself!\n");
                        sleep(2);
                        clearScreen();
                        printf("You watch, paralyzed in fear as his arms tense up and...\n");
                        sleep(4);
                        clearScreen();
                        enemyLife -= gameGun.shells[currShell];
                        currShell += 1;
                        if (gameGun.shells[currShell - 1] == 1) {
                            printf("BANG! you see a flash, and see his brains fly all over the room!\n");
                        } else {
                            printf("CLICK...\n");
                            skipTurn = 1;
                        }
                        break;
                    }

                }
            }
            sleep(2);
            clearScreen();
            printf("ROUND OVER\n");
            sleep(2);
            clearScreen();
        }
        if (playerLife < 1) {
            printf("YOU LOSE\n");
            if (doubleRNothin == 'y') {
                doubleRNothin = 'n';
                score = 0;
            }
        } else {
            printf("YOU WIN!\n");
            score += 1000;

            printf("your current score is %d\n", score);
            printf("double or nothing? (y/n): ");
            scanf(" %c", &doubleRNothin);
            // one could argue this isn't technically double or nothing lol
            if (doubleRNothin == 'y') {
                score = score * 2;
            }
        }
    } while (doubleRNothin == 'y');

    printf("your final score is: %d\n", score);
    printf("Thank you for playing!");
    return EXIT_SUCCESS;

}

