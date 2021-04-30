/*main.cpp*/
//
// Author: Latif Vaid, UIC, Spring 2021
//
//Project 06 Part 01

#include <iostream>
#include <fstream>
#include <string>

#include "classreg.h"
using namespace std;


//opens the file with enrollment data and reads data as necessary and if unable to open the file error is output on screen

void inputFromFile(string filename, ClassReg classes[]){
    fstream inFile(filename);
    if(!inFile.good()){
        cout << "**Error: unable to open output file '" << filename << "'" << endl;
        return;
    }
    int curClass = 0;              // now its on cs111...1-cs141...2-151 etc
    string word, word2;           //word2 used with priority
    while(curClass < 5){
        inFile >> word;
        classes[curClass].setName(word);
        inFile >> word;
        classes[curClass].setCapacity(stoi(word));
        inFile >> word;
        while(word != "#"){            //checks till end line
            classes[curClass].enrollStudent(word);
            inFile >> word;
        }
        inFile >> word;
        while(word != "#"){
            inFile >> word2;
            classes[curClass].waitlistStudent(word, stoi(word2));
            inFile >> word;
        }
        curClass++;   
    }
}

//outputs out all the commands on the screen 

void helpCommand(){
    cout << "stats" << endl;
    cout << "list class" << endl;
    cout << "increase class capacity" << endl;
    cout << "enroll class netid" << endl;
    cout << "waitlist class netid priority" << endl;
    cout << "process filename" << endl;
    cout << "output filename" << endl;
    cout << "quit" << endl;
}

//outputs name, enrollment, and waitlist for all the classes 

void statsCommand(ClassReg classes[]){
    
    for(int i = 0; i < 5; i++){
        cout << classes[i].getName() << ": enrolled=" << classes[i].numEnrolled() << ", waitlisted=" << classes[i].numWaitlisted() << endl;
    }
}

//sorts class enrollment data by name

void sortingbyName(string sortingEnroll[], int size){

    for(int i = 0; i < size-1; i++){
        for(int j = i + 1; j < size; j++){
            if(sortingEnroll[j] < sortingEnroll[i]){
                string temp; 
                temp = sortingEnroll[i];
                sortingEnroll[i] = sortingEnroll[j];
                sortingEnroll[j] = temp;
            }
        }
    }
}

//checkClass checks if the class is found if not found -1 is returned (which tells that the class is not found)

int checkClass(ClassReg classes[], string classNum){
    int curClass = -1;
    for(int i = 0; i < 5; i++){
        if(classNum == classes[i].getName()){
            curClass = i;
        }
    }
    return curClass;
}


void listCommand(ClassReg classes[], string classNum){
    int curClass = checkClass(classes, classNum);
    if(curClass == -1){
        cout << "**Invalid class name, try again..." << endl;
    } else {
        cout << classes[curClass].getName() << endl;
        cout << "Capacity: " << classes[curClass].getCapacity() << endl;
        
        string sortingEnroll[classes[curClass].numEnrolled()];
        for(int i = 0; i < classes[curClass].numEnrolled(); i++){
            sortingEnroll[i] = classes[curClass].retrieveEnrolledStudent(i);
        }
        
        sortingbyName(sortingEnroll, classes[curClass].numEnrolled());
        
        cout << "Enrolled (" <<  classes[curClass].numEnrolled() << "): ";
        for(int i = 0; i < classes[curClass].numEnrolled(); i++){
            cout << sortingEnroll[i] << " ";
        }
        cout << endl << "Waitlisted (" << classes[curClass].numWaitlisted() << "): ";
        string netid = " ";
        int priority;
        for(int i = 0; i < classes[curClass].numWaitlisted(); i++){
            classes[curClass].retrieveWaitlistedStudent(i, netid, priority);
            cout << netid << " (" << priority << ") ";
        }
        cout << endl;
    }
}

void increaseCommand(ClassReg classes[], string classNum, int byHowMuch){
    int curClass = checkClass(classes, classNum);
    if(curClass == -1){
        cout << "**Invalid class name, try again..." << endl;
    } else if(byHowMuch < classes[curClass].getCapacity()){
        cout << "**Error, cannot decrease class capacity, ignored..." << endl;
    } else {
        classes[curClass].setCapacity(byHowMuch);
        cout <<  classes[curClass].getName() << endl;
        cout << "Capacity: " <<  classes[curClass].getCapacity() << endl;
    }
}

