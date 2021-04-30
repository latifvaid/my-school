/*main.cpp*/
//
// Author: Latif Vaid, UIC, Spring 2021
//

#include <iostream>
#include <fstream>
#include <string>

#include "classreg.h"
using namespace std;

int main() {
//     ClassReg cs111, cs141, cs151, cs211, cs251;
    ClassReg classreg;
    string className;
    int cap;
    cout << "Enter class name> " << endl;
    cin >> className;
    cout << "Enter class capacity> " << endl;
    cin >> cap;
    
    classreg.setName(className);
    classreg.setCapacity(cap);

    string netID;
    int i = 1;
    
    cout << "Enter a student name to enroll (# to stop)>" << endl;
    cin >> netID;
    while(netID != "#"){
        if(classreg.numEnrolled() < cap){
            classreg.enrollStudent(netID);
            cout << "Student '" << netID << "' " << "was enrolled" << endl;
        } else {
            classreg.waitlistStudent(netID, i);
            cout << "Student '" << netID << "' " << "added to waitlist" << endl;
            i++;
        }
        cout << "Enter a student name to enroll (# to stop)>" << endl;
        cin >> netID;
    }
    cout << classreg.getName() << endl;
    cout << "capacity: " << classreg.getCapacity() << endl;
    cout << "enrolled: ";
    for(int i = 0; i < classreg.numEnrolled(); i++){
        string enrolled = classreg.retrieveEnrolledStudent(i);
        cout << enrolled << " ";
    }
    cout << endl;
    string netid;
    int priority;
    cout << "waitlisted: ";
    for(int i = 0; i < classreg.numWaitlisted(); i++){
        classreg.retrieveWaitlistedStudent(i, netid, priority);
        cout << netid << " ";
    }
    cout << endl;

    return 0;
}