#include <iostream>
using namespace std;

const int NUM_DEPARTMENTS = 6;
const int INFINITY_DISTANCE = 9999;
const char departmentNames[NUM_DEPARTMENTS] = {'A', 'B', 'C', 'D', 'E', 'F'};
int weightMatrix[NUM_DEPARTMENTS][NUM_DEPARTMENTS];
int previousVertex[NUM_DEPARTMENTS];

int getIndex(char departmentName){
    for(int i = 0; i < NUM_DEPARTMENTS; i++)
        if(departmentNames[i] == departmentName) return i;
    return -1;
}

void addEdge(char fromName, char toName, int weight){
    weightMatrix[getIndex(fromName)][getIndex(toName)] = weight;
}

int getClosestVertex(int distance[], bool isDone[]){
    int smallestDistance = INFINITY_DISTANCE, closestVertex = -1;
    for(int vertex = 0; vertex < NUM_DEPARTMENTS; vertex++){
        if(!isDone[vertex] && distance[vertex] < smallestDistance){
            smallestDistance = distance[vertex];
            closestVertex = vertex;
        }
    }
    return closestVertex;
}

void printPath(int vertex){
    if (previousVertex[vertex] != -1){
        printPath(previousVertex[vertex]);
        cout << " -> ";
    }
    cout << departmentNames[vertex];
}

void dijkstra(int sourceVertex){
    int distance[NUM_DEPARTMENTS];
    bool isDone[NUM_DEPARTMENTS];

    for (int i = 0; i < NUM_DEPARTMENTS; i++){
        distance[i] = INFINITY_DISTANCE;
        isDone[i] = false;
        previousVertex[i] = -1;
    }
    distance[sourceVertex] = 0;

    for(int step = 0; step < NUM_DEPARTMENTS; step++){
        int currentVertex = getClosestVertex(distance, isDone);
        if (currentVertex == -1) break;
        isDone[currentVertex] = true;

        for(int neighbour = 0; neighbour < NUM_DEPARTMENTS; neighbour++){
            int edgeWeight = weightMatrix[currentVertex][neighbour];
            if(!isDone[neighbour] && edgeWeight != 0 && distance[currentVertex] + edgeWeight < distance[neighbour]){
                distance[neighbour] = distance[currentVertex] + edgeWeight;
                previousVertex[neighbour] = currentVertex;
            }
        }
    }

    cout << "Shortest paths from " << departmentNames[sourceVertex] << endl;
    for(int vertex = 0; vertex < NUM_DEPARTMENTS; vertex++){
        if(vertex == sourceVertex) continue;
        cout << departmentNames[sourceVertex] << " to " << departmentNames[vertex] << ": ";
        if(distance[vertex] == INFINITY_DISTANCE){
            cout << "Unreachable" << endl;
        }
        else{
            printPath(vertex);
            cout << "  (Total cost = " << distance[vertex] << ")" << endl;
        }
    }
}

int main(){
    addEdge('A', 'B', 4);
    addEdge('A', 'C', 2);
    addEdge('B', 'C', 5);
    addEdge('B', 'D', 10);
    addEdge('C', 'E', 3);
    addEdge('E', 'D', 4);
    addEdge('D', 'F', 11);
    dijkstra(0);
    return 0;
}