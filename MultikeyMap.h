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

#include <map>
#include <stdexcept>

// MultikeyMap: Similar to std::map, but with two keys

template <typename Key1, typename Key2, typename ValType>
class MultikeyMap{
public:

	// typedefs used below
	typedef std::pair<Key1,Key2> KeyPair;
	typedef std::pair<const KeyPair, ValType> KeyPairVal;
	typedef typename std::map<KeyPair, ValType>::iterator iterator;

	// Implementation of standard map methods (method # refers to which key)
	int count1(const Key1& key1){ return map1.count(key1); }
	int count2(const Key2& key2){ return map2.count(key2); }
	iterator begin(){ return mainMap.begin(); }
	iterator end()  { return mainMap.end();   }
	iterator find1(const Key1& key1){ return mainMap.find(map1.at(key1)); }
	iterator find2(const Key2& key2){ return mainMap.find(map2.at(key2)); }
	size_t size(){ return mainMap.size(); }
	KeyPairVal& at1(const Key1& key1) { return *find1(key1); }
	KeyPairVal& at2(const Key2& key2) { return *find2(key2); }

	// Insert value into map with two keys
	void insert(const Key1& key1, const Key2& key2, const ValType& val){
		KeyPair kp = make_pair(key1,key2);
		map1[key1] = kp;
		map2[key2] = kp;
		mainMap[kp] = val;
	}

	// Erases entry from map matching keypair 
	// Note: keypair passed by copy because its deleted
	void erase(const KeyPair kp){ 
		map1.erase(kp.first);
		map2.erase(kp.second);
		mainMap.erase(kp);
	}

	// Erases entry from map matching key1
	void erase1(const Key1& key1){
		if(!map1.count(key1)) return;
		erase(map1[key1]);
	}

	// Erases entry from map matching key2
	void erase2(const Key2& key2){
		if(!map2.count(key2)) return;
		erase(map2[key2]);
	}

private:
	// Maps keypair to value
	std::map<KeyPair, ValType> mainMap;
	// Maps key1 to keypair
	std::map<Key1, KeyPair>    map1;
	// Maps key2 to keypair
	std::map<Key2, KeyPair>    map2;

};

