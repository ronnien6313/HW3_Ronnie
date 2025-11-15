#include "constraint.h"

TopicConstraint::TopicConstraint(const std::string& topic, int minValue, int maxValue)
    : topic(topic), minValue(minValue), maxValue(maxValue) {}

bool TopicConstraint::isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const {
    int count = 0;
    for (const auto& problem : problems) {
        auto tdp = std::dynamic_pointer_cast<TopicDifficultyProblem>(problem);
        if (tdp && tdp->getTopic() == topic) {
            count++;
        }
    }
    return count >= minValue && count <= maxValue;
}

DifficultyConstraint::DifficultyConstraint(int minValue, int maxValue)
    : minValue(minValue), maxValue(maxValue) {}

bool DifficultyConstraint::isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const {
    int total = 0;
    for (const auto& problem : problems) {
        auto tdp = std::dynamic_pointer_cast<TopicDifficultyProblem>(problem);
        if (tdp) {
            total += tdp->getDifficulty();
        }
    }
    return total >= minValue && total <= maxValue;
}