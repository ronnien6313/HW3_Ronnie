#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "problem.h"

// Split the string <s> at every occurence of the delimiter <del>.
std::vector<std::string> split(std::string s, std::string del) {
    std::vector<std::string> v;
    int start = 0;
    for (int end = s.find(del, start); end != std::string::npos; end = s.find(del, start)) {
        v.push_back(s.substr(start, end - start));
        start = end + del.size();
    }
    v.push_back(s.substr(start));
    return v;
}

std::string FORMAT = "^([\\s\\S]*)\\\\answer\\{([\\s\\S]*)\\}[\\s\\S]*\\\\topic\\{(.*)\\}[\\s\\S]*\\\\difficulty\\{(.*)\\}";
std::regex re(FORMAT);

std::string TopicDifficultyProblem::getQuestion() {return question;}
std::string TopicDifficultyProblem::getAnswer() {return answer;}
std::string TopicDifficultyProblem::getTopic() const {return topic;}
int TopicDifficultyProblem::getDifficulty() const {return difficulty;}

TopicDifficultyProblem::TopicDifficultyProblem(std::string rawProblem) {
    std::smatch match;
    if (!std::regex_search(rawProblem, match, re) == true) {
        std::cerr << "Invalid problem: " << rawProblem;
        throw std::runtime_error("Invalid problem");
    }
    question = match.str(1);
    answer = match.str(2);
    topic = match.str(3);
    difficulty = std::stoi(match.str(4));
}

std::vector<TopicDifficultyProblem> TopicDifficultyProblem::problemList(const std::string& filename) {
    // Read problems from file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening the problem list" << std::endl;
        throw std::runtime_error("Cannot open problem list");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string str = buffer.str();

    // Split into individual problems, throw out header at beginning
    std::vector<std::string> problemStrings = split(str, "\\item");
    problemStrings.erase(problemStrings.begin());

    // Convert strings to Problems
    std::vector<TopicDifficultyProblem> problems = {};
    for (std::string problemString : problemStrings) {
        TopicDifficultyProblem problem(problemString);
        problems.push_back(problem);
    }
    return problems;
}

std::string TAL_FORMAT = "^([\\s\\S]*)\\\\answer\\{([\\s\\S]*)\\}[\\s\\S]*\\\\topic\\{(.*)\\}[\\s\\S]*\\\\author\\{(.*)\\}[\\s\\S]*\\\\isLong\\{(.*)\\}";
std::regex tal_re(TAL_FORMAT);

std::string TopicAuthorLengthProblem::getQuestion() {return question;}
std::string TopicAuthorLengthProblem::getAnswer() {return answer;}
std::string TopicAuthorLengthProblem::getTopic() const {return topic;}
std::string TopicAuthorLengthProblem::getAuthor() const {return author;}
bool TopicAuthorLengthProblem::getIsLong() const {return isLong;}

TopicAuthorLengthProblem::TopicAuthorLengthProblem(std::string rawProblem) {
    std::smatch match;
    if (!std::regex_search(rawProblem, match, tal_re) == true) {
        std::cerr << "Invalid problem: " << rawProblem;
        throw std::runtime_error("Invalid problem");
    }
    question = match.str(1);
    answer = match.str(2);
    topic = match.str(3);
    author = match.str(4);
    isLong = (match.str(5) == "true");
}

std::vector<TopicAuthorLengthProblem> TopicAuthorLengthProblem::problemList(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening the problem list" << std::endl;
        throw std::runtime_error("Cannot open problem list");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string str = buffer.str();

    std::vector<std::string> problemStrings = split(str, "\\item");
    problemStrings.erase(problemStrings.begin());

    std::vector<TopicAuthorLengthProblem> problems = {};
    for (std::string problemString : problemStrings) {
        TopicAuthorLengthProblem problem(problemString);
        problems.push_back(problem);
    }
    return problems;
}