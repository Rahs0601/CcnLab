#include <iostream>
#include <string>
using namespace std;

// Calculate the checksum of a message using the specified generating polynomial
string calculate_checksum(const string &message, const string &generating_polynomial)
{
    // Initialize the checksum to the message
    string checksum = message;

    // While the length of the checksum is greater than or equal to the length of the generating polynomial
    while (checksum.length() >= generating_polynomial.length())
    {
        // Calculate the remainder of the checksum divided by the generating polynomial using the XOR operation
        string remainder;
        for (size_t i = 0; i < generating_polynomial.length(); ++i)
        {
            remainder += (checksum[i] == generating_polynomial[i]) ? '0' : '1';
        }

        // Append the next bit of the message to the remainder
        remainder += message[checksum.length()];

        // Set the checksum to the remainder
        checksum = remainder;
    }

    // Return the checksum
    return checksum;
}

// Test the error detection capability of the CRC method
void test_error_detection(const string &message, const string &generating_polynomial)
{
    cout << "Message: " << message << endl;
    cout << "Generating polynomial: " << generating_polynomial << endl;

    // Calculate the checksum of the message
    string checksum = calculate_checksum(message, generating_polynomial);

    // Concatenate the message and checksum to form the codeword
    string codeword = message + checksum;
    cout << "Codeword: " << codeword << endl;

    // Test error detection
    cout << "Enter the position of the error (0-based index, or -1 to skip): ";
    int error_position;
    cin >> error_position;

    if (error_position >= 0 && error_position < static_cast<int>(codeword.length()))
    {
        // Toggle the bit at the specified position to introduce an error
        codeword[error_position] = (codeword[error_position] == '0') ? '1' : '0';
        cout << "Erroneous codeword: " << codeword << endl;
    }

    // Calculate the checksum of the received codeword
    string received_checksum = calculate_checksum(codeword, generating_polynomial);

    if (received_checksum == checksum)
    {
        cout << "No error detected" << endl;
    }
    else
    {
        cout << "Error detected" << endl;
    }
}

int main()
{
    test_error_detection("1010101010", "1101");
    return 0;
}

// Created by rahul on 24-12-2022.
//
