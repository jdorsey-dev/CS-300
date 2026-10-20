
/*
 * Name: Josh Dorsey
 * Course: CS 300
 * Project Two: Advising Assistance Program
 * Description: This is a program that reads course information from a CSV file,
 *              validates the data, stores the courses in a binary search
 *              tree, prints the full course list in alphanumeric order,
 *              and lets the user search for a course and view its
 *              prerequisite information.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <limits>

using namespace std;

// Stores all of the information for one course.
// Each Course has a course number, title, and a list of prerequisite numbers.
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Represents one node in the binary search tree.
// Each node stores one Course and pointers to the left and right child nodes.
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Creates a new node containing the provided Course.
    // New nodes begin without any left or right children.
    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

// Binary search tree used to organize Course objects by course number.
// Smaller course numbers are placed on the left and larger course numbers
// are placed on the right so the tree can be searched efficiently.
class BinarySearchTree {
private:
    Node* root;

    // Recursively inserts a Course into the correct position in the tree.
    // The course number is compared to the current node to decide whether
    // the new Course should continue down the left or right side.
    void addNode(Node* node, Course course) {
        if (course.courseNumber < node->course.courseNumber) {
            if (node->left == nullptr) {
                node->left = new Node(course);
            }
            else {
                addNode(node->left, course);
            }
        }
        else {
            if (node->right == nullptr) {
                node->right = new Node(course);
            }
            else {
                addNode(node->right, course);
            }
        }
    }

    // Frees the nodes in the left and right subtrees before deleting
    // the current node. This is needed because each node uses new.
    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    // Performs an in-order traversal of the binary search tree.
    // Visiting the left subtree, current node, and then right subtree
    // causes the courses to print in alphanumeric order.
    void printInOrder(Node* node) {
        if (node != nullptr) {
            printInOrder(node->left);

            cout << node->course.courseNumber << ", "
                << node->course.courseTitle << endl;

            printInOrder(node->right);
        }
    }

public:
    // Creates an empty binary search tree by starting with no root node.
    BinarySearchTree() {
        root = nullptr;
    }

    // Deletes remaining nodes automatically when the tree goes away.
    ~BinarySearchTree() {
        deleteTree(root);
    }

    // Empties the tree before loading a new set of valid courses.
    void Clear() {
        deleteTree(root);
        root = nullptr;
    }

    // Inserts a Course into the binary search tree.
    // The first Course becomes the root, and later Courses are positioned
    // by addNode based on their course numbers.
    void Insert(Course course) {
        if (root == nullptr) {
            root = new Node(course);
        }
        else {
            addNode(root, course);
        }
    }

    // Searches the tree for a Course using its course number.
    // The search moves left or right depending on how the requested number
    // compares to the Course stored in the current node.
    // If no match is found, an empty Course object is returned.
    Course Search(string courseNumber) {
        Node* currentNode = root;

        while (currentNode != nullptr) {
            if (currentNode->course.courseNumber == courseNumber) {
                return currentNode->course;
            }

            if (courseNumber < currentNode->course.courseNumber) {
                currentNode = currentNode->left;
            }
            else {
                currentNode = currentNode->right;
            }
        }

        Course course;
        return course;
    }

    // Prints the full Course list by starting an in-order traversal at root.
    void PrintCourseList() {
        printInOrder(root);
    }
};

// Removes extra spaces and line-ending characters from a CSV field.
// This also lets the program recognize a field containing only spaces as blank.
string Trim(string text) {
    size_t first = text.find_first_not_of(" \t\r\n");

    if (first == string::npos) {
        return "";
    }

    size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

// Reads course data from the provided CSV file, checks the file for errors,
// creates Course objects, validates prerequisite relationships, and inserts
// all valid Courses into the binary search tree.
bool LoadCourses(string filename, BinarySearchTree& courseTree) {
    // Courses are stored temporarily here so the entire file can be
    // validated before any data is inserted into the tree.
    vector<Course> parsedCourses;

    ifstream file(filename);

    // Stop loading if the file cannot be found or opened.
    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return false;
    }

    bool fileIsValid = true;
    string line;

    // Read the file one line at a time.
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> tokens;
        string token;

        // Split the current line wherever a comma appears.
        // The first token should be the course number, the second should
        // be the course title, and any remaining tokens are prerequisites.
        while (getline(ss, token, ',')) {
            // Trimming also removes any Windows carriage return (\r).
            tokens.push_back(Trim(token));
        }

        // Every valid line must contain at least a course number and title.
        // Dr. Webb also recommended checking that these fields are not blank.
        if (tokens.size() < 2 ||
            tokens[0].empty() ||
            tokens[1].empty()) {

            cout << "Error: Invalid file format." << endl;
            fileIsValid = false;
            break;
        }

        // Create one Course object from the current line.
        Course course;
        course.courseNumber = tokens[0];
        course.courseTitle = tokens[1];

        /*
         * A Course may have no prerequisites, so blank fields at the end
         * of a line are allowed. However, a blank prerequisite should not
         * appear before another actual prerequisite value.
         */
        bool blankPrerequisiteFound = false;

        for (size_t i = 2; i < tokens.size(); ++i) {
            if (tokens[i].empty()) {
                blankPrerequisiteFound = true;
            }
            else {
                if (blankPrerequisiteFound) {
                    cout << "Error: Invalid blank prerequisite." << endl;
                    fileIsValid = false;
                    break;
                }

                course.prerequisites.push_back(tokens[i]);
            }
        }

        if (fileIsValid == false) {
            break;
        }

        // Check the Courses already read from the file to make sure the same
        // course number has not been listed more than once.
        for (Course storedCourse : parsedCourses) {
            if (storedCourse.courseNumber == course.courseNumber) {
                cout << "Error: Duplicate course number." << endl;
                fileIsValid = false;
                break;
            }
        }

        if (fileIsValid == false) {
            break;
        }

        // Store the completed Course temporarily until validation is finished.
        parsedCourses.push_back(course);
    }

    file.close();

    if (fileIsValid == false) {
        return false;
    }

    // An empty file has no course information to load.
    if (parsedCourses.empty()) {
        cout << "Error: Course data file is empty." << endl;
        return false;
    }

    // Make sure every prerequisite listed in the file matches an actual
    // Course number that also exists in the input data.
    for (Course course : parsedCourses) {
        for (string prerequisite : course.prerequisites) {
            bool prerequisiteFound = false;

            for (Course storedCourse : parsedCourses) {
                if (storedCourse.courseNumber == prerequisite) {
                    prerequisiteFound = true;
                    break;
                }
            }

            if (prerequisiteFound == false) {
                cout << "Error: Prerequisite course not found." << endl;
                fileIsValid = false;
                break;
            }
        }

        if (fileIsValid == false) {
            break;
        }
    }

    if (fileIsValid == false) {
        return false;
    }

    // Replace older course data only after the new file is fully valid.
    // Clearing prevents duplicates when Option 1 is selected again.
    courseTree.Clear();

    // After the entire file has passed validation, insert each Course
    // into the binary search tree.
    for (Course course : parsedCourses) {
        courseTree.Insert(course);
    }

    return true;
}

