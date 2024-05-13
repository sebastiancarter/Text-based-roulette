#include "utils.h"
#include "items.h"
#include "gameLogic.h"


int main() {
    int playerLife, 
        enemyLife, 
        currShell, 
        input, 
        dealerChoice, 
        playerItemArray[5], 
        enemyItemArray[5],
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
                        printf("You have %d beers, %d spyglasses, %d ciggies %d handcuffs and %d saws\n", playerItemArray[0],
                               playerItemArray[1], playerItemArray[2], playerItemArray[3], playerItemArray[4]);
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
                        if (playerItemArray[4] > 0) {
                            printf("7. use a saw\n");
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
                        }else if (input == 7 && playerItemArray[4] > 0) {
                            playerItemArray[4] -= 1;
                            saw(&gameGun, currShell);
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
                            if (gameGun.shells[currShell - 1] >= 1) {
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
                // if the enemy is still cuffed, skip the enemy turn
                if (enemyCuffed > 0) {
                    printf("The dealer is cuffed, his turn is skipped\n");
                    enemyCuffed -= 1;
                    sleep(2);
                    clearScreen();
                    continue;
                }
                dealerChoice = dealerLogic(gameGun, &currShell, &enemyLife,  enemyItemArray);
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