void enrollCommand(ClassReg classes[], string classNum, string netid){
    int curClass, search = -1, search2 = -1, priority =  0;
    string tempid;
    curClass = checkClass(classes, classNum);
    if(curClass == -1){
        cout << "**Invalid class name, try again..." << endl;
    } else {
        search = classes[curClass].searchEnrolled(netid);
        if(search != -1){
        cout << "Student '" << netid << "' enrolled in " << classes[curClass].getName() << endl;
            
        } else {
            search2 = classes[curClass].searchWaitlisted(netid);
        }
        if(search2 != -1){
            if(classes[curClass].numEnrolled() < classes[curClass].getCapacity()){
                classes[curClass].removeWaitlistedStudent(search2);
                classes[curClass].enrollStudent(netid);
                cout << "Student '" << netid << "' enrolled in " << classes[curClass].getName() << endl;
            } else if(classes[curClass].numEnrolled() == classes[curClass].getCapacity() && search2 != -1){
                cout << "Class full, '" << netid << "' waitlisted for " << classes[curClass].getName() << endl;
            }
        } else if(classes[curClass].numEnrolled() < classes[curClass].getCapacity() && search == -1){
            classes[curClass].enrollStudent(netid);
            cout << "Student '" << netid << "' enrolled in " << classes[curClass].getName() << endl;
        } else if(classes[curClass].numEnrolled() == classes[curClass].getCapacity() && search == -1){
            if(classes[curClass].numWaitlisted() == 0){
                classes[curClass].waitlistStudent(netid, 1);
                cout << "Class full, '" << netid << "' waitlisted for " << classes[curClass].getName() << endl;
            } else {
                classes[curClass].retrieveWaitlistedStudent((classes[curClass].numWaitlisted())-1, tempid, priority);
                classes[curClass].waitlistStudent(netid, priority);
                cout << "Class full, '" << netid << "' waitlisted for " << classes[curClass].getName() << endl;
            }
        }
    }
}

void waitlistCommand(ClassReg classes[], string classNum, string netid, int priority){
    int curClass, search = -1, search2 = -1;
    curClass = checkClass(classes, classNum);
    if(curClass == -1){
        cout << "**Invalid class name, try again..." << endl;
    } else {
        search = classes[curClass].searchEnrolled(netid);
        if(search != -1){
        cout << "Student '" << netid << "' enrolled in " << classes[curClass].getName() << endl;
        } else {
            search2 = classes[curClass].searchWaitlisted(netid);
        }
        if(search2 != -1){
            classes[curClass].waitlistStudent(netid, priority);
            cout << "Student '" << netid << "' waitlisted for " << classes[curClass].getName() << endl;
        } else if(search == -1 && search2 == -1){
            classes[curClass].waitlistStudent(netid, priority);
            cout << "Student '" << netid << "' waitlisted for " << classes[curClass].getName() << endl;
        }
    } 
}


void outputCommand(ClassReg classes[], string filename, string filename2){
    string line;
    ofstream outFile(filename2);
    int curClass = 0;

    while(curClass < 5){
        outFile << classes[curClass].getName() << endl;
        outFile << classes[curClass].getCapacity() << endl;
        if(classes[curClass].numEnrolled() == 0){
            outFile << "#" << endl;
        } else {
            for(int i = 0; i < classes[curClass].numEnrolled(); i++){
                if(i < classes[curClass].numEnrolled() - 1){
                    outFile << classes[curClass].retrieveEnrolledStudent(i) << " ";
                } else {
                    outFile << classes[curClass].retrieveEnrolledStudent(i) << " #" << endl;
                }
            }
        }
        if(classes[curClass].numWaitlisted() == 0){
            outFile << "#" << endl;
        } else {
            string netid;
            int priority;
            for(int i = 0; i < classes[curClass].numWaitlisted(); i++){
                if(i < classes[curClass].numWaitlisted() - 1){
                    classes[curClass].retrieveWaitlistedStudent(i, netid, priority);
                    outFile << netid << " " << priority << " ";
                } else {
                    classes[curClass].retrieveWaitlistedStudent(i, netid, priority);
                    outFile << netid << " " << priority << " #" << endl;
                }
            }
        }
        curClass++;
    }
}

