#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>  /* pair */
#include <list>  /* list */
#include <iomanip>  /* setw() */
using namespace std;

Bug* searchByID(vector<Bug*>& bug_vector, int id)
{
    for (Bug* pBug : bug_vector)
    {
        if (pBug->getID() == id)
        {
            return pBug;
        }
    }
    return nullptr;
}

bool parseLine(string const& line, vector<Bug*>& bug_vector)
{
    bool success = false;
    try
    {
        stringstream strStream(line);
        string field;

        string type;
        getline(strStream, type, ';');

        int id;
        getline(strStream, field, ';');
        id = stoi(field);

        int x;
        getline(strStream, field, ';');
        x = stoi(field);

        int y;
        getline(strStream, field, ';');
        y = stoi(field);

        int direction;
        getline(strStream, field, ';');
        direction = stoi(field);
        
        int size;
        getline(strStream, field, ';');
        size = stoi(field);

        Bug* pBug = nullptr;

        if (type == "C")
        {
            pBug = new Crawler(id, x, y, direction, size);
        }
        else if (type == "H")
        {
            int hopLength;
            getline(strStream, field, ';');
            hopLength = stoi(field);

            pBug = new Hopper(id, x, y, direction, size, hopLength);
        }

        // check if bug ID exists before pushing; if bug ID exists then bug is duplicate
        if (searchByID(bug_vector, id) != nullptr)
        {
            cout << "[Duplicate bug detected]<-";
        }
        else
        {
            bug_vector.push_back(pBug);
            success = true;
        }
    }
    catch (invalid_argument const& e)
    {
        cout << "[Error occured when processing - " << e.what() << "]<-";
    }
    catch (out_of_range const& e)
    {
        cout << "[Error occured when processing - Integer Overflow]<-";
    }
    return success;
}

void loadBugsData(vector<Bug*>& bug_vector)
{
    string line;
    ifstream inStream("bugs.txt");
    bool success = false;
    bool allSuccess = true;

    if (inStream.good())
    {
        while (getline(inStream, line))
        {
            success = parseLine(line, bug_vector);
            if (!success)
            {
                cout << "[Fail to process line of data]\n";
                allSuccess = false;
            }
        }
        inStream.close();
        if (allSuccess)
        {
            cout << "[All data loaded successfully]\n";
        }
        else
        {
            cout << "[Finished loading data; some data failed to be processed]\n";
        }
    }
    else
    {
        cout << "[File doesn't exist]\n";
    }
}

void initialiseBugBoard(vector<Bug*>& bug_vector)
{
    cout << "\nOption: Initialise Bug Board\n\n";
    loadBugsData(bug_vector);
}

void displayAllBugs(vector<Bug*>& bug_vector)
{
    cout << "\nOption: Display All Bugs\n\nList of bugs:\n";
    if (bug_vector.size() == 0)
    {
        cout << "None\n";
    }
    else
    {
        cout << "ID    Type      Location   Size    Direction   Hop Length    Status\n";
        for (int i = 0; i < bug_vector.size(); i++)
        {
            Bug* pBug = bug_vector[i];
            if (typeid(*pBug) == typeid(Crawler))
            {
                cout << left << setw(6) << pBug->getID() << setw(11) << "Crawler" << setw(11) << pBug->getPositionInBrackets() << setw(9) << pBug->getSize() << setw(24) << pBug->getDirectionInText() << pBug->getStatusInText() << endl;
            }
            else if (typeid(*pBug) == typeid(Hopper))
            {
                // Dynamic casting
                // Reference: https://www.learncpp.com/cpp-tutorial/12-9-dynamic-casting/
                Hopper* pHopper = dynamic_cast<Hopper*>(pBug);
                cout << pHopper->getID() << "   Hopper     " << pHopper->getPositionInBrackets() << "      " << pHopper->getSize() << "       " << pHopper->getDirectionInText() << "          " << pHopper->getHopLength() << "          " << pHopper->getStatusInText() << endl;
            }
        }
        cout << "(Total: " << bug_vector.size() << " bugs)\n";
    }
}

