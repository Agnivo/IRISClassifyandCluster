/* Name : Assignment8.c
   Creator : Agnivo Saha
   Roll Number : 12CS10062
   Description : To identify various segments in an image inputed which have nearly similar colours and print an image having that many segments.
*/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>
#include<time.h>

/* A structure for storing the nodes in MST and also used for the queue used in the BFS traversal. */
typedef struct Adjacencynode{
  int i;
  int j;
  struct Adjacencynode *next;
}Adjnode;

/* A structure for each vertex in the MST to point to the node with which it shares an edge */
typedef Adjnode* Adjlist;

/* A structure for the MST which stores its size and the vertex set */
typedef struct MinimumSpanningTree{
  int size;
  Adjlist **array;
}MST;

/* A structure for storing weights of its neighbours ( with whom it shares an edge ) and also its R,G,B values */
typedef struct PIXEL{
    int R;
    int G;
    int B;
    int nbr[8];
}Graph;

/* A Heap structure used both in Prim's algorithm as well as for storing the s maximum weights of the edges */
typedef struct HEAP{
    int weight;
    int i1,j1,i2,j2;
}Heap;

/* A Queue structure used for Breadth First Search Traversal of the Minimum Spanning Tree */
typedef struct QUEUE{
    Adjnode *Front,*Rear;
}Queue;

/* This function creates a MST and initializes each vertex to have no neighbours */
MST* create_MST(int width,int height)
{

  int i,j;
  MST* min_span_tree = (MST *)malloc(sizeof(MST));
  min_span_tree->size = width * height;
  min_span_tree->array = (Adjlist **)malloc(height * sizeof(Adjlist *));
  for(i = 0;i < height;++i){
     min_span_tree->array[i] = (Adjlist *)malloc(width * sizeof(Adjlist));
     for(j = 0;j < width;++j){
         min_span_tree->array[i][j] = NULL;
     }
  }
  return min_span_tree;
}

/* This function adds edges between two vertices passed as arguments and as it is an undirected graph so it adds edges in both vertices */
void Add_edge(MST *min_span_tree,int i1,int j1,int i2,int j2)
{
    Adjnode *newnode1,*newnode2;
    newnode1 = (Adjnode *)malloc(sizeof(Adjnode));
    //initialize with the location of the pixel with which it shares an edge
    newnode1->i = i2;
    newnode1->j = j2;
    newnode1->next = min_span_tree->array[i1][j1];
    min_span_tree->array[i1][j1] = newnode1;
    newnode2 = (Adjnode *)malloc(sizeof(Adjnode));
    newnode2->i = i1;
    newnode2->j = j1;
    newnode2->next = min_span_tree->array[i2][j2];
    min_span_tree->array[i2][j2] = newnode2;
}

/* This function reads the colour values of each pixels and also calculates the weights of the edges it shares with its neighbours in an array */
Graph** read_Graph(FILE *fin,int width,int height)
{
    int i,j,r,g,b,k,l,s;
    Graph **G = (Graph **)malloc(height * sizeof(Graph *));
    for(i = 0;i < height;++i)
        G[i] = (Graph *)malloc(width * sizeof(Graph));
    for(i = 0;i < height;++i){
        for(j = 0;j < width;++j){
            fscanf(fin,"%d",&G[i][j].R);
            fscanf(fin,"%d",&G[i][j].G);
            fscanf(fin,"%d",&G[i][j].B);
        }

    }
    for(i = 0;i < height;++i){
        for(j = 0;j < width;++j){
            s = 0;
            for(k = i - 1;k <= i + 1;++k){
                for(l = j - 1;l <= j + 1;++l){
                    if(k == -1 || l == -1 || k == height || l == width){
                        G[i][j].nbr[s] = -1;
                        ++s;
                    }
                    else if(k == i && l == j)
                        continue;
                    else {
                        r = abs(G[i][j].R - G[k][l].R);
                        g = abs(G[i][j].G - G[k][l].G);
                        b = abs(G[i][j].B - G[k][l].B);
                        G[i][j].nbr[s] = r + g + b;
                        ++s;
                    }
                }
            }
        }
    }
    return G;
}

