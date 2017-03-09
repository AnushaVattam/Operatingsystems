#include <stdlib.h>
#include <stdio.h>

/********************* Implement Queue **********************/
/* Pointers for Queue */
struct Queue{
    struct ListNode *front;
    struct ListNode *rear;
};

/* Linked List node for Queue */
struct ListNode{
    struct node *data;
    struct ListNode* next;
};

/**
* Function to create queue.
*
* @return - pointer of queue
*/
struct Queue *CreateQueue(){
    struct Queue *Q;
    Q = (struct Queue *)malloc(sizeof(struct Queue));
    if(!Q)
    	return NULL;
    // set to default value
    Q->front = Q->rear = NULL;
    return Q;
}

/**
* Function to check if the queue is empty.
*
* @param Q - pointer to queue
* @return - 1 if stack is empty, else 0
*/
int IsEmptyQueue(struct Queue *Q){
    if(!Q)
        return 1;
    return(Q->front == NULL);
}

/**
* Function return the size of Queue.
*
* @param Q - pointer of queue
* @return - size of queue, 0 if queue is empty
*/
int QueueSize(struct Queue *Q){
    if(IsEmptyQueue(Q))
        return 0;
    struct ListNode *tmp = Q->front;
    int count = 0;
    // count number of nodes, start from front
    while(tmp){
        tmp = tmp->next;
        count++;
    }
    return count;
}

/**
* Function to add element in Queue.
*
* @param Q - pointer of queue
* @param data - data of the node to be added in queue
*/
void EnQueue(struct Queue *Q, struct node *data){
    /* create a new node */
    struct ListNode *new_node;
    new_node = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (new_node == NULL){
        printf("Error: no space available for noden");
    } else {    	/* initialize node */
        new_node->data = data;
        new_node->next = NULL;
        // add node at rear
        if(Q->rear != NULL)
            Q->rear->next = new_node;
        // move rear to new node
        Q->rear = new_node;
        // first node added
        if(Q->front == NULL)
            Q->front = Q->rear;
    }
}

/**
* Function to delete element from Queue.
*
* @param Q - pointer of queue
* @return - data of element deleted
*/
struct node *DeQueue(struct Queue *Q) {
    if (IsEmptyQueue(Q)) { /* queue is empty */
        printf("Error: Queue underflown");
        return NULL;
    } else { /* pop a node */
        struct ListNode *tmp = Q->front;
        /* pull out the data before the node is deleted */
        struct node *value = Q->front->data;
        Q->front = Q->front->next;
        // queue has only one node
        if(Q->front == NULL)
            Q->rear = NULL;
        free(tmp);
        return value;
    }
}

/**
* Function to delete Queue.
*
* @param Q - pointer of queue
*/
void DeleteQueue(struct Queue **Q){
    if (IsEmptyQueue(*Q)) {
        return;
    }
    else {
        struct ListNode *temp, *p;
        temp = (*Q)->front;
        while(temp){
            p = temp;
            temp = temp->next;
            // free nodes in queue
            free(p);
        }
        // free queue
        free(*Q);
        *Q = NULL;
    }
}

/**
 * Function to print Queue.
 *
 * @param Q - pointer to queue
 */
void PrintQueue(struct Queue *Q)
{
    printf("nList is: ");
    if(Q){
        struct ListNode *tmp;
        tmp = Q->front;
        while(tmp)
        {
            printf("%d  ", tmp->data);
            tmp = tmp->next;
        }
    }
}
/******************************************************/

/******************* Implement Stack ******************/
/* Linked List for Stack */
struct Stack{
    // data is of type "struct node *"
    struct node *data;
    struct Stack* next;
};

/**
* Function to create stack.
*
* @return - initial value for stack
*/
struct Stack *CreateStack(){
    return NULL;
}

/**
* Function to add node at top of the stack.
*
* @param head - top of the stack
* @param value - value of the node to be added in stack
*/
void Push(struct Stack **head, struct node *value){
    /* create a new node */
    struct Stack *tmp;
    tmp = (struct Stack *)malloc(sizeof(struct Stack));
    if (tmp == NULL){
        printf("Error: no space available for noden");
    } else {        /* initialize node */
        tmp->data = value;

        /* link the old list off the new node */
        tmp->next = *head;

        /* move the head to point to the new node */
        *head = tmp;
    }
}

