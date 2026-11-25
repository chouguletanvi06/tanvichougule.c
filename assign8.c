#include <stdio.h>

#define SAFE_DISTANCE 20  // Safe limit in cm

// Function to find the nearest (minimum) distance using pointer
int findNearest(int *dist, int n)
{
    int min = *dist;

    for (int i = 1; i < n; i++)
    {
        if (*(dist + i) < min)
        {
            min = *(dist + i);
        }
    }

    return min;
}

int main()
{
    int n, i;

    printf("Enter number of sensors: ");
    scanf("%d", &n);

    int distance[n];

    printf("Enter distance readings (in cm):\n");

    for (i = 0; i < n; i++)
    {
        printf("Sensor %d: ", i + 1);
        scanf("%d", &distance[i]);
    }

    int minDist = findNearest(distance, n);

    printf("\nNearest obstacle distance: %d cm\n", minDist);

    if (minDist < SAFE_DISTANCE)
    {
        printf("WARNING: Obstacle too close! Robot should stop or slow down.\n");
    }
    else
    {
        printf("Path is clear. Robot can move safely.\n");
    }

    return 0;
}