/* This function swaps to location in the heap */
void swap(Heap *H,int i,int j)
{
    int temp;
    temp = H[i].weight;
    H[i].weight = H[j].weight;
    H[j].weight = temp;
    temp = H[i].i1;
    H[i].i1 = H[j].i1;
    H[j].i1 = temp;
    temp = H[i].j1;
    H[i].j1 = H[j].j1;
    H[j].j1 = temp;
    temp = H[i].i2;
    H[i].i2 = H[j].i2;
    H[j].i2 = temp;
    temp = H[i].j2;
    H[i].j2 = H[j].j2;
    H[j].j2 = temp;
}

/* This function is the heapify routine used for the heap maintained for Prim's algorithm */
void Min_heapify(Heap *H,int **Location,int size,int i)
{
   int l,r,min;
   while(i < size){
     l = (2 * i) + 1;
     r = (2 * i) + 2;
     if(l > size - 1)
       return;
     if(l == size - 1)
       min = l;
     else {
       if(H[l].weight <= H[r].weight)
         min = l;
       else
         min = r;
     }
     if(H[min].weight >= H[i].weight)
       return;
    // We have to change the location of the positions changed in the heap  so that we can search for it later by just looking in to the array
     Location[H[i].i1][H[i].j1] = min;
     Location[H[min].i1][H[min].j1] = i;
     swap(H,i,min);
     i = min;
   }
}

/* This function is used in the Prim's algorithm to change the priority of the heap ,that is , if the new value in the i1,j1th location is less
   than the current value we have to change the value to the new value and store the i2,j2th location corresponding to it and ensure heap property
   and update the new location of it else return */
void Minheap_Change_Priority(Heap *H,int **Location,int weight,int i1,int j1,int i2,int j2)
{
   int i,p;
   i = Location[i1][j1];
   if(weight >= H[i].weight)
     return;
   H[i].i2 = i2;
   H[i].j2 = j2;
   H[i].weight = weight;
   while(i > 0){
     p = (i - 1)/2;
     if(H[i].weight < H[p].weight){
       Location[H[p].i1][H[p].j1] = i;
       Location[H[i].i1][H[i].j1] = p;
       swap(H,i,p);
       i = p;
     }
     else
       return;
   }
}

/* This is the heapify routine for the min heap storing the maximum weights */
void min_heapify(Heap *D,int size,int i)
{
  int l,r,min;
  while(i < size){
    l = (2 * i) + 1;
    r = (2 * i) + 2;
    if(l > size - 1)
      return;
    if(l == size - 1)
      min = l;
    else {
      if(D[l].weight <= D[r].weight)
        min = l;
      else
       min = r;
    }
    if(D[min].weight >= D[i].weight)
      return;
    swap(D,i,min);
    i = min;
  }
}

/* If the value is less than the current minimum then return else place it in the 0th location and heapify it to ensure Heap property */
void Minheap_Insert(Heap *D,int size,int weight,int i1,int j1,int i2,int j2)
{
   if (weight < D[0].weight)
     return;
   D[0].weight = weight;
   D[0].i1 = i1;
   D[0].j1 = j1;
   D[0].i2 = i2;
   D[0].j2 = j2;
   min_heapify(D,size,0);
}

/* This function deletes the minimum of the heap and returns the new size of the heap which is 1 less than the old value */
int Delete_Min(Heap *H,int **Location,int size)
{
   swap(H,0,size - 1);
   Min_heapify(H,Location,size - 1,0);
   return size - 1;
}

