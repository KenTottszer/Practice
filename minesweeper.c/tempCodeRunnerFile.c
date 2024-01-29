    // Cast the void pointers to pointers of type leaderboardEntry
    leaderboardEntry *entryA = (leaderboardEntry *)a;
    leaderboardEntry *entryB = (leaderboardEntry *)b;

    // Compare the timeTaken fields of the two entries
    if (entryA->timeTaken > entryB->timeTaken) {
        
        return 1;
    } else if (entryA->timeTaken < entryB->timeTaken) {

        return -1;
    } else {
 
        return 0;
    }