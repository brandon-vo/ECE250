#include "Process.h"

Process::Process(unsigned int pid, int physicalAddress, int hash) {
    this->pid = pid;
    this->physicalAddress = physicalAddress;
    this->hash = hash;
}

unsigned int Process::getPID() {
    return pid;
}

void Process::setPID(unsigned int pid) {
    this->pid = pid;
}

int Process::getPhysicalAddress() {
    return physicalAddress;
}

void Process::setPhysicalAddress(int physicalAddress) {
    this->physicalAddress = physicalAddress;
}

int Process::getHash() {
    return hash;
}

void Process::setHash(int hash) {
    this->hash = hash;
}