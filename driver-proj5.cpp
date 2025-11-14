#include <iostream>
#include "arrayheap-student-proj5.h"
#include "process-proj5.h"
using namespace std;

int main() {
    // read in the number of processes
    int numProcesses;
    cin >> numProcesses;

    ArrayHeap<Process> processHeap;

    int idNum = 0;
    int systemTime = 0;
    int numPassed = 0;
    int numSkipped = 0;

    Process nextProcess(idNum);
    cin >> nextProcess;
    idNum++;
    bool hasMoreProcesses = true;

    // main loop - loops while heap is not empty and while there are
    // more processes to be run
    while (hasMoreProcesses || processHeap.getNumItems() > 0) {
        // sub loop to add processes
        // loops while you can submit processes and while there
        // are more processes to run

        // simulating the incrementation of time if cpu is idle
        if (processHeap.getNumItems() == 0 && hasMoreProcesses
            && nextProcess.getSubmissionTime() >= systemTime) {
            systemTime = nextProcess.getSubmissionTime();
        }

        // kinda like the processing stage :)
        // that was a joke sry
        while (nextProcess.getSubmissionTime() <= systemTime
            && hasMoreProcesses) {

            // insert process to the heap
            processHeap.insert(nextProcess);

            // read in the processes since you are able
            if (idNum < numProcesses) {
                Process tempProcess(idNum);
                cin >> tempProcess;
                nextProcess = tempProcess;
                idNum++;
            }
            // case where the heap wasn't empty but there were no
            // more processes to run
            else {
                hasMoreProcesses = false;
            }
        }

        // get and remove the highest priority process
        Process currentProcess = processHeap.getMinItem();
        processHeap.removeMinItem();

        // case of running process
        if (currentProcess.canComplete(systemTime)) {
            cout << "running process id " << currentProcess.getId()
            << " at " << systemTime << endl;
            systemTime = currentProcess.run(systemTime);
            numPassed++;
        }
        // case of skipping process
        else {
            cout << "skipping process id " << currentProcess.getId()
            << " at " << systemTime << endl;
            systemTime++;
            numSkipped++;
        }
    }


    cout << "final clock is                 " << systemTime << endl;
    cout << "number of processes run is     " << numPassed << endl;
    cout << "number of processes skipped is " << numSkipped << endl;

    return 0;
}
