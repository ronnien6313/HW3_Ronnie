#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <set>
#include "problem.h"
#include "constraint.h"
#include "selector.h"
#include "formatter.h"

// ****************************************************************************
// Configuration details

// Title to be printed at the beginning of the test
std::string TITLE = "Arithmetic Test";

// Source file for problem bank
std::string BANK = "arithmetic_problems.tex";

// Filename for the created test
std::string FILENAME = "simple_test.tex";

// Constraints on the problem choice
int NUM_PROBLEMS = 20; // The test must have 20 problems
int MIN_TOPIC = 3; // Each topic must be covered
int MAX_TOPIC = 7; // by 3-7 problems
int MIN_DIFFICULTY = 65; // Total difficulty (using the difficulty defined
int MAX_DIFFICULTY = 75; // in the problem bank) must be 65-75

// tex files to include in the test file
std::string TEX_HEADER = "simple_tex_header.tex";
std::string CONTENT_HEADER = "simple_content_header.tex";

// ****************************************************************************

int main() {
    std::vector<TopicDifficultyProblem> rawProblems = 
        TopicDifficultyProblem::problemList(BANK);
    
    std::vector<std::shared_ptr<IProblem>> problemBank;
    for (auto& p : rawProblems) {
        problemBank.push_back(std::make_shared<TopicDifficultyProblem>(p));
    }

    std::set<std::string> topics;
    for (const auto& p : rawProblems) {
        topics.insert(p.getTopic());
    }

    std::vector<std::shared_ptr<IConstraint>> constraints;
    constraints.push_back(
        std::make_shared<DifficultyConstraint>(MIN_DIFFICULTY, MAX_DIFFICULTY)
    );
    for (const std::string& topic : topics) {
        constraints.push_back(
            std::make_shared<TopicConstraint>(topic, MIN_TOPIC, MAX_TOPIC)
        );
    }


    ShuffleSelector selector;
    SimpleFormatter formatter(TEX_HEADER, CONTENT_HEADER, TITLE);
    std::vector<std::shared_ptr<IProblem>> test = 
        selector.selectProblems(problemBank, NUM_PROBLEMS, constraints);


    std::ofstream outputFile(FILENAME);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    formatter.writeTest(outputFile, test);
    outputFile.close();

    std::cout << "Test generated: " << FILENAME << std::endl;
    return 0;
}