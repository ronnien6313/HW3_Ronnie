#ifndef FORMATTER_H
#define FORMATTER_H

#include "problem.h"
#include <vector>
#include <memory>
#include <fstream>
#include <string>

class ITestFormatter {
public:
    virtual ~ITestFormatter() = default;
    virtual void writeTest(std::ofstream& file, 
                          const std::vector<std::shared_ptr<IProblem>>& problems) = 0;
};

class SimpleFormatter : public ITestFormatter {
private:
    std::string texHeader;
    std::string contentHeader;
    std::string title;

public:
    SimpleFormatter(std::string texHdr, std::string contentHdr, std::string testTitle);
    void writeTest(std::ofstream& file, 
                  const std::vector<std::shared_ptr<IProblem>>& problems) override;
};

class FancyFormatter : public ITestFormatter {
private:
    std::string texHeader;
    std::string contentHeader;
    std::string CLASS;
    std::string TERM;
    std::string EXAM;
    std::string TIME;
    std::string FORM;
    int NUM_PROBLEMS;
    std::string TITLE;

public:
    FancyFormatter(std::string texHdr, std::string contentHdr,
                  std::string cls, std::string trm, std::string exam,
                  std::string tm, std::string frm, int numProbs, std::string testTitle);
    void writeTest(std::ofstream& file, 
                  const std::vector<std::shared_ptr<IProblem>>& problems) override;
};

#endif