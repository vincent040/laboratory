#include <iostream>

using namespace std;

const double molecule = 3.0E-23;

int main(void)
{
	cout << "你有几瓶农夫山泉？" << endl;

	int n;
	cin >> n;

	cout.setf(ios_base::scientific, ios_base::floatfield);
	cout.precision(3);

	cout << "哇！你拥有"
	     << n * 450 / molecule
	     << "个水分子"
	     << endl;

	return 0;
}
