#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);
bool checkIfValid(const char numString[]);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool addNumbers(int c1, int n1, int d1, int c2, int n2, int d2, int& newCharacterisitc, int& newNumerator, int& newDenominator);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool multiplyNumbers(int c1, int n1, int d1, int c2, int n2, int d2, int& newCharacteristic, int& newNumerator, int& newDenominator);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divideNumbers(int c1, int n1, int d1, int c2, int n2, int d2, int& newCharacteristic, int& newNumerator, int& newDenominator);

int numDigits(int number);

void appendCharacteristic(char result[], int characteristic, int numOfDigits, int& charsUsed, bool isNegativeZero, int len);
void appendMantissa(char result[], int newNumerator, int newDenominator, int charsUsed, int len);

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
    
    int numTestCases = 3;
    int characs1[numTestCases] = {2, 1, -40};
    int numerators1[numTestCases] = {66, 1, 0};
    int denominators1[numTestCases] = {100, 10000, 10};

    int characs2[numTestCases] = {-5, 13, -3};
    int numerators2[numTestCases] = {1, 9999, 2};
    int denominators2[numTestCases] = {10, 10000, 10};

    int c1, n1, d1;
    int c2, n2, d2;
    int len;
    int lengths[numTestCases] = {10, 6, 8};
    for (int i = 0; i < numTestCases; i++)
    {
        cout << "Test " << i + 1 << endl;
        c1 = characs1[i];
        n1 = numerators1[i];
        d1 = denominators1[i];

        c2 = characs2[i];
        n2 = numerators2[i];
        d2 = denominators2[i];
        
        len = lengths[i];
        cout << "Number 1) Characteristic: " << c1 << " Numerator: " << n1 << " Denominator: " << d1 << endl;
        cout << "Number 2) Characteristic: " << c2 << " Numerator: " << n2 << " Denominator: " << d2 << endl << endl;

        if(add(c1, n1, d1, c2, n2, d2, answer, len))
        {
            cout<<"Add Answer: "<<answer<<endl;
        }
        else
        {
            cout<<"Error on add"<<endl;
        }
    
        if(subtract(c1, n1, d1, c2, n2, d2, answer, len))
        {
            cout<<"Subtract Answer: "<<answer<<endl;
        }
        else
        {
            cout<<"Error on add"<<endl;
        }
    
        if(multiply(c1, n1, d1, c2, n2, d2, answer, len))
        {
            cout<<"Multiply Answer: "<<answer<<endl;
        }
        else
        {
            cout<<"Error on mult"<<endl;
        }
    
        if(divide(c1, n1, d1, c2, n2, d2, answer, len))
        {
            cout<<"Divide Answer: "<<answer<<endl;
        }
        else
        {
            cout<<"Error on divide"<<endl;
        }

        cout << endl << endl;

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
    // if len is at most 10 (9 characters and null terminator), but at least 2 (for a digit and null terminator)
    if (len > 10 || len <= 1)
    {
        return false;
    }

    int addedCharacteristic = 0;
    int newNumerator = 0;
    int newDenominator = 0;

    bool isNegativeZero = addNumbers(c1, n1, d1, c2, n2, d2, addedCharacteristic, newNumerator, newDenominator); // get the added values
    int numOfDigits = numDigits(addedCharacteristic); 
    if (addedCharacteristic < 0 || isNegativeZero)
    {
        numOfDigits++;  // add a digit cout for negative zero
    }

    if (numOfDigits > len - 1)  // check to see if we can hold at least the characteristic
    {
        return false;  // we can't store the added chara cterisitic
    }
    else  // if we get here, we can store at least the characteristic
    {  
        int charsUsed = 0;

        appendCharacteristic(result, addedCharacteristic, numOfDigits, charsUsed, isNegativeZero, len);
       
        if (charsUsed >= len - 2 || newNumerator == 0) // we cant add anything else 
        {
            result[charsUsed] = '\0';
        } 
        else 
        {
            // add everything after decimal
            appendMantissa(result, newNumerator, newDenominator, charsUsed, len);
        }
    }
 
    return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to subtract the two numbers
    return add(c1, n1, d1, -c2, n2, d2, result, len);
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    if (len > 10 || len <= 1)
    {
        return false;
    }

    int multipliedCharacteristic = 0;
    int newNumerator = 0;
    int newDenominator = 0;

    bool isNegativeZero = multiplyNumbers(c1, n1, d1, c2, n2, d2, multipliedCharacteristic, newNumerator, newDenominator); // get the added values
    int numOfDigits = numDigits(multipliedCharacteristic); 

    if (multipliedCharacteristic < 0 || isNegativeZero)
    {
        numOfDigits++;
    }

    if (numOfDigits > len - 1)  // check to see if we can hold at least the characteristic
    {
        return false;  // we can't store the added chara cterisitic
    }
    else  // if we get here, we can store at least the characteristic
    {  
        int charsUsed = 0;

        appendCharacteristic(result, multipliedCharacteristic, numOfDigits, charsUsed, isNegativeZero, len);
       
        if (charsUsed >= len - 2 || newNumerator == 0) // we cant add anything else 
        {
            result[charsUsed] = '\0';
        } 
        else 
        {
            // add everything after decimal
            appendMantissa(result, newNumerator, newDenominator, charsUsed, len);
        }
    }
 
    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to divide the two numbers
    //hard coded return value to make the main() work
    if (len > 10 || len <= 1)
    {
        return false;
    }

    int newCharacteristic = 0;
    int newNumerator = 0;
    int newDenominator = 0;

    bool isNegativeZero = divideNumbers(c1, n1, d1, c2, n2, d2, newCharacteristic, newNumerator, newDenominator); // get the added values
    int numOfDigits = numDigits(newCharacteristic); 

    if (newCharacteristic < 0 || isNegativeZero)
    {
        numOfDigits++;
    }

    if (numOfDigits > len - 1)  // check to see if we can hold at least the characteristic
    {
        return false;  // we can't store the added chara cterisitic
    }
    else  // if we get here, we can store at least the characteristic
    {  
        int charsUsed = 0;

        appendCharacteristic(result, newCharacteristic, numOfDigits, charsUsed, isNegativeZero, len);
       
        if (charsUsed >= len - 2 || newNumerator == 0) // we cant add anything else 
        {
            result[charsUsed] = '\0';
        } 
        else 
        {
            // add everything after decimal
            appendMantissa(result, newNumerator, newDenominator, charsUsed, len);
        }
    }
 
    return true;
}