/* This function cuts the s-1 edges in the MST to produce a forest containing s trees */
MST *cut_tree(MST *min_span_tree,Heap *D,int s,int width)
{
    int i = 0;
    Adjnode *p,*q,*r;
    for(i = 0;i < s;++i){
        q = min_span_tree->array[D[i].i1][D[i].j1];
        p = min_span_tree->array[D[i].i1][D[i].j1];
        // Locate the node to be deleted and then delete it.
        if(p->i == D[i].i2 && p->j == D[i].j2){
            r = p;
            min_span_tree->array[D[i].i1][D[i].j1] = p->next;
            free(r);
        }
        else {
            p = p->next;
            while(p != NULL){
                if(p->i == D[i].i2 && p->j == D[i].j2){
                    r = p;
                    q->next = p->next;
                    free(r);
                    break;
                }
                q = q->next;
                p = p->next;
            }
        }
	    // As it is an undirected forest so we need to delete edges in both the vertex.
        q = min_span_tree->array[D[i].i2][D[i].j2];
        p  = min_span_tree->array[D[i].i2][D[i].j2];
        if(p->i == D[i].i1 && p->j == D[i].j1){
            r = p;
            min_span_tree->array[D[i].i2][D[i].j2] = p->next;
            free(r);
        }
        else {
            p = p->next;
            while(p != NULL){
                if(p->i == D[i].i1 && p->j == D[i].j1){
                    r = p;
                    q->next = p->next;
                    free(r);
                    break;
                }
                q = q->next;
                p = p->next;
            }
        }
    }
    return min_span_tree;
}

/* This function implemnts the Prim's algorithm to generate a Minimum Spanning Tree. */
MST *Make_Prim_MST(Graph **graph,int width,int height,int s)
{
    int i,j,k,l,n,weight,i1,j1,i2,j2,size,**set,**Location;
    Heap *H,*D;
    MST *min_span_tree;
    size = width * height;
    // Heap H is the heap used in Prim's algorithm , Heap D is used to store the s maximum weights selected.
    H = (Heap *)malloc(size * sizeof(Heap));
    D = (Heap *)malloc((s - 1) * sizeof(Heap));
    /* Array set stores 0 if the vertex i,j is in the set P and 1 if the vertex i,j is in the set Q . Location array stores the current location
       of i,jth vertex in the heap for the ease of search */
    set = (int **)malloc(height * sizeof(int *));
    Location = (int **)malloc(height * sizeof(int *));
    k = 0;
    /*Initialize Heap with 0,0th vertex and INT_MAX as the weight and all the vertices are initially placed in set P except 0,0 which is in set Q ,
      so initialize the set array 0. */
    for(i = 0;i < height;++i){
        Location[i] = (int *)malloc(width * sizeof(int));
        set[i] = (int *)malloc(width * sizeof(int));
        for(j = 0;j < width;++j){
            Location[i][j] = k;
            H[k].weight = INT_MAX;
            H[k].i1 = i;
            H[k].j1 = j;
            H[k].i2 = 0;
            H[k].i2 = 0;
            set[i][j] = 0;
            ++k;
        }
    }
    //Initialize the min heap which stores the s - 1 maximum values to -1 as any entry will be >= 0.
    for(i = 0;i < s - 1;++i){
        D[i].weight = -1;
    }
    // Create the MST.
    min_span_tree = create_MST(width,height);
    //Include 0,0 th vertex in set Q.
    set[0][0] = 1;
    Minheap_Change_Priority(H,Location,graph[0][0].nbr[4],0,1,0,0);  // Change the priority of neighbours of 0,0 th vertex.
    Minheap_Change_Priority(H,Location,graph[0][0].nbr[6],1,0,0,0);
    Minheap_Change_Priority(H,Location,graph[0][0].nbr[7],1,1,0,0);
    //Size of Q is 1 initially ,so when size becomes 1, P becomes empty and Q becomes full , so that ends the formation of MST.
    while(size > 1){
         //Store the current minimum and delete it from the heap and add it in the MST with its neighbour which is stored in i2,j2.
         weight = H[0].weight;
         i1 = H[0].i1;
         j1 = H[0].j1;
         i2 = H[0].i2;
         j2 = H[0].j2;
         size = Delete_Min(H,Location,size);
         Add_edge(min_span_tree,i1,j1,i2,j2);
         //Insert in the heap storing s - 1 maximums if it is greater than the current minimum.
         Minheap_Insert(D,s - 1,weight,i1,j1,i2,j2);
         set[i1][j1] = 1;  //Include it in set Q.
         n = 0;
         //Change priority of each neighbour of the minimum deleted if the neighbour is in set P.
         for(k = i1 - 1;k <= i1 + 1;++k){
                for(l = j1 - 1;l <= j1 + 1;++l){
                    if(k == i1 && l == j1)
                        continue;
                    else {
                        if(graph[i1][j1].nbr[n] != -1){
                            if(set[k][l] == 0){
                                Minheap_Change_Priority(H,Location,graph[i1][j1].nbr[n],k,l,i1,j1);
                            }
                        }
                       ++n;
                    }
                }
         }

    }
    //Cut the minimum spanning tree into s segments by cutting the s - 1 maximum edges.
    min_span_tree = cut_tree(min_span_tree,D,s - 1,width);
    return min_span_tree;
}

