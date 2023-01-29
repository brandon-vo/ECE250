////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#include <iostream>
#include <vector>
using namespace std;

// Main function
int main() {
    string command; // Read commands

    // Read command
    while (cin >> command) {

        if (command == "M") {
            // Create a new hash table with size of 𝑚 = 𝑁 / 𝑃
            // N: memory size
            // P: page size
            // You may assume that this command appears
            // exactly once, as the first command in the test
            // file after the type of test, and N, P > 0 always

        } else if (command == "INSERT") {
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
            // Search for the key PID in the table.

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

    return 0; // Terminate
}