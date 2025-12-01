#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
#include <vector>

class IProblem {
public:
    virtual ~IProblem() = default;
    virtual std::string getQuestion() = 0;
    virtual std::string getAnswer() = 0;
};

class TopicDifficultyProblem : public IProblem {
private:
    std::string question;
    std::string answer;
    std::string topic;
    int difficulty;

public:
    std::string getQuestion() override;
    std::string getAnswer() override;
    std::string getTopic() const;
    int getDifficulty() const;

    TopicDifficultyProblem(std::string rawProblem);
    static std::vector<TopicDifficultyProblem> problemList(const std::string& filename);
};

class TopicAuthorLengthProblem : public IProblem {
private:
    std::string question;
    std::string answer;
    std::string topic;
    std::string author;
    bool isLong;

public:
    std::string getQuestion() override;
    std::string getAnswer() override;
    std::string getTopic() const;
    std::string getAuthor() const;
    bool getIsLong() const;

    TopicAuthorLengthProblem(std::string rawProblem);
    static std::vector<TopicAuthorLengthProblem> problemList(const std::string& filename);
};

#endif