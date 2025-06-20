#include "init_add.h"
#include "Branching_and_checkout.h"
#include "commit.h"
#include "merge.h"

#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

int main() {
    init(); // Initialize .minigit structure

    std::string command;
    std::cout << "mingit > "; // Command prompt

    while (std::cin >> command) {
        if (command == "init") {
            init();
        }
        else if (command == "add") {
            std::string filename;
            std::cin >> filename;

            if (!checkFileExists(filename)) {
                std::cerr << "File does not exist: " << filename << std::endl;
            } else {
                std::ifstream inFile(filename);
                std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
                inFile.close();

                std::string hash = hashContentOfFile(content);
                writeTheBlob(hash, content);
                stageFile(filename, hash);
                std::cout << "File added and staged: " << filename << std::endl;
            }
        }
        else if (command == "commit") {
            std::string msg;
            std::getline(std::cin >> std::ws, msg); // Read full line (after trimming whitespace)
            makeCommit(msg);
        }
        else if (command == "log") {
            showLog();
        }
        else if (command == "branch") {
            std::string branchName;
            std::cin >> branchName;
            createBranch(branchName);
        }
        else if (command == "checkout") {
            std::string target;
            std::cin >> target;

            if (fs::exists(".minigit/branches/" + target + ".txt")) {
                checkoutBranch(target);
            } else {
                checkoutCommit(target);
            }
        }
        else if (command == "merge") {
            std::string branchToMerge;
            std::cin >> branchToMerge;
            merge(branchToMerge);
        }
        else {
            std::cout << "Unknown command." << std::endl;
        }

        std::cout << "mingit > ";
    }

    return 0;
}