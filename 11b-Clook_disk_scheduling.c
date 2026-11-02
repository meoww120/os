
#include <stdio.h>
#include <stdlib.h>

int a[20], n, start;

// Sort requests
void sort()
{
    int i, j, t;

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (a[i] > a[j])
            {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

void clook()
{
    int i, head = start, total = 0;

    printf("\nC-LOOK: %d", head);

    // Serve requests towards right
    for (i = 0; i < n; i++)
    {
        if (a[i] >= start)
        {
            total += abs(head - a[i]);
            head = a[i];
            printf(" -> %d", head);
        }
    }

    // Jump to lowest pending request
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
    clook();

    return 0;
}
