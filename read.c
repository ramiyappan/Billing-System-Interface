#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Function Prototypes **/
struct Stack* createStack(unsigned capacity);
int isFull(struct Stack* stack);
int isEmpty(struct Stack* stack);
void push(struct Stack* stack, int item);
int pop(struct Stack* stack);
int peek(struct Stack* stack);

// A structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

// Main function to test above functions
int main()
{
    int i;
    int input=-10;

    struct Stack* stack = createStack(10);

    for(i=0;i<stack->capacity||input !=0;i++){
    printf("\nEnter the value to push; Enter 0 to stop: ");
    scanf("%d",&input);
    push(stack, input);
    if (input == 0)
        break;
    }

    printf("%d popped from stack\n", pop(stack));
    printf("%d popped from stack\n", pop(stack));
    printf("%d popped from stack\n", pop(stack));

    printf("\nTop element on the stack is %d", peek(stack));
    printf("\nElements present on the stack are: ");

    for(i=0;i<=stack->top;i++)
        printf("%d ", stack->array[i]);

    printf("\n\n");
    return 0;
}

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, int item)
{
    if (isFull(stack))
        return;

    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}

// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}

// Function to return the top from stack without removing it
int peek(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}