#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

vector<string> read (string dir)
{
    vector<string> ids;

    fstream read ("data/" + dir + ".csv");
    if (read.fail() == true) { cout << "Failed..."; return ids; } 
    string line;
    while (read.good() == true)
    {
        getline (read, line);
        cout << "Reading: " << line << endl;
     
        int endOfId = line.find ('"', 1);
        string id = line.substr (1, endOfId - 1);
        if (id == "id") continue; // Skip the header
        ids.push_back (id);
    }
    read.close ();
    return ids;
}
string IdToString(string id, string dir)
{
    fstream read ("data/" + dir + ".csv");
    string line;
    while (read.good() == true)
    {
        getline (read, line);
     
        int endOfId = line.find ('"', 1);
        string currentId = line.substr (1,endOfId - 1);

        if (id == currentId)
        {
            return line;
        }
    }
    cout << "returning nothing " << endl;
    
    
    read.close ();
    return id;
}
int main ()
{
    // Input
    cout << "First file to read from: ";
    string r1;
    cin >> r1;
    cout << "Second file to compare from: ";
    string r2;
    cin >> r2;

    vector<string> beforeIds = read (r1);
    vector<string> afterIds  = read (r2);

    cout << "Before lines size : " << beforeIds.size() << endl;
    cout << "After lines size  : " << afterIds.size() << endl;

    vector<string> removed;
    vector<string> added;

    for (string id : beforeIds)
        if (find(afterIds.begin(), afterIds.end(), id) == afterIds.end())
            removed.push_back(id);
    for (string id : afterIds)
        if (find(beforeIds.begin(), beforeIds.end(), id) == beforeIds.end())
            added.push_back(id);

    // Write
    ofstream write ("data/results" + to_string(time(0)) + ".txt");

    write << "--- REMOVED ---\n";
    for (string id : removed)
        write << IdToString(id, r1) << endl;

    write << "\n--- ADDED ---\n";
    for (string id : added)
        write << IdToString(id, r2) << endl;

    write.close();

    return 0;
}