// Searches for one Course and prints its course number, title, and
// prerequisite information.
void PrintCourseInformation(BinarySearchTree& courseTree,
    string courseNumber) {

    // Convert the user's entry to uppercase so input such as "csci400"
    // will still match the Course number stored as "CSCI400".
    for (char& character : courseNumber) {
        character = toupper(character);
    }

    Course course = courseTree.Search(courseNumber);

    // An empty course number means Search did not find a matching Course.
    if (course.courseNumber.empty()) {
        cout << "Course not found." << endl;
        return;
    }

    cout << course.courseNumber << ", "
        << course.courseTitle << endl;

    // Courses without prerequisites are identified separately.
    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
        return;
    }

    cout << "Prerequisites:" << endl;

    // Search for each prerequisite Course so both its number and title
    // can be displayed to the adviser.
    for (string prerequisite : course.prerequisites) {
        Course prerequisiteCourse = courseTree.Search(prerequisite);

        if (!prerequisiteCourse.courseNumber.empty()) {
            cout << prerequisiteCourse.courseNumber << ", "
                << prerequisiteCourse.courseTitle << endl;
        }
    }
}

int main() {
    // Main binary search tree used throughout the program.
    BinarySearchTree courseTree;

    int userChoice = 0;

    // Keeps track of whether valid course data has been loaded before
    // allowing the user to print or search the Course information.
    bool coursesLoaded = false;

    cout << "Welcome to the course planner." << endl;

    // Continue displaying the menu until the user chooses option 9.
    while (userChoice != 9) {
        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << endl;

        cout << "What would you like to do? ";

        // Make sure the user enters a numeric menu option.
        // If cin fails because letters or other invalid input were entered,
        // clear the error and discard the invalid characters before continuing.
        if (!(cin >> userChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter 1, 2, 3, or 9."
                << endl;

            continue;
        }

        // Option 1 loads and validates the CSV file.
        if (userChoice == 1) {
            string filename;

            cout << "Enter the course data filename: ";
            getline(cin >> ws, filename);

            if (LoadCourses(filename, courseTree)) {
                coursesLoaded = true;
                cout << "Courses loaded successfully." << endl;
            }
        }

        // Option 2 prints all Courses in alphanumeric order.
        else if (userChoice == 2) {
            if (coursesLoaded == false) {
                cout << "Please load the course data first." << endl;
            }
            else {
                cout << "Here is a sample schedule:" << endl;
                cout << endl;

                courseTree.PrintCourseList();
            }
        }

        // Option 3 searches for one Course and prints its information.
        else if (userChoice == 3) {
            if (coursesLoaded == false) {
                cout << "Please load the course data first." << endl;
            }
            else {
                string courseNumber;

                cout << "What course do you want to know about? ";
                cin >> courseNumber;

                PrintCourseInformation(courseTree, courseNumber);
            }
        }

        // Option 9 ends the program.
        else if (userChoice == 9) {
            cout << "Thank you for using the course planner!" << endl;
        }

        // Any other numeric option is outside the allowed menu choices.
        else {
            cout << userChoice
                << " is not a valid option." << endl;
        }
    }

    return 0;
}
