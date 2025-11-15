#include "selector.h"
#include <algorithm>
#include <random>

std::vector<std::shared_ptr<IProblem>> ShuffleSelector::selectProblems(
    std::vector<std::shared_ptr<IProblem>>& bank,
    int numProblems,
    std::vector<std::shared_ptr<IConstraint>>& constraints) {
    
    std::random_device rd;
    std::mt19937 gen(rd());

    while (true) {
        std::shuffle(bank.begin(), bank.end(), gen);
        std::vector<std::shared_ptr<IProblem>> selected(bank.begin(), bank.begin() + numProblems);
        
        bool allSatisfied = true;
        for (auto& constraint : constraints) {
            if (!constraint->isSatisfied(selected)) {
                allSatisfied = false;
                break;
            }
        }
        
        if (allSatisfied) {
            return selected;
        }
    }
}