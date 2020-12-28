
#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>


using namespace std;

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
