#include "process-proj5.h"

/**
 * Process
 *
 * This is function that acts as the constructor for the Process
 * class. The only argument is the id number, which will be incremented
 * and set in the driver
 *
 * Parameters:
*   theID: the id number of the process
 *
 * Return value: creates a process object in memory
 */
Process::Process(int theId) {
    id = theId;
    submissionTime = 0;
    deadline = 0;
    requiredTime = 0;
    information = "";
}

/**
 * run
 *
 * This function runs the process, and in this particular simulation,
 * executes the process' instructions by printing its contents.
 *
 * Parameters:
*   currentSystemTime: the system time that is incremented in the driver.
 *
 * Return value: returns the new system time, as well as the message of
 * the process
 */
int Process::run(int currentSystemTime) const {
    cout << information << endl;
    return currentSystemTime + requiredTime;
}

/**
 * canComplete
 *
 * This function returns either a true or false telling the user
 * whether the process can be completed provided the current
 * systemTime.
 *
 * Parameters:
*   currentSystemTime: the system time that is incremented in the driver.
 *
 * Return value: a boolean value telling if a process can be completed.
 */
bool Process::canComplete(int currentSystemTime) const {
    return currentSystemTime + requiredTime <= deadline;
}

/**
 * getID
 *
 * This function is a getter for the Process class, obtaining
 * the id data member from the object
 *
 * Parameters:
*   NONE
 *
 * Return value: the id of the target object
 */
int Process::getId() const {
    return this -> id;
}

/**
 * getSubmissionTime
 *
 * This function is a getter for the submission time of the
 * object. Accesses the data member in order to return the
 * submission time.
 *
 * Parameters:
*   NONE
 *
 * Return value: the submission time, which is of type int.
 */
int Process::getSubmissionTime() const {
    return this -> submissionTime;
}

/**
 * operator<
 *
 * This function overloads the < operator, which compares the
 * values of the two process objects by deadline, the required
 * time, then finally by ID number
 *
 * Parameters:
*   p: the object that is being compared to.
 *
 * Return value: a boolean that tells the user which
 * object is of higher priority (lower value) through
 * a series of checks.
 */
bool Process::operator<(Process const &p) const {
    if (this -> deadline != p.deadline) {
        return this -> deadline < p.deadline;
    }

    // second tiebreaker case
    if (this -> requiredTime != p.requiredTime) {
        return this -> requiredTime < p.requiredTime;
    }

    // last case
    return this -> id < p.id;
}

/**
 * operator>>
 *
 * This function overloads the >> operator and essentially
 * delegates how Process objects will be read into memory.
 *
 * Parameters:
*   is: the istream object used to read in the data.
*   p: the process object being read in.
 *
 * Return value: returns a istream object that will be used to
 * safely read the process object into memory.
 */
istream &operator>>(istream &is, Process &p) {
    is >> p.submissionTime;
    is >> p.deadline;
    is >> p.requiredTime;
    is.ignore();
    // gets the rest of the line in the case that information
    // is more than one word
    getline(is, p.information);
    return is;
}