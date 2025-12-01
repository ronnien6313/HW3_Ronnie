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

// Variable information to be printed on the test
std::string CLASS = "Math";
std::string TERM = "Fall 2025";
std::string EXAM = "Final";
std::string TIME = "Day";
std::string TITLE = "Final Exam";
std::string FORM = "A";

// Source file for problem bank
std::string BANK = "math_problems.tex";
std::string FILENAME = "topic_author_length_test.tex";

// Constraints on the problem choice
int NUM_PROBLEMS = 10;
int MIN_AUTHOR = 1;
int MAX_AUTHOR = 2;
int MIN_TOPIC = 1;
int MAX_TOPIC = 2;
int MIN_LONG = 3;
int MAX_LONG = 4;

// tex files to include in the test file
std::string TEX_HEADER = "fancy_tex_header.tex";
std::string CONTENT_HEADER = "fancy_content_header.tex";

// ****************************************************************************

int main() {

    std::vector<TopicAuthorLengthProblem> rawProblems = 
        TopicAuthorLengthProblem::problemList(BANK);
    

    std::vector<std::shared_ptr<IProblem>> problemBank;
    for (auto& p : rawProblems) {
        problemBank.push_back(std::make_shared<TopicAuthorLengthProblem>(p));
    }


    std::set<std::string> topics;
    std::set<std::string> authors;
    for (const auto& p : rawProblems) {
        topics.insert(p.getTopic());
        authors.insert(p.getAuthor());
    }
    std::vector<std::string> topicsVec(topics.begin(), topics.end());
    std::vector<std::string> authorsVec(authors.begin(), authors.end());


    std::vector<std::shared_ptr<IConstraint>> constraints;
    for (const std::string& author : authors) {
        constraints.push_back(
            std::make_shared<AuthorConstraint>(author, MIN_AUTHOR, MAX_AUTHOR)
        );
    }

    for (const std::string& topic : topics) {
        constraints.push_back(
            std::make_shared<TopicConstraint>(topic, MIN_TOPIC, MAX_TOPIC)
        );
    }

    constraints.push_back(
        std::make_shared<LongProblemConstraint>(MIN_LONG, MAX_LONG)
    );

 
    NewSelector selector;
    LongProblemFormatter formatter(TEX_HEADER, CONTENT_HEADER, CLASS, TERM, EXAM, 
                                   TIME, FORM, NUM_PROBLEMS, TITLE);
    
    std::vector<std::shared_ptr<IProblem>> test = 
        selector.selectProblems(problemBank, NUM_PROBLEMS, constraints);
    std::ofstream outputFile(FILENAME);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    formatter.writeTest(outputFile, test);
    outputFile.close();

    std::cout << "Topic/Author/Length test generated: " << FILENAME << std::endl;
    return 0;
}