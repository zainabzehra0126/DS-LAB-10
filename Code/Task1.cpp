// Q1: BFS and DFS on graphs (a) to (h)  -- Lab 11 style (adjacency matrix, array queue, recursive DFS)
#include <iostream>
using namespace std;

const int MAX_VERTICES = 8;
int numVertices;
const char* vertexNames;
int adjMatrix[MAX_VERTICES][MAX_VERTICES];
bool isVisited[MAX_VERTICES];

int queueArray[MAX_VERTICES];
int queueFront = 0, queueRear = 0;

void enqueue(int vertex){
    queueArray[queueRear++] = vertex;
}

int  dequeue(){
    return queueArray[queueFront++];
}

bool isQueueEmpty(){
    return queueFront == queueRear;
}

int getIndex(char vertexName){
    for (int i = 0; i < numVertices; i++)
        if (vertexNames[i] == vertexName) return i;
    return -1;
}

void addEdge(char fromName, char toName){
    adjMatrix[getIndex(fromName)][getIndex(toName)] = 1;
}

void clearVisited(){
    for (int i = 0; i < MAX_VERTICES; i++)
        isVisited[i] = false;
}

void resetGraph(int vertexCount, const char* names){
    numVertices = vertexCount;
    vertexNames = names;
    for (int row = 0; row < MAX_VERTICES; row++)
        for (int col = 0; col < MAX_VERTICES; col++)
            adjMatrix[row][col] = 0;
    clearVisited();
    queueFront = queueRear = 0;
}

void BFS(int startVertex){
    isVisited[startVertex] = true;
    enqueue(startVertex);

    while (!isQueueEmpty()){
        int currentVertex = dequeue();
        cout << vertexNames[currentVertex] << " ";

        for (int neighbour = 0; neighbour < numVertices; neighbour++){
            if (adjMatrix[currentVertex][neighbour] == 1 && !isVisited[neighbour]){
                isVisited[neighbour] = true;
                enqueue(neighbour);
            }
        }
    }
}

void DFS(int currentVertex){
    isVisited[currentVertex] = true;
    cout << vertexNames[currentVertex] << " ";

    for (int neighbour = 0; neighbour < numVertices; neighbour++){
        if (adjMatrix[currentVertex][neighbour] == 1 && !isVisited[neighbour])
            DFS(neighbour);
    }
}

void runTraversals(const char* graphTitle, char startName){
    cout << graphTitle << endl;
    cout << "start = " << startName << "" << endl;

    clearVisited();
    queueFront = queueRear = 0;
    cout << "BFS: ";
    BFS(getIndex(startName));
    cout << endl;

    clearVisited();
    cout << "DFS: ";
    DFS(getIndex(startName));
    cout << endl << endl;
}

void graphA(){
    resetGraph(5, "abcde");
    addEdge('a','b');
    addEdge('a','c');
    addEdge('a','d');
    addEdge('a','e');
    addEdge('b','d');
    addEdge('c','d');
    addEdge('c','e'); 
    addEdge('d','e');
    runTraversals("a", 'a');
}

void graphB(){
    resetGraph(7, "1234567");
    addEdge('1','2'); 
    addEdge('1','4');
    addEdge('2','3'); 
    addEdge('2','5');
    addEdge('3','7'); 
    addEdge('4','6'); 
    addEdge('5','7'); 
    addEdge('6','5'); 
    addEdge('6','7');
    runTraversals("b", '1');
}

// Both C and D are same, so I am only initializing C
void graphC(const char* graphTitle){
    resetGraph(6, "ABCDEF");
    addEdge('A','B'); 
    addEdge('A','C'); 
    addEdge('C','B'); 
    addEdge('C','D');
    addEdge('C','E'); 
    addEdge('D','E'); 
    addEdge('B','F'); 
    addEdge('E','F');
    runTraversals(graphTitle, 'A');
}

// Both E and H are same, so I am only initializing E
void graphE(const char* graphTitle){
    resetGraph(8, "ABCDEFGH");
    addEdge('A','B'); 
    addEdge('A','D'); 
    addEdge('B','C'); 
    addEdge('B','F');
    addEdge('C','E'); 
    addEdge('C','G'); 
    addEdge('C','H'); 
    addEdge('D','F');
    addEdge('E','B'); 
    addEdge('E','F'); 
    addEdge('F','A'); 
    addEdge('G','E');
    addEdge('G','H'); 
    addEdge('H','A');
    runTraversals(graphTitle, 'A');
}

void graphF(){
    resetGraph(8, "01234567");
    addEdge('0','1'); 
    addEdge('0','2'); 
    addEdge('0','3'); 
    addEdge('1','3');
    addEdge('2','4'); 
    addEdge('3','5'); 
    addEdge('3','6'); 
    addEdge('4','5');
    addEdge('4','7'); 
    addEdge('5','2');
    runTraversals("f", '0');
}

void graphG(){
    resetGraph(8, "01234567");
    addEdge('0','1'); 
    addEdge('1','0'); 
    addEdge('0','3'); 
    addEdge('3','0');
    addEdge('0','7'); 
    addEdge('1','4'); 
    addEdge('7','4'); 
    addEdge('7','5');
    addEdge('3','5'); 
    addEdge('4','6'); 
    addEdge('5','6');
    runTraversals("g", '0');
}

int main(){
    graphA();
    graphB();
    graphC("c");
    graphC("d");
    graphE("e");
    graphF();
    graphG();
    graphE("h");
    return 0;
}