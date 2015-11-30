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
   ofstream out2;
   out2.open("TestData.txt");
   //int count = 0;
   char input[100];
   out1 << "1" << endl;
   out1 << "50" << endl;
   out2 << "2" << endl;
   out2 << "100" << endl;
   bool flag = true;
   bool flag1 = false;
   int count1 = 0,count2 = 0;
   ofstream out;
   while(!in.eof()){
      in >> input;
      int i;
      if(flag == true && flag1 == true){
      flag = false;
      flag1 = false;
      count1++;
      for(i = 0;i < strlen(input);i++){
        //out << count + 1 << ". ";
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
      else {
        if (flag == false){
            flag = true;
        }
        else if(flag1 == false){
            flag1 = true;
        }
        count2++;
        for(i = 0;i < strlen(input);i++){
        //out << count + 1 << ". ";
        if(input[i] == ','){
            out2 << " ";
        }
        else if(input[i] == 'I'){
            break;
        }
        else {
            out2 << input[i];
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
        out2 << "0.0" << endl;
      }
      else if(!strcmp(temp,b)){
        out2 << "1.0" << endl;
      }
      else if(!strcmp(temp,c)){
        out2 << "2.0" << endl;
      }
      }
      //count++;
   }
   out1.close();
   out2.close();
   in.close();
   cout << count1 << " " << count2;
   //cout << "count = " << count << endl;
   return 0;
}
