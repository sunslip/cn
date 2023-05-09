#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_FRAMES 50
#define FRAME_SIZE 10
#define TIMEOUT_SEC 2

typedef struct frame {
    int seq_num;
    char data[FRAME_SIZE];
} Frame;

int main() {
    // Set up random seed
    srand(time(NULL));

    // Initialize sequence number and ACK number
    int seq_num = 0;
    int ack_num = 0;

    // Loop to send NUM_FRAMES frames
    for (int i = 0; i < NUM_FRAMES; i++) {
        // Create new frame with current sequence number
        Frame curr_frame;
        curr_frame.seq_num = seq_num;
        for (int j = 0; j < FRAME_SIZE; j++) {
            curr_frame.data[j] = 'A' + rand() % 26;
        }

        // Print information about the frame being sent
        printf("Sending frame with seq_num=%d\n", curr_frame.seq_num);

        // Simulate random delay before sending frame
        usleep((rand() % 2000 + 1000) * 1000);

        // Simulate possibility of frame being lost or damaged
        if (rand() % 10 < 8) {
            // Frame was successfully received by receiver
            // Simulate random delay before sending ACK/NACK
            usleep((rand() % 2000 + 1000) * 1000);

            // Simulate possibility of ACK/NACK being lost or damaged
            if (rand() % 10 < 8) {
                // ACK/NACK was successfully received by sender
                // Check if received ACK matches current sequence number
                if (ack_num == curr_frame.seq_num) {
                    // ACK matches current sequence number, so increment both sequence number and ACK number
                    seq_num++;
                    ack_num++;
                    // Print information about the received ACK
                    printf("Received ACK for frame with ack_num=%d\n", ack_num - 1);
                } else {
                    // ACK does not match current sequence number, so ignore it and do not increment sequence number or ACK number
                    // Print information about the received ACK
                    printf("Received ACK for frame with ack_num=%d, but expected ack_num=%d\n", ack_num - 1, curr_frame.seq_num);
                }
            } else {
                // ACK/NACK was lost or damaged, so simulate a timeout and retransmit the frame
                // Print information about the timeout
                printf("Timeout for frame with seq_num=%d\n", curr_frame.seq_num);
                // Decrement loop variable to repeat this iteration
                i--;
            }
        } else {
            // Frame was lost or damaged, so simulate a timeout and retransmit the frame
            // Print information about the timeout
            printf("Timeout for frame with seq_num=%d\n", curr_frame.seq_num);
            // Decrement loop variable to repeat this iteration
            i--;
        }

        // Simulate random delay before sending next frame
        usleep((rand() % 2000 + 1000) * 1000);
    }

    return 0;
}
