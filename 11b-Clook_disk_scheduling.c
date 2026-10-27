#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, j, head, direction;
    int a[100], temp, total = 0, pos;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk requests:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    int original = head;

    printf("Enter direction (0 = lower, 1 = higher): ");
    scanf("%d", &direction);

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

    // Find the first request greater than or equal to head
    for (i = 0; i < n; i++)
    {
        if (a[i] >= head)
            break;
    }
    pos = i;

    total = 0;
    printf("\nC-LOOK Head Movement: %d", original);

    if (direction == 1)
    {
        // Move towards higher cylinders
        for (i = pos; i < n; i++)
        {
            total += abs(head - a[i]);
            head = a[i];
            printf(" -> %d", head);
        }

        // Jump to the lowest request
        if (pos > 0)
        {
            total += abs(head - a[0]);
            head = a[0];
            printf(" -> %d", head);

            // Continue in the same direction
            for (i = 1; i < pos; i++)
            {
                total += abs(head - a[i]);
                head = a[i];
                printf(" -> %d", head);
            }
        }
    }
    else
    {
        // Move towards lower cylinders
        for (i = pos - 1; i >= 0; i--)
        {
            total += abs(head - a[i]);
            head = a[i];
            printf(" -> %d", head);
        }

        // Jump to the highest request
        if (pos < n)
        {
            total += abs(head - a[n - 1]);
            head = a[n - 1];
            printf(" -> %d", head);

            // Continue in the same direction
            for (i = n - 2; i >= pos; i--)
            {
                total += abs(head - a[i]);
                head = a[i];
                printf(" -> %d", head);
            }
        }
    }

    printf("\nTotal Head Movement = %d cylinders\n", total);

    return 0;
}