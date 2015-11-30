#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstdlib>

using namespace std;

#define Length_Nodes 40
#define Width_Nodes 40
#define NUM_FEATURES 4

int main(){
    ifstream w_i_h[4];
	w_i_h[0].open("weights_1.txt");
	w_i_h[1].open("weights_2.txt");
	w_i_h[2].open("weights_3.txt");
	w_i_h[3].open("weights_4.txt");
	ofstream out_norm,out_norm2;
	out_norm.open("weights_norm.ppm");
	out_norm2.open("weights_norm_black&white.ppm");
	double weights[Length_Nodes][Width_Nodes][NUM_FEATURES];
	double sum[Length_Nodes][Width_Nodes],max = 0;
	for(int i = 0;i < Length_Nodes;i++){
		for (int j = 0; j < Width_Nodes; ++j)
		{
			sum[i][j] = 0;
			for (int k = 0; k < NUM_FEATURES; ++k)
			{
				 w_i_h[k] >> weights[i][j][k];
                 sum[i][j] += (weights[i][j][k] * weights[i][j][k]);
			}
            if(sum[i][j] > max){
                max = sum[i][j];
            }
		}
	}
	int check[Length_Nodes * Width_Nodes],k = 0;
	for(int i = 0;i < Length_Nodes;i++){
		for (int j = 0; j < Width_Nodes; ++j)
		{
             check[k++] = (int)(sum[i][j] * 255 / max);
		}
	}
	//sort(check,check + Length_Nodes * Width_Nodes);
	for (int i = 0; i < 4; ++i)
    {
        w_i_h[i].close();
    }
    out_norm << "P3\n";
    out_norm << "400 400\n";
    out_norm << "255\n";
    out_norm2 << "P3\n";
    out_norm2 << "400 400\n";
    out_norm2 << "255\n";
    for(int i = 0;i < 10 * Length_Nodes;i++){
		for (int j = 0; j < 10 * Width_Nodes; ++j)
		{
            out_norm2 << (int)(sum[i/10][j/10] * 255 / max) << " " << (int)(sum[i/10][j/10] * 255 / max) << " " << (int)(sum[i/10][j/10] * 255 / max) << endl;
            if((int)(sum[i/10][j/10] * 255 / max) <= 108){
                out_norm << "255 0 0" << endl;
            }
            else if((int)(sum[i/10][j/10] * 255 / max) <= 151){
                out_norm << "0 255 0" << endl;
            }
            else {
                out_norm << "0 0 255" << endl;
            }
		}
	}
	//cout << check[532] << " , " << check[1066] << " , " << check[1599] << endl;
    out_norm.close();
    out_norm2.close();
    return 0;
 }
