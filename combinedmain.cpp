#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
void ensureFoldersExist(); // Ensures .minigit folders exist
void init(); // Initializes .minigit structure
bool checkFileExists(const string& filename); // Checks if a file exists
string hashContentOfFile(const string& content); // Hashes content using DJB2 or similar
void writeTheBlob(const string& hash, const string& content); // Stores content under hash
void stageFile(const string& filename, const string& hash); // Records staged files
void makeCommit(const string& message); // Commits staged changes
void showLog(); // Shows commit history
void createBranch(const string& branchName); // Creates new branch
void checkoutBranch(const string& branchName); // Switches to a branch
void checkoutCommit(const string& commitId); // Switches to a specific commit
void merge(const string& branchToMerge); // Merges a branch into current branch

int main() {
    ensureFoldersExist(); // Step 1: Ensure required directories exist

    string command;
    cout << "mingit > "; // Command prompt

    while (cin >> command) {
        if (command == "init") {
            // Initializes .minigit folders and HEAD.txt
            init();
        }
        else if (command == "add") {
            // Stages a file for commit
            string filename;
            cin >> filename;

            if (!checkFileExists(filename)) {
                cerr << "File does not exist: " << filename << endl;
            } else {
                ifstream inFile(filename);
                string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
                inFile.close();

                string hash = hashContentOfFile(content);
                writeTheBlob(hash, content);
                stageFile(filename, hash);
                cout << "File added and staged: " << filename << endl;
            }
        }
        else if (command == "commit") {
            // Commits staged files with a message
            string msg;
            getline(cin >> ws, msg); // Read full line (after trimming whitespace)
            makeCommit(msg);
        }
        else if (command == "log") {
            // Displays all commits
            showLog();
        }
        else if (command == "branch") {
            // Creates a new branch
            string branchName;
            cin >> branchName;
            createBranch(branchName);
        }
        else if (command == "checkout") {
            // Switches to a branch or commit
            string target;
            cin >> target;

            if (fs::exists(".minigit/branches/" + target + ".txt")) {
                checkoutBranch(target); // Switch to branch
            } else {
                checkoutCommit(target); // Switch to specific commit
            }
        }
        else if (command == "merge") {
            // Merges target branch into current
            string branchToMerge;
            cin >> branchToMerge;
            merge(branchToMerge);
        }
        else {
            // Unknown command entered
            cout << "Unknown command." << endl;
        }

        cout << "mingit > "; // Show prompt again
    }

    return 0;
}
