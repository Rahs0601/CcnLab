#include <iostream>
using namespace std;
#include <string.h>
int main()
{
    int i = 0;
    int j = 0;
    char frame[20], stuffframe[50] = "\0";
    char dframe[20] = "\0", recframe[50] = "/0";
    cout << "........Sender......\n";
    cout << "enter frame:";
    cin >> frame;
    strcpy(stuffframe, "dlestx");
    j = strlen("dlestx");
    for (i = 0; i < strlen(frame); i++)
    {
        if (frame[i] == 'd' && frame[i + 1] == 'l' && frame[i + 2] == 'e')
        {
            stuffframe[j++] = 'd';
            stuffframe[j++] = 'l';
            stuffframe[j++] = 'e';
            stuffframe[j++] = frame[i++];
            stuffframe[j++] = frame[i++];
            stuffframe[j++] = frame[i];
        }
        else
            stuffframe[j++] = frame[i];
    }
    strcat(stuffframe, "dleetx");
    cout << "\n Frame after stuffing:" << stuffframe;
    cout << "........Receiver......";
    j = 0;
    strcpy(recframe, stuffframe);
    for (i = 0; i < strlen(recframe); i++)
    {
        if (recframe[i] == 'd' && recframe[i + 1] == 'l' && recframe[i + 2] == 'e' && recframe[i + 3] == 'e' && recframe[i + 4] == 't' && recframe[i + 5] == 'x')

            i = i + 6;

        if (recframe[i] == 'd' && recframe[i + 1] == 'l' && recframe[i + 2] == 'e' && recframe[i + 3] == 's' && recframe[i + 4] == 't' && recframe[i + 5] == 'x')

            i = i + 6;

        if (recframe[i] == 'd' && recframe[i + 1] == 'l' && recframe[i + 2] == 'e')

            i = i + 3;

        dframe[j++] = recframe[i];
    }
    dframe[j] = '\0';
    cout << "\n Frame after destuffing:" << dframe << endl;
    return 0;
}
// output
// /tmp/BLClkZu8oX.o
// ........Sender......
// enter frame:dledledle
// Frame after stuffing:dlestxdledledledledledledleetx
// ........Receiver......
//  Frame after destuffing:dledledle