int numDigits(int number)
{
    number = abs(number);
    int comparissonValue = 10;
    int magnitude = 0;

    while (number >= comparissonValue)
    {
        comparissonValue*=10;
        magnitude++;
    }

    return magnitude + 1; // returns number of digits excluding negative signs
}

bool addNumbers(int c1, int n1, int d1, int c2, int n2, int d2, int& newCharacteristic, int& newNumerator, int& newDenominator)
{
    int maxDenom = max(d1, d2);
    int powerOfTen = 1;
    while (powerOfTen < maxDenom) {
        powerOfTen *= 10;
    }
    newDenominator = powerOfTen;  // to get a new common denominator of a power of 10.

    n1 *= (newDenominator / d1);
    n2 *= (newDenominator / d2);

    // Convert to improper fraction format
    int total1 = c1 * newDenominator + n1 * (c1 < 0 ? -1 : 1);
    int total2 = c2 * newDenominator + n2 * (c2 < 0 ? -1 : 1);

    int totalSum = total1 + total2; // add both improper fractions

    newCharacteristic = totalSum / newDenominator; // get nearest whole number
    newNumerator = abs(totalSum % newDenominator); // get a positive numerator

    return (newCharacteristic == 0 && totalSum < 0 && newNumerator > 0);
}

bool multiplyNumbers(int c1, int n1, int d1, int c2, int n2, int d2, int& newCharacteristic, int& newNumerator, int& newDenominator)
{
    // we will take a FOIL method of producing multiplication calculations
    // be careful of d1 being zero
    bool isNegativeZero = false;
    int absC1 = abs(c1);
    int absC2 = abs(c2);
    int wholeNumberTerm = absC1 * absC2;
    
    int term2Numerator = (n1 * absC2) % d1;
    int term2Charac = (n1 * absC2) / d1;

    int term3Numerator = (n2 * absC1) % d2;
    int term3Charac = (n2 * absC1) / d2;

    int term4Numerator = n1 * n2;
    int term4Denom = d1 * d2;

    int runningCharacteristic = 0;
    int runningNumerator = 0;
    int runningDenominator = 0;

    addNumbers(wholeNumberTerm, 0, 10, term2Charac, term2Numerator, d1, runningCharacteristic, runningNumerator, runningDenominator);

    addNumbers(runningCharacteristic, runningNumerator, runningDenominator, term3Charac, term3Numerator, d2, runningCharacteristic, runningNumerator, runningDenominator);

    addNumbers(runningCharacteristic, runningNumerator, runningDenominator, 0, term4Numerator, term4Denom, newCharacteristic, newNumerator, newDenominator);

    if ((c1 < 0 && c2 >= 0) || (c1 >= 0 && c2 < 0)) 
    {
        newCharacteristic = -newCharacteristic;
        if (newCharacteristic == 0) {
            isNegativeZero = true;
        }
    }

    return isNegativeZero;
}

