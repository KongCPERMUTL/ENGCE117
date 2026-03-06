#include <stdio.h>

#define MINIMUM_DISC_LIMIT 1
#define DEFAULT_START_PEG 1
#define DEFAULT_TEMP_PEG 2
#define DEFAULT_END_PEG 3
#define TOTAL_DISC_AMOUNT 3

void ExecuteRingTransfer(int ringCount, int sourcePole, int auxPole, int targetPole) {
    if (ringCount < MINIMUM_DISC_LIMIT) {
        return;
    }

    if (ringCount == MINIMUM_DISC_LIMIT) {
        printf("Disc %d from %d to %d\n", MINIMUM_DISC_LIMIT, sourcePole, targetPole);
        return;
    }

    int nextRingLevel;
    nextRingLevel = ringCount - MINIMUM_DISC_LIMIT;

    ExecuteRingTransfer(nextRingLevel, sourcePole, targetPole, auxPole);

    printf("Disc %d from %d to %d\n", ringCount, sourcePole, targetPole);

    ExecuteRingTransfer(nextRingLevel, auxPole, sourcePole, targetPole);
}

int main() {
    int discAmount;
    int startPeg;
    int tempPeg;
    int endPeg;

    discAmount = TOTAL_DISC_AMOUNT;
    startPeg = DEFAULT_START_PEG;
    tempPeg = DEFAULT_TEMP_PEG;
    endPeg = DEFAULT_END_PEG;

    ExecuteRingTransfer(discAmount, startPeg, tempPeg, endPeg);

    return 0;
}