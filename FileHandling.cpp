#include<bits/stdc++.h>
using namespace std;


int main(){

	fstream f;
	f.open("input.csv");

	ofstream wf("output.csv");
	vector<vector<string> > data;

	if(f.is_open()){
		string line,word;
		while(getline(f,line)){
			stringstream ss(line);
			while(getline(ss,word,','))
				wf<<word<<",";
			wf<<endl;
		}
	}



	return 0;
}