#include <iostream>
#include <vector>
using namespace std;

// Global variable to store the initial power of Abhimanyu
int basePower;

// Recursive function with memoization to check if Abhimanyu can pass through the Chakravyuha
bool isAbleToCross(int idx, int &numCircles, vector<int> &foes, int currentPower, 
                    int skipsRemaining, int rechargesRemaining, vector<vector<vector<vector<int>>>> &memo) {
    
    // If all circles are cleared
    if (idx == numCircles) {
        return (currentPower >= 0);
    }

    // Return cached result if the state has been computed before
    if (memo[idx][currentPower][skipsRemaining][rechargesRemaining] != -1) {
        return memo[idx][currentPower][skipsRemaining][rechargesRemaining];
    }

    bool result = false;

    // Case where Abhimanyu defeats the enemy in the current circle
    if (currentPower >= foes[idx]) {
        result |= isAbleToCross(idx + 1, numCircles, foes, currentPower - foes[idx], skipsRemaining, rechargesRemaining, memo);
    }

    // Special condition: enemies in specific circles have regenerative properties
    if (idx == 2 || idx == 6) {
        foes[idx + 1] += foes[idx] / 2;
    }

    // Case where Abhimanyu skips the current enemy
    if (skipsRemaining > 0) {
        result |= isAbleToCross(idx + 1, numCircles, foes, currentPower, skipsRemaining - 1, rechargesRemaining, memo);
    }

    // Case where Abhimanyu recharges his power to the initial value
    if (rechargesRemaining > 0) {
        currentPower = basePower;
        result |= isAbleToCross(idx + 1, numCircles, foes, currentPower, skipsRemaining, rechargesRemaining - 1, memo);
    }

    // Store and return the result for this state
    return memo[idx][currentPower][skipsRemaining][rechargesRemaining] = result;
}

// Function to process each test case
void processTestCase() {
    int numCircles = 11, powerLevel, skipCount, rechargeCount;
    
    // Input: power level, number of skips, and number of recharges
    cin >> powerLevel >> skipCount >> rechargeCount;
    basePower = powerLevel;
    
    vector<int> foes(numCircles, 0);

    // Input: power level of enemies in each of the 11 circles
    for (int i = 0; i < numCircles; i++) {
        cin >> foes[i];
    }

    // DP table for memoization
    vector<vector<vector<vector<int>>>> memo(12, vector<vector<vector<int>>>(205, vector<vector<int>>(20, vector<int>(20, -1))));

    // Check if Abhimanyu can cross the Chakravyuha
    bool success = isAbleToCross(0, numCircles, foes, powerLevel, skipCount, rechargeCount, memo);
    
    if (success) {
        cout << "Abhimanyu can cross the Chakravyuh: WIN" << endl;
    } else {
        cout << "Abhimanyu cannot cross the Chakravyuh: LOST" << endl;
    }
}

// Main function
int main() {
    int t;
    // Input: number of test cases
    cin >> t;
    while (t--) {
        processTestCase();
    }
    return 0;
}
