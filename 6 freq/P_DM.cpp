#include <bits/stdc++.h>
using namespace std;

ifstream fin;
double minfre;
vector<set<string>> records;
set<string> items;
map<string, int> freq;

vector<string> wordsof(string str)
{
   vector<string> tmpset;
   string tmp = "";
   int i = 0;
   while (str[i])
   {
       if (isalnum(str[i]))
           tmp += str[i];
       else
       {
           if (tmp.size() > 0)
               tmpset.push_back(tmp);
           tmp = "";
       }
       i++;
   }

   if (tmp.size() > 0)
       tmpset.push_back(tmp);

   return tmpset;
}

string combine(vector<string> &arr, int miss)
{
   string str;
   for (int i = 0; i < arr.size(); i++)
       if (i != miss)
           str += arr[i] + " ";
   str = str.substr(0, str.size() - 1);
   return str;
}

set<string> cloneit(set<string> &arr)
{
   set<string> dup;
   for (auto it = arr.begin(); it != arr.end(); it++)
       dup.insert(*it);
   return dup;
}

set<string> apriori_gen(set<string> &sets, int k)
{
   set<string> set2;
   for (auto it1 = sets.begin(); it1 != sets.end(); it1++)
   {
       auto it2 = it1;
       it2++;
       for (; it2 != sets.end(); it2++)
       {
           vector<string> v1 = wordsof(*it1);
           vector<string> v2 = wordsof(*it2);

           bool alleq = true;
           for (int i = 0; i < k - 1 && alleq; i++)
               if (v1[i] != v2[i])
                   alleq = false;

           v1.push_back(v2[k - 1]);
           if (v1[v1.size() - 1] < v1[v1.size() - 2])
               swap(v1[v1.size() - 1], v1[v1.size() - 2]);

           for (int i = 0; i < v1.size() && alleq; i++)
           {
               string tmp = combine(v1, i);
               if (sets.find(tmp) == sets.end())
                   alleq = false;
           }

           if (alleq)
               set2.insert(combine(v1, -1));
       }
   }
   return set2;
}

int main(){
   fin.open("input.csv", ios::in);

   cout << "Frequency % :";
   cin >> minfre;

   string str;
   while (!fin.eof())
   {
       getline(fin, str);
       vector<string> arr = wordsof(str);
       set<string> tmpset;
       for (int i = 0; i < arr.size(); i++)
           tmpset.insert(arr[i]);
       records.push_back(tmpset);

       for (auto it = tmpset.begin(); it != tmpset.end(); it++)
       {
           items.insert(*it);
           freq[*it]++;
       }
   }
   fin.close();
    cout << "No of transactions: " << records.size() << endl;
   minfre = minfre * (records.size()-1) / 100;
   cout << "Min frequency:" << minfre << endl;

      queue<set<string>::iterator> q;
   for (auto it = items.begin(); it != items.end(); it++)
       if (freq[*it] < minfre)
           q.push(it);

   while (q.size() > 0)
   {
       items.erase(*q.front());
       q.pop();
   }

   int pass = 1;
   cout << "\nFrequent " << pass++ << " -item set : \n";
   for (auto it = items.begin(); it != items.end(); it++)
       cout << "{" << *it << "} " << freq[*it] << endl;

   int i = 2;
   set<string> prev = cloneit(items);

   while (i)
   {
       set<string> cur = apriori_gen(prev, i - 1);

       if (cur.size() < 1)
       {
           break;
       }

       for (auto it = cur.begin(); it != cur.end(); it++)
       {
           vector<string> arr = wordsof(*it);

           int tot = 0;
           for (int j = 0; j < records.size(); j++)
           {
               bool pres = true;
               for (int k = 0; k < arr.size() && pres; k++)
                   if (records[j].find(arr[k]) == records[j].end())
                       pres = false;
               if (pres)
                   tot++;
           }
           if (tot >= minfre)
               freq[*it] += tot;
           else
               q.push(it);
       }

       while (q.size() > 0)
       {
           cur.erase(*q.front());
           q.pop();
       }

       bool flag = true;

       for (auto it = cur.begin(); it != cur.end(); it++)
       {
           vector<string> arr = wordsof(*it);

           if (freq[*it] < minfre)
               flag = false;
       }

       if (cur.size() == 0)
           break;

       cout << "\n\nFrequent " << pass++ << " -item set : \n";
       for (auto it = cur.begin(); it != cur.end(); it++)
           cout << "{" << *it << "} " << freq[*it] << endl;

       prev = cloneit(cur);
       i++;
   }

   ofstream fw("output.csv", ios::out);


   for (auto it = prev.begin(); it != prev.end(); it++)
   {


        stringstream ss(*it);
        string word;
        while(getline(ss,word,' '))
            fw<<word<<",";

        fw<<endl;
   }

   return 0;
}