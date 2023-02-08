#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
    int pid;
    int physicalAddress;
    int hash;
public:
    Process(unsigned int pid, int physicalAddress, int hash);
    unsigned int getPID();
    void setPID(unsigned int pid);
    int getPhysicalAddress();
    void setPhysicalAddress(int physicalAddress);
    int getHash();
    void setHash(int hash);
};

#endif