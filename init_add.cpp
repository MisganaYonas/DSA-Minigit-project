
//#include "minigit.h"
#include "init_add.h"
#include "Branching_and_checkout.h"
#include "commit.h"
#include "merge.h"

using namespace std;

// Step 1: Initialize MiniGit folders and HEAD file
void init() {
    if (filesystem::exists(".minigit")) {
        cout << "MiniGit already initialized." << endl;
        return;
    }

    filesystem::create_directory(".minigit");
    filesystem::create_directory(".minigit/objects");
    filesystem::create_directory(".minigit/commits");
    filesystem::create_directory(".minigit/branches"); // Add this line

    ofstream headFile(".minigit/HEAD.txt");
    if (headFile.is_open()) {
        headFile << "NULL";
        headFile.close();
        cout << "MiniGit is initialized." << endl;
    } else {
        cerr << "Failed to create HEAD.txt" << endl;
    }

// Create main branch file with no commit (empty)
    ofstream mainBranchFile(".minigit/branches/main.txt");
    if (mainBranchFile.is_open()) {
        mainBranchFile.close();
    }
}

// Check if a file exists
bool checkFileExists(const string& filename) {
    return filesystem::exists(filename);
}

// Generate a simple hash for file content (DJB2)
string hashContentOfFile(const string& content) {
    unsigned long hash = 5381;
    for (char c : content) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return to_string(hash);
}

// Write the content of a file as a blob (with hash as filename)
void writeTheBlob(const string& hash, const string& content) {
    ofstream outFile(".minigit/objects/" + hash + ".txt");
    outFile << content;
    outFile.close();
}

// Record the staged file and its hash in staging_area.txt
void stageFile(const string& filename, const string& hash) {
    ofstream stageFile(".minigit/staging_area.txt", ios::app);
    stageFile << filename << " " << hash << endl;
    stageFile.close();
}

/* int main() {
    init(); // run the setup

    // 1. Create a file (for testing only)
    ofstream testFile("test.txt");
    testFile << "This is a test file." << endl;
    testFile.close();

    // 2. Ask for filename (Ex: "test.txt")
    string filename;
    cout << "Enter the filename to add: ";
    cin >> filename;

    // 3. Check if file exists
    if (!checkFileExists(filename)) {
        cerr << "File does not exist: " << filename << endl;
        return 1;
    }

    // 4. Read the file's content
    ifstream inFile(filename);
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    // 5. Hash and store it
    string hash = hashContentOfFile(content);
    writeTheBlob(hash, content);
    stageFile(filename, hash);

    cout << "File added and staged: " << filename << endl;

    // 6. Show contents of staging area
    ifstream stage(".minigit/staging_area.txt");
    string line;
    cout << "\nCurrent staging area:\n";
    while (getline(stage, line)) {
        cout << line << endl;
    }
    stage.close();

    return 0;
} */

