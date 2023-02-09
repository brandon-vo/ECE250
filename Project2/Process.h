#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
    unsigned int pid;
    int startAddress;
    int hash;
    int page;

public:
    Process(unsigned int pid, int startAddress, int hash, int page);
    void setPID(unsigned int pid);
    unsigned int getPID();
    void setStartAddress(int startAddress);
    int getStartAddress();
    void setHash(int hash);
    int getHash();
    void setPage(int pageSize);
    int getPage();
};

#endif