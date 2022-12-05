#include<bits\stdc++.h>
using namespace std;

double median(vector<int>& a,int i,int j) {
	int n = j-i+1;
    if((n%2)==1)
        return a[(i+j)/2];

    double f1=(double)a[((i+j)/2)]+(double)a[((i+j+1)/2)];
    return f1/2.0;
}

int main(){
    vector<int> v;
    ifstream readFile("input5.csv");
	int min=INT_MAX;
	string marks;
    cout<<"Data :";
	while(readFile.good())
	{
		getline(readFile,marks,'\n');
		
		stringstream obj;
		int value;
		obj<<marks;
		obj>>value;
		cout<<value<<" ";
		v.push_back(value);
	}
	cout<<endl;
    sort(v.begin(),v.end());
    int n=v.size();
    vector<int>v1;
    v1.push_back(v[0]);
    v1.push_back(v[n-1]);
    int min_number=v[0];
    int max_number=v[n-1];
    int q1=median(v,0,(n-1)/2-1);
    int q2=median(v,0,n-1);
    int q3=median(v,(n-1)/2+1,n-1);
    
    cout<<"\n\nFive Number Summary :\n";
    cout<<"minimun number  : "<<min_number<<endl;
    
    cout<<"quartile 1 number  : "<<q1<<endl;
    cout<<"quartile 2 number  : "<<q2<<endl;
    cout<<"quartile 3 number  : "<<q3<<endl;
    cout<<"maximum number  : "<<max_number<<endl;
    
    int iqr=q3-q1;
    
    double lower_outlier=q1-(1.5)*iqr;
    double upper_outlier=q3+(1.5)*iqr;

    cout<<"Interquartile range :"<<iqr<<"\n";
    cout<<"Lower Outlier :"<<lower_outlier<<"\n";
    cout<<"Upper Outlier"<<upper_outlier<<"\n";
    ofstream writeFile("output5.csv");
    writeFile<<"minimun number "<<','<<min_number<<endl;
    writeFile<<"maximum number "<<','<<max_number<<endl;
    writeFile<<"median "<<','<<q2<<endl;
    writeFile<<"quartile one"<<','<<q1<<endl;
    writeFile<<"quartile three "<<','<<q3<<endl;
    writeFile<<"lower Outlier"<<','<<lower_outlier<<endl;
    writeFile<<"upper Outlier"<<','<<upper_outlier<<endl;
     
    return 0;

}