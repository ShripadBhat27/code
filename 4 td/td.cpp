#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
 
using namespace std;
 
int main(){
string fname="TWeight&DWeightN.csv";
vector<vector<string>> content;
vector<string> row;
string line, word;
 
fstream file ;
file.open(fname);
if(file.is_open())
{


while(getline(file, line))
{

row.clear();
 
stringstream str(line);
 
while(getline(str, word, ','))
row.push_back(word);
content.push_back(row);
}
}
else
cout<<"Could not open the file\n";
 cout<<endl;

int c1_tot = 0;
int c2_tot = 0;
int r1_tot = 0;
int r2_tot = 0;
for(int i=1;i<content.size();i++)
{
for(int j=1;j<content[i].size();j++)
{ 
 if(i==1)
  r1_tot+=stoi(content[i][j]);
 if(i==2)
  r2_tot+=stoi(content[i][j]);
 if(j==1)
  c1_tot+=stoi(content[i][j]);
 if(j==2)
  c2_tot+=stoi(content[i][j]);

}

}
ofstream writeFile("output4.csv");

vector<vector<double> > tweight(4,vector<double>(4)),dweight(4,vector<double>(4));

for(int i = 1; i < content.size(); i++) {
    
            for(int j = 1; j < content[i].size(); j++) {
                if(i == 1)
                    tweight[i][j]=((double)stoi(content[i][j]) / r1_tot) * 100;
                if(i == 2)
                     tweight[i][j]=((double)stoi(content[i][j]) / r2_tot) * 100;
                if(j == 1)
                    dweight[i][j]=((double)stoi(content[i][j]) / c1_tot) * 100;
                if(j == 2)
                    dweight[i][j]=((double)stoi(content[i][j]) / c2_tot) * 100;
            }
}

writeFile<<"T-weight"<<"\n";
writeFile<<content[0][0]<<","<<content[0][1]<<","<<content[0][2]<<"\n";
for(int i=1;i<=2;i++){
    writeFile<<content[i][0]<<",";
    for(int j=1;j<=2;j++)
        writeFile<<tweight[i][j]<<"%"<<",";
    writeFile<<"\n";
}

writeFile<<"\n\n\n";
writeFile<<"D-weight"<<"\n";
writeFile<<content[0][0]<<","<<content[0][1]<<","<<content[0][2]<<"\n";
for(int i=1;i<=2;i++){
    writeFile<<content[i][0]<<",";
    for(int j=1;j<=2;j++)
        writeFile<<dweight[i][j]<<"%"<<",";
    writeFile<<"\n";
}
return 0;
}
 
 