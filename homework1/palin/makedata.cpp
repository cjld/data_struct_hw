#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
	srand(time(0));
	freopen("input.txt","w",stdout);
	int n=100;
	cout<<n<<endl;
	while (n--) {
		cout<<rand()*300000ll+rand()<<endl;
	}
}