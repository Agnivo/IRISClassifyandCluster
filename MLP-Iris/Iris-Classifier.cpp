#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdio>

#define LEARNING_RATE 0.3

using namespace std;

int main()
{
	freopen("inputs.txt","r",stdin);
	freopen("outputs.txt","w",stdout);
	ifstream w_i_h1;
	w_i_h1.open("weights_input_hidden_node1.txt");
	double weights_input_hidden_node1[5];
	w_i_h1 >> weights_input_hidden_node1[0] >> weights_input_hidden_node1[1] >> weights_input_hidden_node1[2] >> weights_input_hidden_node1[3] >> weights_input_hidden_node1[4];
	w_i_h1.close();
	ifstream w_i_h2;
	w_i_h2.open("weights_input_hidden_node2.txt");
	double weights_input_hidden_node2[5];
	w_i_h2 >> weights_input_hidden_node2[0] >> weights_input_hidden_node2[1] >> weights_input_hidden_node2[2] >> weights_input_hidden_node2[3] >> weights_input_hidden_node2[4];
	w_i_h2.close();
	ifstream w_i_h3;
	w_i_h3.open("weights_input_hidden_node3.txt");
	double weights_input_hidden_node3[5];
	w_i_h3 >> weights_input_hidden_node3[0] >> weights_input_hidden_node3[1] >> weights_input_hidden_node3[2] >> weights_input_hidden_node3[3] >> weights_input_hidden_node3[4];
	w_i_h3.close();
	ifstream w_i_h4;
	w_i_h4.open("weights_input_hidden_node4.txt");
	double weights_input_hidden_node4[5];
	w_i_h4 >> weights_input_hidden_node4[0] >> weights_input_hidden_node4[1] >> weights_input_hidden_node4[2] >> weights_input_hidden_node4[3] >> weights_input_hidden_node4[4];
	w_i_h4.close();
	ifstream w_h_o1;
	w_h_o1.open("weights_hidden_output1.txt");
	double weights_hidden_output1[5];
	w_h_o1 >> weights_hidden_output1[0] >> weights_hidden_output1[1] >> weights_hidden_output1[2] >> weights_hidden_output1[3] >> weights_hidden_output1[4];
	w_h_o1.close();
	ifstream w_h_o2;
	w_h_o2.open("weights_hidden_output2.txt");
	double weights_hidden_output2[5];
	w_h_o2 >> weights_hidden_output2[0] >> weights_hidden_output2[1] >> weights_hidden_output2[2] >> weights_hidden_output2[3] >> weights_hidden_output2[4];
	w_h_o2.close();
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
		double v_input_hidden_node1 = 0,v_input_hidden_node2 = 0,v_input_hidden_node3 = 0,v_input_hidden_node4 = 0;
		for(int i = 0;i < 5;i++){
			v_input_hidden_node1 += (weights_input_hidden_node1[i] * inputs[i]);
			v_input_hidden_node2 += (weights_input_hidden_node2[i] * inputs[i]);
			v_input_hidden_node3 += (weights_input_hidden_node3[i] * inputs[i]);
			v_input_hidden_node4 += (weights_input_hidden_node4[i] * inputs[i]);
		}
		hidden_outputs[1] = (1/(1 + exp(-v_input_hidden_node1)));
		hidden_outputs[2] = (1/(1 + exp(-v_input_hidden_node2)));
		hidden_outputs[3] = (1/(1 + exp(-v_input_hidden_node3)));
		hidden_outputs[4] = (1/(1 + exp(-v_input_hidden_node4)));
		double v_output_node1 = 0,v_output_node2 = 0;
		for(int i = 0;i < 5;i++){
			v_output_node1 += (weights_hidden_output1[i] * hidden_outputs[i]);
			v_output_node2 += (weights_hidden_output2[i] * hidden_outputs[i]);
		}
		predicted_result1 = (1/(1 + exp(-v_output_node1)));
		predicted_result2 = (1/(1 + exp(-v_output_node2)));
		double delta_output_node1 = predicted_result1 * (1 - predicted_result1) * (actual_result1 - predicted_result1);
		double delta_output_node2 = predicted_result2 * (1 - predicted_result2) * (actual_result2 - predicted_result2);
		for (int i = 0; i < 5; ++i)
		{
			weights_hidden_output1[i] += (learning_rate * delta_output_node1 * hidden_outputs[i]);
			weights_hidden_output2[i] += (learning_rate * delta_output_node2 * hidden_outputs[i]);
		}
		double delta_hidden_node[4];
		for (int i = 1; i < 5; ++i)
		{
		 	delta_hidden_node[i - 1] = hidden_outputs[i] * (1 - hidden_outputs[i]) * (delta_output_node1 * weights_hidden_output1[i] + delta_output_node2 * weights_hidden_output2[i]);
		}
		for (int i = 0; i < 5; ++i)
		{
			weights_input_hidden_node1[i] += (learning_rate * delta_hidden_node[0] * inputs[i]);
		}
		for (int i = 0; i < 5; ++i)
		{
			weights_input_hidden_node2[i] += (learning_rate * delta_hidden_node[1] * inputs[i]);
		}
		for (int i = 0; i < 5; ++i)
		{
			weights_input_hidden_node3[i] += (learning_rate * delta_hidden_node[2] * inputs[i]);
		}
		for (int i = 0; i < 5; ++i)
		{
			weights_input_hidden_node4[i] += (learning_rate * delta_hidden_node[3] * inputs[i]);
		}
		}
		ofstream w_i_h1o;
		w_i_h1o.open("weights_input_hidden_node1.txt");
		w_i_h1o << weights_input_hidden_node1[0] << " " << weights_input_hidden_node1[1] << " " << weights_input_hidden_node1[2] << " " << weights_input_hidden_node1[3] << " " << weights_input_hidden_node1[4] << endl;
		w_i_h1o.close();
		ofstream w_i_h2o;
		w_i_h2o.open("weights_input_hidden_node2.txt");
		w_i_h2o << weights_input_hidden_node2[0] << " " << weights_input_hidden_node2[1] << " " << weights_input_hidden_node2[2] << " " << weights_input_hidden_node2[3] << " " << weights_input_hidden_node2[4] << endl;
		w_i_h2o.close();
		ofstream w_i_h3o;
		w_i_h3o.open("weights_input_hidden_node3.txt");
		w_i_h3o << weights_input_hidden_node3[0] << " " << weights_input_hidden_node3[1] << " " << weights_input_hidden_node3[2] << " " << weights_input_hidden_node3[3] << " " << weights_input_hidden_node3[4] << endl;
		w_i_h3o.close();
		ofstream w_i_h4o;
		w_i_h4o.open("weights_input_hidden_node4.txt");
		w_i_h4o << weights_input_hidden_node4[0] << " " << weights_input_hidden_node4[1] << " " << weights_input_hidden_node4[2] << " " << weights_input_hidden_node4[3] << " " << weights_input_hidden_node4[4] << endl;
		w_i_h4o.close();
		ofstream w_h_o1o;
		w_h_o1o.open("weights_hidden_output1.txt");
		w_h_o1o << weights_hidden_output1[0] << " " << weights_hidden_output1[1] << " " << weights_hidden_output1[2] << " " << weights_hidden_output1[3] << " " << weights_hidden_output1[4] << endl;
		w_h_o1o.close();
		ofstream w_h_o2o;
		w_h_o2o.open("weights_hidden_output2.txt");
		w_h_o2o << weights_hidden_output2[0] << " " << weights_hidden_output2[1] << " " << weights_hidden_output2[2] << " " << weights_hidden_output2[3] << " " << weights_hidden_output2[4] << endl;
		w_h_o2o.close();
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
		double v_input_hidden_node1 = 0,v_input_hidden_node2 = 0,v_input_hidden_node3 = 0,v_input_hidden_node4 = 0;
		for(int i = 0;i < 5;i++){
			v_input_hidden_node1 += (weights_input_hidden_node1[i] * inputs[i]);
			v_input_hidden_node2 += (weights_input_hidden_node2[i] * inputs[i]);
			v_input_hidden_node3 += (weights_input_hidden_node3[i] * inputs[i]);
			v_input_hidden_node4 += (weights_input_hidden_node4[i] * inputs[i]);
		}
		hidden_outputs[1] = (1/(1 + exp(-v_input_hidden_node1)));
		hidden_outputs[2] = (1/(1 + exp(-v_input_hidden_node2)));
		hidden_outputs[3] = (1/(1 + exp(-v_input_hidden_node3)));
		hidden_outputs[4] = (1/(1 + exp(-v_input_hidden_node4)));
		double v_output_node1 = 0,v_output_node2 = 0;
		for(int i = 0;i < 5;i++){
			v_output_node1 += (weights_hidden_output1[i] * hidden_outputs[i]);
			v_output_node2 += (weights_hidden_output2[i] * hidden_outputs[i]);
		}
		predicted_result1 = (1/(1 + exp(-v_output_node1)));
		predicted_result2 = (1/(1 + exp(-v_output_node2)));
		char a[] = "Iris-setosa";
      	char b[] = "Iris-versicolor";
      	char c[] = "Iris-virginica";
      	double predicted_result = (2 * predicted_result1) + predicted_result2;
      	if(round(predicted_result) == actual_result){
            count++;
      	}
      	if(predicted_result == 0){
      		//cout << a << endl;
      	}
      	else if(predicted_result == 1){
      		//cout << b << endl;
      	}
      	else if(predicted_result == 2){
      		//cout << c << endl;
      	}
      	cout << predicted_result << endl;
      }
      cout << "count = " << count << endl;
	}
	return 0;
}