/**
* Function to check if the stack is empty.
*
* @param head - top node of the stack
* @return - 1 if stack is empty, else 0
*/
int IsEmptyStack(struct Stack *head){
    return(head == NULL);
}

/**
* Function to remove node from the top of the stack.
*
* @param head - top of the stack
* @return - return the top node of the stack
*/
struct node *Pop(struct Stack **head) {
    if (IsEmptyStack(*head)) {                   /* stack is empty */
        return NULL;
    } else {                                     /* pop a node */
        struct Stack *top = *head;

        /* pull out the data before the node is deleted */
        struct node *value = top->data;

        /* unlink the head node for the caller */
        *head = top->next;
        free(top);
        return value;
    }
}

/**
* Function to return the data of top of the stack.
*
* @param head - top node of the stack
* @return - data of the top of the stack, NULL if stack empty
*/
struct node *Top(struct Stack *head){
    if (IsEmptyStack(head))
        return NULL;
    return head->data;
}

/**
* Function to delete stack.
*
* @param head - start node of the stack
*/
void DeleteStack(struct Stack **head){
    if (IsEmptyStack(*head)) {
        return;
    }
    else{
        struct Stack *temp, *p;
        p = *head;
        while(p->next){
            temp = p->next;
            p->next = temp->next;
            free(temp);
        }
        free(p);
    }
}

/**
* Function to print stack from top to end.
*
* @param node - top node of the stack
*/
void PrintStack(struct Stack *node)
{
    printf("nList is: ");
    while(node != NULL)
    {
        printf("%d  ", node->data);
        node = node->next;
    }
}
/***********************************************************/

/* A binary tree node has data, left child and right child */
struct node
{
    int data;
    struct node* left;
    struct node* right;
};

/**
* Helper function that allocates a new node with the given data and
* NULL left and right pointers.
*
* @param data - data whose node to be created
* @return - node with data
*/
struct node* newNode(int data)
{
    struct node* node = (struct node *)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

/**
* Iterative process to print tree in reverse level order traversal.
*
* @param root - root of the tree
*/
void ReverseLevelOrder(struct node *root)
{
    struct node *tmp;
    struct Stack *S;
    struct Queue *Q;
    if(!root){
        return;
    }

    S = CreateStack();
    Q = CreateQueue();
    EnQueue(Q, root);
    while(!IsEmptyQueue(Q)){
        tmp = DeQueue(Q);
        if(tmp->left)
            EnQueue(Q, tmp->left);
        if(tmp->right)
            EnQueue(Q, tmp->right);
        // push all elements in stack
        Push(&S, tmp);
    }
    while(!IsEmptyStack(S))
        printf("%d ", Pop(&S)->data);

    DeleteQueue(&Q);
    DeleteStack(&S);
}

/**
* Helper function for DisplayTree function. Recursively print the
* tree nodes. We pass 0 as default value for level.
*
* @param level - shows the level of the binary tree
* @param root - root of the tree
*/
void Display(int level, struct node *root){
    int i;
    printf("n");
    if(root){
        Display(level+1, root->right);

        for(i=0 ; i<level ; i++)
            printf("    ");
        if(level == 0)
            printf("%d(R)", root->data);
        else
            printf("%d", root->data);
        Display(level+1, root->left);
    }
}

/**
* Display the tree in 90 degree anti-clockwise direction.
*  R shows Root node, nodes above R shows Right Subtree and nodes
*  below R shows left subtree.
*
* @param root - root of the tree
*/
void DisplayTree(struct node *root){
    printf("nTree:(R-Root node, Above R-right subtree, Below R-left subtree)");
    Display(0, root);
}

int main()
{
    /* Constructed binary tree is
            4
          /
        2      6
      /      /
    1     3  5
  */
  struct node *root = newNode(4);
  root->left        = newNode(2);
  root->right       = newNode(6);
  root->left->left  = newNode(1);
  root->left->right = newNode(3);
  root->right->left = newNode(5);
  DisplayTree(root);

  printf("nReverse Level Order traversal: ");
  ReverseLevelOrder(root);

  return 0;
}