void findBug(vector<Bug*>& bug_vector)
{
    cout << "\nOption: Find a Bug\n";
    int id;
    string idStr;
    cout << "\nEnter bug ID: ";
    getline(cin, idStr);
    stringstream(idStr) >> id;
    Bug* pBug = searchByID(bug_vector, id);
    if (pBug == nullptr)
    {
        cout << "\nBug not found\n";
    }
    else
    {
        cout << "\nBug details:\n";
        if (typeid(*pBug) == typeid(Crawler))
        {
            cout << "ID    Type      Location   Size    Direction    Status\n";
            cout << pBug->getID() << "   Crawler    " << pBug->getPositionInBrackets() << "      " << pBug->getSize() << "       " << pBug->getDirectionInText() << "        " << pBug->getStatusInText() << endl;
        }
        else if (typeid(*pBug) == typeid(Hopper))
        {
            Hopper* pHopper = dynamic_cast<Hopper*>(pBug);
            cout << "ID    Type      Location   Size    Direction   Hop Length    Status\n";
            cout << pHopper->getID() << "   Hopper     " << pHopper->getPositionInBrackets() << "      " << pHopper->getSize() << "       " << pHopper->getDirectionInText() << "          " << pHopper->getHopLength() << "          " << pHopper->getStatusInText() << endl;
        }
    }
}

void tapBugBoard(vector<Bug*>& bug_vector)
{
    cout << "\nOption: Tap the Bug Board\n";
    for (Bug* pBug : bug_vector)
    {
        pBug->move();
    }
    cout << "\nAll bugs have moved!\n";
}

void displayLifeHistory(vector<Bug*>& bug_vector)
{
    cout << "\nOption: Display Life History of All Bugs\n\nList of bugs:\n";
    if (bug_vector.size() == 0)
    {
        cout << "None\n";
    }
    else
    {
        for (int i = 0; i < bug_vector.size(); i++)
        {
            Bug* pBug = bug_vector[i];
            cout << pBug->getID();
            if (typeid(*pBug) == typeid(Crawler))
            {
                cout << "   Crawler   ";
            }
            else if (typeid(*pBug) == typeid(Hopper))
            {
                cout << "   Hopper    ";
            }
            cout << "Path: " << pBug->getPathInText();
            if (pBug->getStatusInText() == "Alive")
            {
                cout << ", Alive!\n";
            }
            else
            {
                cout << " Eaten by \n";
            }
        }
        cout << "(Total: " << bug_vector.size() << " bugs)\n";
    }
}

//void saveStudentData(vector<Student>& students)
//{
//    ofstream outStream("students.txt");
//
//    if (outStream.good())
//    {
//        for (Student& s : students)
//        {
//            outStream << s.getStudentID() << ";" << s.getTitle() << ";" << s.getName() << ";" << s.getSingleIntFromScores() << ";" << s.getCourse() << endl;
//        }
//        outStream.close();
//        cout << "\n[File saved successfully]\n";
//    }
//    else
//    {
//        cout << "\n[Unable to open file]\n";
//    }
//}

void run()
{
    vector<Bug*> bug_vector;

    cout << "Welcome to the Bug Board!\n";
    int option;
    do
    {
        cout << "\nMENU\n";
        cout << "1. Initialise Bug Board\n";
        cout << "2. Display All Bugs\n";
        cout << "3. Find a Bug\n";
        cout << "4. Tap the Bug Board\n";
        cout << "5. Display Life History of All Bugs\n";
        cout << "6. Display All Cells\n";
        cout << "7. Exit\n";
        cout << "\nEnter Option: ";
        cin >> option;
        while (cin.fail() || (option < 1 || option > 7))
        {
            cout << "[Invalid Option - [1,7] only]\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "\nEnter Option: ";
            cin >> option;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (option)
        {
        case 1: initialiseBugBoard(bug_vector); break;
        case 2: displayAllBugs(bug_vector); break;
        case 3: findBug(bug_vector); break;
        case 4: tapBugBoard(bug_vector); break;
        case 5: displayLifeHistory(bug_vector); break;
        case 7: cout << "\nGoodbye\n"; break;
        }
    } while (option != 7);

    //saveStudentData(students);
}