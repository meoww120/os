#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, j, head, size;
    int a[100], b[100];
    int scan = 0, clook = 0, temp;
    int pos;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk requests:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size (number of cylinders): ");
    scanf("%d", &size);

    // Copy requests for C-LOOK
    for (i = 0; i < n; i++)
        b[i] = a[i];

    // Sort requests in ascending order
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    printf("\nSCAN Disk Scheduling\n");
    printf("Enter initial direction (0 = lower, 1 = higher): ");
    int dir;
    scanf("%d", &dir);

    printf("Head movement: %d", head);

    // Find the first request greater than or equal to head
    for (i = 0; i < n; i++)
    {
        if (a[i] >= head)
        {
            pos = i;
            break;
        }
    }

    if (i == n)
        pos = n;

    if (dir == 1)
    {
        // Move towards higher cylinders
        for (i = pos; i < n; i++)
        {
            scan += abs(head - a[i]);
            head = a[i];
            printf(" -> %d", head);
        }

        // Move to the end of the disk
        if (head != size - 1)
        {
            scan += abs((size - 1) - head);
            head = size - 1;
            printf(" -> %d", head);
        }

        // Reverse direction
        for (i = pos - 1; i >= 0; i--)
        {
            scan += abs(head - a[i]);
            head = a[i];
            printf(" -> %d", head);
        }
    }
    else
    {
        // Move towards lower cylinders
        for (i = pos - 1; i >= 0; i--)
        {
            scan += abs(head - a[i]);
            head = a[i];
            printf(" -> %d", head);
        }

        // Move to cylinder 0
        if (head != 0)
        {
            scan += head;
            head = 0;
            printf(" -> %d", head);
        }

        // Reverse direction
        for (i = pos; i < n; i++)
        {
            scan += abs(head - a[i]);
            head = a[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal SCAN head movement: %d cylinders\n", scan);

    // C-LOOK
    head = (dir == 1) ? head : head;

    // Restore the original head position
    printf("\nC-LOOK Disk Scheduling\n");
    printf("Head movement: ");

    // Sort requests for C-LOOK
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (b[j] > b[j + 1])
            {
                temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }

    // Find the first request greater than or equal to original head
    int originalHead;
    printf("\nEnter initial head position again for C-LOOK: ");
    scanf("%d", &originalHead);

    for (i = 0; i < n; i++)
    {
        if (b[i] >= originalHead)
            break;
    }
    pos = i;

    head = originalHead;
    printf("%d", head);

    if (dir == 1)
    {
        // Move towards higher cylinders
        for (i = pos; i < n; i++)
        {
            clook += abs(head - b[i]);
            head = b[i];
            printf(" -> %d", head);
        }

        // Jump to the lowest request
        if (pos > 0)
        {
            clook += abs(head - b[0]);
            head = b[0];
            printf(" -> %d", head);

            for (i = 1; i < pos; i++)
            {
                clook += abs(head - b[i]);
                head = b[i];
                printf(" -> %d", head);
            }
        }
    }
    else
    {
        // Move towards lower cylinders
        for (i = pos - 1; i >= 0; i--)
        {
            clook += abs(head - b[i]);
            head = b[i];
            printf(" -> %d", head);
        }

        // Jump to the highest request
        if (pos < n)
        {
            clook += abs(head - b[n - 1]);
            head = b[n - 1];
            printf(" -> %d", head);

            for (i = n - 2; i >= pos; i--)
            {
                clook += abs(head - b[i]);
                head = b[i];
                printf(" -> %d", head);
            }
        }
    }

    printf("\nTotal C-LOOK head movement: %d cylinders\n", clook);

    return 0;
}