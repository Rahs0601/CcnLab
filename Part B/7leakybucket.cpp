#include <iostream>
#include <unistd.h>

using namespace std;

#define bucketSize 512

void BktInput(int a, int b) {
    if (a > bucketSize)
        cout << "\n \t \t bucket overflow";
    else {
         sleep(2);
        while (a > b) {
            cout << "\n \t \t " << b << " bytes output";
            a -= b;
             sleep(2);
        }
        if (a > 0)
            cout << "\n \t \t last " << a << " bytes sent \t";
        cout << "\n \t \t bucket output successful";
    }
}

int main() {
    int op, PktSize;
    cout << "enter output rate:";
    cin >> op;
    for (int i = 1; i <= 5; i++) {
        sleep(4);
        PktSize = rand() % 800;
        cout << "\n packet no " << i << ": Packet size= " << PktSize;
        BktInput(PktSize, op);
    }
    return 0;
}

// Output:
// /tmp/BLClkZu8oX.o
// enter output rate:100
// packet no 1: packet-size= 583
//  	 	 bucket overflow
//  packet no 2: packet-size= 486
//  	 	 100 bytes output
//  	 	 100 bytes output
//  	 	 100 bytes output
//  	 	 100 bytes output
//  	 	 last 86 bytes sent 	
//  	 	 bucket output successful
//  packet no 3: packet-size= 777
//  	 	 bucket overflow
//  packet no 4: packet-size= 115
//  	 	 100 bytes output
//  	 	 last 15 bytes sent 	
//  	 	 bucket output successful
//  packet no 5: packet-size= 593
//  	 	 bucket overflow

