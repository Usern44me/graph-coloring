#include "Graf_v.h"
#include <string>
#include<vector>

int
main()
{


	std::cout << "Enter file name with graf" << std::endl;
	std::string str;
	getline(std::cin, str);
	graf g(str);
	//std::cout << g;
	std::string str2;
	std::cout << "Enter output file" << std::endl;
	getline(std::cin, str2);
	
	std::cout << "Choose your metod" << std::endl;
	std::cout << "1)Al perebor" << std::endl;
	std::cout << "2)Greedy metod" << std::endl;
	int n;
	std::cin >> n;
	switch (n)
	{
	case 1:g.all_perebor(str2);
	case 2:g.greedy_metod(str2);
	}

	system("pause");
	return 0;
}