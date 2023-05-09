#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int k, time, win = 2, i2 = 0, frame = 0, a[20], b[20], i, j, s, r, ack, c, d;
int send(int, int);
int receive();
int checsum(int *);
main()
{
    int i1 = 0, j1 = 0, c1;
    printf("Enter the frame size\n");
    scanf("%d", &frame);
    printf("Enter the window size\n");
    scanf("%d", &win);
    j1 = win;
    for (i = 0; i < frame; i++)
    {
        a[i] = rand();
    }
    k = 1;
    while (i1 < frame)
    {
        if ((frame - i1) < win)
            j1 = frame - i1;
        printf("\n\ntransmit the window no %d\n\n", k);
        c1 = send(i1, i1 + j1);
        ack = receive(i1, i1 + j1, c1);
        if (ack != 0)
        {
            printf("\n\n1.Selective window\n");
            printf("2.Go back N\n");
            scanf("%d", &ack);
            switch (ack)
            {
            case 1:
                printf("\n\n\t Selective window \t\nEnter the faulty frame no\n");
                scanf("%d", &i2);
                printf("\n\n Retransmit the frame %d \n", i2);
                send(i2, i2 + 1);
                break;
            case 2:
                printf("\n\n\t Go back n\t\n\n");
                printf("\nRetransmit the frames from %d to %d\n", i1, i1 + j1);
                send(i1, i1 + j1);
                break;
            }
        }
        i1 = i1 + win;
        k++;
    }
}
int send(c, d)
{
    int t1;
    for (i = c; i < d; i++)
    {
        b[i] = a[i];
        printf("frame %d is sent\n", i);
    }
    s = checsum(&a[c]);
    return (s);
}
int receive(c, d, c2)
int c2;
{
    r = checsum(&b[c]);
    if (c2 == r)
    {
        return (0);
    }
    else
        return (1);
}
int checsum(int *c)
{
    int sum = 0;
    for (i = 0; i < win; i++)
        sum = sum ^ (*c);
    return sum;
}
