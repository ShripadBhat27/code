#include <bits/stdc++.h>
using namespace std;

void fun(vector<string> ip , vector<vector<string>> data ){
    cout<<ip.size()<<" "<<data[0].size()<<endl;
    if((ip.size()+1)!=data[0].size()){
        cout<<" no proper input given ! "<<endl;   
        return ;  
    }    
    int n = data.size(),m=data[0].size() , ycount=0 , ncount=0;
    double p_yes=0,p_no=0;
    
    for(int i=1;i<n;i++){
        if(data[i][m-1]=="yes")
            ycount++;
        else 
            ncount++;
    }
    cout<<ycount<<" "<<ncount<<endl;
    p_yes = (ycount*1.0) / (ycount+ncount);
    p_no = (ncount*1.0) / (ycount+ncount);
    ofstream myFile("output.csv",ios::out);
    
    for(int i=1;i<ip.size();i++){
        int tmpyc=0,tmpnc=0;
        for(int j=1;j<n;j++){
            if(data[j][i]==ip[i]){
                if(data[j][m-1]=="yes")
                    tmpyc++;
                else 
                    tmpnc++;
            }
        }
        double Py_tmp = (tmpyc*1.0)/ycount;
        double Pn_tmp = (tmpnc*1.0)/ncount;
        myFile<<data[0][i]<<","<<"P(yes),P(no)"<<endl;
        myFile<<ip[i]<<","<<Py_tmp<<","<<Pn_tmp<<endl;
        myFile<<endl;    
        p_yes*=Py_tmp;
        p_no*=Pn_tmp;
    }
    myFile<<endl;
    myFile<<endl<<endl;
    myFile<<"P(yes),"<<p_yes<<endl;
    myFile<<"P(no)"<<","<<p_no<<endl;
    cout<<p_yes<<" "<<p_no<<endl;
}

int main()
{
    vector<vector<string>> input;
    fstream file;
    file.open("input1.csv");
    if(file.is_open()){
        string word,line;
        while(getline(file, line)){
        stringstream str(line);
            double cnt=0;
            vector<string> tmp;
            while(getline(str, word, ',')){
                tmp.push_back(word);
            }
            input.push_back(tmp);
        }
    }
    else {
        cout<<" could not open file "<<endl;
        return 0; 
    }
    cout<<"Enter Values for respective values : ";
    vector<string> v;
    for(int i=0;i<input[0].size()-1;i++){
        cout<<input[0][i]<<"\t";
        string s ; 
        cin>>s;
        v.push_back(s);
    }
    fun(v,input);
}