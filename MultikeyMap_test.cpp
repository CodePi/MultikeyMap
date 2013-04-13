#include "MultikeyMap.h"
#include <iostream>

using namespace std;

int main(){
	MultikeyMap<int, int, int> mmap;

	mmap.insert(1,2,3);
	mmap.insert(4,5,6);
	mmap.insert(7,8,9);


	cout << mmap.get1(1).second << endl;
	cout << mmap.get1(4).second << endl;
	cout << mmap.get1(7).second << endl;
	cout << mmap.get2(2).second << endl;
	cout << mmap.get2(5).second << endl;
	cout << mmap.get2(8).second << endl;
	cout << mmap.count1(1) << endl;
	cout << mmap.count1(2) << endl;
	cout << mmap.count2(1) << endl;
	cout << mmap.count2(2) << endl;

	try{
		mmap.get1(10);
	}catch(...){
		cout << "Expected exception caught\n";
	}

	mmap.erase1(4);
	mmap.erase2(8);

	getchar();
}