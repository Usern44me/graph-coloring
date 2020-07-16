#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>

class graf
{
public:
	graf(std::string &str);
	void from_file(std::string &str);
	void all_perebor(std::string &str);
	void greedy_metod(std::string &str);
	friend std::ostream& operator<< (std::ostream& os, const graf &a)
	{

		for (unsigned int  i = 0; i < a.matrix.size(); ++i)
		{
			for (unsigned int j = 0; j < a.matrix[i].size(); ++j)
			{
				os << a.matrix[i][j] << ' ';
			}

			os << "\n";
		}
		return os;
	}
private:
	std::vector<std::vector<int>> matrix;
	void dfs(int v, int prev, std::vector<int>  &color, bool *visited);
	void perebor(std::vector<int>  &color, int pos, std::string &str);
	bool check(std::vector<int>  &color);
	void in_file(std::string &str, std::vector<int>  &color);
};

graf::graf(std::string &str)
{
	this->from_file(str);
}



void graf::in_file(std::string &str, std::vector<int>  &color)
{
	std::vector<std::string> palitra;
	palitra.push_back("White");
	palitra.push_back("Green");
	palitra.push_back("Blue");
	palitra.push_back("Red");
	palitra.push_back("Orange");
	palitra.push_back("Brown");
	palitra.push_back("Pink");

	std::fstream fp;
	fp.open(str.c_str(), std::fstream::out);
	fp << "graph MyGraf{ \n";
	fp << "graph [rankdir = LR] \n";
	fp << "node [shape = circle, style = filled, color = grey] \n";
	int n = 0;
	for (unsigned int i = 0; i < matrix[1].size(); i++)
	{
		if (n == matrix[1].size() ) break;
		fp << "node [fillcolor = " << palitra[i].c_str() << "]\n";
		
		for (unsigned int j = 0; j < matrix[1].size(); j++)
		{
			if (color[j] == i)
			{
				fp << j << ' ';
				n++;
			}
		}
		fp << " \n";
	}
	fp << "edge [color = grey] \n";
	for (unsigned int i = 0; i < matrix[1].size(); ++i)
	{
		fp << i << " -- {";
		for (unsigned int j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j] == 1)
			{
				fp << j << " ";
			}
		}
		fp << "} \n";
	}
	fp << "} \n";
	fp.close();
	exit(0);
}



void graf::from_file(std::string &str)
{
	
	unsigned  int i = 0, k = 0;
	std::vector<char> v;
	if (FILE *fp = fopen(str.c_str(), "r"))
	{
		char buf[1024];
		while (size_t len = fread(buf, 1, sizeof(buf), fp))
			v.insert(v.end(), buf, buf + len);

		fclose(fp);
	}

	i = 0;
	while (v[i] != '\n')
	{
		i++;
	}
	matrix.resize(v[i - 1] - '0' + 1);

	while (v[i] != '\0')
	{
		i++;
		for (k = 0; v[i + k] != '\n' && i + k < v.size() - 1; k++)
		{
			if (v[i + k] == '0' && k != 0)
			{
				matrix[v[i] - '0'].push_back(0);
			}
			if (v[i + k] == '1' && k != 0)
			{
				matrix[v[i] - '0'].push_back(1);
			}
		}
		if (i + k == v.size() - 1)break;
		i += k;
	}
}
	

bool graf::check(std::vector<int>  &color)
{
	unsigned int i, j;
	for (i = 0; i < matrix.size(); ++i)
	{
		for (j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j] == 1)
			{
				if (color[i] == color[j])
				{
					return false;
				}
			}
			if (i == matrix.size() - 1 && j == matrix[i].size() - 1)
			{
				return true;
			}
		}
	}
}

void graf::perebor(std::vector<int>  &color, int pos , std::string &str)
{

		if (pos >= color.size())
		{
			if (check(color) == true)
			{
				in_file(str, color);
			}
			return;
		}
		else
		{
			for (int i = pos; i < color.size(); ++i)
			{
				std::swap(color[i], color[pos]);
				perebor(color, pos + 1, str);
				std::swap(color[i], color[pos]);
			}
		}

}


void graf::all_perebor(std::string &str)
{
	std::vector<int>  color;
	for (int i = 0; i < matrix.size(); i++)
	{
		color.push_back(0);
	}
	unsigned int  j;
	int pos = 0;

	while(1)
	{
		for (j = matrix[1].size() - 1; j > pos ; --j)
		{
			color[j]++;
			perebor(color, 0, str);
		}
		pos++;
	}
}

void graf::dfs(int v, int prev, std::vector<int>  &color, bool *visited )
{
	int j;
	visited[v] = true;
	if (color[v] == color[prev] && v != prev)
		color[v]++;
	for (j = 0; j < matrix[1].size(); ++j)
	{
		if (matrix[v][j] == 1)
		{

			if (visited[j] == false)
			{

				dfs(j, v, color, visited);
			}
			else
			{
				if (color[v ] == color[j])
				{
					color[v ]++;
				}
			}
		}

	}if (j == matrix[1].size() - 1) return;

}

inline void graf::greedy_metod(std::string & str)
{
	bool visited[10] = {false};
	std::vector<int>  color;
	for (int i = 0; i < matrix.size(); i++)
	{
		color.push_back(0);
	}
	visited[0] = true;

	dfs(1, 0, color, visited);
	in_file(str, color);

}