/* This function inserts an element in the Queue. */
Queue Enqueue(Queue Q,int i1,int j1)
{
    Adjnode *newnode;
    newnode = (Adjnode *)malloc(sizeof(Adjnode));
    newnode->i = i1;
    newnode->j = j1;
    newnode->next = NULL;
    if(Q.Rear == NULL){
        Q.Front = newnode;
        Q.Rear = newnode;
        return Q;
    }
    Q.Rear->next = newnode;
    Q.Rear = newnode;
    return Q;
}

/* This function deletes an element from the Queue.    */
Queue Dequeue(Queue Q)
{
    Adjnode *r;
    r = Q.Front;
    Q.Front = r->next;
    if(Q.Front == NULL)
        Q.Rear = NULL;
    free(r);
    return Q;
}

/* This function uses BFS for traversing through the forest and for each component it uses a different colour , for first 16 colours a predefined
   set of colours is used and the rest of the colours are genrated randomly */
Graph **BFS_Colouring(MST *min_span_tree,Graph **graph,int s,int width,int height,int MAX_SIZE,int colour_R[16],int colour_G[16],int colour_B[16])
{
    int i,j = 0,i1,j1,k,c,size,colour = 0,colourR,colourG,colourB,**visited;
    Queue Q;
    Adjnode *p;
    // visited array for a vertex stores 0 if the vertex has not been visited and stores 1 if it has been visited.
    visited = (int **)malloc(height * sizeof(int *));
    for(i = 0;i < height;++i){
        visited[i] = (int *)malloc(width * sizeof(int));
        for(j = 0;j < width;++j){
            visited[i][j] = 0;
        }
    }
    k = 0;
    size = width * height;
    // This while loop terminates if all vertices have been visited , that is , all pixels have been coloured.
    while(k < size){
        c = 0;
        // Find the vertex which has still not been visited and choose it for starting the BFS traversal.
        for(i = 0;i < height;++i){
            for(j = 0;j < width;++j){
                if(visited[i][j] == 0){
                    c = 1;
                    break;
                }
            }
            if(c == 1)
                break;
        }
	// Initialize Queue
        Q.Front = NULL;
        Q.Rear = NULL;
	// Insert the first unvisited vertex found in the queue.
        Q = Enqueue(Q,i,j);
	// For < 16 segments use predefined colours else generate colours randomly.
        if(colour < 16){
           colourR = colour_R[colour];
           colourG = colour_G[colour];
           colourB = colour_B[colour];
	       ++colour;
	   }
	   else {
          colourR = rand()%(MAX_SIZE);
          colourG = rand()%(MAX_SIZE);
	      colourB = rand()%(MAX_SIZE);
       }
	   graph[i][j].R = colourR;
       graph[i][j].G = colourG;
       graph[i][j].B = colourB;
       visited[i][j] = 1;
       ++k;
	// The Queue becomes empty when all vertices of a tree in the forest hasbeen visited.
       while(Q.Front != NULL){
          i1 = Q.Front->i;
          j1 = Q.Front->j;
          p = min_span_tree->array[i1][j1];
          Q = Dequeue(Q);
          while(p != NULL){
              // Colour the neigbour if it has not been visited and then insert the neighbour in the Queue.
             if(visited[p->i][p->j] == 0){
                 visited[p->i][p->j] = 1;
                 Q = Enqueue(Q,p->i,p->j);
 		         graph[p->i][p->j].R = colourR;
                 graph[p->i][p->j].G = colourG;
                 graph[p->i][p->j].B = colourB;
                 ++k;
             }
             p = p->next;
          }
        }
    }
    return graph;
}

