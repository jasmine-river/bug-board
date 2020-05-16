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
#include <map>  /* map */
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

map<pair<int, int>, list<Bug*>> initialiseBugBoard(vector<Bug*>& bug_vector)
{
    cout << "\nOption: Initialise Bug Board\n\n";
    loadBugsData(bug_vector);

    // Reference for map: https://en.cppreference.com/w/cpp/container/map
    map<pair<int, int>, list<Bug*>> bug_map;

    for (Bug* pBug : bug_vector)
    {
        pair<int, int> cell = pBug->getPosition();
        list<Bug*> bug_list = bug_map[cell];
        bug_list.push_back(pBug);
        bug_map.insert_or_assign(cell, bug_list);
    }

    return bug_map;
}

void displayAllBugs(vector<Bug*>& bug_vector)
{
    cout << "\nOption: Display All Bugs\n\nList of bugs:\n";
    if (bug_vector.empty())
    {
        cout << "None\n";
    }
    else
    {
        cout << "ID    Type      Location   Size    Direction   Hop Length    Status\n";
        for (Bug* pBug : bug_vector)
        {
            if (typeid(*pBug) == typeid(Crawler))
            {
                // Reference for formatting: https://stackoverflow.com/questions/11226143/formatting-output-in-c
                cout << left << setw(6) << pBug->getID() << setw(11) << "Crawler" << setw(11) << pBug->getPositionInBrackets() << setw(9) << pBug->getSize() << setw(24) << pBug->getDirectionInText() << pBug->getStatusInText() << endl;
            }
            else if (typeid(*pBug) == typeid(Hopper))
            {
                // Dynamic casting
                // Reference: https://www.learncpp.com/cpp-tutorial/12-9-dynamic-casting/
                Hopper* pHopper = dynamic_cast<Hopper*>(pBug);
                cout << setw(6) << pHopper->getID() << setw(11) << "Hopper" << setw(11) << pHopper->getPositionInBrackets() << setw(9) << pHopper->getSize() << setw(14) << pHopper->getDirectionInText() << setw(10) << pHopper->getHopLength() << pHopper->getStatusInText() << endl;
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
            cout << left << setw(6) << pBug->getID() << setw(11) << "Crawler" << setw(11) << pBug->getPositionInBrackets() << setw(9) << pBug->getSize() << setw(11) << pBug->getDirectionInText() << pBug->getStatusInText() << endl;
        }
        else if (typeid(*pBug) == typeid(Hopper))
        {
            Hopper* pHopper = dynamic_cast<Hopper*>(pBug);
            cout << "ID    Type      Location   Size    Direction   Hop Length    Status\n";
            cout << setw(6) << pHopper->getID() << setw(11) << "Hopper" << setw(11) << pHopper->getPositionInBrackets() << setw(9) << pHopper->getSize() << setw(14) << pHopper->getDirectionInText() << setw(10) << pHopper->getHopLength() << pHopper->getStatusInText() << endl;
        }
    }
}

map<pair<int, int>, list<Bug*>> tapBugBoard(vector<Bug*>& bug_vector, map<pair<int, int>, list<Bug*>> bug_map)
{
    cout << "\nOption: Tap the Bug Board\n";
    if (bug_vector.empty())
    {
        cout << "\nThere are no bugs on the board!\n";
    }
    else
    {
        for (Bug* pBug : bug_vector)
        {
            // Before move, delete the bug from the cell
            pair<int, int> cell = pBug->getPosition();
            list<Bug*> bug_list = bug_map[cell];
            bug_list.remove(pBug);
            bug_map.insert_or_assign(cell, bug_list);

            // Only move and add to cell again if alive
            if (pBug->getStatusInText() == "Alive")
            {
                pBug->move();

                // After move, add bug to the cell
                cell = pBug->getPosition();
                bug_list = bug_map[cell];
                bug_list.push_back(pBug);
                bug_map.insert_or_assign(cell, bug_list);
            }
        }
        cout << "\nAll bugs have moved! (except the dead ones)\n";

        // Eat functionality
        for (const auto& pairing : bug_map)
        {
            pair<int, int> cell = pairing.first;
            list<Bug*> bug_list = pairing.second;
            if (bug_list.size() > 1)
            {
                int maxSize = 0;
                Bug* maxBug = bug_list.front();
                for (Bug* pBug : bug_list)
                {
                    if (pBug->getSize() > maxSize)
                    {
                        maxSize = pBug->getSize();
                        maxBug = pBug;
                    }
                }
                for (Bug* pBug : bug_list)
                {
                    if (pBug != maxBug)
                    {
                        if (pBug->getSize() != maxSize)
                        {
                            pBug->changeStatus();
                            maxBug->setSize(maxBug->getSize() + pBug->getSize());
                            pBug->setKiller(maxBug);
                            if (typeid(*pBug) == typeid(Crawler))
                            {
                                cout << "Crawler ";
                            }
                            else if (typeid(*pBug) == typeid(Hopper))
                            {
                                cout << "Hopper ";
                            }
                            cout << pBug->getID() << " has been eaten by ";
                            if (typeid(*maxBug) == typeid(Crawler))
                            {
                                cout << "Crawler ";
                            }
                            else if (typeid(*maxBug) == typeid(Hopper))
                            {
                                cout << "Hopper ";
                            }
                            cout << maxBug->getID() << " on cell (" << cell.first << "," << cell.second << ")\n";
                        }
                    }
                }
            }
        }
    }
    return bug_map;
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
                cout << " Eaten by " << pBug->getKiller()->getID() << "\n";
            }
        }
        cout << "(Total: " << bug_vector.size() << " bugs)\n";
    }
}

