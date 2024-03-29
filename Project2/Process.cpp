////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#include "Process.h"

Process::Process(unsigned int pid, int startAddress, int hash, int page) {
    this->pid = pid;
    this->startAddress = startAddress;
    this->page = page;
}

void Process::setPID(unsigned int pid) {
    this->pid = pid;
}

unsigned int Process::getPID() {
    return pid;
}

void Process::setStartAddress(int startAddress) {
    this->startAddress = startAddress;
}

int Process::getStartAddress() {
    return startAddress;
}

void Process::setPage(int page) {
    this->page = page;
}

int Process::getPage() {
    return page;
}