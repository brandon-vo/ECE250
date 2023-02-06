#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
    int pid;
    int startAddress;
public:
    Process(unsigned int pid, int startAddress);
    int getPID();
    void setPID(unsigned int pid);
    int getStartAddress();
    void setStartAddress(int startAddress);
};

#endif