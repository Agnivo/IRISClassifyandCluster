#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
   ifstream in;
   in.open("Training--Data.txt");
   ofstream out1;
   out1.open("TrainingData.txt");
   out1 << "1" << endl;
   out1 << "150" << endl;
   double values[5];
   double norm;
   in >> norm;
   in >> norm;
   while(!in.eof()){
      norm = 0;
      for(int i = 0;i< 5;i++){
        in >> values[i];
        if(i < 4){
            norm += values[i] * values[i];
        }
     }
     norm = sqrt(norm);
     for(int i = 0;i< 5;i++){
        if(i < 4){
            out1 << values[i]/norm << " ";
        }
        else {
            out1 << values[i] << endl;
        }
     }
   }
   in.close();
   out1.close();
   return 0;
}
