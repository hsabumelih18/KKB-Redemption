#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <Windows.h>
#include <conio.h>

using namespace std;
//check whether a number is between 0 and 7
int checkBetween(int number)
{
    while (number < 0 || number>7)
    {
        cout << "Input a number between 0 and 7!" << endl;
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

int generateCoord(bool* used)
{
    int num;
    while (1)
    {
        num = randomInt(0, 7);
        if (used[num] == false)
        {
            used[num] = true;
            return num;
        }
    }
}

//generates 4 random numbers between 0 and 7
vector<int> generateCombination(bool repetitions)
{
    srand(time(NULL)); //resets the seed so that everytime the numbers are different
    vector<int> coords;
    int num;
    bool used[7] = { 0 };
    for (int i = 0; i < 4; i++)
    {
        if (repetitions == false)
        {
            coords.push_back(generateCoord(used));
        }
        else
        {
            coords.push_back(randomInt(0, 7));
        }
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


void printStrings(string s)
{
    string str;
    int indexdel = 0;
    while (s.find(",") != string::npos)
    {
        indexdel = s.find(",");
        str = s.substr(0, indexdel);
        s = s.substr(indexdel + 1, s.size() - indexdel);
        centerstring(str);
        cout << endl;
    }
}

void resize()
{
    if (_kbhit())
    {
        char ch = _getch();
        switch (ch)
        {
        case 32: //int(' ')
            system("cls");
            break;
        }
    }
}

bool Menu()
{
    string greeting = "+--------------------------+,|   Welcome to bletchley   |,|                          |,|   +------------------+   |,|   | Choose an Option |   |,|   +------------------+   |,|                          |,+--------------------------+,|                          |,|   1.Play vs AI           |,|                          |,|   2.Play vs Player       |,|                          |,+--------------------------+,";
    printStrings(greeting);
    resize();
    int a;
    cin >> a;
    printStrings(greeting);
    return true;
}

vector<int> makeGuess(vector<int> combination)
{
    vector<int> guess;
    int i, number;
    cout << "Try to guess the coordinates of the battleship. ";
    cout << "Enter 4 numbers between 0 and 7" << endl;
    for (i = 0; i < 4; i++)
    {
        cin >> number;
        number = checkBetween(number);
        guess.push_back(number);
    }

    return guess;
}

void showCorrectGuess(int guessedCount, int guessedPositionCount)
{
    cout << "You guessed " << guessedCount << " numbers correct" << endl;
    cout << "You guessed " << guessedPositionCount;
    cout << " numbers and positions correct" << endl;
}

void checkWinner(int guessedCount)
{
    cout << "You won, poggers" << endl;
}

void checkGuess(vector<int> guess, vector<int> combination)
{
    int guessedPositionCount=0, guessedCount=0;
    for (size_t i = 0; i < combination.size(); i++)
    {
        if (guess[i] == combination[i]) guessedPositionCount++;

        for (size_t j = 0; j < combination.size(); j++)
        {
            if (guess[j] == combination[i])
            {
                guessedCount++;
                break;
            }
        }
    }
    showCorrectGuess(guessedCount, guessedPositionCount);

}

int main()
{
    
}
