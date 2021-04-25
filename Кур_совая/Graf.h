#pragma
#include <fstream>
#include <iostream>
#include <vector>

class graf
{
public:
	graf();
	~graf();
	void from_file(std::string &str);
	friend std::ostream& operator<< (std::ostream& os, const graf &a)
	{

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				os << a.tabl[i][j];
			}
			os << "\n";
		}
		return os;
	}
	void all_perebor();
	int  size()
	{
		return this->size_tabl;
	}
private:
	char **tabl;
	//std::vector<std::vector<char>> tabl;
	int size_tabl;

};

graf::graf()
{	
	size_tabl = 10;
	tabl = (char**)calloc(10, sizeof(char*));
	for (int i = 0; i < 10; i++)
	{
		*(tabl + i) = (char*)calloc(10, sizeof(char));
	}
}

graf::~graf()
{
	for (int i = 0; i < 10; i++)
	{
		delete[] * (tabl + i);
	}
	delete[] tabl;
}


void graf::from_file(std::string &str)
{
	FILE *fin;
	fopen_s(&fin, str.c_str(), "r");

	if (fin == NULL)
	{
		std::cout << "ERROR" << std::endl;
	}

	fseek(fin, 0, SEEK_END);
	int size = ftell(fin);
	char* buf = (char*)calloc(size, sizeof(char));
	fseek(fin, 0, SEEK_SET);
	for (int i = 0; feof(fin) == 0; i++)
	{
		*(buf + i) = getc(fin);
	}

	int j = 0;
	int n = 0;
	for (int i = 25; i < size; i++)
	{
		if (buf[i] == '\n')
		{
			i += 3;
			j++;
			n = 0;
		}
		if (buf[i] != '\n' && buf[i] != ' ')
		{
			tabl[j][n] = buf[i];
			n++;
		}
	}

}

void graf::all_perebor()
{
	for (int i = size_tabl; i > 0; i --)
	{
		for (int j = 0; j < i; j ++)
		{
			//printf("!");
			if (tabl[i][j] == '1' && i != j)
			{
				std::cout << 'v' << i << ' v' << j << '\n';
			}
		}
	}
}
