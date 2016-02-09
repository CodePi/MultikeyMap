// Copyright (C) 2013 Paul Ilardi (http://github.com/CodePi)
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

#include "../MultikeyMap.h"
#include <iostream>
#include <assert.h>

using namespace std;
using namespace codepi;

typedef MultikeyMap<int, int, int> MMiii; 

void print_map(MMiii& mmap){
	for(auto& p : mmap){
		cout << p.second->key1 << " " << p.second->key2 << " " << p.second->val << endl; 
	}
	cout << "-----\n";
}

int main(){
	MMiii mmap = { {1,2,3}, {1,2,4}, {4,5,6}, {4,5,7}, {7,8,9} };

	mmap.insert(1,12,13);
	mmap.insert(14,5,16);
	mmap.insert(17,18,19);

	mmap.insert({21,22,23});

	cout << mmap.count1(1) << endl;
	cout << mmap.count1(2) << endl;
	cout << mmap.count2(1) << endl;
	cout << mmap.count2(5) << endl;

	print_map(mmap);
	
	vector<MMiii::EntryPtr> vec1 = mmap.get1(1);
	vector<MMiii::EntryPtr> vec2 = mmap.get2(5);
	cout << vec1.size() << " " <<  vec2.size() << endl;

	mmap.erase1(4);
	mmap.erase2(8);

	print_map(mmap);

	mmap.erase(17,18);

	print_map(mmap);

	#ifdef WIN32
	getchar();
	#endif
}
