/*
 * ProjectTwo.cpp
 *
 *  Created on: Jun 18, 2026
 *      Author: Administrator
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// Structure used to store course information
struct Course {
	string courseNumber;   //Course ID
	string courseTitle;    //Course title
	vector<string> prerequisites;  //List of prerequisite course numbers
};

//Map used to store all courses
//The key is the course number
map<string, Course> courseMap;

// Loads course data from a file
void loadCourses(string fileName) {

    ifstream file(fileName.c_str());

    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    string line;

    while (getline(file, line)) {

        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Split line by commas
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Validate line format
        if (tokens.size() < 2) {
            cout << "Invalid course data found." << endl;
            continue;
        }

        // Create course object
        Course course;

        course.courseNumber = tokens[0];
        course.courseTitle = tokens[1];

        // Add prerequisites
        for (unsigned int i = 2; i < tokens.size(); i++) {
            course.prerequisites.push_back(tokens[i]);
        }

        // Store course in map
        courseMap[course.courseNumber] = course;
    }

    cout << "Courses loaded successfully." << endl;

    file.close();
}

// Print all courses in alphanumeric order
void printCourseList() {

    cout << endl;
    cout << "Here is a sample schedule:" << endl;

    map<string, Course>::iterator it;

    for (it = courseMap.begin(); it != courseMap.end(); ++it) {
        cout << it->second.courseNumber
             << ", "
             << it->second.courseTitle
             << endl;
    }
}

// Print information for a specific course
void printCourse(string courseNumber) {

    // Convert input to uppercase
    transform(courseNumber.begin(), courseNumber.end(),
              courseNumber.begin(), ::toupper);

    // Search for course
    if (courseMap.find(courseNumber) != courseMap.end()) {

        Course course = courseMap[courseNumber];

        cout << endl;
        cout << course.courseNumber
             << ", "
             << course.courseTitle
             << endl;

        cout << "Prerequisites: ";

        if (course.prerequisites.size() == 0) {
            cout << "None";
        }
        else {
            for (unsigned int i = 0; i < course.prerequisites.size(); i++) {

                string prereqNumber = course.prerequisites[i];

                cout << prereqNumber;

                // Print prerequisite title if it exists in the map
                if (courseMap.find(prereqNumber) != courseMap.end()) {
                    cout << " - " << courseMap[prereqNumber].courseTitle;
                }

                if (i < course.prerequisites.size() - 1) {
                    cout << ", ";
                }
            }
        }

        cout << endl;
    }
    else {
        cout << "Course not found." << endl;
    }
}

int main() {

    int choice = 0;
    bool isLoaded = false;

    // Display welcome message
    cout << "Welcome to the course planner." << endl;

    // Continue displaying menu until user chooses 9
    while (choice != 9) {

        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << endl;

        cout << "What would you like to do? ";
        cin >> choice;

        // Menu option 1
        if (choice == 1) {
        	string fileName;

        	cout << "Enter file name: ";
        	cin.ignore();
        	getline(cin, fileName);

        	courseMap.clear();
        	loadCourses(fileName);

        	if (!courseMap.empty()) {
        	    isLoaded = true;
        	}
        }

        // Menu option 2
        else if (choice == 2) {
            if (isLoaded) {
                printCourseList();
            }
            else {
                cout << "Please load the course data first." << endl;
            }
        }

        // Menu option 3
        else if (choice == 3) {

            if (isLoaded) {
                string courseNumber;

                cout << "What course do you want to know about? ";
                cin >> courseNumber;

                printCourse(courseNumber);
            }
            else {
                cout << "Please load the course data first." << endl;
            }
        }
        // Menu option 9
        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
        }

        // Invalid menu option
        else {
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}

