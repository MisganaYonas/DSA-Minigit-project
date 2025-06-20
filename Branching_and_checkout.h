#ifndef BRANCHING_AND_CHECKOUT_H
#define BRANCHING_AND_CHECKOUT_H

#include <string>

void createBranch(const std::string& branchName);
void checkoutBranch(const std::string& branchName);
void checkoutCommit(const std::string& commitId);

#endif