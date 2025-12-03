
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Date {
private:
    int day, month, year;

public:
    Date() {
        day = 1;
        month = 1;
        year = 1990;
    }

    Date(const Date& refDate) {
        day = refDate.day;
        month = refDate.month;
        year = refDate.year;
    }

    Date(int d, int m, int y) {
        set(d, m, y);
    }

    ~Date() {}

    Date& operator=(const Date& refDate) {
        if (this != &refDate) {
            day = refDate.day;
            month = refDate.month;
            year = refDate.year;
        }
        return *this;
    }

    char* toString() const {
        char* result = new char[11];
        char dayStr[3] = "00", monthStr[3] = "00", yearStr[5] = "0000";

        int tempDay = day;
        if (tempDay < 10) {
            dayStr[1] = '0' + tempDay;
        }
        else {
            dayStr[0] = '0' + (tempDay / 10);
            dayStr[1] = '0' + (tempDay % 10);
        }

        int tempMonth = month;
        if (tempMonth < 10) {
            monthStr[1] = '0' + tempMonth;
        }
        else {
            monthStr[0] = '0' + (tempMonth / 10);
            monthStr[1] = '0' + (tempMonth % 10);
        }

        int tempYear = year;
        yearStr[0] = '0' + (tempYear / 1000);
        yearStr[1] = '0' + ((tempYear / 100) % 10);
        yearStr[2] = '0' + ((tempYear / 10) % 10);
        yearStr[3] = '0' + (tempYear % 10);

        strcpy_s(result, 11, dayStr);
        strcat_s(result, 11, "/");
        strcat_s(result, 11, monthStr);
        strcat_s(result, 11, "/");
        strcat_s(result, 11, yearStr);

        return result;
    }

    void set(int d, int m, int y) {
        if (m < 1 || m > 12 || y < 1 || d < 1) {
            day = 1;
            month = 1;
            year = 1990;
            return;
        }

        bool isLeap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        int maxDays = 31;

        if (m == 4 || m == 6 || m == 9 || m == 11) {
            maxDays = 30;
        }
        else if (m == 2) {
            maxDays = isLeap ? 29 : 28;
        }

        if (d <= maxDays) {
            day = d;
            month = m;
            year = y;
        }
        else {
            day = 1;
            month = 1;
            year = 1990;
        }
    }

    int getDay() { return day; }
    int getMonth() { return month; }
    int getYear() { return year; }

    bool isLeapYear() {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int compare(const Date& refDate) {
        if (year != refDate.year) return year < refDate.year ? -1 : 1;
        if (month != refDate.month) return month < refDate.month ? -1 : 1;
        if (day != refDate.day) return day < refDate.day ? -1 : 1;
        return 0;
    }

    void copyFrom(const Date& refDate) {
        day = refDate.day;
        month = refDate.month;
        year = refDate.year;
    }
};

istream& operator>>(istream& inputStream, Date& currentDate) {
    int dTemp, mTemp, yTemp;
    if (inputStream >> dTemp >> mTemp >> yTemp) {
        currentDate.set(dTemp, mTemp, yTemp);
        return inputStream;
    }
    return inputStream;
}

ostream& operator<<(ostream& outputStream, const Date& constReferenceDate) {
    char* tempStr = constReferenceDate.toString();
    outputStream << tempStr;
    delete[] tempStr;
    return outputStream;
}

bool readSafeInput(int& day, int& month, int& year) {
    if (cin >> day >> month >> year) {
        if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1) {
            return true;
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return false;
}

int main() {
    int n;
    cout << "Enter number of dates: ";
    if (!(cin >> n)) {
        cout << "Invalid input";
        return 1;
    }

    Date* dates = new Date[n];

    ifstream inFile("dates.txt");
    if (inFile.is_open()) {
        bool isFileReadSuccessful = true;
        for (int i = 0; i < n; i++) {
            int dTemp, mTemp, yTemp;
            if (inFile >> dTemp >> mTemp >> yTemp) {
                dates[i].set(dTemp, mTemp, yTemp);
            }
            else {
                dates[i].set(1, 1, 1990);
                isFileReadSuccessful = false;
            }
        }
        inFile.close();
        if (!isFileReadSuccessful) {
            cout << "File read error using defaults\n";
        }
    }
    else {
        cout << "File not found using defaults\n";
        for (int i = 0; i < n; i++) {
            dates[i].set(1, 1, 1990);
        }
    }

    cout << "\nDates from file:\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << dates[i] << endl;
    }

    char choice;
    cout << "\nDo you want to modify a date? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        int idx, d, m, y;
        cout << "Enter date number to modify (1-" << n << "): ";
        cin >> idx;
        if (idx >= 1 && idx <= n) {
            cout << "Enter new date (day month year): ";
            if (readSafeInput(d, m, y)) {
                dates[idx - 1].set(d, m, y);
            }
            else {
                cout << "Invalid input, keeping old date.\n";
            }
        }
        else {
            cout << "Invalid index!\n";
        }
    }

    ofstream outFile("dates.txt");
    if (outFile.is_open()) {
        cout << "\nFinal dates:\n";
        for (int i = 0; i < n; i++) {
            cout << i + 1 << ". " << dates[i] << endl;
            outFile << dates[i] << endl;
        }
        outFile.close();
    }
    else {
        cout << "Write failed\n";
    }

    for (int i = 0; i < n; i++) {
        cout << dates[i] << " is " << (dates[i].isLeapYear() ? "" : "not ") << "leap year\n";
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int cmp = dates[i].compare(dates[j]);
            cout << dates[i] << " vs " << dates[j] << ": ";
            if (cmp < 0) cout << "earlier";
            else if (cmp > 0) cout << "later";
            else cout << "same";
            cout << endl;
        }
    }

    delete[] dates;
    return 0;
}
