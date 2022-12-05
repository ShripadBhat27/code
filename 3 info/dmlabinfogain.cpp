#include<bits\stdc++.h>
using namespace std;

double getentropy(int p,int n){
    
    if(p==0||n==0) return 0;
    double first = (-1*log2((1.0)*p/(p+n))*p)/(p+n);
    double second = (-1*log2((1.0)*n/(p+n))*n)/(p+n);

    return first + second;
}

int main(){
    string fname = "input.csv";

    vector<vector<string>> content;
    vector<string> row;
    string line, word;
    
    fstream file (fname, ios::in);
    ofstream myFile("output.csv",ios::out);
    if(file.is_open()){
        while(getline(file, line)){
            row.clear();
            stringstream str(line);
            while(getline(str, word, ',')){
                row.push_back(word);
            }
            content.push_back(row);
        }
    }   
    int cnt=0;
    map<int,string> attribute_mapping;
    bool isdone=false;
    cout<<"\nDATA :\n";
    for(auto vec : content){
        for(auto str: vec){
            if(!isdone){
                attribute_mapping[cnt++]=str;
            }
            cout<<str<<" ";
        }
        isdone=true;
        cout<<endl;
    }

    int totalYes = 0,totalNo=0,total=0;
    vector<pair<int,int>> v;
    int columns=content[0].size();
    for(int i=1;i<content.size();i++){
        if(content[i][columns-1]=="Yes"){
            totalYes++;
        }
        else{
            totalNo++;
        } 
        total++;
    }
 
    cout<<"\n\nNumber\tAttribute\n";
    for(auto mp:attribute_mapping){
        cout<<mp.first<<"\t"<<mp.second<<"\n";
    }

    int choice,class_attribute=cnt-1;
    cout<<"\nEnter Attribute Number whose info gain is to be calculated :";
    cin>>choice;

    cout<<"\nTotal Number of No's :"<<totalNo<<"\nTotal Number of yes's :"<<totalYes;
    cout<<"\nTotal number of entries : "<<total<<endl;

    map<string , pair<int,int>> m;

    for(int i=0;i<content.size();i++){
        
        if(content[i][class_attribute]=="Yes")
            m[content[i][choice]].first++;
        if(content[i][class_attribute]=="No")
            m[content[i][choice]].second++;
    }

    cout<<"\n\n<ATTRIBUTE's yes and no count>\n";
    map<int,string> mp;
    cnt=0;
    for(auto i : m){
        cout<<i.first<<" :"<<(i.second).first<<" "<<(i.second).second<<"\n";
        mp[cnt]=i.first;
        v.push_back(i.second);
        cnt++;
    }


    // calculating entropy  
    double attributeEntropy = 0;
    myFile<<" Value , Number of yes , Number of No , Entropy \n";
    cnt=0;
    for(auto i : v){
        double entropy = getentropy(i.first,i.second) ;
        myFile<<mp[cnt]<<","<<i.first<<","<<i.second<<","<<entropy<<endl;
        double s =( entropy * (i.first+i.second)*(1.0) )/total;
        attributeEntropy+=s;
        cnt++;
    }

    double classentropy=getentropy(totalYes,totalNo);
    cout<<"\nClass Entropy :"<<classentropy<<endl;

    cout<<"\nAttribute Entropy :"<<attributeEntropy<<endl;
    myFile<<"\n \n ";
    double info_gain = getentropy(totalYes,totalNo) - attributeEntropy ; 
    
    cout<<"\nInfo Gain :"<<info_gain<<"\n";
    myFile<<"information gain , "<<info_gain<<endl;
       
    return 0;
}