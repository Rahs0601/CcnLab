#include <iostream>
#include <string.h>

using namespace std;


void xor1();

void crc();

char msg[28], cs[28], g[] = "1000100000100001";
int msglen, i, j;

int main() {
    int genlen, err;
    cout << "\n message to be send is :";
    cin >> msg;
    cout << "\n-----------------";
    cout << "\n Genterating polynomial:" << g;
    msglen = strlen(msg);
    genlen = strlen(g);
    for (i = msglen; i < msglen + genlen - 1; i++)
        msg[i] = '0';
    cout << "\n------------------";
    cout << "\n After appending zero's to message :" << msg;
    cout << "\n-------------------";
    crc();
    cout << "\n Checksum is: " << cs;
    for (i = msglen; i < msglen + genlen - 1; i++)
        msg[i] = cs[i - msglen];
    cout << "\n-------------------";
    cout << "\n Final codeword (message+checksum) to be transmitted is:" << msg;
    cout << "\n-------------------";
    cout << "\n \n Test error detection: NO(0) Yes(1)?:";
    cin >> err;
    if (err == 1) {
        do {
            cout << "\n Enter the position where error is to be inserted :";
            cin >> err;
        } while (err == 1 || err > msglen + genlen - 1);
        msg[err - 1] = (msg[err - 1] == '0') ? '1' : '0';
        cout << "\n \n Erroneous data transmitted:" << msg << endl;
        cout << "\n------------------";
    }
    crc();
    cout << "\n Remainder :" << cs;
    for (i = 0; (i < genlen - 1) && (cs[i] != '1'); i++);
    if (i < genlen - 1)
        cout << "\n\n Error detected \n\n";
    else
        cout << "\n\n NO error detected\n\n";
    cout << "\n--------------------\n";
    return 0;
}

void xor1() {
    for (j = 1; j < strlen(g); j++)
        cs[j] = ((cs[j] == g[j]) ? '0' : '1');
}

void crc() {
    for (i = 0; i < strlen(g); i++)
        cs[i] = msg[i];
    do {
        if (cs[0] == '1')
            xor1();
        for (j = 0; j < strlen(g) - 1; j++)
            cs[j] = cs[j + 1];
        cs[j] = msg[i++];
    } while (i <= msglen + strlen(g) - 1);
}

// Output
// /tmp/BLClkZu8oX.o
// message to be send is :1010101010
// -----------------
//  Genterating polynomial:10001000000100001
// ------------------
//  After appending zero's to message :10101010100000000000000000
// -------------------
//  Checksum is: 1000110000011111
// -------------------
//  Final codeword (message+checksum) to be transimitted is:10101010101000110000011111
// -------------------
//  Test error detection: NO(0) Yes(1)?:1
//  Enter the position where error is to be inserted :2
//  Erroneous data transmitted:11101010101000110000011111

// ------------------
//  Remainder :0000000000000000

//  NO error dtected
// --------------------
