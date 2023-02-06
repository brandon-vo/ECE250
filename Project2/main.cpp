////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#include "HashTable.h"
#include "OpenAddressingTable.h"
#include "SeparateChainingTable.h"
#include <iostream>
#include <vector>
using namespace std;

void useOpenHashing() {
    string command;

    // Read command
    while (cin >> command) {

        OpenAddressingTable *openTable; // Hash table;
        int n;
        int p;
        int pid;
        int addr;
        int x;

        if (command == "M") {
            cin >> n; // N: memory size
            cin >> p; // P: page size

            openTable = new OpenAddressingTable(n, p);
            cout << "success" << endl;

        } else if (command == "INSERT") {
            cin >> pid;
            openTable->insertDoubleHash(pid);

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

            // END: Exit loop
        } else if (command == "END") {
            break;
        }
    }

    return; // Terminate
}

void useOrderedHashing() {
    string command;

    // Read command
    while (cin >> command) {

        SeparateChainingTable *orderedTable; // Hash table;
        int n;
        int p;
        int pid;
        int addr;
        int x;
        int m;

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

    return; // Terminate
}

// Main function
int main() {
    string type; // OPEN or ORDERED
    cin >> type;

    if (type == "OPEN") {
        useOpenHashing();
    } else if (type == "ORDERED") {
        useOrderedHashing();
    }
}
