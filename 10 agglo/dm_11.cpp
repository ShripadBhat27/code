#include <bits/stdc++.h>
using namespace std;

void agglo(int itr, int n, int tot_itr, vector<vector<int>> dist, vector<string> header)
{
	if (itr == tot_itr)
	{
		cout << "\nFinal Cluster: " << header[0] << "\n";
		return;
	}

	cout << "\n"
		 << itr << "th iteration:-----------------------------------------\n";
	if (itr != 1)
		cout << "New ";
	cout << "Distance Matrix:" << endl;

	for (int i = 0; i < header.size() - 1; i++)
		printf("%5s", header[i].c_str());
	cout << "	" << header[header.size() - 1] << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= i; j++)
			printf("%5d", dist[i][j]);
		cout << endl;
	}

	int m = INT_MAX, row, column;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < i; j++)
			if (dist[i][j] < m)
			{
				m = dist[i][j];
				row = i;
				column = j;
			}
	}
	cout << "\nMinimum: " << m << endl;
	vector<vector<int>> new_dist_matrix;
	vector<int> cd;
	for (int i = 0; i < n; i++)
	{
		vector<int> r;
		m = INT_MAX;
		for (int j = 0; j < n; j++)
		{
			if (i != row && i != column)
			{
				m = min(dist[i][row], dist[i][column]);
				if (j != row && j != column)
					r.push_back(dist[i][j]);
			}
		}

		if (m != INT_MAX)
		{
			cd.push_back(m);
			r.push_back(m);
		}

		if (!r.empty())
			new_dist_matrix.push_back(r);

	}
	cd.push_back(0);
	new_dist_matrix.push_back(cd);


	string str = "(";
	if (row < column)
	{
		str += header[row] + ", " + header[column] + ")";
	}
	else
	{
		str += header[column] + ", " + header[row] + ")";
	}

	header.erase(header.begin() + row);
	header.erase(header.begin() + column);
	header.push_back(str);

	agglo(++itr, --n, tot_itr, new_dist_matrix, header);
}

vector<vector<int>> dist_matrix(vector<int> Ax, vector<int> Ay)
{
	vector<vector<int>> res;
	for (int i = 0; i < Ax.size(); i++)
	{
		vector<int> row;
		for (int j = 0; j < Ax.size(); j++)
			row.push_back(abs(Ax[i] - Ax[j]) + abs(Ay[i] - Ay[j]));
		res.push_back(row);
	}

	return res;
}

int main()
{
	fstream fin("input.csv", ios::in);
	vector<vector<string>> content;
	vector<string> row;
	string line = "", word = "";

	if (fin.is_open())
	{
		while (getline(fin, line))
		{
			row.clear();
			stringstream s(line);
			while (getline(s, word, ','))
			{
				row.push_back(word);
			}
			content.push_back(row);
		}
	}

	vector<int> Ax, Ay;
	for (int i = 1; i < content.size(); i++)
	{
		Ax.push_back(stoi(content[i][0]));
		Ay.push_back(stoi(content[i][1]));
	}

	vector<string> header;
	char c = 'A';
	for (int i = 0; i < Ax.size(); i++)
	{
		string str(1, c + i);
		header.push_back(str);
	}

	vector<vector<int>> d = dist_matrix(Ax, Ay);
	agglo(1, Ax.size(), Ax.size(), d, header);
	fin.close();
}