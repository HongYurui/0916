#include <iostream>
#include <vector>
#include "time.h"

using namespace std;

int main() {
	Time t;
	++t;
	cout << t.get(); 
}