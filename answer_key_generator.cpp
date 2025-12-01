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
std::string FILENAME = "answer_key_test.tex";

// Constraints on the problem choice
int NUM_PROBLEMS = 20;
int MIN_TOPIC = 3;
int MAX_TOPIC = 7;
int MIN_DIFFICULTY = 65;
int MAX_DIFFICULTY = 75;

// tex files to include in the test file 
std::string TEX_HEADER = "questions_tex_header.tex";
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
    AnswerKeyFormatter formatter(TEX_HEADER, CONTENT_HEADER, TITLE); 
    std::vector<std::shared_ptr<IProblem>> test = 
        selector.selectProblems(problemBank, NUM_PROBLEMS, constraints);

    std::ofstream outputFile(FILENAME);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    formatter.writeTest(outputFile, test);
    outputFile.close();

    std::cout << "Answer key test generated: " << FILENAME << std::endl;
    return 0;
}