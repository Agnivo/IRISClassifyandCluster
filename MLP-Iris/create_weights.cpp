#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream w_i_h1;
	w_i_h1.open("weights_input_hidden_node1.txt");
	w_i_h1 << "0.1 0.2 0.3 0.4 0.5\n";
	w_i_h1.close();
	w_i_h1.open("weights_input_hidden_node2.txt");
	w_i_h1 << "0.2 0.3 0.6 0.4 0.5\n";
	w_i_h1.close();
	w_i_h1.open("weights_input_hidden_node3.txt");
	w_i_h1 << "0.1 0.3 0.5 0.1 0.2\n";
	w_i_h1.close();
	w_i_h1.open("weights_input_hidden_node4.txt");
	w_i_h1 << "0.2 0.4 0.6 0.1 0.3\n";
	w_i_h1.close();
	w_i_h1.open("weights_hidden_output1.txt");
	w_i_h1 << "0.2 0.4 0.5 0.1 0.3\n";
	w_i_h1.close();
	w_i_h1.open("weights_hidden_output2.txt");
	w_i_h1 << "0.1 0.4 0.5 0.3 0.6\n";
	w_i_h1.close();
	return 0;
}

