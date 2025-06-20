#include "minigit.h"  // Add this to get function declarations
using namespace std;

// Create a new branch pointing to current HEAD commit
void createBranch(const string& branchName) {
    string currentCommit = getLastCommitId();
    ofstream branchFile(".minigit/branches/" + branchName + ".txt");
    if (branchFile.is_open()) {
        branchFile << currentCommit;
        branchFile.close();
        cout << "Branch '" << branchName << "' created at commit " << currentCommit << endl;
    } else {
        cout << "Failed to create branch." << endl;
    }
}

// Checkout to a given branch
void checkoutBranch(const string& branchName) {
    string branchPath = ".minigit/branches/" + branchName + ".txt";
    ifstream branchFile(branchPath);
    if (!branchFile.is_open()) {
        cout << "Branch not found." << endl;
        return;
    }

    string commitId;
    getline(branchFile, commitId);
    branchFile.close();

    updateHEAD(commitId);
    cout << "Checked out branch '" << branchName << "' at commit " << commitId << endl;
    // (Optional) Restore files here based on commit content
}

// Checkout to a specific commit
void checkoutCommit(const string& commitId) {
    string commitPath = ".minigit/commits/" + commitId + ".txt";
    ifstream commitFile(commitPath);
    if (!commitFile.is_open()) {
        cout << "Commit not found." << endl;
        return;
    }

    updateHEAD(commitId);
    cout << "Checked out to commit " << commitId << endl;
    // (Optional) Restore files here
}
