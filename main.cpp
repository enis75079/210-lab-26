/*

lab25: data structures races
COMSC-210
Naveen Islam

*/
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;
using namespace std::chrono;

// function prototypes
// reading functions
void readingVec(vector<string>&);
void readingList(list<string>&);
void readingSet(set<string>&);

// sorting functions
void sortingVec(vector<string>&);
void sortingList(list<string>&);
int sortingSet(set<string>&);

// inserting functions
void insertingVec(vector<string>&, string);
void insertingList(list<string>&, string);
void insertingSet(set<string>&, string);

// deleting functions
void deletingVec(vector<string>&);
void deletingList(list<string>&);
int deletingSet(set<string>&);

// main function
int main() {
    const int RUNNUM = 15;

    long long totalReadV = 0;
    long long totalReadL = 0;
    long long totalReadS = 0;

    long long totalSortV = 0;
    long long totalSortL = 0;
    long long totalSortS = 0;

    long long totalInsertV = 0;
    long long totalInsertL = 0;
    long long totalInsertS = 0;

    long long totalDeleteV = 0;
    long long totalDeleteL = 0;
    long long totalDeleteS = 0;

    long long results[3][4][RUNNUM] = {};
    long long total[3][4] = {};

    // output header
    for (int i = 0; i < RUNNUM; i++) {
        // create vector, list, and set object
        vector<string> testv;
        list<string> testl;
        set<string> tests;

        // reading race (changed to microseconds due to insert operations completing too quickly)
        auto start = high_resolution_clock::now();
        readingVec(testv);
        auto end = high_resolution_clock::now();
        auto durationV = duration_cast<microseconds>(end - start);
        results[0][0][i] = durationV.count();
        total[0][0] += results[0][0][i];

        start = high_resolution_clock::now();
        readingList(testl);
        end = high_resolution_clock::now();
        auto durationL = duration_cast<microseconds>(end - start);
        results[0][1][i] = durationL.count();
        total[0][1] += results[0][1][i];

        start = high_resolution_clock::now();
        readingSet(tests);
        end = high_resolution_clock::now();
        auto durationS = duration_cast<microseconds>(end - start);
        results[0][2][i] = durationS.count();
        total[0][2] += results[0][2][i];

        // sorting race (changed to microseconds due to insert operations completing too quickly)
        start = high_resolution_clock::now();
        sortingVec(testv);
        end = high_resolution_clock::now();
        auto sortDurationV = duration_cast<microseconds>(end - start);
        results[1][0][i] = sortDurationV.count();
        total[1][0] += results[1][0][i];

        start = high_resolution_clock::now();
        sortingList(testl);
        end = high_resolution_clock::now();
        auto sortDurationL = duration_cast<microseconds>(end - start);
        results[1][1][i] = sortDurationL.count();
        total[1][1] = results[1][1][i];

        results[1][2][i] = sortingSet(tests);
        total[1][2] += results[1][2][i];

        // inserting race (changed to microseconds due to insert operations completing too quickly)
        start = high_resolution_clock::now();
        insertingVec(testv, "TESTCODE");
        end = high_resolution_clock::now();
        auto insertDurationV = duration_cast<microseconds>(end - start);
        results[2][0][i] = insertDurationV.count();
        total[2][0] += results[2][0][i];
        
        start = high_resolution_clock::now();
        insertingList(testl, "TESTCODE");
        end = high_resolution_clock::now();
        auto insertDurationL = duration_cast<microseconds>(end - start);
        results[2][1][i] = insertDurationL.count();
        total[2][1] += results[2][1][i];

        start = high_resolution_clock::now();
        insertingSet(tests, "TESTCODE");
        end = high_resolution_clock::now();
        auto insertDurationS = duration_cast<microseconds>(end - start);
        results[2][2][i] = insertDurationS.count();
        total[2][2] += results[2][2][i];

        // deleting race (changed to microseconds due to insert operations completing too quickly)
        start = high_resolution_clock::now();
        deletingVec(testv);
        end = high_resolution_clock::now();
        auto deleteDurationV = duration_cast<microseconds>(end - start);
        results[3][0][i] = deleteDurationV.count();
        total[3][0] += results[3][0][i];

        start = high_resolution_clock::now();
        deletingList(testl);
        end = high_resolution_clock::now();
        auto deleteDurationL = duration_cast<microseconds>(end - start);
        results[3][1][i] = deleteDurationL.count();
        total[3][1] += results[3][1][i];

        start = high_resolution_clock::now();
        deletingSet(tests);
        end = high_resolution_clock::now();
        auto deleteDurationS = duration_cast<microseconds>(end - start);
        results[3][2][i] = deleteDurationS.count();
        total[3][2] += results[3][2][i];
    }

    // calc
    cout << "Number of simulations: " << RUNNUM << endl;
    cout << left << setw(10) << "Operation" << setw(10) << "Vector" << setw(10) << "List" << setw(10) << "Set" << endl;
    string opTitles[4] = {"Read", "Sort", "Insert", "Delete"};
    for (int i = 0; i < 4; i++) {
        cout << left << setw(10) << opTitles[i];
        for (int j = 0; j < 3; j++) {
            cout << setw(10) << total[i][j] / RUNNUM;
        }
        cout << endl;
    }
    return 0;
}


// readingVec function. reads a file and inputs the values into the parameter vector
void readingVec(vector<string>& v) {
    string read;
    ifstream file("codes.txt");
    while(getline(file, read)) {
        v.push_back(read);
    }
    file.close();
}

// readinglist function. reads a file and inputs the values into the parameter list
void readingList(list<string>& l) {
    string read;
    ifstream file("codes.txt");
    while(getline(file, read)) {
        l.push_back(read);
    }
    file.close();
}

// readingSet function. reads a file and inputs the values into the parameter set
void readingSet(set<string>& s) {
    string read;
    ifstream file("codes.txt");
    while(getline(file, read)) {
        s.insert(read);
    }
    file.close();
}

// sortingVec function. sorts the parameter vector by increasing
void sortingVec(vector<string>& v) {
    sort(v.begin(), v.end());
}

// sortingVec function. sorts the parameter list by increasing
void sortingList(list<string>& s) {
    s.sort();
}

// sortingSet function. set is already sorted, so just returns -1
int sortingSet(set<string>& s) {
    return -1;
}

// insertingVec function. inserts the parameter string into the middle of the parameter vector
void insertingVec(vector<string>& v, string stringInsert) {
    int middle = v.size() / 2;
    v.insert(v.begin() + middle, stringInsert);
}

// insertingList function. inserts the parameter string into the middle of the parameter list
void insertingList(list<string>& l, string stringInsert) {
    int middle = l.size() / 2;
    auto it = l.begin();
    advance(it, middle);
    l.insert(it, stringInsert);
}

// insertingSet function. inserts the parameter string the parameter set
void insertingSet(set<string>& s, string stringInsert) {
    s.insert(stringInsert);
}

// deletingVec function. deletes the middle string of the parameter vector
void deletingVec(vector<string>& v) {
    int middle = v.size() / 2;
    v.erase(v.begin() + middle);
}

// deletingList function. deletes the middle string of the parameter list
void deletingList(list<string>& l) {
    int middle = l.size() / 2;
    auto it = l.begin();
    advance(it, middle);
    l.erase(it);
}

// deletingSet function. deletes the middle string of the parameter set
int deletingSet(set<string>& s) {
    int middle = s.size() / 2;
    auto it = s.begin();
    advance(it, middle);
    s.erase(it);
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/