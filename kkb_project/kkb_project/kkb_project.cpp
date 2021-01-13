#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <Windows.h>
#include <conio.h>

using namespace std;

const string greeting = "+--------------------------+,|   Welcome to Bletchley   |,|                          |,|   +------------------+   |,|   | Choose an Option |   |,|   +------------------+   |,|                          |,+--------------------------+,|                          |,|   1.Play vs AI           |,|                          |,|   2.Play vs Player       |,|                          |,+--------------------------+,";
const string difString = "+-----------------------+,|                       |,| Select difficulty     |,|                       |,+-----------------------+,|                       |,| 1.Without repetitions |,|                       |,| 2.With repetitons     |,|                       |,+-----------------------+,";
const string resizeInf = "Press space to resize the window.";

//corrects the user if they enter something different from an integer
int readInt()
{
    int a;

    //loops until the user enters an integer
    while (!(cin >> a))    
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Incorrect value!" << endl;
    }

    return a;
}


//checks whether a number is between 0 and 7
int checkBetween(int number)
{
    if (number < 0 || number>7)
    {
        cout << "You must input numbers between 0 and 7!" << endl;
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
        //checks whether the number is between 0 and 7
        number = readInt(); 

        //if it is then it gets pushed in the vector for the combination
        coords.push_back(number);   
    }
     
    //the user is asked to enter a 4-integer combination
    for (int i = 0; i < 4; i++)    
    {
        number = checkBetween(coords[i]);
        if (number != -1)
        {
            //the number is assigned to the vector if it passes the check
            coords[i] = number;
        }
        else 
        {
            //otherwise it asks the user to enter another combination
            return askForCombination();
        }
    }
    //clears the screen
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
        //generates a number between 0 and 7
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
    vector<int> coords;
    int num;
    bool used[7] = { 0 };
    for (int i = 0; i < 4; i++)
    {
        if (repetitions == false)
        {
            //a coordinate that has not been used yet is added to the vector
            coords.push_back(generateCoord(used));
        }
        else
        {
            //if repetitions are allowed, then just a random number between 0 and 7 is added to the vector
            coords.push_back(randomInt(0, 7));
        }
    }
    return coords;
}

//centers the text based on the size of the window
void centerString(string s)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    //gets the window size and assigns it to the csbiInfo variable
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    COORD NewSBSize;
    //assigns the x size of the screen
    NewSBSize.X = csbiInfo.dwSize.X;
    int l = s.size();
    //calculates the spaces needed before the text in order to be centered
    int pos = (int)((NewSBSize.X - l) / 2);
    for (int i = 0; i < pos; i++)
        cout << " ";

    cout << s;
}


void printStrings(string rawStr)
{
    string str;
    int indexDel = 0;
    //searches for a comma in the string
    while (rawStr.find(",") != string::npos)
    {
        indexDel = rawStr.find(",");
        str = rawStr.substr(0, indexDel);
        rawStr = rawStr.substr(indexDel + 1, rawStr.size() - indexDel);
        centerString(str);
        cout << endl;
    }
}

void resize()
{
    //infinity loop breaks only if spacebar is pressed
    while(1)
    {
        //checks if there is any input from the user
        if (_kbhit())
        {
            //assigns the value of the input to the ch
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

//returns 4 number combination vector
vector<int> makeGuess()
{
    vector<int> guess;
    int number;
    cout << "Try to guess the coordinates of the battleship. ";
    cout << "Enter 4 numbers between 0 and 7" << endl << endl;
    
    //asks the user for a combination
    for (int i = 0; i < 4; i++)
    {
        number = readInt();
        guess.push_back(number);
    }
    for (int i = 0; i < 4; i++) 
    {
        //checks whether the number is valid
        number = checkBetween(guess[i]);
        if (number != -1)
        {
            //if it is it assigns it to the vector
            guess[i] = number;
        }
        else 
        {
            /*if not calls the function again to enter new combination
            until the combination is accepted by the conditions*/
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

//checks how many of the coordinates of the guess match those of the ship
bool checkGuess(vector<int> guess, vector<int> combination)
{
    int guessedPositionCount=0, guessedCount=0;
    //counts the guessed numbers and positions
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
    //checks if the player has won
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
    //checks if repetions are allowed
    if (repetitions == 1) 
    {
        reps = false;
    }
    else
    {

        reps = true;
    }
    //checks whether the user is playing against AI or a player
    if (option == 2) 
    {
         combination = askForCombination();
    }
    else 
    {
         combination = generateCombination(reps);
    }

    //gives the player 13 tries to win
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
    //user validation input
    if (option != 1 && option != 2)
    {
        while(option != 1 && option != 2)
        {
            cout << "Choose one from the given options!" << endl;
            option = readInt();
        }
    }
    system("CLS");
    //user validation input
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
    //callss the main loop
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
    srand(time(NULL)); //resets the seed so that everytime the numbers are different
    while(Menu());
}
