#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_SIZE 4
#define BUFFER_SIZE 8

typedef struct {
    int seq_no;
    char data;
} Frame;

int send(Frame frame);
void receive(Frame *frame);
void send_ack(int seq_no);
void receive_ack(int *seq_no);

int main() {
    char buffer[BUFFER_SIZE];
    int num_frames, i;

    printf("Enter data to transmit: ");
    scanf("%s", buffer);

    num_frames = strlen(buffer);

    Frame send_buffer[num_frames];
    int send_base = 0;
    int next_seq_no = 0;

    while (send_base < num_frames) {
        // send frames
        while (next_seq_no < send_base + WINDOW_SIZE && next_seq_no < num_frames) {
            Frame frame = {next_seq_no, buffer[next_seq_no]};
            send_buffer[next_seq_no] = frame;
            if (send(frame)) {
                next_seq_no++;
            }
        }

        // receive acknowledgements
        int ack_seq_no;
        receive_ack(&ack_seq_no);
        if (ack_seq_no >= send_base && ack_seq_no < next_seq_no) {
            send_base = ack_seq_no + 1;
        }

        // timeout
        for (i = send_base; i < next_seq_no; i++) {
            Frame frame = send_buffer[i];
            if (send(frame)) {
                printf("Resending frame with sequence number %d\n", frame.seq_no);
            }
        }
    }

    return 0;
}

int send(Frame frame) {
    printf("Sending frame with sequence number %d\n", frame.seq_no);
    return rand() % 2;
}

void receive(Frame *frame) {
    printf("Receiving frame\n");
    frame->seq_no = rand() % 10;
    frame->data = rand() % 128;
}

void send_ack(int seq_no) {
    printf("Sending acknowledgement with sequence number %d\n", seq_no);
}

void receive_ack(int *seq_no) {
    printf("Receiving acknowledgement\n");
    *seq_no = rand() % 10;
}
