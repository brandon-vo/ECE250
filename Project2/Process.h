#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
    unsigned int pid;
    int startAddress;
    int hash;
public:
    Process(unsigned int pid, int startAddress, int hash);
    unsigned int getPID();
    void setPID(unsigned int pid);
    int getStartAddress();
    void setStartAddress(int startAddress);
    int getHash();
    void setHash(int hash);
};

#endif