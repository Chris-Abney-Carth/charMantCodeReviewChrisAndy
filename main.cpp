
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

int power(int base, int exp);
int getMagnitude(int number);

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
    c1 = 1;
    n1 = 1;
    d1 = 2;

    c2 = 2;
    n2 = 2;
    d2 = 3; 

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
    //you will have to come up with an algorithm to add the two numbers
    //hard coded return value to make the main() work
    // result[0] = '4';
    // result[1] = '.';
    // result[2] = '1';
    // result[3] = '6';
    // result[4] = '6';
    // result[5] = '6';
    // result[6] = '6';
    // result[7] = '6';
    // result[8] = '6';
    // result[9] = '\0';
    if (len > 10 || len <= 0)
    {
        return false;
    }

    int added_characteristic = c1 + c2;

    if (abs(added_characteristic) >= power(10, len))  // change this to accout for mantissa with addition
    {
        return false;  // we can't store the added characterisitic
    }
    else  // if we get here, we can store at least the characteristic
    {   // update char array to hold characteristic
        // add into array
        // get a magnitude
        // w
        int magnitude = getMagnitude(added_characteristic);

        if (magnitude >= len - 1) // if our added_characterisitc contains more digits than len - 1
        {
            return false;
        }
        // for (int i = 0; i < magnitude; i++)
        // {

        // }
        // cout << getMagnitude(9) << endl;
        // cout << getMagnitude(99) << endl;
        // cout << getMagnitude(100) << endl;
        // cout << getMagnitude(101) << endl;
        // cout << getMagnitude(-100) << endl;
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

int power(int base, int exp)
{
    int retVal = base;

    if (power <= 0) 
    {
        retVal = 0;
    }
    else 
    {
        for (int i = 0; i < exp - 1; i++) 
        {
            retVal *= base;
        }
    }

    return retVal;
}

int getMagnitude(int number)
{
    number = abs(number);
    int comparissonValue = 10;
    int magnitude = 0;

    while (number >= comparissonValue)
    {
        comparissonValue*=10;
        magnitude++;
    }

    return magnitude;
}
