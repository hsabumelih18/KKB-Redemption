#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <Windows.h>
#include <conio.h>

using namespace std;

const string greeting = "+--------------------------+,|   Welcome to bletchley   |,|                          |,|   +------------------+   |,|   | Choose an Option |   |,|   +------------------+   |,|                          |,+--------------------------+,|                          |,|   1.Play vs AI           |,|                          |,|   2.Play vs Player       |,|                          |,+--------------------------+,";
const string difString = "+-----------------------+,|                       |,| Select difficulty     |,|                       |,+-----------------------+,|                       |,| 1.Without repetitions |,|                       |,| 2.With repetitons     |,|                       |,+-----------------------+,";
const string resizeInf = "Press space to resize the window.";

int readInt()
{
    int a;

    while (!(cin >> a))
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Incorrect value!" << endl;
    }

    return a;
}
//check whether a number is between 0 and 7
int checkBetween(int number)
{
    if (number < 0 || number>7)
    {
        cout << "Input a numbers between 0 and 7!" << endl;
        return -1;
    }
    return number;
}


//asks the Germans to enter the coordinates of the ship
vector<int> askForCombination() 
{
    vector<int> coords;
    int number;
    cout << "Enter 4 numbers between 0 and 7";
    cout << "(The coordinates of the ship)"<<endl << endl;
    for (int i = 0; i < 4; i++)
    {
        number = readInt();
        coords.push_back(number);
    }
    for (int i = 0; i < 4; i++)
    {
        number = checkBetween(coords[i]);
        if (number != -1)
        {
            coords[i] = number;
        }
        else {
            return askForCombination();
        }
    }
    system("CLS");
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


void centerString(string s)
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
        centerString(str);
        cout << endl;
    }
}

void resize()
{
    while(1)
    {
        if (_kbhit())
        {
            char ch = _getch();
            switch (ch)
            {
            case 32: //int(' ')
                system("cls");
                return;
                break;
            }
        }
    }
}

vector<int> makeGuess()
{
    vector<int> guess;
    int number;
    cout << "Try to guess the coordinates of the battleship. ";
    cout << "Enter 4 numbers between 0 and 7" << endl << endl;
    
    for (int i = 0; i < 4; i++)
    {
        number = readInt();
        guess.push_back(number);
    }
    for (int i = 0; i < 4; i++) 
    {
        number = checkBetween(guess[i]);
        if (number != -1)
        {
            guess[i] = number;
        }
        else {
            return makeGuess();
        }
    }

    return guess;
}

void showCorrectGuess(int guessedCount, int guessedPositionCount)
{
    cout << "You guessed " << guessedCount << " numbers correct" << endl;
    cout << "You guessed " << guessedPositionCount;
    cout << " numbers and positions correct" << endl << endl;
}

bool checkGuess(vector<int> guess, vector<int> combination)
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
    if (guessedPositionCount == 4)
    {
        return true;
    }
    return false;
    

}
    
bool mainLoop(int option, int repetitions)
{
    vector<int> combination;
    bool reps;
    if (repetitions == 1) 
    {
        reps = false;
    }
    if (repetitions == 2)
    {
        reps = true;
    }
    if (option == 2) {
         combination = askForCombination();
    }
    else {
         combination = generateCombination(reps);
    }
    for (int i = 0; i < 13; i++)
    {
        vector<int> guess;
        guess = makeGuess();
        if (checkGuess(guess, combination))
        {
            return true;
        }     
    }
    return false;
}

bool Menu()
{
    int option, dif=0;
    cout << resizeInf;
    resize();
    cout << endl << endl;    printStrings(greeting);
    option = readInt();
    if (option != 1 && option != 2)
    {
        while(option != 1 && option != 2)
        {
            cout << "Choose one from the given options!" << endl;
            option = readInt();
        }
    }
    system("CLS");
    if (option == 1)
    {
        printStrings(difString);
        dif = readInt();
        if (dif != 1 && dif != 2)
        {
            while (dif != 1 && dif != 2)
            {
                cout << "Choose one from the given options!" << endl;
                dif = readInt();
            }
        }
        system("CLS");
    }
        if (mainLoop(option, dif))
        {
            cout << "You won, poggers!" << endl;
        }
        else
        {
            cout << "You lost, not poggers!" << endl;
        }
    
    return true;
}

int main()
{
    while(Menu());
}
