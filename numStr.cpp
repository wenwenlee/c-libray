#include <iostream>
#include <string>
#include <sstream>


using namespace std;



   string numtostr(int input)
  {
      stringstream stream;
      string str;
      
      stream << input;
      stream >> str;
      return str;
      
  }
int  strtonum(int input)
  {
      stringstream stream;
      int num ;
      
      stream << input;
      stream >> num;
      return num;
      
  }

  

int main(int argc,char **argv)
  {
     
     
     for (int i = 0; i <3; i++)
      {
         string s;
         s = numtostr (i);
         cout << s ;
      } 
  }
