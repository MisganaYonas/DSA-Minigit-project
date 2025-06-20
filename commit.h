#ifndef COMMIT_H
#define COMMIT_H

#include <string>

std::string getCurrentTime();
std::string getLastCommitId();
void updateHEAD(const std::string& newId);
void makeCommit(std::string message);
void showLog();

#endif