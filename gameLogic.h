//
// created by Sebastian Carter
//



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


// for setting items, have an items array, add 1 to a total num items counter and then random number generate until you get
// a number that isnt associated with any items or you have hit like 4 items i think it should max out at 4
void setItems(int arrayItems[]) {
    int itemToAdd;
    int addedItems;
    arrayItems[0] = 0;
    arrayItems[1] = 0;
    arrayItems[2] = 0;
    arrayItems[3] = 0;
    arrayItems[4] = 0;

    addedItems = 0;
    itemToAdd = rand() % 6;
    while (itemToAdd != 5 && addedItems < 4) {
        /*
        // for debugging only
        if(itemToAdd == 0){
            printf("Beer!\n");
        }else if(itemToAdd == 1){
            printf("Spyglass!\n");
        }else if(itemToAdd == 2){
            printf("cigarette!\n");
        }else if(itemToAdd == 3){
            printf("cuffs!\n");
        }else if(itemToAdd == 4){
            printf("saw\n");
        }
        */
        arrayItems[itemToAdd] += 1;
        itemToAdd = rand() % 6;
        addedItems += 1;
    }
}


int dealerLogic(struct shotgun gun, int *currentShell, int *Health, int itemArray[]){
    // should know what the final shell is
    // should use the spyglass immediately and make the right choice unless its the last shell
    // should heal when possible
    // should use cuffs when possible
    // should drink beer unless spyglass is available
    // no using the same thing twice
    // put the stuff that wouldn't result in an action being made first

    // handling cigarettes
    while(itemArray[2] > 0 && *Health < 4){
        itemArray[2] -= 1;
        *Health = *Health + 1;
        printf("The dealer smokes a cigarette\n");
        printf("His health is now %d\n", *Health);
        sleep(2);
        clearScreen();
    }


    // beer logic
    // if you have a beer and you do not have a spyglass or there are 2 shells left (you can have a spyglass in this case)
    // oh yeah also if its the last round in the gun, don't drink a beer
    if(itemArray[0] > 0 && (itemArray[1] < 1 || (*currentShell + 2) == gun.length)){
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






