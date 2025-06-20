#ifndef MERGE_H
#define MERGE_H

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

std::string getBranchCommitId(const std::string& branchName);
std::string getCurrentBranch();
std::string writeCommitObject(const std::string& content);
std::string findLCA(const std::string& commit1, const std::string& commit2);
void threeWayMerge(const std::string& lcaCommit, const std::string& currentCommit, 
                   const std::string& targetCommit, const std::string& targetBranch);
void merge(const std::string& branchName);

#endif