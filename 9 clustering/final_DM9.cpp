#include <bits/stdc++.h>
using namespace std;


double distance(double x1,double y1,double x2,double y2) {
    double sq_x = (x2 - x1) * (x2 - x1);
    double sq_y = (y2 - y1) * (y2 - y1);
    return sqrt(sq_x + sq_y);
}



vector<vector<double>> solve(double new_x,double new_y,double n,vector<double>&x,vector<double>&y,double&final_radius){

    vector<double> x_cord1;
    x_cord1.push_back(new_x);
    for(double i = 0 ; i < n ; ++i) {
        x_cord1.push_back(x[i]);
    }

    vector<double> y_cord1;
    y_cord1.push_back(new_y);
    for(double i = 0 ; i < n ; ++i) {
        y_cord1.push_back(y[i]);
    }

    vector<vector<double>> res1(n+1,vector<double>(n+1,0));
    for(double i = 0 ; i <= n; ++i) {
        for(double j = i + 1 ; j <= n; ++j) {
            double dis = distance(x_cord1[i],y_cord1[i],x_cord1[j],y_cord1[j]);
            if(i==0&&final_radius<dis)
                final_radius=dis;
            res1[i][j] = dis;
        }
    }
    return res1;

}

double getSum(vector<double>arr) {
    double sum = 0;
    for(auto&el:arr)
        sum+=el;
    return sum;
}

int main() {
    vector<double> x,y;

    fstream file;
    file.open("input.csv");
    if(file.is_open()){
    string word,line;
    bool isdone=false;
    while(getline(file, line)){
    stringstream str(line);
        double cnt=0;
        while(getline(str, word, ',')){
            if(cnt==1&&isdone)
                x.push_back(stod(word));
            else if(cnt==2&&isdone)
                y.push_back(stod(word));
            cnt++;
        }
        isdone=true;
        
    }
}
    double sumX = getSum(x);
    double sumY = getSum(y);

    double n=x.size();
    double midX = sumX / n;
    double midY = sumY / n;

    ofstream writeFile("output.csv");
    cout<<"\nCentroid :"<<"("<<midX<<","<<midY<<")\n";
    writeFile<<"\nCentroid(C) :"<<","<<midX<<" "<<midY<<"\n";
        writeFile<<"\nmatrix from C\n";
    vector<double> x_cord;
    x_cord.push_back(midX);
    for(double i = 0 ; i < n ; ++i) {
        x_cord.push_back(x[i]);
    }

    vector<double> y_cord;
    y_cord.push_back(midY);
    for(double i = 0 ; i < n ; ++i) {
        y_cord.push_back(y[i]);
    }

    double minD = 1e7+9;;
    double new_x,new_y;
    int idx;

    vector<vector<double>> res(n+1,vector<double>(n+1,0));
    for(double i = 0 ; i <= n; ++i) {
        for(double j = i + 1 ; j <= n; ++j) {
            double dis = distance(x_cord[i],y_cord[i],x_cord[j],y_cord[j]);
            res[i][j] = dis;
            if(i==0&&dis < minD) {
                minD = dis;
                new_x=x_cord[j];
                new_y=y_cord[j];
                idx=j;
            }
        }
    }
    


    for(double i = 0 ; i <= n ; ++i) {
        for(double j = 0 ; j <= n ; ++j) {
            cout << res[i][j] << ' ';
        }
        cout << endl;
    }    
    
    writeFile<<" "<<","<<"C"<<",";
    for(int i=1;i<=n;i++)
        writeFile<<"P"<<i<<",";
    writeFile<<"\n";
    for(double i = 0 ; i <= n ; ++i) {
        if(i==0) writeFile<<"C "<<",";
        else writeFile<<"P"<<(i)<<",";
        for(double j = 0 ; j <= n ; ++j) {
            writeFile << res[i][j] << ',';
        }
        writeFile << endl;
    }
    
    cout<<"\n\nNew Coordinate :";
    cout<<new_x<<" "<<new_y<<"\n";
    
    writeFile<<"\n\nMatrix from :("<<new_x<<" "<<new_y<<")\n\n";
    double final_radius=0;
    vector<vector<double>> res1=solve(new_x,new_y,n,x,y,final_radius);



    for(double i = 0 ; i <= n ; ++i) {
        for(double j = 0 ; j <= n ; ++j) {
            cout << res1[i][j] << ' ';
        }
        cout << endl;
    }    
     writeFile<<" "<<","<<"P"<<idx<<",";
     for(int i=1;i<=n;i++)
        writeFile<<"P"<<i<<",";
    writeFile<<"\n";
     
      for(double i = 0 ; i <= n ; ++i) {
        if(i==0)
            writeFile<<"P"<<idx<<",";
        else
            writeFile<<"P"<<(i)<<",";
            
            
        for(double j = 0 ; j <= n ; ++j) {
            writeFile << res1[i][j] << ',';
        }
        writeFile << endl;
    }


    cout<<"\n\nCENTER of cluster :"<<"("<<new_x<<" "<<new_y<<")\n";
    cout<<"RADIUS of cluster :"<<final_radius;
    
    
    writeFile<<"\n\nCENTER of cluster :"<<"("<<new_x<<" "<<new_y<<")\n";
    writeFile<<"RADIUS of cluster :"<<final_radius;
   
   
        
    return 0;
}
