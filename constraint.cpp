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
        auto talp = std::dynamic_pointer_cast<TopicAuthorLengthProblem>(problem);
        if (talp && talp->getTopic() == topic) {
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

AuthorConstraint::AuthorConstraint(const std::string& author, int minValue, int maxValue)
    : author(author), minValue(minValue), maxValue(maxValue) {}

bool AuthorConstraint::isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const {
    int count = 0;
    for (const auto& problem : problems) {
        auto talp = std::dynamic_pointer_cast<TopicAuthorLengthProblem>(problem);
        if (talp && talp->getAuthor() == author) {
            count++;
        }
    }
    return count >= minValue && count <= maxValue;
}

LongProblemConstraint::LongProblemConstraint(int minValue, int maxValue)
    : minValue(minValue), maxValue(maxValue) {}

bool LongProblemConstraint::isSatisfied(const std::vector<std::shared_ptr<IProblem>>& problems) const {
    int count = 0;
    for (const auto& problem : problems) {
        auto talp = std::dynamic_pointer_cast<TopicAuthorLengthProblem>(problem);
        if (talp && talp->getIsLong()) {
            count++;
        }
    }
    return count >= minValue && count <= maxValue;
}



bool TopicConstraint::exceedsMax(const std::vector<std::shared_ptr<IProblem>>& problems) const {
    int count = 0;
    for (const auto& problem : problems) {
        auto tdp = std::dynamic_pointer_cast<TopicDifficultyProblem>(problem);
        if (tdp && tdp->getTopic() == topic) {
            count++;
        }
        auto talp = std::dynamic_pointer_cast<TopicAuthorLengthProblem>(problem);
        if (talp && talp->getTopic() == topic) {
            count++;
        }
    }
    return count > maxValue;
}


bool DifficultyConstraint::exceedsMax(const std::vector<std::shared_ptr<IProblem>>& problems) const {
    int total = 0;
    for (const auto& problem : problems) {
        auto tdp = std::dynamic_pointer_cast<TopicDifficultyProblem>(problem);
        if (tdp) { 
            total += tdp->getDifficulty(); 
        }
    }
    return total > maxValue;
}


bool AuthorConstraint::exceedsMax(const std::vector<std::shared_ptr<IProblem>>& problems) const {
    int count = 0;
    for (const auto& problem : problems) {
        auto talp = std::dynamic_pointer_cast<TopicAuthorLengthProblem>(problem);
        if (talp && talp->getAuthor() == author) {
            count++;
        }
    }
    return count > maxValue;
}


bool LongProblemConstraint::exceedsMax(const std::vector<std::shared_ptr<IProblem>>& problems) const {
    int count = 0;
    for (const auto& problem : problems) {
        auto talp = std::dynamic_pointer_cast<TopicAuthorLengthProblem>(problem);
        if (talp && talp->getIsLong()) {
            count++;
        }
    }
    return count > maxValue;
}