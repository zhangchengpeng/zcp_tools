#include "printf_utils.h"
#include <typeinfo>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	int a = 1;
	int b = 2;
	auto result = [](int x, int y)->int{return x+y;};
	int c = result(a, b);
	cout <<  typeid(result).name() << ":" << c << endl;
	return 0;
}
