#include "ShiftScheduling.h"
#include "vector.h"
#include "error.h"
using namespace std;

Set<Shift> bestSchedule;
int bestProfit = 0;

void recurse(Vector<Shift>& shifts, int index, int remainingHours, Set<Shift>& chosen, int currentProfit) {
    if (index == shifts.size()) {
        if (currentProfit > bestProfit) {
            bestProfit = currentProfit;
            bestSchedule = chosen;
        }
        return;
    }

    Shift current = shifts[index];

    bool overlaps = false;
    for (const Shift& s : chosen) {
        if (overlapsWith(s, current)) {
            overlaps = true;
            break;
        }
    }

    int shiftLen = lengthOf(current);
    if (!overlaps && shiftLen <= remainingHours) {
        chosen += current;
        recurse(shifts, index + 1, remainingHours - shiftLen, chosen, currentProfit + profitFor(current));
        chosen -= current;
    }

    recurse(shifts, index + 1, remainingHours, chosen, currentProfit);
}

Set<Shift> maxProfitSchedule(const Set<Shift>& shifts, int maxHours) {
    if (maxHours < 0) {
        error("maxHours must not be negative.");
    }

    Vector<Shift> allShifts;
    for (const Shift& s : shifts) {
        allShifts += s;
    }

    Set<Shift> chosen;
    bestSchedule = {};
    bestProfit = 0;
    recurse(allShifts, 0, maxHours, chosen, 0);
    return bestSchedule;
}

