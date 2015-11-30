#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

int main()
{
   ifstream in;
   in.open("Training-Data.txt");
   ofstream out1;
   out1.open("TrainingData.txt");
   char input[100];
   out1 << "1" << endl;
   out1 << "150" << endl;
   bool flag = true;
   bool flag1 = false;
   int count1 = 0;
   while(!in.eof()){
      in >> input;
      int i;
      count1++;
      for(i = 0;i < strlen(input);i++){
        if(input[i] == ','){
            out1 << " ";
        }
        else if(input[i] == 'I'){
            break;
        }
        else {
            out1 << input[i];
        }
      }
      char temp[100],length = 0;
      for(int j = i;j < strlen(input);j++){
        temp[length++] = input[j];
      }
      temp[length] = '\0';
      char a[] = "Iris-setosa";
      char b[] = "Iris-versicolor";
      char c[] = "Iris-virginica";
      if(!strcmp(temp,a)){
        out1 << "0.0" << endl;
      }
      else if(!strcmp(temp,b)){
        out1 << "1.0" << endl;
      }
      else if(!strcmp(temp,c)){
        out1 << "2.0" << endl;
      }
   }
   out1.close();
   //out2.close();
   in.close();
   cout << count1 << " " << endl;
   //cout << "count = " << count << endl;
   return 0;
}