void displayAllCells(vector<Bug*>& bug_vector, map<pair<int, int>, list<Bug*>> bug_map)
{
    cout << "\nOption: Display All Cells\n\n";

    for (int x = 0; x <= 10; x++)
    {
        for (int y = 0; y <= 10; y++)
        {
            cout << "(" << x << "," << y << "): ";
            pair<int, int> cell{ x,y };
            list<Bug*> bug_list = bug_map[cell];
            if (bug_list.empty())
            {
                cout << "empty\n";
            }
            else
            {
                for (Bug* pBug : bug_list)
                {
                    if (typeid(*pBug) == typeid(Crawler))
                    {
                        cout << "Crawler ";
                    }
                    else if (typeid(*pBug) == typeid(Hopper))
                    {
                        cout << "Hopper ";
                    }
                    cout << pBug->getID();
                    pBug != bug_list.back() ? (cout << ", ") : (cout << endl);
                }
            }
        }
    }
}

void saveBugsData(vector<Bug*>& bug_vector)
{
    ofstream outStream("bugs_life.out");

    if (outStream.good())
    {
        for (Bug* pBug : bug_vector)
        {
            if (typeid(*pBug) == typeid(Crawler))
            {
                outStream << "C;";
            }
            else if (typeid(*pBug) == typeid(Hopper))
            {
                outStream << "H;";
            }
            outStream << pBug->getID() << ";" << pBug->getPosition().first << ";" << pBug->getPosition().second << ";" << pBug->getDirection() << ";" << pBug->getSize() << ";";
            if (typeid(*pBug) == typeid(Hopper))
            {
                Hopper* pHopper = dynamic_cast<Hopper*>(pBug);
                outStream << pHopper->getHopLength();
            }
            outStream << endl;
        }
        outStream.close();
        cout << "\n[File saved successfully]\n";
    }
    else
    {
        cout << "\n[Unable to open file]\n";
    }
}

void run()
{
    vector<Bug*> bug_vector;
    map<pair<int, int>, list<Bug*>> bug_map;

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
        case 1: bug_map = initialiseBugBoard(bug_vector); break;
        case 2: displayAllBugs(bug_vector); break;
        case 3: findBug(bug_vector); break;
        case 4: bug_map = tapBugBoard(bug_vector, bug_map); break;
        case 5: displayLifeHistory(bug_vector); break;
        case 6: displayAllCells(bug_vector, bug_map); break;
        case 7: saveBugsData(bug_vector); break;
        }
    } while (option != 7);

    cout << "\nGoodbye\n";

    // don't forget to delete the pointers
}