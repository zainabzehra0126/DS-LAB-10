#include <iostream>
using namespace std;

const int NUM_DEPARTMENTS = 6;
const char departmentNames[NUM_DEPARTMENTS] = {'A', 'B', 'C', 'D', 'E', 'F'};
int weightMatrix[NUM_DEPARTMENTS][NUM_DEPARTMENTS];

int getIndex(char departmentName) {
    if (departmentName >= 'a' && departmentName <= 'z')
        departmentName = departmentName - 'a' + 'A';
    for (int i = 0; i < NUM_DEPARTMENTS; i++)
        if (departmentNames[i] == departmentName) return i;
    return -1;
}

void insertEdge(char fromName, char toName, int weight) {
    int fromIndex = getIndex(fromName);
    int toIndex = getIndex(toName);
    if (fromIndex == -1 || toIndex == -1) {
        cout << "Invalid department" << endl;
        return;
    }
    if (weight <= 0) {
        cout << "Weight must be greater than 0" << endl;
        return;
    }
    weightMatrix[fromIndex][toIndex] = weight;
    cout << "Edge " << departmentNames[fromIndex] << " -> " << departmentNames[toIndex] << " inserted with weight " << weight << endl;
}

void deleteEdge(char fromName, char toName) {
    int fromIndex = getIndex(fromName);
    int toIndex = getIndex(toName);
    if (fromIndex == -1 || toIndex == -1) {
        cout << "Invalid department" << endl;
        return;
    }
    if (weightMatrix[fromIndex][toIndex] == 0) {
        cout << "Edge does not exist" << endl;
        return;
    }
    weightMatrix[fromIndex][toIndex] = 0;
    cout << "Edge " << departmentNames[fromIndex] << " -> " << departmentNames[toIndex] << " deleted" << endl;
}

void displayMatrix() {
    cout << "Adjacency Matrix:" << endl;
    cout << "    ";
    for (int col = 0; col < NUM_DEPARTMENTS; col++)
        cout << departmentNames[col] << "   ";
    cout << endl;
    for (int row = 0; row < NUM_DEPARTMENTS; row++) {
        cout << departmentNames[row] << "   ";
        for (int col = 0; col < NUM_DEPARTMENTS; col++) {
            cout << weightMatrix[row][col];
            if (weightMatrix[row][col] < 10) cout << "   ";
            else cout << "  ";
        }
        cout << endl;
    }
}

void displayIncomingOutgoing() {
    for (int vertex = 0; vertex < NUM_DEPARTMENTS; vertex++) {
        cout << "Vertex " << departmentNames[vertex] << endl;

        cout << "  Outgoing: ";
        int outgoingCount = 0;
        for (int neighbour = 0; neighbour < NUM_DEPARTMENTS; neighbour++) {
            if (weightMatrix[vertex][neighbour] != 0) {
                cout << departmentNames[vertex] << "->" << departmentNames[neighbour] << "(" << weightMatrix[vertex][neighbour] << ") ";
                outgoingCount++;
            }
        }
        if (outgoingCount == 0) cout << "none";
        cout << endl;

        cout << "  Incoming: ";
        int incomingCount = 0;
        for (int neighbour = 0; neighbour < NUM_DEPARTMENTS; neighbour++) {
            if (weightMatrix[neighbour][vertex] != 0) {
                cout << departmentNames[neighbour] << "->" << departmentNames[vertex] << "(" << weightMatrix[neighbour][vertex] << ") ";
                incomingCount++;
            }
        }
        if (incomingCount == 0) cout << "none";
        cout << endl;
    }
}

int main() {
    insertEdge('A', 'B', 4);
    insertEdge('A', 'C', 2);
    insertEdge('B', 'C', 5);
    insertEdge('B', 'D', 10);
    insertEdge('C', 'E', 3);
    insertEdge('E', 'D', 4);
    insertEdge('D', 'F', 11);

    int choice = 0;
    while (choice != 5) {
        cout << endl;
        cout << "1. Insert edge" << endl;
        cout << "2. Delete edge" << endl;
        cout << "3. Display adjacency matrix" << endl;
        cout << "4. Display incoming and outgoing edges of each vertex" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        char fromName, toName;
        int weight;
        if (choice == 1) {
            cout << "Enter from, to and weight: ";
            cin >> fromName >> toName >> weight;
            insertEdge(fromName, toName, weight);
        } else if (choice == 2) {
            cout << "Enter from and to: ";
            cin >> fromName >> toName;
            deleteEdge(fromName, toName);
        } else if (choice == 3) {
            displayMatrix();
        } else if (choice == 4) {
            displayIncomingOutgoing();
        } else if (choice != 5) {
            cout << "Invalid choice" << endl;
        }
    }
    return 0;
}