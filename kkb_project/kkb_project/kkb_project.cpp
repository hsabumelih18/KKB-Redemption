
#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;
//check whether a number is between 0 and 7
int checkBetween(int number)
{
    while (number < 0 || number>7)
    {
        cout << "Input a number between 0 and 7" << endl;
        cin >> number;
    }
    return number;
}


//asks the Germans to enter the coordinates of the ship
vector<int> askForCombination() 
{
    vector<int> coords;
    int number;
    cout << "Enter 4 numbers between 0 and 7";
    cout << "(The coordinates of the ship)"<<endl;
    for (int i = 0; i < 4; i++)
    {
        cin >> number;
        number = checkBetween(number);
        coords.push_back(number);
    }
    return coords;
}


//generates a random number
int randomInt(int minimum, int maximum)
{
    return rand() % (maximum - minimum + 1) + minimum;
}

//generates 4 random numbers between 0 and 7
vector<int> generateCombination()
{
    srand(time(NULL)); //resets the seed so that everytime the numbers are different
    vector<int> coords;

    for (int i = 0; i < 4; i++)
    {
        coords.push_back(randomInt(0, 7));
    }

    return coords;
}


void centerstring(string s)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    COORD NewSBSize;
    NewSBSize.X = csbiInfo.dwSize.X;
    int l = s.size();
    int pos = (int)((NewSBSize.X - l) / 2);
    for (int i = 0; i < pos; i++)
        cout << " ";

    cout << s;
}





int main()
{
    
    //vector<int> arr = askForCombination();
    vector<int> arr = generateCombination();
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    
	string greeting = R"(
 
 
         +--------------------------+
         |   Welcome to bletchley   |
         |                          |
         |   +------------------+   |
         |   | Choose an Option |   |
         |   +------------------+   |                  
         |                          |
         +--------------------------+
         |                          |
         |   1.Play vs AI           |
         |                          |
         |   2.Play vs Player       |
         |                          |
         +--------------------------+  
 
 
 
)";
    string mitko = "asd";
    centerstring(mitko);
    cout << endl;
    int a;
    cin >> a;
    centerstring(mitko);
   
    
}
