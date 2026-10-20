# CS-300: Data Structures and Algorithms

## Project Overview

This repository contains my work from CS-300 at Southern New Hampshire University. For these projects, I worked on designing and building a course-planning program that academic advisors at ABCU could use to look up courses and their prerequisites.

In Project One, I compared vectors, hash tables, and binary search trees to figure out which would work best for the program. In Project Two, I took what I learned and built the program in C++ using a binary search tree.

## Project Reflection

### What was the problem you were solving in the projects for this course?

The main goal was to build a program that would make it easier for academic advisors to look up course information. The program needed to read course data from a CSV file, print a list of courses in alphanumeric order, and let advisors search for a specific course to see its prerequisites. Before building the program, I had to figure out which data structure made the most sense for what we were trying to accomplish.

### How did you approach the problem? Consider why data structures are important to understand.

I started by writing pseudocode for three different data structures: a vector, a hash table, and a binary search tree. From there, I looked at their runtime and memory requirements and compared what each one did well and where it might struggle. I ended up choosing a binary search tree because it could search for courses and print them in order without needing an extra sorting step. One thing I learned from this was that there isn't really one data structure that's best for everything. It depends on what you need the program to do.

### How did you overcome any roadblocks you encountered while going through the activities or project?

I ran into a few issues while working on the projects. One was getting the program to find and read the CSV file correctly. I had to go back and check where the file was located and where the program was trying to find it. I also had a build issue because the executable was still running. Neither problem was particularly complicated once I figured out what was happening, but they were frustrating at first. I've gotten better about slowing down, checking things one at a time, and trying to understand what's causing a problem instead of just changing code until something works.

### How has your work on this project expanded your approach to designing software and developing programs?

I think the biggest change is that I'm starting to put more thought into how I want a program to work before I start coding it. In the past, I was usually more focused on just getting everything to work. This course made me think more about why I would choose one approach over another. Working through the pseudocode and runtime analysis also showed me how much the structure of a program can affect its performance. It's something I'll definitely be paying more attention to in future projects.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

I've gotten more comfortable breaking programs into smaller functions instead of trying to do too much in one place. For Project Two, I kept things like reading the file, validating the data, searching for courses, and printing information in separate functions. I also tried to use names that made sense and comments that explained what the code was doing. I think this makes it a lot easier to go back through a program and figure out what's happening, especially when something needs to be fixed or changed later.

## Repository Contents

- **Project One: Runtime and Memory Analysis** - My comparison of vectors, hash tables, and binary search trees, including their runtime, memory requirements, and why I chose a binary search tree for the final program.
- **Project Two: Advising Assistance Program** - My C++ program that reads course information from a CSV file, stores it in a binary search tree, and lets users print the course list or search for a course and its prerequisites.
