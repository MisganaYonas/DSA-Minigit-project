
#include "minigit.h"

namespace fs = std::filesystem;


    // Read commit ID from a branch file
std::string getBranchCommitId(const std::string& branchName) {
    std::string branchPath = ".minigit/branches/" + branchName + ".txt";
    std::ifstream branchFile(branchPath);
    if (!branchFile.is_open()) {
        return "";
    }
    std::string commitId;
    std::getline(branchFile, commitId);
    branchFile.close();
    return commitId;
}

// Get current branch name from HEAD
std::string getCurrentBranch() {
    std::ifstream headFile(".minigit/HEAD.txt");
    std::string headContent;
    std::getline(headFile, headContent);
    headFile.close();
    // Assume HEAD contains "ref: branchName" or a commit ID
    if (headContent.find("ref: ") == 0) {
        return headContent.substr(5); // Extract branch name
    }
    return "";
}

// Write a commit object
std::string writeCommitObject(const std::string& content) {
    // Simple hash simulation (in practice, use SHA-1 or similar)
    std::string commitId = std::to_string(std::hash<std::string>{}(content));
    std::ofstream commitFile(".minigit/commits/" + commitId + ".txt");
    if (commitFile.is_open()) {
        commitFile << content;
        commitFile.close();
    }
    return commitId;
}

// Find lowest common ancestor (simplified BFS approach)
std::string findLCA(const std::string& commit1, const std::string& commit2) {
    std::string commitPath = ".minigit/commits/" + commit1 + ".txt";
    if (fs::exists(commitPath)) {
        return commit1; 
    }
    return "";
}

// Perform three-way merge
void threeWayMerge(const std::string& lcaCommit, const std::string& currentCommit, 
                   const std::string& targetCommit, const std::string& targetBranch) {

    // Create a merge commit without file content merging
    std::stringstream commitContent;
    commitContent << "parent: " << currentCommit << "\n";
    commitContent << "parent: " << targetCommit << "\n";
    commitContent << "timestamp: " << std::time(nullptr) << "\n";
    commitContent << "message: Merge branch '" << targetBranch << "'\n";
    
    // No file blobs merged (first code doesn't handle file content)
    std::string commitHash = writeCommitObject(commitContent.str());
    
    
    // Update current branch to point to merge commit
    std::string currentBranch = getCurrentBranch();
    if (currentBranch.empty()) {
        std::cout << "Cannot merge in detached HEAD state.\n";
        return;
    }
    


    std::ofstream branchFile(".minigit/branches/" + currentBranch + ".txt");
    if (branchFile.is_open()) {
        branchFile << commitHash;
        branchFile.close();
        updateHEAD(commitHash);
        std::cout << "Merge commit created: " << commitHash << "\n";
    } else {
        std::cout << "Failed to update branch.\n";
    }
}

// Merge a branch into the current branch
void merge(const std::string& branchName) {
    // Check if target branch exists
    if (!fs::exists(".minigit/branches/" + branchName + ".txt")) {
        std::cout << "Branch '" << branchName << "' does not exist.\n";
        return;
    }

    // Get current branch and commit
    std::string currentBranch = getCurrentBranch();
    if (currentBranch.empty()) {
        std::cout << "Cannot merge in detached HEAD state.\n";
        return;
    }
    std::string currentCommit = getLastCommitId();
    std::string targetCommit = getBranchCommitId(branchName);

    if (targetCommit.empty()) {
        std::cout << "Cannot resolve branch '" << branchName << "'.\n";
        return;
    }

    // Check if already up to date
    if (currentCommit == targetCommit) {
        std::cout << "Already up to date.\n";
        return;
    }

    // Find lowest common ancestor
    std::string lcaCommit = findLCA(currentCommit, targetCommit);
    if (lcaCommit.empty()) {
        std::cout << "No common ancestor found.\n";
        return;
    }

    // Fast-forward merge
    if (lcaCommit == currentCommit) {
        std::cout << "Fast-forward merge.\n";
        // Update current branch to target commit
        std::ofstream branchFile(".minigit/branches/" + currentBranch + ".txt");
        if (branchFile.is_open()) {
            branchFile << targetCommit;
            branchFile.close();
            updateHEAD(targetCommit);
            checkoutBranch(currentBranch); // Update working directory
        } else {
            std::cout << "Failed to update branch.\n";
        }
        return;
    }

    // Perform three-way merge
    threeWayMerge(lcaCommit, currentCommit, targetCommit, branchName);
}
