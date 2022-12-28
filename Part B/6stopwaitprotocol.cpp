#include <iostream>
#include <unistd.h>

using namespace std;

#define RTT 4
#define TIMEOUT 4
#define TOT_FRAMES 7
enum {
    NO,
    YES
} ACK;

int main() {
    int wait_time;
    ACK = YES;
    for (int i = 1; i <= TOT_FRAMES;) {
        if (ACK == YES && !i)
            cout << "Sender: ACK for frame " << i - 1 << " received" << endl;


        cout << "Sender: Frame " << i << " sent" << endl << " Waiting for ACK..." << endl;
        ACK = NO;

        wait_time = rand() % 4 + 1;
        if (wait_time == TIMEOUT) {
            cout << "Sender: Timeout" << endl << "ACK not received for frame " << i << endl;
            cout << "Resending frame " << i << "...." << endl;
        } else {
//            sleep(RTT / 2);
            cout << "Receiver: Frame " << i << " received, ACK sent" << endl;
            cout << "-----------------------------------------" << endl;
            ACK = YES;
//            sleep(RTT / 2);
            i++;
        }
    }

    return 0;
}

// Output
// tmp/BLClkZu8oX.o
// sender: frame 1 sent
//  waiting for ACK...
// RECEIVER : frame 1 RECEIVED,ACK sent
// -----------------------------------------
//  sender: ACK for frame 1 received

//  sender: frame 2 sent
//  waiting for ACK...
// RECEIVER : frame 2 RECEIVED,ACK sent
// -----------------------------------------
//  sender: ACK for frame 2 received

//  sender: frame 3 sent
//  waiting for ACK...
// RECEIVER : frame 3 RECEIVED,ACK sent
// -----------------------------------------
//  sender: ACK for frame 3 received

//  sender: frame 4 sent
//  waiting for ACK...
// RECEIVER : frame 4 RECEIVED,ACK sent
// -----------------------------------------
//  sender: ACK for frame 4 received

//  sender: frame 5 sent
//  waiting for ACK...
// RECEIVER : frame 5 RECEIVED,ACK sent
// -----------------------------------------
//  sender: ACK for frame 5 received

//  sender: frame 6 sent
//  waiting for ACK...
// RECEIVER : frame 6 RECEIVED,ACK sent
// -----------------------------------------