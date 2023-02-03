#include "Process.h"

Process::Process(int pid, int startAddress) {
    this->pid = pid;
    this->startAddress = startAddress;
}

int Process::getPID() {
    return pid;
}

int Process::getStartAddress() {
    return startAddress;
}