/* This function writes the colour value of each pixel to the file. */
void print_image(FILE *fout,Graph **graph,int width,int height,int MAX_SIZE)
{
    int i,j;
    fprintf(fout,"P3 \n");
    fprintf(fout,"%d %d \n",width,height);
    fprintf(fout,"%d \n",MAX_SIZE);
    for(i = 0;i < height;++i){
        for(j = 0;j < width;++j){
            fprintf(fout,"%d %d %d \n",graph[i][j].R,graph[i][j].G,graph[i][j].B);
        }
    }
}

int main()
{
    int i,s,width,height,Max_level,colour_R[16] = {255,60,0,220,0,155,255,84,0,160,135,0,255,255,255,0};
    int colour_G[16] = {165,139,255,0,205,48,80,255,0,82,206,255,220,0,114,106};
    int colour_B[16] = {0,69,127,0,205,0,30,255,220,45,159,0,255,255,86,106} ;
    char str[100],string[100];
    //16 colours have been predefined and the rest generated randomly .
    srand((unsigned int)time(NULL));
    FILE *fin,*fout,*f_in,*f_out;
    Graph** graph;
    MST *min_span_tree;
    printf("Enter the value of s \n");
    scanf("%d",&s);
    f_in = fopen("weights_norm_black&white.ppm","r");
    fout = fopen("new.ppm","w");
    f_out = fopen("original1.ppm","w");
    //If we find anything starting with a # sign we ignore everything after that in that line.
    while(!feof(f_in)){
        fscanf(f_in,"%s",str);
        if(str[0] == '#'){
            fscanf(f_in,"%[^\n]",string);
            continue;
        }
        else
            fprintf(f_out,"%s \n",str);
    }
    fclose(f_in);
    fclose(f_out);
    printf("Comments have been deleted in the input file. \n");
    fin = fopen("original1.ppm","r");
    //Ignore P3.
    fscanf(fin,"%*c");
    fscanf(fin,"%*c");
    fscanf(fin,"%d",&width);
    fscanf(fin,"%d",&height);
    fscanf(fin,"%d",&Max_level);
    //Read the R,G,B values of each pixel.
    graph = read_Graph(fin,width,height);
    printf("The following segmentation is produced with s = %d \n",s);
    //Make the minimum spanning tree after cutting which contains s components.
    min_span_tree = Make_Prim_MST(graph,width,height,s);
    printf("The Minimum Spanning Tree has been generated . \n");
    //Colour the s components with s colours.
    graph = BFS_Colouring(min_span_tree,graph,s,width,height,Max_level,colour_R,colour_G,colour_B);
    printf("Colouring of segments have been done. \n");
    //Print the image generated.
    print_image(fout,graph,width,height,Max_level);
    fclose(fin);
    fclose(fout);
    free(graph);
    return 0;
}
