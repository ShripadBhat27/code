#include<bits/stdc++.h>
using namespace std;



vector<vector<string>> content;

int n;
double calcEntropy(int y,int n){
    if(y==0||n==0)
    return 0;
    double s_entropy=-(y/(float)(y+n))*(log2(y/(float)(y+n)));
    s_entropy=s_entropy+(-(n/(float)(y+n))*(log2(n/(float)(y+n))));
    return s_entropy;
}









double calcgain(map<string,pair<int,int> >tmp,double s_entropy,int total){
 
 
 	for(auto itr=tmp.begin();itr!=tmp.end();++itr){
    	double p_entropy=calcEntropy(itr->second.second,itr->second.first);
    	double mul=(itr->second.second+itr->second.first);
    	mul=mul/total;
    	s_entropy-=((mul)*p_entropy);
 	} 
	 
	
 	return s_entropy;  
}
double giniIndex(map<string,pair<int,int>>tmp,double s_entropy,int total){
    
	double gini=0.0;
   
    for(auto itr=tmp.begin();itr!=tmp.end();++itr){
     double ans=1;
     // cout<<itr->first<<" :"<<itr->second.first<<" "<<itr->second.second<<"\n";
     int tot=itr->second.second+itr->second.first;
     ans-=pow(((float)itr->second.second/tot),2);
     ans-=pow(((float)itr->second.first/tot),2);
     gini+=(ans*((float)tot/total));
    } 
    
    
 return gini;
}

double sqx(int num,int deno){

    return (num*num*1.0)/(deno*deno);
}


double helper(map<string,pair<int,int>>tmp,int inequality){
    int a1=0,a2=0,b1=0,b2=0;
    //a for <= && b for >
    //1 for NO and 2 for YES

    for(auto p:tmp){
        if(stoi(p.first)<=inequality){
            if(p.second.first)
                a1+=p.second.first;
            if(p.second.second)
                a2+=p.second.second;
        }else{
            if(p.second.first)
                b1+=p.second.first;
            if(p.second.second)
                b2+=p.second.second;
        }
    }

    // cout<<a1<<" "<<a2<<"\n"<<b1<<" "<<b2<<"\n";
    double first_term=((a1+a2)*1.0/n)*(1-sqx(a1,a1+a2)-sqx(a2,a1+a2));
    double second_term=((b1+b2)*1.0/n)*(1-sqx(b1,b1+b2)-sqx(b2,b1+b2));
    return first_term+second_term; 
}
double giniIndexN(map<string,pair<int,int>>tmp){
    
   
    
    double gini=INT_MAX;
    int splitting_criteria;
    for(auto number:tmp){
        double inter=helper(tmp,stoi(number.first));
        if(inter<gini){
            gini=inter;
            splitting_criteria=stoi(number.first);
        }
    }

   cout<<"\nBEST SPLITTING :"<<splitting_criteria<<"\n";
   return gini;
}


int main()
{
    fstream fin("input.csv",ios::in);
    vector<vector<string>> content;
    vector<string> row;
    
   
    string line, word;
    int cnty=0;
    int cntn=0;
    if(fin.is_open()){
        while(getline(fin,line)){
            row.clear();
            stringstream s(line);
            while(getline(s,word,',')){
                    row.push_back(word);
            }
            content.push_back(row);
		}
    }
    
    
    n=content.size()-1;
    map<string,map<string,pair<int,int>> >entireData;
   
    for(int i=1;i<content.size();i++)
    {	
    	
        if(content[i][content[i].size()-1]=="No")
        {
            cntn++;
            for(int j=1;j<content[0].size()-1;j++){
            	entireData[content[0][j]][content[i][j]].first+=1;
                
			}
            
            
        }
        else
        {
            cnty++;
            
            for(int j=1;j<content[0].size()-1;j++){
            	entireData[content[0][j]][content[i][j]].second+=1;
			}
            
        }
    }
  	
    map<int,string> indexing;
    int idx=0;
    for(auto s:entireData){
        indexing[idx]=s.first;idx++;
    }
    double s_entropy=calcEntropy(cnty,cntn); 
    
    cout<<"Number\t"<<"Atttribute\n";
    for(auto p:indexing)
        cout<<p.first<<"\t"<<p.second<<"\n";

    int choice;
    cout<<"\nEnter Atttribute for which GiniIndex is to be found :";
    cin>>choice;    
    
    bool isnumerical=false;
    cout<<"Is entered attribute numerical ? :";
    cin>>isnumerical;

    if(isnumerical==0)
    cout<<"GiniIndex for "<<indexing[choice]<<": "<<giniIndex(entireData[indexing[choice]],s_entropy,content.size()-1)<<"\n";
 	else
        cout<<"GiniIndex for "<<indexing[choice]<<": "<<giniIndexN(entireData[indexing[choice]])<<"\n";
    

    cout<<"\nEnter Atttribute for which GiniIndex is to be found :";
    cin>>choice;    
    
    
    cout<<"Is entered attribute numerical ? :";
    cin>>isnumerical;

    if(isnumerical==0)
        cout<<"GiniIndex for "<<indexing[choice]<<": "<<giniIndex(entireData[indexing[choice]],s_entropy,content.size()-1)<<"\n";
    else
        cout<<"GiniIndex for "<<indexing[choice]<<": "<<giniIndexN(entireData[indexing[choice]])<<"\n";
    
  
 	return 0;
}


