#include <iostream>
#include <unistd.h>

using namespace std;
#define RTT 5

int main() {
    int window_size, i, f, frames[100];

    cout << "Enter window size: ";
    cin >> window_size;

    cout << "\nEnter number of frames to transmit: ";
    cin >> f;

    cout << "\nEnter " << f << " frames: ";
    for (i = 1; i <= f; i++)
        cin >> frames[i];

    cout << "\nAfter sending " << window_size << " frames at each stage, sender waits for ACK" << endl;
    cout << "Sending frames in the following order:" << endl;

    for (i = 1; i <= f; i++)
        if (i % window_size != 0)
            cout << "\nSending frame no " << frames[i] << endl;
        else {
            cout << "\nSending frame no " << frames[i] << endl;
            cout << "\nSENDER: waiting for ACK for " << i << " frames" << endl << endl;
            sleep(RTT / 2);
            cout<< "Receiver: "<<i<<" frames received ACK sent"<<endl;
            sleep(RTT / 2);
            cout << "Sender: ACK received for frame " << i << ", sending next frame" << endl;
        }


    if (f % window_size != 0) {
        cout << "\nSENDER: waiting for ACK..." << endl;
        sleep(RTT / 2);
        cout << "\nReceiver received, ACK sent..." << endl;
        cout << "--------------------------------" << endl;
        sleep(RTT / 2);
        cout << "\nSENDER: ACK received" << endl;
    }

    return 0;
}


// output
// /tmp/BLClkZu8oX.o
// enter window size:4
// enter no of frames to transmit :7
// enter 7 frames: 2 3 5 6 7 8 2
// after sending 4 frames at each stage  sender waits for ACK
//  sending frames in the following 

//  sending  frame no 2 
//  sending  frame no 3 
//  sending  frame no 5 
//  sending  frame no 6 
//  SENDER: waiting for ack for 4 frames 

// sender: ack received for the frame 4 sending next frame

//  sending  frame no 7 
//  sending  frame no 8 
//  SENDER: waiting for ACK....
// receiver recvd, ACK sent....
// --------------------------------
//  SENDER: ACK recvd..
