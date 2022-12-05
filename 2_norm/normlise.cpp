#include<bits/stdc++.h>
using namespace std;

double mean_ofArray(vector<double> MinMaxArray, int num_elements){
		double mean;
		double  sum=0, valuesAbovemean=0;

		for (int i=0; i<num_elements; i++)
				sum+=MinMaxArray[i];
				
		mean=sum/num_elements;

		for (int i=0; i<num_elements; i++)
			if (MinMaxArray[i]>mean)
				valuesAbovemean++;
			

		cout<<"Values above the mean are: "<<valuesAbovemean<<endl;
		cout<<"mean: "<< mean<<endl;
		return mean;
}


double Maximum_fromArray(vector<double> MinMaxArray, int num_elements){
		double maxi=INT_MIN;
			for (int i=0; i<num_elements; i++){
				if (MinMaxArray[i]>maxi)	maxi=MinMaxArray[i];	
			}
		return maxi;
}





double Minimun_fromArray( vector<double> MinMaxArray, int num_elements){
		double mini=INT_MAX;
		for (int i=0; i<num_elements; i++){
				if(MinMaxArray[i]<mini)
					mini=MinMaxArray[i];
		}
	return mini;
}


vector<double> norm_by_minmax(int min, int max, int new_min,int new_max, vector<double>MinMaxArray, int num_elements){


		cout<<"\n\nNormalisation using min-max \n";
		vector<double> normalized(num_elements);
			for (int i=0; i<num_elements; i++){
				normalized[i]=(((MinMaxArray[i] -min)/(max-min))*(new_max-new_min)) + new_min;
			}
		cout<<"\nNormalized Values are :";
		for (int i=0; i<num_elements; i++)
			{
			cout<<normalized[i]<<" ";
			
		}
		

		cout<<"\n";

		return normalized;
}

int main(){

 vector<double> MinMaxArray;
    string fname="input2.csv";
//vector<vector<string>> content;
string line, word;
 
fstream file ;
file.open(fname);
if(file.is_open())
{
while(getline(file, line))
{

 
stringstream str(line);
 
while(getline(str, word, ','))
MinMaxArray.push_back(stod(word));

}
}
	
	for(auto i:MinMaxArray)
	cout<<i<<" ";
	cout<<endl;
	

	int num_of_elements=MinMaxArray.size();
	vector<double>alias=MinMaxArray;
	int new_max, new_min,old_min,old_max;

	cout<<"Enter New Min: ";
	cin>>new_min;
	cout<<"Enter New Max: ";
	cin>> new_max;
	
	double mean;
	old_max = Maximum_fromArray(MinMaxArray,num_of_elements);
	old_min = Minimun_fromArray(MinMaxArray,num_of_elements);




	mean = mean_ofArray(MinMaxArray,num_of_elements);

	vector<double>v=norm_by_minmax(old_min, old_max, new_min,new_max,MinMaxArray,num_of_elements);




	cout<<"\n\nz-score Normalisation\n";

	int n=alias.size();
	double sd=0.0;

	for(int i=0;i<n;i++)
			sd+= pow(alias[i] - mean, 2);


	double std_dev=sqrt(sd/n);
	// cout<<"||"<<std_dev<<" "<<mean<<"|";
	vector<double> newArr=alias;
	for(int i=0;i<n;i++){
		newArr[i]=(newArr[i]-mean)/std_dev;	
	}
	 

	cout<<"\nZ-score Values are :";
	for(int i=0;i<n;i++)
		cout<<newArr[i]<<" ";
	
	ofstream writeFile("output2.csv");
	   writeFile<<"Marks"<<","<<"Normalized Marks(Min-Max )"<<","<<"Normalized Marks (Z Score)"<<endl;
	
		for(int i=0;i<MinMaxArray.size();i++)
		writeFile <<MinMaxArray[i]  << "," << v[i]<<","<<newArr[i]<<endl;
		
	

	return 0;
}
