// Copyright (C) 2013 Paul Ilardi (code@pilardi.com)
// 
// Permission is hereby granted, free of charge, to any person obtaining a 
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation 
// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the 
// Software is furnished to do so, unconditionally.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
// DEALINGS IN THE SOFTWARE.

#include "MultikeyMap.h"
#include <iostream>

using namespace std;

int main(){
	typedef MultikeyMap<int, int, int> MMiii; 
	MMiii mmap;

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

	for(MMiii::iterator i=mmap.begin(); i!=mmap.end(); i++){
		int key1 = i->first.first;
		int key2 = i->first.second;
		int value = i->second;
		cout << key1 << " " << key2 << " " << value << endl; 
	}

	try{
		mmap.get1(10);
	}catch(...){
		cout << "Expected exception caught\n";
	}

	mmap.erase1(4);
	mmap.erase2(8);

	getchar();
}