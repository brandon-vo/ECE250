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

        if (command == "M") {
            cin >> n; // N: memory size
            cin >> p; // P: page size

            openTable = new OpenAddressingTable(n, p);
            cout << "success" << endl;

        } else if (command == "INSERT") {
            cin >> pid;
            openTable->insertDoubleHash(pid);
            // Insert a PID (a key).
            // If it is possible, a new page of memory is
            // allocated to PID. Note that regardless of the
            // type of hashing used, if all pages are used
            // insertion is not possible and the table is
            // considered to be full.
            // Your program must keep track of which page is
            // allocated to which process or the commands
            // below will not work.
            // Assume PID > 0; this means that 0 can be used
            // as a sentinel value

        } else if (command == "SEARCH") {
            cin >> pid;
            openTable->searchKey(pid);

        } else if (command == "WRITE") {
            // Write the integer (x) to the memory address.
            // Please take into account that both PID and
            // ADDR (virtual address) are given to determine
            // the physical address as discussed earlier in this
            // document

        } else if (command == "READ") {
            // Read the integer stored in the memory address.
            // Please take into account that both PID and
            // ADDR are given to determine the physical
            // address as discussed above.

        } else if (command == "DELETE") {
            // Delete the key PID from the hash table.
            // NOTE: This de-allocates the memory page
            // associated with that PID, but you do not need
            // to do anything with the memory stored there.

        } else if (command == "PRINT") {
            // Print the chain of stored keys in position m of
            // the hash table. Keys should be printed in
            // descending order. Keys in the chain are
            // separated by one space. The output indicates
            // that the chain is empty if that is the case.
            // NOTE: This command is only for separate
            // chaining. It will not be used to test double
            // hashing.

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

        if (command == "M") {
            cin >> n; // N: memory size
            cin >> p; // P: page size

            orderedTable = new SeparateChainingTable(n, p);
            cout << "success" << endl;

        } else if (command == "INSERT") {
            cin >> pid;
            orderedTable->insertOrdered(pid);
            // table ->insertOrdered(pid);
            // Insert a PID (a key).
            // If it is possible, a new page of memory is
            // allocated to PID. Note that regardless of the
            // type of hashing used, if all pages are used
            // insertion is not possible and the table is
            // considered to be full.
            // Your program must keep track of which page is
            // allocated to which process or the commands
            // below will not work.
            // Assume PID > 0; this means that 0 can be used
            // as a sentinel value

        } else if (command == "SEARCH") {
            cin >> pid;
            orderedTable->searchKey(pid);

        } else if (command == "WRITE") {
            // Write the integer (x) to the memory address.
            // Please take into account that both PID and
            // ADDR (virtual address) are given to determine
            // the physical address as discussed earlier in this
            // document

        } else if (command == "READ") {
            // Read the integer stored in the memory address.
            // Please take into account that both PID and
            // ADDR are given to determine the physical
            // address as discussed above.

        } else if (command == "DELETE") {
            // Delete the key PID from the hash table.
            // NOTE: This de-allocates the memory page
            // associated with that PID, but you do not need
            // to do anything with the memory stored there.

        } else if (command == "PRINT") {
            // Print the chain of stored keys in position m of
            // the hash table. Keys should be printed in
            // descending order. Keys in the chain are
            // separated by one space. The output indicates
            // that the chain is empty if that is the case.
            // NOTE: This command is only for separate
            // chaining. It will not be used to test double
            // hashing.

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
        // Use open hashing
        useOpenHashing();
    } else if (type == "ORDERED") {
        // Use ordered hashing
        useOrderedHashing();
    }
}
