#include "Process.h"

Process::Process(int pid, int startAddress) {
    this->pid = pid;
    this->startAddress = startAddress;
}

int Process::getPID() {
    return pid;
}

void Process::setPID(int pid) {
    this->pid = pid;
}

int Process::getStartAddress() {
    return startAddress;
}