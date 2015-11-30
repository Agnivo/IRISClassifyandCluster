#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;

#define Learning_Rate 0.1
#define NUM_FEATURES 4
#define Length_Nodes 40
#define Width_Nodes 40
#define Lambda 2000
#define Radius_0 20
#define Time_Constant (Lambda/log(Radius_0))

double calc_distance_weights(vector<double> node1_weights,vector<double> node2_weights){
	double temp = 0;
	for (int i = 0; i < NUM_FEATURES; ++i)
	{
		temp = temp + ((node1_weights[i] - node2_weights[i]) * (node1_weights[i] - node2_weights[i]));
	}
	return sqrt(temp);
}

double calc_distance(int x1,int y1,int x2,int y2){
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main()
{
	freopen("TrainingData.txt","r",stdin);
	//freopen("output_logs.txt","w",stdout);
	vector<double> weights[Length_Nodes][Width_Nodes];
	ifstream w_i_h[4];
	w_i_h[0].open("weights_1.txt");
	w_i_h[1].open("weights_2.txt");
	w_i_h[2].open("weights_3.txt");
	w_i_h[3].open("weights_4.txt");
	double temp;
	for(int i = 0;i < Length_Nodes;i++){
		for (int j = 0; j < Width_Nodes; ++j)
		{
			for (int k = 0; k < NUM_FEATURES; ++k)
			{
				 w_i_h[k] >> temp;
				 weights[i][j].push_back(temp);
				 //cout << temp << endl;
			}
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		w_i_h[i].close();
	}
	//cout << "OK \n";
	int choice,n;
	cin >> choice;
	double actual_answer;
	if(choice == 1){
		cin >> n;
        vector<double> inputs[n];
        for(int l = 0;l < Lambda;l++){
          cout << l << " th Started " << endl;
		  for(int t = 0;t < n;t++){
			if(l == 0){
                for (int i = 0; i < NUM_FEATURES; ++i)
                {
                    cin >> temp;
                    inputs[t].push_back(temp);
                }
                cin >> actual_answer;
			}
			double min = 10000000,min_locx = 0,min_locy = 0;
	    		//cout << "Input data : " << t << " Time Step : " << l << endl;
	    		for(int i = 0;i < Length_Nodes;i++){
					for (int j = 0; j < Width_Nodes; ++j)
					{
	    				temp = calc_distance_weights(weights[i][j],inputs[t]);
	    				if(temp < min){
	    					min = temp;
	    					min_locx = i;
	    					min_locy = j;
	    				}
	    			}
	    		}
	    		//cout << "BMU : " << min_locx << " , " << min_locy << endl << endl;
	    		double L_t,theta_t;
	    		double Radius = Radius_0 * exp(-((double)l)/Time_Constant);
	    		for(int i = 0;i < Length_Nodes;i++){
					for (int j = 0; j < Width_Nodes; ++j)
					{
						double dist = calc_distance(i,j,min_locx,min_locy);
						if(dist <= Radius){
							L_t = Learning_Rate * exp(-l/Lambda);
							theta_t = exp(-(dist * dist)/(2 * Radius * Radius));
							//cout <<"Weights of " << i << " , " << j << " changed by a factor of " << L_t * theta_t << endl;
							for(int k = 0;k < NUM_FEATURES;k++){
								weights[i][j][k] += (L_t * theta_t * (inputs[t][k] - weights[i][j][k]));
							}
						}
					}
				}
          }
		}
		//cout << "OK again \n";
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
					w_i_ho[k] << weights[i][j][k] << " ";
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
	}
	else {

	}
	return 0;
}
