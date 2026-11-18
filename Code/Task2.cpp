#include <iostream>
using namespace std;

const int MAX_VERTICES = 7;
const int INFINITY_WEIGHT = 9999;
int numVertices;
const char* vertexNames;
int weightMatrix[MAX_VERTICES][MAX_VERTICES];

int getIndex(char vertexName){
    for (int i = 0; i < numVertices; i++)
        if (vertexNames[i] == vertexName) return i;
    return -1;
}

void addEdge(char firstName, char secondName, int weight){
    weightMatrix[getIndex(firstName)][getIndex(secondName)] = weight;
    weightMatrix[getIndex(secondName)][getIndex(firstName)] = weight;
}

void resetGraph(int vertexCount, const char* names){
    numVertices = vertexCount;
    vertexNames = names;
    for(int row = 0; row < MAX_VERTICES; row++)
        for(int col = 0; col < MAX_VERTICES; col++)
            weightMatrix[row][col] = 0;
}

void primMST() {
    int cheapestEdge[MAX_VERTICES];
    int treeParent[MAX_VERTICES];
    bool isInTree[MAX_VERTICES];

    for (int i = 0; i < numVertices; i++){
        cheapestEdge[i] = INFINITY_WEIGHT;
        isInTree[i] = false;
    }
    cheapestEdge[0] = 0;
    treeParent[0] = -1;

    for(int step = 0; step < numVertices; step++){
        int currentVertex = -1;
        for(int vertex = 0; vertex < numVertices; vertex++)
            if(!isInTree[vertex] && (currentVertex == -1 || cheapestEdge[vertex] < cheapestEdge[currentVertex]))
                currentVertex = vertex;
        isInTree[currentVertex] = true;

        for(int neighbour = 0; neighbour < numVertices; neighbour++){
            int edgeWeight = weightMatrix[currentVertex][neighbour];
            if(edgeWeight != 0 && !isInTree[neighbour] && edgeWeight < cheapestEdge[neighbour]){
                cheapestEdge[neighbour] = edgeWeight;
                treeParent[neighbour] = currentVertex;
            }
        }
    }

    int totalWeight = 0;
    for(int vertex = 1; vertex < numVertices; vertex++){
        int edgeWeight = weightMatrix[vertex][treeParent[vertex]];
        cout << "Edge " << vertex << ": " << vertexNames[treeParent[vertex]] << " - " << vertexNames[vertex];
        cout << ", Weight " << vertex << ": " << edgeWeight << endl;
        totalWeight += edgeWeight;
    }
    cout << "Total weight of MST = " << totalWeight << endl << endl;
}

int main(){
    resetGraph(5, "01234");
    addEdge('0','1',3);
    addEdge('0','3',7); 
    addEdge('0','4',8);
    addEdge('1','2',1); 
    addEdge('1','3',4); 
    addEdge('3','2',2); 
    addEdge('4','3',3);
    cout << "Graph A Prim's MST" << endl;
    cout << "Start = 0" << endl;
    primMST();

    resetGraph(7, "ABCDEFG");
    addEdge('A','B',1); 
    addEdge('A','D',5); 
    addEdge('B','D',3); 
    addEdge('B','C',4);
    addEdge('D','G',4); 
    addEdge('D','E',1); 
    addEdge('C','E',7); 
    addEdge('E','G',2);
    addEdge('E','F',1); 
    addEdge('G','F',10);
    cout << "Graph B Prim's MST" << endl;
    cout << "Start = A" << endl;
    primMST();
    return 0;
}