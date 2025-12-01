#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <string>
#include <vector>
#include "problem.h"
#include <memory>

class IConstraint {
public:
    virtual ~IConstraint() = default;
    virtual bool isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const = 0;
    virtual bool exceedsMax(const std::vector<std::shared_ptr<IProblem>>& problems) const = 0;
};

class TopicConstraint : public IConstraint {
private:
    std::string topic;
    int minValue;
    int maxValue;
public:
    TopicConstraint(const std::string& topic, int minValue, int maxValue);
    bool isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const override;
    bool exceedsMax(const std::vector<std::shared_ptr<IProblem>>& problems) const override;
};

class DifficultyConstraint : public IConstraint {
private:
    int minValue;
    int maxValue;
public:
    DifficultyConstraint(int minValue, int maxValue);
    bool isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const override;
    bool exceedsMax(const std::vector<std::shared_ptr<IProblem>>& problems) const override; 
};
   
class AuthorConstraint : public IConstraint {
private:
    std::string author;
    int minValue;
    int maxValue;
public:
    AuthorConstraint(const std::string& author, int minValue, int maxValue);
    bool isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const override;
    bool exceedsMax(const std::vector<std::shared_ptr<IProblem>>& problems) const override;
};

class LongProblemConstraint : public IConstraint {
private:
    int minValue;
    int maxValue;
public:
    LongProblemConstraint(int minValue, int maxValue);
    bool isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const override;
    bool exceedsMax(const std::vector<std::shared_ptr<IProblem>>& problems) const override; 
};


#endif