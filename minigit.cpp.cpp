#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "minigit.h"


using namespace std;

//writing function to get the current date and time as a string
string getCurrentTime(){
    time_t now = time(0);   //to get currrent time
    string dt = ctime(&now);  //to convert to string
    return dt;  //return the formated date and time
}

// This function gets the id of the last commit from HEAD.txt
string getLastCommitId (){
    ifstream headFile(".minigit/HEAD.txt");
    string lastId;
    if (headFile.is_open()){
        getline(headFile, lastId);
        headFile.close();
    
    }
    return lastId;
}

//function to updatte the Head.txt with the new commit id
void updateHEAD(string newId){
    ofstream headFile(".minigit/HEAD.txt");
    headFile << newId;
    headFile.close();
}

// this function creates a new commit with a message
void makeCommit(string message){
    string parentId = getLastCommitId();
    string newCommitId = "commit_" + to_string(rand()% 10000);  //random id
    ofstream commitFile(".minigit/commits/" + newCommitId + ".txt"); //creats file for the new commit

    if (commitFile.is_open()){
        commitFile << "ID: " <<newCommitId << endl;
        commitFile << "Message: " << message << endl;
        commitFile << "Time: " <<getCurrentTime();
        commitFile << "Parent: " <<parentId << endl;
        commitFile.close();
        
        updateHEAD(newCommitId);
        cout << "commit saved as " <<newCommitId<<endl;
    } 
    else{
        cout << "error creating commit file." << endl;
    }
}

//this function displays alll commits starting from the latest 
void showLog(){
    string currentId = getLastCommitId();
    while (!currentId.empty()){
        ifstream file(".minigit/commits/" + currentId + ".txt");
        string line, parentLine;
        
        if (file.is_open()){
            while(getline(file,line)){
                cout << line <<endl;
                if (line.find("Parent: ") != string::npos){
                    parentLine = line.substr(8);
                }
            }
            file.close();
            cout << "------------"<<endl;
            currentId = parentLine;    //go to the parent commits
        }
        else {
            break;
        }
    }
}

/* int main (){
    string command;
    cout<<"minGit > ";
    while(cin >> command){
        if (command == "commit"){
        string msg;
        getline(cin>> ws, msg);
        makeCommit(msg);
    }
    else if (command == "log"){
        showLog();
    }
    else {
        cout <<"unknown command." << endl;
    }
    cout << "mingit > " ;
    } 
    return 0;
} */















