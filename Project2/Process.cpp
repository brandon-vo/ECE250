#include "Process.h"

Process::Process(unsigned int pid, int startAddress) {
    this->pid = pid;
    this->startAddress = startAddress;
}

int Process::getPID() {
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