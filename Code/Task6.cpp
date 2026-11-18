#include <iostream>
using namespace std;

const int NUM_COURSES = 6;
int adjMatrix[NUM_COURSES][NUM_COURSES];
int indegree[NUM_COURSES];

void addEdge(int fromCourse, int toCourse){
    adjMatrix[fromCourse][toCourse] = 1;
}

void topologicalSort(){
    for(int course = 0; course < NUM_COURSES; course++)
        for(int nextCourse = 0; nextCourse < NUM_COURSES; nextCourse++)
            if(adjMatrix[course][nextCourse] == 1)
                indegree[nextCourse]++;

    cout << "Indegrees:" << endl;
    for(int course = 0; course < NUM_COURSES; course++)
        cout << "Course " << course << ": " << indegree[course] << endl;

    int queueArray[NUM_COURSES], queueFront = 0, queueRear = 0;
    for(int course = 0; course < NUM_COURSES; course++)
        if(indegree[course] == 0)
            queueArray[queueRear++] = course;

    int completedCount = 0;
    cout << "Course completion order: ";
    while(queueFront < queueRear){
        int currentCourse = queueArray[queueFront++];
        cout << currentCourse << " ";
        completedCount++;

        for(int nextCourse = 0; nextCourse < NUM_COURSES; nextCourse++){
            if(adjMatrix[currentCourse][nextCourse] == 1){
                indegree[nextCourse]--;
                if(indegree[nextCourse] == 0)
                    queueArray[queueRear++] = nextCourse;
            }
        }
    }
    cout << endl;

    if(completedCount != NUM_COURSES)
        cout << "Cycle detected, no valid course order exists!" << endl;
    else
        cout << "No cycle found, valid order generated" << endl;
}

int main(){
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 4);
    addEdge(2, 5);
    addEdge(3, 5);
    topologicalSort();
    return 0;
}