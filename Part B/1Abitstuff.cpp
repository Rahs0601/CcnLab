#include <iostream>
#include <cstring>

using namespace std;

int main() {
    int i, j, count = 0;
    char frame[100], stufframe[100] = "\0", dframe[100] = "\0", recframe[100] = "\0";
    cout << "\n ...sender...";
    cout << "\n enter input frame(0's and 1's only):";
    cin >> frame;
    strcpy(stufframe, "01111110");
    j = strlen(stufframe);
    for (i = 0; frame[i]; i++) {
        if (frame[i] == '1')
            count++;
        else
            count = 0;
        stufframe[j++] = frame[i];
        if (count == 5) {
            stufframe[j++] = '0';
            count = 0;
        }
    }
    strcat(stufframe, "01111110");
    cout << "\n after bit stuffing:" << stufframe;
    cout << "\n ...receiver..";
    strcpy(recframe, stufframe);
    j = 0;
    for (i = 0; i < strlen(recframe); i++) {
        if (recframe[i] == '0' && recframe[i + 1] == '1' && recframe[i + 2] == '1' && recframe[i + 3] == '1' &&
            recframe[i + 4] == '1' && recframe[i + 5] == '1' && recframe[i + 6] == '1' && recframe[i + 7] == '0')
            i = i + 8;
        dframe[j++] = recframe[i];

        if (recframe[i] == '1' && recframe[i + 1] == '1' && recframe[i + 2] == '1' && recframe[i + 3] == '1' &&
            recframe[i + 4] == '1') {
            i = i + 1;
            dframe[j++] = recframe[i++];
            dframe[j++] = recframe[i++];
            dframe[j++] = recframe[i++];
            dframe[j++] = recframe[i++];
        }
    }
    cout << "\n bits after destuffing:" << dframe << endl;
    return 0;
}

// output
// /tmp/BLClkZu8oX.o
// ...sender...
//  enter input frame(0's and 1's only):00011000110
//  after bit stuffing:011111100001100011001111110
//  ...receiver..
//  bits after destuffing:00011000110