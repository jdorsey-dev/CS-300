# CS-300: Data Structures and Algorithms

## Project Overview

This repository contains work completed for CS-300: Data Structures and Algorithms at Southern New Hampshire University. The projects focused on developing a course-planning program for academic advisors at ABCU.

In Project One, I designed pseudocode and analyzed the runtime and memory requirements of three data structures: vectors, hash tables, and binary search trees. In Project Two, I used C++ to build the course-planning program with a binary search tree.

## Project Reflection

### What was the problem you were solving in the projects for this course?

The goal was to create a program that would help academic advisors access course information more easily. The program needed to read course data from a CSV file, display the courses in alphanumeric order, and allow users to search for individual courses and view their prerequisites. Before writing the final program, I had to compare different data structures to determine which would work best for these requirements.

### How did you approach the problem? Consider why data structures are important to understand.

I started by developing pseudocode for vectors, hash tables, and binary search trees. I then compared their runtime and memory requirements, along with the advantages and disadvantages of each structure. I ultimately chose a binary search tree because it supports searching by course number and can print courses in alphanumeric order through an in-order traversal. This helped me understand that choosing a data structure isn't just about which one is fastest, but which one best fits what the program needs to do.

### How did you overcome any roadblocks you encountered while going through the activities or project?

One of the challenges I encountered was getting the program to locate and read the CSV file correctly. I had to check the file location and make sure the program was looking in the right place. I also ran into a build issue when the executable was still in use. Working through these problems reminded me how important it is to test programs and troubleshoot one issue at a time. Breaking the program into smaller functions also made it easier to understand what was happening when something wasn't working.

### How has your work on this project expanded your approach to designing software and developing programs?

Before this course, I mainly focused on getting my programs to work correctly. These projects helped me think more about how a program should be designed before writing the code. Comparing the different data structures showed me how much a design decision can affect performance, memory usage, and the amount of work required to complete a task. I also gained more experience using pseudocode to plan a program before implementing it in C++.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

These projects reinforced the importance of keeping code organized and easy to follow. In Project Two, I separated tasks such as loading and validating course data, searching for courses, and printing course information into their own functions. I also used descriptive names and comments to explain what different parts of the program were doing. Going forward, I want to continue writing programs this way because it makes the code easier to troubleshoot, update, and understand when I come back to it later.

## Repository Contents

- **Project One: Runtime and Memory Analysis** - Pseudocode and analysis comparing vectors, hash tables, and binary search trees, including the reasoning behind my final data structure recommendation.
- **Project Two: Advising Assistance Program** - C++ source code for a course-planning program that loads and validates course data, stores courses in a binary search tree, prints courses in alphanumeric order, and displays course prerequisite information.