/*the coolest part of this function is that it can do 2 things read a file full of commands or input commands from keybord
I did not know we could use istream like that I learned something really powerfull if promptUser true then its keybord input it promptUser is false its an file input
(defult comes true from main)
*/


void processCommands(istream& input, bool promptUser, ClassReg classes[], string filename){
    string cmd, classNum, netid, filename2;
    int byHowMuch = 0, priority = 0;
    
    while(cmd != "q" and cmd != "quit"){
        if(promptUser){
            cout << endl;
            cout << "Enter a command (help for more info, quit to stop)> " << endl;
        }
        input >> cmd;
        if(cmd == "h" or cmd == "help"){
            helpCommand();
        } else if(cmd == "s" or cmd == "stats"){
            statsCommand(classes);
        } else if(cmd == "l" or cmd == "list"){
            input >> classNum;
            listCommand(classes, classNum);
        } else if(cmd == "i" or cmd == "increase"){
            input >> classNum;
            input >> byHowMuch;
            increaseCommand(classes, classNum, byHowMuch);
        } else if(cmd == "e" or cmd == "enroll"){
            input >> classNum;
            input >> netid;
            enrollCommand(classes, classNum, netid);
        } else if(cmd == "w" or cmd == "waitlist"){
            input >> classNum;
            input >> netid;
            input >> priority;
            waitlistCommand(classes, classNum, netid, priority);
        } else if(cmd == "p" or cmd == "process") {
            input >> filename;
            cout << "**Processing commands from '" << filename << "'" << endl;
            fstream inFile(filename);
            if(!inFile.good()){
                cout << "**Error: unable to open output file '" << filename << "'" << endl;
                processCommands(cin, true, classes, filename);
            }
            processCommands(inFile, false, classes, filename);
            cout << "**Done processing '" << filename << "'" << endl;
        } 
        else if(cmd == "o" or cmd == "output"){
            input >> filename2;
            outputCommand(classes, filename, filename2);
            cout << "Enrollment data output to '" << filename2 << "'" << endl;
        } else if(cmd == "q" or cmd == "quit"){
            if(promptUser == true){
                cout << "**Done**" << endl;
            }
        } else {
            cout << "**Invalid command, please try again..." << endl;
        }
            
    }
    
}


// void userInput(ClassReg classes[]){
//     string cmd, classNum, netid;
//     int byHowMuch = 0, priority = 0;
//     while(cmd != "quit"){
//         cout << endl;
//         cout << "Enter a command (help for more info, quit to stop)> " << endl;
//         cin >> cmd;
//         if(cmd == "h" or cmd == "help"){
//             helpCommand();
//         } else if(cmd == "s" or cmd == "stats"){
//             statsCommand(classes);
//         } else if(cmd == "l" or cmd == "list"){
//             cin >> classNum;
//             listCommand(classes, classNum);
//         } else if(cmd == "i" or cmd == "increase"){
//             cin >> classNum;
//             cin >> byHowMuch;
//             increaseCommand(classes, classNum, byHowMuch);
//         } else if(cmd == "e" or cmd == "enroll"){
//             cin >> classNum;
//             cin >> netid;
//             enrollCommand(classes, classNum, netid);
//         } else if(cmd == "w" or cmd == "waitlist"){
//             cin >> classNum;
//             cin >> netid;
//             cin >> priority;
//             waitlistCommand(classes, classNum, netid, priority);
//         } else {
            
//         }
            
//     }
// }

int main() {
//     ClassReg cs111, cs141, cs151, cs211, cs251;
    ClassReg classes[5];
    
    string filename;
    cout << "**CS Enrollment System**" << endl;
    cout << "Enter enrollments filename>" << endl;
    cin >> filename;
    inputFromFile(filename, classes);
    
//     userInput(classes);     //calling user input function where all the commands are
    processCommands(cin, true, classes, filename); //all the commands function
    return 0;
}