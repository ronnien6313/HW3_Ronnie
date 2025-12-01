#ifndef SELECTOR_H
#define SELECTOR_H
#include <vector>
#include <memory>
#include "problem.h"
#include "constraint.h"

class ISelector {
    public:
        virtual ~ISelector() = default;
        virtual std::vector<std::shared_ptr<IProblem>> selectProblems(std::vector<std::shared_ptr<IProblem>>& problems,
        int numProblems,
        std::vector<std::shared_ptr<IConstraint>>& constraints) = 0;
};

class ShuffleSelector : public ISelector {
    public:
        std::vector<std::shared_ptr<IProblem>> selectProblems(std::vector<std::shared_ptr<IProblem>>& problems,
        int numProblems,
        std::vector<std::shared_ptr<IConstraint>>& constraints) override;
};

class NewSelector : public ISelector {
    public:
        std::vector<std::shared_ptr<IProblem>> selectProblems(std::vector<std::shared_ptr<IProblem>>& problems,
        int numProblems,
        std::vector<std::shared_ptr<IConstraint>>& constraints) override;
};

#endif