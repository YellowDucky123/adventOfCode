



#include <iostream> 
#include <stdlib.h> 
#include <unistd.h>

using namespace std;
  
int main() 
{ 
  
    cout << "GFG!\n"; 
    cout << "GeeksforGeeks!\n"; 
  
    // Called getch() to halt the program 
    // This allows us to visualize the effect produced by 
    // clrscr() Upon pressing a single key the program 
    // execution continues & system is called 
    sleep(1);
  
    // Calling system function and passing cls as argument 
    system("clear"); 
  
    cout << "The screen has been cleared!\n"; 
    return 0; 
}