//--------------------------------------------------------------------
//
//  Laboratory B, In-lab Exercise 1                       ossim.cs
//
//  (Shell) Operating system task scheduling simulation
//
//--------------------------------------------------------------------

// Simulates an operating system's use of a priority queue to regulate
// access to a system resource (printer, disk, etc.).

#include <iostream>
#include <cstdlib>
#include "ptyqueue.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the task data struct
//

struct TaskData
{
    int priority,              // Task's priority
        arrived;               // Time when task was enqueued

    void setPty(int newPty)
        { priority = newPty; }   // Set the priority

    int pty () const
        { return priority; }   // Returns the priority
};

//--------------------------------------------------------------------

void main ()
{
    PtyQueue<TaskData> taskPQ;   // Priority queue of tasks
    TaskData task;               // Task
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        numPtyLevels,            // Number of priority levels
        numArrivals;             // Number of new tasks arriving

    cout << endl << "Enter the number of priority levels : ";
    cin >> numPtyLevels;

    cout << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    cout << "..." << endl;

    srand(500);
    int ptyOne = 0;
    int ptyZero = 0;

    for ( minute = 0 ; minute < simLength ; minute++ )
    {
        cout << endl << "Current minute = " << minute << endl;
        // Dequeue the first task in the queue (if any).
        if (!taskPQ.isEmpty()) {
            cout << "Task Dequeued" << endl;
            TaskData front = taskPQ.dequeue();
            cout << "This task's priority: " << front.pty() << endl;
            cout << "This task was arrived at " << front.arrived << ", and waited for " << minute - front.arrived << " minutes." << endl;

            if (front.pty() == 1) {
                ptyOne = ptyOne > minute - front.arrived ? ptyOne : minute - front.arrived;
            }
            else {
                ptyZero = ptyZero > minute - front.arrived ? ptyZero : minute - front.arrived;
            }
        }

        // Determine the number of new tasks and add them to
        // the queue.
        TaskData task;
        numArrivals = rand() % 4; // 0 ~ 3

        switch (numArrivals) {
        case 1:     // add one task
            cout << "Adding 1 tasks" << endl;
            numPtyLevels = rand() % 2; // 0 ~ 1
            task.setPty(numPtyLevels);
            task.arrived = minute;
            taskPQ.enqueue(task);
            break;
        case 2:     // add two task
            cout << "Adding 2 tasks" << endl;
            numPtyLevels = rand() % 2; // 0 ~ 1
            task.setPty(numPtyLevels);
            task.arrived = minute;
            taskPQ.enqueue(task);

            numPtyLevels = rand() % 2; // 0 ~ 1
            task.setPty(numPtyLevels);
            task.arrived = minute;
            taskPQ.enqueue(task);
            break;
        case 0: case 3:     // do not add
            cout << "No task was added this time" << endl;
            break;
        }

        taskPQ.showStructure();
    }
    cout << "Longest wait for any low-priority(0) task: " <<  ptyZero << endl;
    cout << "Longest wait for any high-priority(1) task: " << ptyOne << endl;


    system("pause");
}
