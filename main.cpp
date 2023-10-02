#include <cstdint>
#include <iostream>

using namespace std;

int32_t main(int32_t argc, char* argv[])
{
	for (uint32_t i = 0; i < argc; i++)
	{
		cout << argv[i] << endl;
	}

	system("pause");
	return 0;
}