#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
    int pid;
    int startAddress;

public:
    Process(int pid, int startAddress);

    int getPID();
    int getStartAddress();
};

#endif