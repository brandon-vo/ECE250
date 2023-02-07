#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
    int pid;
    int startAddress;
    int pageNumber;

public:
    Process(unsigned int pid, int startAddress);
    int getPID();
    void setPID(unsigned int pid);
    int getStartAddress();
    void setStartAddress(int startAddress);
    int getPageNumber();
    void setPageNumber(int pageNumber);
};

#endif