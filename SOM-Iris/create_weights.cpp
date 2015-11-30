#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;

#define Length_Nodes 40
#define Width_Nodes 40
#define NUM_FEATURES 4

int main()
{
    srand(time(NULL));
    ofstream w_i_ho[4];
    w_i_ho[0].open("weights_1.txt");
    w_i_ho[1].open("weights_2.txt");
    w_i_ho[2].open("weights_3.txt");
    w_i_ho[3].open("weights_4.txt");
    for(int i = 0;i < Length_Nodes;i++){
        for (int j = 0; j < Width_Nodes; ++j)
        {
            for (int k = 0; k < NUM_FEATURES; ++k)
            {
                w_i_ho[k] << (((double)rand())/RAND_MAX) << " ";
            }
        }
        for (int k = 0; k < NUM_FEATURES; ++k)
        {
            w_i_ho[k] << endl;
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        w_i_ho[i].close();
    }
    return 0;
}
