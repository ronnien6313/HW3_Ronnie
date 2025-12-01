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

std::vector<std::shared_ptr<IProblem>> NewSelector::selectProblems(
    std::vector<std::shared_ptr<IProblem>>& bank,
    int numProblems,
    std::vector<std::shared_ptr<IConstraint>>& constraints) {
    
    std::random_device rd;
    std::mt19937 gen(rd());

    while (true) {
        std::shuffle(bank.begin(), bank.end(), gen);
        std::vector<std::shared_ptr<IProblem>> selected;

        for (const auto& problem : bank) {
            if (selected.size() >= numProblems) {
                break;  
            }

            selected.push_back(problem);

            bool exceedsM = false;
            for (auto& constraint : constraints) {
                if (constraint->exceedsMax(selected)) {
                    exceedsM = true;
                    break;
                }
            }
            if (exceedsM) {
                selected.pop_back();
            }
        }

        if (selected.size() == numProblems) {
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
}