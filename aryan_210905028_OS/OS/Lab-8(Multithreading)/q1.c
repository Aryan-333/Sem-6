// Write a multithreaded program that generates the Fibonacci series. The program
// should work as follows: The user will enter on the command line the number of
// Fibonacci numbers that the program is to generate. The program then will create a
// separate thread that will generate the Fibonacci numbers, placing the sequence in
// data that is shared by the threads (an array is probably the most convenient data
// structure). When the thread finishes execution the parent will output the sequence
// generated by the child thread. Because the parent thread cannot begin outputting the
// Fibonacci sequence until the child thread finishes, this will require having the parent
// thread wait for the child thread to finish.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *fibonacci(void *param)
{
    int i;
    int n = (int)param;
    // printf("%d\n", n);
    int *fib = (int *)malloc(sizeof(int) * n);
    // the problem with static local declaration is array is local to the function, which means its memory is allocated on the stack and exists only within the scope of the function.
    // When you allocate memory using malloc, the memory is allocated on the heap, and it persists until explicitly deallocated using free.
    fib[0] = 0;
    fib[1] = 1;

    for (i = 2; i < n; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return (void *)fib;
}
int main(int argc, char *argv[])
{
    pthread_t thread;
    int n = atoi(argv[1]); // to convert to int
    int *fib;

    pthread_create(&thread, 0, &fibonacci, (void *)n);

    pthread_join(thread, (void **)&fib);

    printf("Fibonnaci numbers are:\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d", fib[i]);
    }
}