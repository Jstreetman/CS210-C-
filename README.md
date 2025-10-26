# CS210-C++ Project

# First Shoutout to my instructor :D

# Corner Grocer Project

## Project Summary  
The Corner Grocer project was created to help a grocery store analyze which items customers purchase most often. The store wanted to rearrange its produce section based on the popularity of items. To solve this problem, I built a C++ program that reads a text file of purchased items, counts how often each one appears, and displays the results in different ways. The program can show an item’s frequency, print a full list of item counts, and display a histogram that gives a visual view of which items sell most frequently.

## What I Did Well  
I did a good job organizing the code using a class that keeps the logic clean and easy to follow. I also focused on making sure the program runs smoothly for users by including input validation and helpful messages. The program automatically creates a backup file when it starts, which shows attention to detail and helps prevent data loss.

## Areas for Improvement  
I could enhance the code by adding better error handling and allowing the user to choose different input files instead of just one default file. This would make the program more flexible for real-world use. I could also improve efficiency by using unordered maps for faster lookups, especially if the file becomes very large. Adding color to the histogram or a simple graphical interface could also make the output more engaging and easier to understand.

## Challenges and How I Overcame Them  
The most challenging part was getting the map to handle items correctly in a case-insensitive way while still keeping the original item names for display. I solved this by using a helper function that converted all text to lowercase for counting but stored the first version of each item for printing. I used online C++ documentation and coding forums to learn more about string manipulation and the map container, which helped me get through those challenges.

## Tools and Resources Added to My Support Network  
I am adding resources like C++ reference sites, official documentation, and online coding communities where developers share advice and solutions. I also plan to use GitHub more actively to track my changes, read other people’s code, and continue improving my own projects.

## Transferable Skills  
The skills I gained from this project include using classes to organize code, reading and writing files, and using maps to store and search data efficiently. These skills can be applied to many other programming projects, including data analysis, inventory systems, and web applications. I also improved my ability to write clear code with comments, which is useful for teamwork and professional development.

## Code Maintainability and Readability  
I made the program maintainable and readable by using clear variable names and adding comments that explain each part of the code. The logic is divided into smaller functions that make it easy to find and update specific sections without breaking the whole program. Using a class structure keeps the data and behavior organized, which will make it simple to expand the program later if new features are needed, such as database integration or a graphical user interface.
