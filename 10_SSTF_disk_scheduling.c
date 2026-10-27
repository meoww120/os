#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, head, total = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int req[n];
    int visited[n];

    printf("Enter disk requests:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &req[i]);
        visited[i] = 0;
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nSeek Sequence: %d", head);

    for (i = 0; i < n; i++)
    {
        int min = 999999;
        int pos = -1;

        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && abs(head - req[j]) < min)
            {
                min = abs(head - req[j]);
                pos = j;
            }
        }

        total += abs(head - req[pos]);
        head = req[pos];
        visited[pos] = 1;

        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement = %d cylinders\n", total);

    return 0;
}