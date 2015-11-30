#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdio>

#define LEARNING_RATE 0.2

using namespace std;

int main()
{
	freopen("TestData.txt","r",stdin);
	freopen("outputs.txt","w",stdout);
	ifstream w_i_h[4];
	w_i_h[0].open("weights_input_hidden_node1.txt");
	w_i_h[1].open("weights_input_hidden_node2.txt");
	w_i_h[2].open("weights_input_hidden_node3.txt");
	w_i_h[3].open("weights_input_hidden_node4.txt");
	double weights_input_hidden_node[4][5];
	for(int i = 0;i < 4;i++){
		w_i_h[i] >> weights_input_hidden_node[i][0] >> weights_input_hidden_node[i][1] >> weights_input_hidden_node[i][2] >> weights_input_hidden_node[i][3] >> weights_input_hidden_node[i][4];
		w_i_h[i].close();
	}
	ifstream w_h_o[2];
	w_h_o[0].open("weights_hidden_output1.txt");
	w_h_o[1].open("weights_hidden_output2.txt");
	double weights_hidden_output[2][5];
	for(int i = 0;i < 2;i++){
		w_h_o[i] >> weights_hidden_output[i][0] >> weights_hidden_output[i][1] >> weights_hidden_output[i][2] >> weights_hidden_output[i][3] >> weights_hidden_output[i][4];
		w_h_o[i].close();
	}
	double inputs[5];
	inputs[0] = 1;
	double hidden_outputs[5];
	hidden_outputs[0] = 1;
	int choice;
	//cout << "Enter 1 for training data , 2 for testing data " << endl;
	cin >> choice;
	double learning_rate = LEARNING_RATE;
	if(choice == 1){
		int n;
		cin >> n;
		for(int t = 0;t < n;t++){
		double actual_result,actual_result1,actual_result2,predicted_result1,predicted_result2;
		cin >> inputs[1];
		cin >> inputs[2];
		cin >> inputs[3];
		cin >> inputs[4];
		cin >> actual_result;
		if(actual_result == 0.0){
			actual_result1 = 0.0;
			actual_result2 = 0.0;
		}
		else if(actual_result == 1.0){
			actual_result1 = 0.0;
			actual_result2 = 1.0;
		}
		else if(actual_result == 2.0){
			actual_result1 = 1.0;
			actual_result2 = 0.0;
		}
		double v_input_hidden_node[4];
		for(int i = 0;i < 4;i++){
			v_input_hidden_node[i] = 0;
		}
		for(int i = 0;i < 5;i++){
			for(int j = 0;j < 4;j++){
				v_input_hidden_node[j] += (weights_input_hidden_node[j][i] * inputs[i]);
			}
		}
		for(int i = 1;i < 5;i++){
			hidden_outputs[i] = (1/(1 + exp(-v_input_hidden_node[i - 1])));
		}
		double v_output_node[2];
		for (int i = 0; i < 2; ++i)
		{
			v_output_node[i] = 0;
		}
		for(int i = 0;i < 5;i++){
			for(int j = 0;j < 2;j++){
				v_output_node[j] += (weights_hidden_output[j][i] * hidden_outputs[i]);
			}
		}
		predicted_result1 = (1/(1 + exp(-v_output_node[0])));
		predicted_result2 = (1/(1 + exp(-v_output_node[1])));
		double delta_output_node1 = predicted_result1 * (1 - predicted_result1) * (actual_result1 - predicted_result1);
		double delta_output_node2 = predicted_result2 * (1 - predicted_result2) * (actual_result2 - predicted_result2);
		for (int i = 0; i < 5; ++i)
		{
			weights_hidden_output[0][i] += (learning_rate * delta_output_node1 * hidden_outputs[i]);
			weights_hidden_output[1][i] += (learning_rate * delta_output_node2 * hidden_outputs[i]);
		}
		double delta_hidden_node[4];
		for (int i = 1; i < 5; ++i)
		{
		 	delta_hidden_node[i - 1] = hidden_outputs[i] * (1 - hidden_outputs[i]) * (delta_output_node1 * weights_hidden_output[0][i] + delta_output_node2 * weights_hidden_output[1][i]);
		}
		for(int j = 0;j < 4;j++){
			for (int i = 0; i < 5; ++i)
			{
				weights_input_hidden_node[j][i] += (learning_rate * delta_hidden_node[j] * inputs[i]);
			}
		}
		}
		ofstream w_i_ho[4];
		w_i_ho[0].open("weights_input_hidden_node1.txt");
		w_i_ho[1].open("weights_input_hidden_node2.txt");
		w_i_ho[2].open("weights_input_hidden_node3.txt");
		w_i_ho[3].open("weights_input_hidden_node4.txt");
		for(int i = 0;i < 4;i++){
			w_i_ho[i] << weights_input_hidden_node[i][0] << " " << weights_input_hidden_node[i][1] << " " << weights_input_hidden_node[i][2] << " " << weights_input_hidden_node[i][3] << " " << weights_input_hidden_node[i][4] << endl;
			w_i_ho[i].close();
		}
		ofstream w_h_oo[2];
		w_h_oo[0].open("weights_hidden_output1.txt");
		w_h_oo[1].open("weights_hidden_output2.txt");
		for(int i = 0;i < 2;i++){
			w_h_oo[i] << weights_hidden_output[i][0] << " " << weights_hidden_output[i][1] << " " << weights_hidden_output[i][2] << " " << weights_hidden_output[i][3] << " " << weights_hidden_output[i][4] << endl;
			w_h_oo[i].close();
		}
		//cout << "Predicted output is " << predicted_result << endl;
	}
	else {
		int n,count = 0;
		cin >> n;
		for(int t = 0;t < n;t++){
		double actual_result,actual_result1,actual_result2,predicted_result1,predicted_result2;
		cin >> inputs[1];
		cin >> inputs[2];
		cin >> inputs[3];
		cin >> inputs[4];
		cin >> actual_result;
		double v_input_hidden_node[4];
		for(int i = 0;i < 4;i++){
			v_input_hidden_node[i] = 0;
		}
		for(int i = 0;i < 5;i++){
			for(int j = 0;j < 4;j++){
				v_input_hidden_node[j] += (weights_input_hidden_node[j][i] * inputs[i]);
			}
		}
		for(int i = 1;i < 5;i++){
			hidden_outputs[i] = (1/(1 + exp(-v_input_hidden_node[i - 1])));
		}
		double v_output_node[2];
		for (int i = 0; i < 2; ++i)
		{
			v_output_node[i] = 0;
		}
		for(int i = 0;i < 5;i++){
			for(int j = 0;j < 2;j++){
				v_output_node[j] += (weights_hidden_output[j][i] * hidden_outputs[i]);
			}
		}
		predicted_result1 = (1/(1 + exp(-v_output_node[0])));
		predicted_result2 = (1/(1 + exp(-v_output_node[1])));
		char a[] = "Iris-setosa";
      	char b[] = "Iris-versicolor";
      	char c[] = "Iris-virginica";
      	double predicted_result = round((2 * predicted_result1) + predicted_result2);
      	if(predicted_result == actual_result){
            count++;
      	}
      	if(predicted_result == 0){
      		cout << a << endl;
      	}
      	else if(predicted_result == 1){
      		cout << b << endl;
      	}
      	else if(predicted_result == 2){
      		cout << c << endl;
      	}
      	//cout << predicted_result << endl;
      }
      cout << "count = " << count << endl;
	}
	return 0;
}
