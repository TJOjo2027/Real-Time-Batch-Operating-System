Real-Time Batch Operating System Simulator

A resume-focused academic project enhanced into a polished, educational RTOS simulation tool.

📌 Overview

This project implements a Real-Time Batch Operating System Simulator capable of scheduling processes based on deadlines, arrival times, and execution duration. It models how a real RTOS handles tasks under strict timing constraints, using a priority-driven scheduling strategy backed by a custom array-based heap structure.

Originally developed as part of an academic assignment, this repository expands the project into a reusable and explanatory open-source tool suitable for showcasing system-level programming, C++ data structures, and scheduling logic.

👨‍🏫 Acknowledgments & Provided Components

Foundational components of this project were provided by Professor Greg Hamerly (Baylor University) for educational use:

Process class baseline
Includes parsing, process metadata (submission time, duration, deadline, ID), and helper methods such as canComplete(), run(), and operator overloads for comparison.

ArrayHeap interface and partial implementation
The structure and API for a flexible array-based min-heap used to manage process priority.

Reference outputs and test cases
Provided to validate correctness and ensure accurate scheduling behavior.

These contributions formed the starting framework on which the remaining implementation work was built.

👨‍💻 My Contributions

All of the following were fully designed and implemented by me:

🔧 ArrayHeap Functionality

Completed the entire heap implementation, including:

insert()

removeMinItem()

bubbleUp() / bubbleDown()

doubleCapacity()

copy constructor & assignment operator

Designed a correct index-stack system for managing free data slots and heap positions.

Ensured stable priority ordering using heap indices pointing to a separate data array.

🖥 RTOS Driver / Scheduler

Implemented the main simulation loop that:

Reads processes as they become available (no preloading the whole dataset)

Inserts ready processes into the heap at the correct times

Advances system time based on idle states, task completion, or task skipping

Applies real-time constraints: if a process cannot meet its deadline, it is skipped

Ensured correctness by matching all professor-provided reference outputs.

🧪 Testing & Validation

Added targeted tests to verify:

Heap structural integrity under repeated insert/remove operations

Correct deadline-based scheduling behavior

Accurate reporting of finished vs. skipped processes

Proper time advancement emulating real RTOS batch behavior

⚙️ How the Simulator Works

Processes arrive at specific submission times.

The system reads and enqueues only tasks whose submission time has passed.

The min-heap selects the next process based on earliest deadline (and ID tiebreakers).

The scheduler:

Runs the process if it can finish before its deadline

Skips it otherwise

System time is advanced based on action taken.

The simulation ends after all processes have been handled.

This models hard real-time scheduling, where missing a deadline invalidates the task.

🛠 Technologies & Concepts Demonstrated

C++17

Custom data structures

Array-backed min-heap

Free-stack index management

RAII, memory management, deep copying

Operator overloading

Scheduling algorithms (RTOS-inspired)

Event-driven simulation

Priority-based execution and deadline enforcement

Clean modular design

🚀 Example Input
5
10 20 5 hello there
11 20 5 how are you
12 20 5 i am fine
13 20 5 i am glad to hear that
14 30 5 goodbye

🧾 Example Output
Final Clock Value -> 27
Number of Processes Run -> 3
Number of Processes Skipped -> 2

📄 Purpose of this Repository

This repository serves as:

A resume-ready showcase of C++ data structure implementation

A demonstration of RTOS scheduling concepts through simulation

A learning tool for others studying scheduling, heaps, or system-level programming

A cleaned, documented, and extensible version of the original academic assignment

📬 Contact

Questions or feedback welcome—feel free to open an issue or reach out!
