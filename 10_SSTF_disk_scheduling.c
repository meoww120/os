#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[5] = {10, 20, 60, 90, 30};
    int visited[5] = {0};
    int n = 5, head = 50, curr, total = 0;

    curr = head;

    for (int i = 0; i < n; i++)
    {
        int min = 999999;
        int pos = -1;

        for (int j = 0; j < n; j++)
        {
            if (visited[j] == 0)
            {
                int diff = abs(curr - arr[j]);

                if (diff < min)
                {
                    min = diff;
                    pos = j;
                }
            }
        }

        visited[pos] = 1;
        total += abs(curr - arr[pos]);
        curr = arr[pos];

        printf("Head moves from %d to %d\n", head, arr[pos]);
        head = arr[pos];
    }

    printf("Total head movement = %d\n", total);

    return 0;
}
