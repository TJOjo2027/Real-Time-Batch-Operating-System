# Real-Time Batch Operating System Simulator

## ABOUT
This project is a **Real-Time Batch Operating System (RTOS) Simulator** written in C++.  
It models how an operating system schedules and executes real-time processes using a priority-based min-heap.

Originally developed as a college assignment, it has since been refined into a **resume project** showcasing data structures, simulation design, and systems programming.

## PROJECT BACKGROUND
This project was built using baseline components provided by **Professor Greg Hamerly**, who contributed:

- The foundational `Process` class  
- The skeleton implementation of the `ArrayHeap` class  
- Reference outputs used for verification and correctness testing  

My work involved:

- Implementing all heap operations (insert, removeMinItem, bubble-up/down, free-slot management)  
- Building the driver that simulates the RTOS scheduling loop  
- Ensuring correctness against provided reference outputs  
- Extending the codebase into a reusable and user-friendly simulator  

## WHAT THE SIMULATOR DOES
The simulator:

- Reads processes from input one at a time  
- Tracks a system clock that advances based on CPU activity  
- Inserts processes into a min-heap as they arrive  
- Selects the highest-priority process when the CPU is free  
- Runs or skips processes depending on their deadlines  
- Produces a final summary including:  
  - Final clock value  
  - Number of successful process completions  
  - Number of skipped processes  

This models how real RTOS schedulers behave when handling time-sensitive workloads.

## KEY FEATURES
- **Custom Array-Based Min Heap**  
  Efficient runtime behavior with dynamic memory expansion and stack-based free-slot reuse.

- **Process Scheduling Simulation**  
  Uses arrival times, deadlines, and run durations to determine scheduling outcomes.

- **Deadline-Aware Execution**  
  A process is either executed fully or skipped when it can no longer complete before its deadline.

- **Lightweight, Single-Pass Input Handling**  
  Processes are not stored in a large vector — they are consumed only when needed, matching real OS behavior.

## TECHNOLOGIES USED
- C++  
- Custom data structures (array-based heap)  
- Heap-based priority scheduling  
- Input-driven simulation loop  

## FUTURE PLANS
- Add a graphical visualization of system time, queue depth, and active process  
- Provide an interface for loading datasets and exporting simulation reports  

## STAY TUNED
This project will continue evolving into a more complete RTOS simulation and teaching tool.  
Follow for future updates and improvements.
