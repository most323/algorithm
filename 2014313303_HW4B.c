#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1981  //input + \n + NULL = 1979 + 1 + 1
#define MAX_COND_LEN 41 //animal1 + / + animal2 + \n + NULL = 19 + 1 + 19 + 1 + 1
#define MAX_QUEUE 99  //Max queue size is 99.

typedef enum { false, true } bool; 
typedef enum {WHITE, GRAY, BLACK} color;

//Make struct Animal.
typedef struct{
    char* name;  //Store animal's name.
    int rank;    //Store animal's rank.
    int num;     //Store animal's number in adjacency array.
    int indegree;//Store animal's the number of indegree edges.
} Animal;

typedef Animal Data;
typedef struct {
	int front, rear;
	Data items[MAX_QUEUE];
} Queue;

// Make queue empty.
void InitQueue(Queue *pqueue);
// Check whether queue is full.
bool IsFull(Queue *pqueue);
// Check whether queue is empty.
bool IsEmpty(Queue *pqueue);
// Read the item at the front.
Data Peek(Queue *pqueue);
// Insert an item at the rear.
void EnQueue(Queue *pqueue, Data item);
// Delete an item at the front.
void DeQueue(Queue *pqueue);

bool IsCycle_DFS(int** adj_arr, int N, color* visited);
bool IsCycle_DFS_Visit(int** adj_arr, int N, color* visited, int u);
int compare(const void *a, const void *b);
int main(){
    int N,C;  //N : the number of animals, C : the number of conditions.
    Animal* animal;  //The array of animal.
    Animal u;  //vertex u.
    int v;     //vertex v.
    char* p;
    char* p1;
    char* p2;
    int index = 1;
    char input[MAX_INPUT];  //Store second line input.
    char cond[MAX_COND_LEN]; //Store condition input.
    int i,j;
    int strong, weak;
    bool flag = false;
    int temp_rank;
    color* visited;  //The array to represent the node is visited or not.
    bool ret;  //Store return value.
    int current, next; //The number of animals in current distance and next distance.
    Queue q;  //Queue.
    InitQueue(&q); //Initialize queue.

    scanf("%d %d",&N,&C); //Get input N and C.
    while(getchar()!='\n'){}; //Eliminate any other input between C and '\n'.

    //Allocate array animal.
    animal = (Animal*)malloc(sizeof(Animal) * N);

    //Allocate array visited.
    visited = (color*)malloc(sizeof(color) * N);
    for(i=0;i<N;i++){ //Initialize array visited.
        visited[i] = WHITE;
    }

    fgets(input, sizeof(input), stdin); //Store second line input to array input.
    input[strlen(input)-1] = 0; //Change '\n' to NULL.

    //The array input is cut to '/' and store its first address in p.
    p = strtok(input, "/");
    //animal[0].
    animal[0].name = p;
    animal[0].rank = 0;
    animal[0].num = 0;
    animal[0].indegree = 0;
    //Fill the value of animal.
    while(p = strtok(NULL, "/")){
        animal[index].name = p;
        animal[index].rank = 0;
        animal[index].num = index;
        animal[index].indegree = 0;
        index++;
    }

    //Allocate array adj_arr.
    int** adj_arr;
    adj_arr = (int**)malloc(sizeof(int*) * N);
    for(i=0;i<N;i++){
        adj_arr[i] = (int*)malloc(sizeof(int) * N);
    }
    //Initialize array adj_arr.
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            adj_arr[i][j] = 0;
        }
    }

    for(i=0;i<C;i++){
        //Store condition input to array cond.
        fgets(cond, sizeof(cond), stdin);
        cond[strlen(cond)-1] = 0;//Change '\n' to NULL.

        //The array input is cut to '/' and store its first address in p1 and p2.
        p1 = strtok(cond, "/");
        p2 = strtok(NULL, "/");

        flag = false;
        for(j=0;j<N;j++){
            if(!strcmp(animal[j].name, p1)){ //animal[j].name = p1
                strong = j;
                if(flag == true){
                    break;
                }
                flag = true;
            }
            if(!strcmp(animal[j].name, p2)){ //animal[j].name = p2
                weak = j;
                if(flag == true){
                    break;
                }
                flag = true;
            }
        }
        adj_arr[strong][weak] = 1; //Build the adjacency array.
        animal[weak].indegree++;
    }

    //Use DFS to check a cycle.
    ret = IsCycle_DFS(adj_arr, N, visited);
    if(ret){ //There is a cycle.
        printf("Stupid David!\n");

        //Free array animal.
        free(animal);

        //Free array adj_arr.
        for(i=0;i<N;i++){
            free(adj_arr[i]);
        }
        free(adj_arr);

        return 1;
    }

    for(i=0;i<N;i++){
        if(animal[i].indegree == 0){ //The animal doesn't have indegree edges.
            animal[i].rank = 1; //rank = 1.
            EnQueue(&q, animal[i]); //Enqueue the animal to have rank 1.
            temp_rank = 2;
            current = 1; //The number of animal in same distance.
            next = 0; //The number of animal in next distance.
            while(IsEmpty(&q) == false){
                u = Peek(&q);
                DeQueue(&q);
                current--;
                for(v=0;v<N;v++){
                    if(adj_arr[u.num][v] == 1){ //Next distance animal is discovered.
                        EnQueue(&q, animal[v]);
                        if(animal[v].rank < temp_rank){ //A larger one is selected.
                            animal[v].rank = temp_rank;
                        }
                        next++;
                    }
                }
                if(current == 0){ //Current distance animals are all checked.
                    current = next; //Go to the next distance.
                    next = 0;
                    temp_rank++;
                }
            }
        }
    }

    //Sort array animal.
    qsort(animal, N, sizeof(Animal), compare);

    for(i=0;i<N;i++){ //Print output.
        printf("%d %s\n",animal[i].rank,animal[i].name);
    }

    //Free array animal.
    free(animal);

    //Free array adj_arr.
    for(i=0;i<N;i++){
        free(adj_arr[i]);
    }
    free(adj_arr);

    return 0;
}
bool IsCycle_DFS(int** adj_arr, int N, color* visited){
    int i;
    bool ret;

    for(i=0;i<N;i++){
        if(visited[i] == WHITE){ //i'th node is never visited.
            ret = IsCycle_DFS_Visit(adj_arr, N, visited, i);
            if(ret){
                return true; //There is a cycle.
            }
        }
    }
    return false; //There is not a cycle.
}
bool IsCycle_DFS_Visit(int** adj_arr, int N, color* visited, int u){
    int v;
    bool ret;

    visited[u] = GRAY; //u'th node is visited.
    for(v=0;v<N;v++){
        if(adj_arr[u][v] == 1){ //u->v.
            if(visited[v] == WHITE){
                ret = IsCycle_DFS_Visit(adj_arr, N, visited, v);
                if(ret){
                    return true; //There is a cycle.
                }
            }else if(visited[v] == GRAY){
                return true; //There is a cycle.
            }
        }
    }
    visited[u] = BLACK; //u'th node is finished.
    return false; //There is not a cycle.
}
//Sort the array.
int compare(const void *a, const void *b){
    Animal* p1 = (Animal*)a;
    Animal* p2 = (Animal*)b;
    int r1, r2;
    char* n1;
    char* n2;

    r1 = p1->rank;
    r2 = p2->rank;
    
    n1 = p1->name;
    n2 = p2->name;

    if(r1 > r2){ //Sort by rank.
        return 1;
    }else if(r1 < r2){
        return -1;
    }else{ //If ranks are same, sort by name.
        return strcmp(n1, n2);
    }
}
// Make queue empty.
void InitQueue(Queue *pqueue)
{
	pqueue->front = pqueue->rear = 0;
}

// Check whether queue is full.
bool IsFull(Queue *pqueue)
{
	return pqueue->front
		== (pqueue->rear + 1) % MAX_QUEUE;
}

// Check whether queue is empty.
bool IsEmpty(Queue *pqueue)
{
	return pqueue->front == pqueue->rear;
}

// Read the item at the front.
Data Peek(Queue *pqueue)
{
	if (IsEmpty(pqueue))
		exit(1); //error: empty stack
	return pqueue->items[pqueue->front];
}

// Insert an item at the rear.
void EnQueue(Queue *pqueue, Data item)
{
	if (IsFull(pqueue))
		exit(1); //error: stack full
	pqueue->items[pqueue->rear] = item;
	pqueue->rear = (pqueue->rear + 1) % MAX_QUEUE;
}

// Delete an item at the front.
void DeQueue(Queue *pqueue)
{
	if (IsEmpty(pqueue))
		exit(1); //error: empty stack
	pqueue->front = (pqueue->front + 1) % MAX_QUEUE;
}
