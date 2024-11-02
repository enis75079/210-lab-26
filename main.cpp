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
    // create vector, list, and set object
    vector<string> testv;
    list<string> testl;
    set<string> tests;

    // output header
    cout << left << setw(10) << "Operation" << setw(10) << "Vector" << setw(10) << "List" << setw(10) << "Set" << endl;
    
    // reading race (changed to microseconds due to insert operations completing too quickly)
    auto start = high_resolution_clock::now();
    readingVec(testv);
    auto end = high_resolution_clock::now();
    auto durationV = duration_cast<microseconds>(end - start);

    start = high_resolution_clock::now();
    readingList(testl);
    end = high_resolution_clock::now();
    auto durationL = duration_cast<microseconds>(end - start);

    start = high_resolution_clock::now();
    readingSet(tests);
    end = high_resolution_clock::now();
    auto durationS = duration_cast<microseconds>(end - start);

    // read output
    cout << left << setw(10) << "Read" << setw(10) << durationV.count() << setw(10) << durationL.count() << setw(10) << durationS.count() << endl;

    // sorting race (changed to microseconds due to insert operations completing too quickly)
    start = high_resolution_clock::now();
    sortingVec(testv);
    end = high_resolution_clock::now();
    auto sortDurationV = duration_cast<microseconds>(end - start);

    start = high_resolution_clock::now();
    sortingList(testl);
    end = high_resolution_clock::now();
    auto sortDurationL = duration_cast<microseconds>(end - start);

    // sort output
    cout << left << setw(10) << "Sort" << setw(10) << sortDurationV.count() << setw(10) << sortDurationL.count() << setw(10) << sortingSet(tests) << endl;

    // inserting race (changed to microseconds due to insert operations completing too quickly)
    start = high_resolution_clock::now();
    insertingVec(testv, "TESTCODE");
    end = high_resolution_clock::now();
    auto insertDurationV = duration_cast<microseconds>(end - start);

    start = high_resolution_clock::now();
    insertingList(testl, "TESTCODE");
    end = high_resolution_clock::now();
    auto insertDurationL = duration_cast<microseconds>(end - start);

    start = high_resolution_clock::now();
    insertingSet(tests, "TESTCODE");
    end = high_resolution_clock::now();
    auto insertDurationS = duration_cast<microseconds>(end - start);

    // insert output
    cout << left << setw(10) << "Insert" << setw(10) << insertDurationV.count() << setw(10) << insertDurationL.count() << setw(10) << insertDurationS.count() << endl;

    // deleting race (changed to microseconds due to insert operations completing too quickly)
    start = high_resolution_clock::now();
    deletingVec(testv);
    end = high_resolution_clock::now();
    auto deleteDurationV = duration_cast<microseconds>(end - start);

    start = high_resolution_clock::now();
    deletingList(testl);
    end = high_resolution_clock::now();
    auto deleteDurationL = duration_cast<microseconds>(end - start);

    start = high_resolution_clock::now();
    deletingSet(tests);
    end = high_resolution_clock::now();
    auto deleteDurationS = duration_cast<microseconds>(end - start);

    // delete output
    cout << left << setw(10) << "Delete" << setw(10) << deleteDurationV.count() << setw(10) << deleteDurationL.count() << setw(10) << deleteDurationS.count() << endl;

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