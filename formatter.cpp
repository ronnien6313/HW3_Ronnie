#include "formatter.h"


SimpleFormatter::SimpleFormatter(std::string texHdr, std::string contentHdr, std::string testTitle)
    : texHeader(texHdr), contentHeader(contentHdr), title(testTitle) {}

void SimpleFormatter::writeTest
    (std::ofstream& file, 
    const std::vector<std::shared_ptr<IProblem>>& problems) {

    file << "\\input{" << texHeader << "}\n";
    file << "\\newcommand{\\testtitle}{" << title << "}\n";
    file << "\\input{" << contentHeader << "}\n";

    for (const auto& problem : problems) {
        file << "\\item " << problem->getQuestion() << "\n";
    }

    file << "\\end{enumerate}\n\\end{document}";
}

// FancyFormatter Implementation
FancyFormatter::FancyFormatter
    (std::string texHdr, std::string contentHdr,
    std::string cls, std::string trm, std::string exam,
    std::string tm, std::string frm, int numProbs, std::string testTitle)
    : texHeader(texHdr), contentHeader(contentHdr), CLASS(cls), TERM(trm), 
      EXAM(exam), TIME(tm), FORM(frm), NUM_PROBLEMS(numProbs), TITLE(testTitle) {}

void FancyFormatter::writeTest(std::ofstream& file, 
                              const std::vector<std::shared_ptr<IProblem>>& problems) {
    // REUSED from fancy_test_generator.cpp output section
    file << "\\input{" << texHeader << "}\n";
    
    file << "\\newcommand{\\class}{" << CLASS << "}\n";
    file << "\\newcommand{\\term}{" << TERM << "}\n";
    file << "\\newcommand{\\examno}{" << EXAM << "}\n";
    file << "\\newcommand{\\dayeve}{" << TIME << "}\n";
    file << "\\newcommand{\\formletter}{" << FORM << "}\n";
    file << "\\newcommand{\\numproblems}{" << NUM_PROBLEMS << " }\n";
    file << "\\newcommand{\\testtitle}{" << TITLE << "}\n";
    file << "\\input{" << contentHeader << "}\n";

    int problem_number = 1;
    for (const auto& problem : problems) {
        if (problem_number % 2 == 1) {
            file << "\\pagebreak\n\n";
        } else {
            file << "\\vspace{350pt}\n\n";
        }
        file << "\\item\\begin{tabular}[t]{p{5in} p{.3in} p{.8in}}\n";
        file << problem->getQuestion();
        file << "& & \\arabic{enumi}.\\hrulefill\n\\end{tabular}\n";
        problem_number += 1;
    }

    file << "\\end{enumerate}\n\\end{document}";
}
