#include "Process.h"

Process::Process(unsigned int pid, int startAddress, int hash) {
    this->pid = pid;
    this->startAddress = startAddress;
    this->hash = hash;
}

unsigned int Process::getPID() {
    return pid;
}

void Process::setPID(unsigned int pid) {
    this->pid = pid;
}

int Process::getStartAddress() {
    return startAddress;
}

void Process::setStartAddress(int startAddress) {
    this->startAddress = startAddress;
}

int Process::getHash() {
    return hash;
}

void Process::setHash(int hash) {
    this->hash = hash;
}