#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);
bool checkIfValid(const char numString[]);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    const char number[] = "123.456";
    int c, n, d;

    //if both conversions from c-string to integers can take place
    if (characteristic(number, c) && mantissa(number, n, d))
    {
        //do some math with c, n, and d
        cout << "c: " << c << endl;
        cout << "n: " << n << endl;
        cout << "d: " << d << endl;
    }
    else //at least one of the conversions failed
    {
        //handle the error on input
        cout << "Error on input" << endl;
    }

    //room for 9 characters plus the null terminating character
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;

    //initialize the values
    c1 = 1;
    n1 = 1;
    d1 = 2;

    c2 = 2;
    n2 = 2;
    d2 = 3;

    //if the c-string can hold at least the characteristic
    if (add(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout << "Answer: " << answer << endl;
    }
    else
    {
        //display error message
        cout << "Error on add" << endl;
    }

    if (divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout << "Answer: " << answer << endl;
    }
    else
    {
        //display error message
        cout << "Error on divide" << endl;
    }

    return 0;
}
//--
bool characteristic(const char numString[], int& c)
{
    if (checkIfValid(numString) == false) {
        return false;
    }
    char goThrough;
    int i = 0;
    //this will store the chareristic for conversion.
    char topPart[10] = "";
    char stringCopy[10];
    strcpy_s(stringCopy, numString);
    if (strchr(stringCopy, '.') != nullptr) {
        goThrough = numString[i];
        while (goThrough != '.') {
            i++;
            goThrough = numString[i];
        }
        strncpy_s(topPart, numString, i);

        c = atoi(topPart);
        return true;
    }
    else {
        return false;
    }
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    //using strtok_s, which requires alot, maily a str, a delimiter, context, and local
    if (checkIfValid(numString) == false) {
        return false;
    }
    char bottomPart[10];
    char stringCopy[10];
    char seps[] = ".";
    char* token = NULL;
    char* nextToken = NULL;
    int passThrough = 0;
    denominator = 0;
    char* pch;
    strcpy_s(stringCopy, numString);
    pch = strchr(stringCopy, '.');
    if (strchr(stringCopy, '.') != nullptr) {
        token = strtok_s(stringCopy, seps, &nextToken);
        while (token != NULL) {
            if (passThrough == 1) {
                strcpy_s(bottomPart, token);
            }
            passThrough += 1;
            token = strtok_s(NULL, seps, &nextToken);

        }
        int i = 0;
        char goThrough = bottomPart[i];
        while (goThrough != '\0') {
            if (denominator == 0) {
                denominator += 1;
            }
            denominator *= 10;
            i++;
            goThrough = bottomPart[i];
        }
        numerator = atoi(bottomPart);
        //returning true as everything works
        return true;
    }
    else {
        return false;
    }
    
}
//--
bool checkIfValid(const char numString[]) {
    char goThrough;
    int i = 0;
    goThrough = numString[i];
    while (goThrough != '\0') {
        if (goThrough != '1' && goThrough != '2' && goThrough != '3' && goThrough != '4' && goThrough != '5' && goThrough != '6' && goThrough != '7' && goThrough != '8' && goThrough != '9' && goThrough != '0' && goThrough != '.' && goThrough != '-') {
            return false;
        }
        i++;
        goThrough = numString[i];
    }
    return true;
}
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to add the two numbers
    //hard coded return value to make the main() work
    result[0] = '4';
    result[1] = '.';
    result[2] = '1';
    result[3] = '6';
    result[4] = '6';
    result[5] = '6';
    result[6] = '6';
    result[7] = '6';
    result[8] = '6';
    result[9] = '\0';

    return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to subtract the two numbers
    return true;
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to multiply the two numbers
    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to divide the two numbers
    //hard coded return value to make the main() work
    result[0] = '0';
    result[1] = '.';
    result[2] = '5';
    result[3] = '6';
    result[4] = '2';
    result[5] = '5';
    result[6] = '\0';

    return true;
}