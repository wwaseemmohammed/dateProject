# dateProject
A Date Manager (C++)
A simple C++ console application that defines a Date class to manage dates (day, month, year) with value validation, string formatting, comparison operations, and support for reading from and writing to a text file.

Project features
Defines a Date class that includes:

A default constructor that sets the date to 01/01/1990.

A copy constructor and assignment operator to safely copy objects.

A set(int d, int m, int y) function that validates the day, month, and year (including the number of days in each month and leap years) and falls back to the default date if the input is invalid.

Getter functions getDay, getMonth, and getYear to access individual components.
A toString() function that returns the date in DD/MM/YYYY format.

An isLeapYear() function to check whether the year is a leap year.

A compare(const Date& other) function that returns:

-1 if the current date is earlier than the other date

0 if both dates are equal

1 if the current date is later than the other date.

A copyFrom(const Date& other) function to copy another date into the current object.

Overloaded input and output operators >> and << to easily read and print dates using standard streams and files.

What the main program does
Prompts the user to enter the number of dates n, then dynamically allocates an array of Date objects of size n.

Attempts to read n dates from a text file named dates.txt (format: day month year on each line).

If reading succeeds, the dates are stored in the array.

If reading fails or the file is missing, all dates are set to the default value 01/01/1990 and a warning message is printed.

Displays all dates loaded from the file in the console.

Allows the user to choose a specific date (by index from 1 to n) and modify it by entering new values, with validation handled by the helper function readSafeInput.

After editing, prints the final dates to the console and writes them back to dates.txt so they are preserved for the next run.
For each date, checks whether its year is a leap year and prints the result.

Compares every pair of dates in the array and prints whether each pair is earlier, later, or the same.

Input file structure
File name: dates.txt

Format:

Each line contains three integers: day month year

Example:

1 1 2000

29 2 2020

The file should contain at least n lines; otherwise, missing entries are replaced with thedefault date.

Future improvements
Add a menu-driven interface to perform multiple operations on dates without restarting the program.

Support additional date formats (such as YYYY-MM-DD or localized formats).

Add unit tests to verify the correctness of key functions, especially validation and leap-year logic.

Split the Date class into header (Date.h) and implementation (Date.cpp) files for better project organization.
