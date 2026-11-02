
#include <stdio.h>
#include <stdlib.h>

int a[20], n, start;

// Bubble Sort in ascending order
void sort()
{
    int i, j, t;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

// SCAN disk scheduling
void scan()
{
    int i, head = start, total = 0;

    printf("\nSCAN: %d", head);

    // Move towards higher cylinders
    for (i = 0; i < n; i++)
    {
        if (a[i] >= start)
        {
            total += abs(head - a[i]);
            head = a[i];
            printf(" -> %d", head);
        }
    }

    // Reach the last cylinder
    total += abs(head - 199);
    head = 199;
    printf(" -> %d", head);

    // Reverse direction
    for (i = n - 1; i >= 0; i--)
    {
        if (a[i] < start)
        {
            total += abs(head - a[i]);
            head = a[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal movement = %d\n", total);
}

// C-LOOK disk scheduling
void clook()
{
    int i, head = start, total = 0;

    printf("\nC-LOOK: %d", head);

    // Serve requests on the right
    for (i = 0; i < n; i++)
    {
        if (a[i] >= start)
        {
            total += abs(head - a[i]);
            head = a[i];
            printf(" -> %d", head);
        }
    }

    // Jump to the lowest pending request
    for (i = 0; i < n; i++)
    {
        if (a[i] < start)
        {
            total += abs(head - a[i]);
            head = a[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal movement = %d\n", total);
}

int main()
{
    int i;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter requests: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &start);

    sort();

    scan();
    clook();

    return 0;
}
