#include <iostream> // for cout and cerr as well as cin
#include <fstream> // for writing files
#include <filesystem> // for directory creation
using namespace std;
void init() {
    // checks if the .minigit already exists
    if (std::filesystem::exists(".minigit")) {
        cout << "MiniGit already exists and is initialized." << endl;
        return;
    }
    // if the .minigit doesn't exist creates necessary folders
    std::filesystem::create_directory(".minigit");
    std::filesystem::create_directory(".minigit/objects");
    std::filesystem::create_directory(".minigit/commits");
    // creates the head.txt file and write "NULL" into it
    ofstream headFile(".minigit/head.txt");
    if (headFile.is_open()) {
        headFile << "NULL";
        headFile.close();
        cout << "minigit is initialized" << endl;
    } else {
        cerr << "failed to create head file" << endl;
    }
}
int main() {
    init();
    return 0;
}
