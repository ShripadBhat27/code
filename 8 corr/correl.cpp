#include<bits/stdc++.h>
using namespace std;


double correlation(vector<int>&a,vector<int>&b){
	int prob_aUb=0,prob_a=0,prob_b=0;

	int n=a.size();
	for(int i=0;i<n;i++){
		if(a[i]==1&&b[i]==1)
			prob_aUb++;
		
		if(a[i]==1)
			prob_a++;

		if(b[i]==1)
			prob_b++;
	}
	
	double num=(prob_aUb*1.0)/n;
	double deno=((prob_a*1.0)/n)*((prob_b*1.0)/n);
	// double coef=((prob_aUb*1.0)/)/(prob_a*prob_b);

	return num/deno;
}


int main(){
	vector<int> a,b,c;

	fstream file;
	file.open("input.csv");
	if(file.is_open()){
	string word,line;
	bool isdone=false;
	while(getline(file, line)){
	stringstream str(line);
 		int cnt=0;
		while(getline(str, word, ',')){
			if(cnt==0&&isdone)
				a.push_back(stoi(word));
			else if(cnt==1&&isdone)
				b.push_back(stoi(word));
			else if(cnt==2&&isdone)
				c.push_back(stoi(word));
			cnt++;
		}
		isdone=true;
		
	}
	}

	

	cout<<"correlation of a&b :"<<correlation(a,b)<<endl;
	cout<<"correlation of b&c :"<<correlation(b,c)<<endl;
	cout<<"correlation of a&c :"<<correlation(a,c)<<endl;

	ofstream writeFile("output.csv");


	writeFile<<"correlation of a&b :"<<","<<correlation(a,b)<<endl;
	writeFile<<"correlation of b&c :"<<","<<correlation(b,c)<<endl;
	writeFile<<"correlation of a&c :"<<","<<correlation(a,c)<<endl;
	return 0;


}
