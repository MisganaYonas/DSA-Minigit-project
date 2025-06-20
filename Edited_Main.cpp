/* int main() {
    ensureFoldersExist();

    string command;
    cout << "mingit > ";
    while (cin >> command) {
        if (command == "commit") {
            string msg;
            getline(cin >> ws, msg);
            makeCommit(msg);
        }
        else if (command == "log") {
            showLog();
        }
        else if (command == "branch") {
            string branchName;
            cin >> branchName;
            createBranch(branchName);
        }
        else if (command == "checkout") {
            string target;
            cin >> target;
            if (filesystem::exists(".minigit/branches/" + target + ".txt")) {
                checkoutBranch(target);
            } else {
                checkoutCommit(target);
            }
        }
        else {
            cout << "Unknown command." << endl;
        }
        cout << "mingit > ";
    }

    return 0;
} */
