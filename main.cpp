
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

int numDigits(int number);
void addNumbers(int c1, int n1, int d1, int c2, int n2, int d2, int& newCharacterisitc, int& newNumerator, int& newDenominator);
void appendCharacteristic(char result[], int characteristic, int numOfDigits, int& charsUsed, int len);
void appendMantissa(char result[], int newNumerator, int newDenominator, int charsUsed, int len);

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    const char number[] = "123.456"; 
    int c, n, d;

    //if both conversions from c-string to integers can take place
    if(characteristic(number, c) && mantissa(number, n, d))
    {
        //do some math with c, n, and d
        cout<<"c: "<<c<<endl;
        cout<<"n: "<<n<<endl;
        cout<<"d: "<<d<<endl;
    }
    else //at least one of the conversions failed
    {
        //handle the error on input
        cout<<"Error on input"<<endl;
    }

    //room for 9 characters plus the null terminating character
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;

    //initialize the values
    c1 = 10; // change this back to 1
    n1 = 5;
    d1 = 10;

    c2 = -2;
    n2 = 834;
    d2 = 1000; 

    //if the c-string can hold at least the characteristic
    if(add(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on add"<<endl;
    }

    if(divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }

    return 0;
} 
//--
bool characteristic(const char numString[], int& c)
{
    //hard coded return value to make the main() work
    c = 123;
    return true;
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    //hard coded return value to make the main() work
    numerator = 456;
    denominator = 1000;
    return true;
}
//--
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

    addNumbers(c1, n1, d1, c2, n2, d2, addedCharacteristic, newNumerator, newDenominator); // get the added values
    int numOfDigits = numDigits(addedCharacteristic); 
    if (addedCharacteristic < 0)
    {
        numOfDigits++;
    }

    if (numOfDigits >= len)  // check to see if we can hold at least the characteristic
    {
        return false;  // we can't store the added chara cterisitic
    }
    else  // if we get here, we can store at least the characteristic
    {  
        int charsUsed = 0;

        appendCharacteristic(result, addedCharacteristic, numOfDigits, charsUsed, len);
       
        if (charsUsed >= len - 2) // we cant add anything else 
        {
            result[charsUsed] = '\0';
            return true;
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

    return magnitude + 1;
}

void addNumbers(int c1, int n1, int d1, int c2, int n2, int d2, int& newCharacteristic, int& newNumerator, int& newDenominator)
{
    newDenominator = max(d1, d2);

    if (c1 < 0)
    {
        n1 *= -1;
    }

    if (c2 < 0)
    {
        n2 *= -1;
    }

    newNumerator = n1 * (newDenominator / d1) + n2 * (newDenominator / d2);
    newCharacteristic = c1 + c2;

    if ((c1 < 0 && c2 > 0) || (c1 > 0 && c2 < 0)) {
        // If the whole numbers have opposite signs, we need to handle carryover carefully
        // First, handle the case when the fraction's numerator is negative
        if (newNumerator > 0 && c1 < 0) {
            newCharacteristic++;  // Subtract from the whole part
            newNumerator = newDenominator - newNumerator;  // Add the denominator to the numerator to fix negative fraction
        }
        else if (newNumerator < 0 && c2 < 0){
            newCharacteristic--;
            newNumerator = newDenominator + newNumerator;
        }
    } 
    else {
        // If the whole numbers are the same sign, add the whole number carryover directly from the fraction
        newCharacteristic += newNumerator / newDenominator;
        newNumerator %= newDenominator;  // Fraction remainder
        newNumerator = abs(newNumerator);
    }
}

// maybe make append characteristic
void appendCharacteristic(char result[], int characteristic, int numOfDigits, int & charsUsed, int len)
{
    if (characteristic < 0)
    {
        result[0] = '-';
        charsUsed++;
    }

    int stop = (characteristic < 0 ? 1 : 0);
    characteristic = abs(characteristic);
    
    for (int i = numOfDigits - 1; i >= stop; i--)
    {
        result[i] = '0' + (characteristic % 10);
        characteristic /= 10;
        charsUsed++;
    }
}

void appendMantissa(char result[], int newNumerator, int newDenominator, int charsUsed, int len) 
{
    int digit = 0;
    result[charsUsed++] = '.';

    cout << newNumerator << endl;
    cout << newDenominator << endl;
    while (newDenominator != 1) 
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
