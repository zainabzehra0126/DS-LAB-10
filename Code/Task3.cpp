#include <iostream>
using namespace std;

struct Edge{
    int from, to, weight;
};

const int MAX_VERTICES = 6;
const int MAX_EDGES = 12;
int numVertices;
int numEdges;
const char* vertexNames;
Edge edgeList[MAX_EDGES];
int setLeader[MAX_VERTICES];

int getIndex(char vertexName){
    for(int i = 0; i < numVertices; i++)
        if (vertexNames[i] == vertexName) return i;
    return -1;
}

void addEdge(char firstName, char secondName, int weight){
    Edge newEdge = {getIndex(firstName), getIndex(secondName), weight};
    edgeList[numEdges++] = newEdge;
}

void resetGraph(int vertexCount, const char* names){
    numVertices = vertexCount;
    vertexNames = names;
    numEdges = 0;
}

int findSet(int vertex){
    while (setLeader[vertex] != vertex)
        vertex = setLeader[vertex];
    return vertex;
}

void sortEdges(){
    for(int i = 0; i < numEdges - 1; i++)
        for(int j = 0; j < numEdges - 1 - i; j++)
            if(edgeList[j].weight > edgeList[j + 1].weight){
                Edge temp = edgeList[j];
                edgeList[j] = edgeList[j + 1];
                edgeList[j + 1] = temp;
            }
}

void kruskalMST(){
    sortEdges();
    for(int i = 0; i < numVertices; i++)
        setLeader[i] = i;

    int totalWeight = 0, edgeCount = 0;
    for(int i = 0; i < numEdges && edgeCount < numVertices - 1; i++){
        int leaderOfFirst = findSet(edgeList[i].from);
        int leaderOfSecond = findSet(edgeList[i].to);

        if(leaderOfFirst != leaderOfSecond){
            edgeCount++;
            cout << "Edge " << edgeCount << ": " << vertexNames[edgeList[i].from] << " to " << vertexNames[edgeList[i].to];
            cout << ", Weight " << edgeCount << ": " << edgeList[i].weight << endl;
            totalWeight += edgeList[i].weight;
            setLeader[leaderOfFirst] = leaderOfSecond;
        }
    }
    cout << "Total weight of MST = " << totalWeight << endl << endl;
}

int main(){
    resetGraph(5, "abcde");
    addEdge('a','d',22); 
    addEdge('c','a',21); 
    addEdge('a','c',10); 
    addEdge('b','c',53);
    addEdge('b','e',45); 
    addEdge('c','e',33); 
    addEdge('e','d',19);
    cout << "Graph A Kruskal's MST" << endl;
    kruskalMST();

    resetGraph(6, "ABCDEF");
    addEdge('A','D',9); 
    addEdge('A','B',3); 
    addEdge('A','C',5); 
    addEdge('B','D',4);
    addEdge('B','C',3); 
    addEdge('B','E',7); 
    addEdge('C','D',2); 
    addEdge('D','E',2);
    addEdge('D','F',2); 
    addEdge('C','E',6); 
    addEdge('E','F',5); 
    addEdge('C','F',8);
    cout << "Graph B Kruskal's MST" << endl;
    kruskalMST();
    return 0;
}