bool divideNumbers(int c1, int n1, int d1, int c2, int n2, int d2, int& newCharacteristic, int& newNumerator, int& newDenominator)
{
    bool isNegativeZero = false;
    int absC1 = abs(c1);
    int absC2 = abs(c2);

    int num1 = absC1 * d1 + n1; 
    int num2 = absC2 * d2 + n2; 

    int resultNumerator = num1 * d2;
    int resultDenominator = d1 * num2;

    newCharacteristic = resultNumerator / resultDenominator;
    int remainder = resultNumerator % resultDenominator; // added abs

    newDenominator = 10;
    while (newDenominator < resultDenominator) 
    {
        newDenominator *= 10;
    }

    newNumerator = abs((remainder * newDenominator) / resultDenominator);

    newDenominator = 10;
    while (newDenominator < newNumerator) 
    {
        newDenominator *= 10;
    }

    if ((c1 < 0 && c2 >= 0) || (c1 >= 0 && c2 < 0)) 
    {
        newCharacteristic = -newCharacteristic;
        if (newCharacteristic == 0) {
            isNegativeZero = true;
        }
    }
    
    return isNegativeZero;
}

// maybe make append characteristic
void appendCharacteristic(char result[], int characteristic, int numOfDigits, int & charsUsed, bool isNegativeZero, int len)
{
    if (characteristic < 0 || isNegativeZero)
    {
        result[0] = '-';
        charsUsed++;
    }

    int stop = (characteristic < 0 || isNegativeZero ? 1 : 0);
    characteristic = abs(characteristic);
    for (int i = numOfDigits - 1; i >= stop; i--)
    {
        result[i] = '0' + (characteristic % 10);
        characteristic /= 10;
        charsUsed++;
    }

    result[charsUsed] = '\0';
}

void appendMantissa(char result[], int newNumerator, int newDenominator, int charsUsed, int len) 
{
    int digit = 0;
    result[charsUsed++] = '.';

    while (newDenominator != 1 && charsUsed < len - 1) 
    {
        newDenominator /= 10;
        digit = newNumerator / newDenominator;
        newNumerator -= digit * newDenominator;
        result[charsUsed++] = '0' + digit;
    }

    for (int i = charsUsed; i < len - 1; i++)
    {
        result[i] = '0';
    }
    result[len - 1] = '\0';
}
