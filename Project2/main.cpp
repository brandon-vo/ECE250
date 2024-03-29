////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#include "HashTable.h"
#include "OpenAddressingTable.h"
#include "SeparateChainingTable.h"
#include <iostream>
using namespace std;

void useOpenHashing() {
    string command;                 // Command: M, INSERT, SEARCH, WRITE, READ, DELETE, END
    OpenAddressingTable *openTable; // Hash table;
    int n;                          // n: memory size
    int p;                          // p: page size
    unsigned int pid;               // pid: process ID key
    int addr;                       // addr: memory address
    int x;                          // x: value to write

    // Read command
    while (cin >> command) {

        if (command == "M") {
            cin >> n;
            cin >> p;

            openTable = new OpenAddressingTable(n, p);
            cout << "success" << endl;

        } else if (command == "INSERT") {
            cin >> pid;
            openTable->insertOpen(pid);

        } else if (command == "SEARCH") {
            cin >> pid;
            openTable->searchOpen(pid);

        } else if (command == "WRITE") {
            cin >> pid;
            cin >> addr;
            cin >> x;
            openTable->writeMemoryOpen(pid, addr, x);

        } else if (command == "READ") {
            cin >> pid;
            cin >> addr;
            openTable->readMemoryOpen(pid, addr);

        } else if (command == "DELETE") {
            cin >> pid;
            openTable->deleteOpen(pid);

        } else if (command == "END") {
            break;
        }
    }
    delete openTable;
    return; // Terminate
}

void useOrderedHashing() {
    string command;                      // Command: M, INSERT, SEARCH, WRITE, READ, DELETE, END
    SeparateChainingTable *orderedTable; // Hash table;
    int n;                               // N: memory size
    int p;                               // P: page size
    unsigned int pid;                    // pid: process ID key
    int addr;                            // addr: memory address
    int x;                               // x: value to write
    int m;                               // m: chain number

    // Read command
    while (cin >> command) {

        if (command == "M") {
            cin >> n; // N: memory size
            cin >> p; // P: page size

            orderedTable = new SeparateChainingTable(n, p);
            cout << "success" << endl;

        } else if (command == "INSERT") {
            cin >> pid;
            orderedTable->insertOrdered(pid);

        } else if (command == "SEARCH") {
            cin >> pid;
            orderedTable->searchOrdered(pid);

        } else if (command == "WRITE") {
            cin >> pid;
            cin >> addr;
            cin >> x;
            orderedTable->writeMemoryOrdered(pid, addr, x);

        } else if (command == "READ") {
            cin >> pid;
            cin >> addr;
            orderedTable->readMemoryOrdered(pid, addr);

        } else if (command == "DELETE") {
            cin >> pid;
            orderedTable->deleteOrdered(pid);

        } else if (command == "PRINT") {
            cin >> m;
            orderedTable->printChain(m);

            // END: Exit loop
        } else if (command == "END") {
            break;
        }
    }
    delete orderedTable;
    return; // Terminate
}

// Main function
int main() {
    string type = ""; // OPEN or ORDERED
    cin >> type;
    if (type == "OPEN") {
        useOpenHashing();
    } else if (type == "ORDERED") {
        useOrderedHashing();
    }
}
