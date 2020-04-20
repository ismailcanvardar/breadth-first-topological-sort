#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NODESIZE 10

// QUEUE SECTION
int *a;
int size = 0;
void enqueue(int data)
{
    int *b = (int *)malloc(sizeof(int) * size + 1);
    int i = 0;
    for (i = 0; i < size; i++)
    {
        b[i] = a[i];
    }
    b[i] = data;
    size++;
    a = b;
}
int dequeue()
{
    if (size <= 0)
        return -1;

    int *b = (int *)malloc(sizeof(int) * size - 1);
    for (int i = 0; i < size - 1; i++)
    {
        b[i] = a[i + 1];
    }
    int result = a[0];
    size--;
    a = b;
    // printf("\ndeque %d\n", result);
    return result;
}
void printqueue()
{
    printf("\n");
    for (int i = 0; i < size; i++)
        printf("%d_", a[i]);
}
//

struct node
{
    int vertex;
    struct node *next;
};
struct node *createNode(int);

struct Graph
{
    int numVertices;
    struct node **adjLists;
};

struct Graph *createGraph(int vertices);
void addEdge(struct Graph *graph, int src, int dest);
void printGraph(struct Graph *graph);
int countEdges(struct Graph *graph, int vertex);
void deleteNode(struct Graph *graph, int vertex);
int findPrerequisition(struct Graph *graph, int vertex);
int findEdgeCount(struct Graph *graph);
void deleteVertex(struct Graph *graph, int vertex);
int checkVisited(int * arr, int x);

int main()
{
    struct Graph *graph = createGraph(NODESIZE);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 5);
    addEdge(graph, 1, 7);
    addEdge(graph, 3, 2);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 7);
    addEdge(graph, 3, 8);
    addEdge(graph, 4, 8);
    addEdge(graph, 6, 0);
    addEdge(graph, 6, 1);
    addEdge(graph, 6, 2);
    addEdge(graph, 8, 2);
    addEdge(graph, 8, 7);
    addEdge(graph, 9, 4);

    int *visitedNums = malloc(sizeof(int) * 10);


    // printGraph(graph);

    while (1)
    {
        
        // vertices that have prerequsition is 0 enters queue in order
        for (int i = 0; i < graph->numVertices; i++)
        {
            if (findPrerequisition(graph, i) == 0 && checkVisited(visitedNums, i) == 0)
            {
                enqueue(i);
                visitedNums[i] = i;
                printf("%d", visitedNums[i]);
            }
        }

        for (int i = 0; i < size; i ++) {
            int dequeuedNum = dequeue();
            // printf("\n%d\n", dequeuedNum);
            // printf("%d", findEdgeCount(graph));
            deleteVertex(graph, dequeuedNum);
        }

        if (findEdgeCount(graph) == 0)
        {
            break;
        }
    }

    return 0;
}

struct node *createNode(int v)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createGraph(int vertices)
{
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node *));

    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = createNode(i);

    return graph;
}

void addEdge(struct Graph *graph, int src, int dest)
{
    if (graph->adjLists[src]->next == NULL)
    {
        struct node *newNode = createNode(dest);
        graph->adjLists[src]->next = newNode;
    }
    else
    {
        struct node *cursor = graph->adjLists[src];

        while (cursor->next != NULL)
        {
            cursor = cursor->next;
        }

        struct node *newNode = createNode(dest);
        cursor->next = newNode;
    }
}

void printGraph(struct Graph *graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node *temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
    }
}

int countEdges(struct Graph *graph, int vertex)
{
    int counter = 0;
    struct node *temp = graph->adjLists[vertex];
    while (temp)
    {
        ++counter;
        temp = temp->next;
    }
    printf("Vertex %d has %d edges.\n", vertex, counter - 1);
    return counter - 1;
}

int findEdgeCount(struct Graph *graph)
{
    int counter = 0;
    for (int i = 0; i < graph->numVertices; i++)
    {
        struct node *temp = graph->adjLists[i]->next;
        while (temp)
        {
            ++counter;
            temp = temp->next;
        }
    }
    // printf("%d", counter);
    return counter;
}

int findPrerequisition(struct Graph *graph, int vertex)
{
    int counter = 0;
    for (int i = 0; i < graph->numVertices; i++)
    {
        struct node *temp = graph->adjLists[i]->next;
        while (temp)
        {
            if (temp->vertex == vertex)
            {
                ++counter;
            }
            temp = temp->next;
        }
    }
    // printf("%d", counter);
    return counter;
}

void deleteNode(struct Graph *graph, int vertex)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        struct node *current = graph->adjLists[i], *prev;
        while (current != NULL)
        {
            // printf("%d\t", current->vertex);
            if (current->vertex == vertex)
            {
                prev->next = current->next;
            }

            prev = current;
            current = current->next;
        }
    }
}

void deleteVertex(struct Graph *graph, int vertex)
{
    struct node *flag = graph->adjLists[vertex];
    flag->next = NULL;
}

int checkVisited(int * arr, int x) {
    for (int i = 0; i < 10; i ++) {
        if (x == arr[i]) {
            return 1;
        }
    }
    return 0;
}