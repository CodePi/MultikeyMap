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
#include <vector>

// MultikeyMap: Similar to std::multimap, but with two keys

template <typename Key1, typename Key2, typename ValType>
class MultikeyMap{
public:

	// typedefs used below
	typedef std::pair<Key1,Key2> KeyPair;
	typedef std::pair<const KeyPair, ValType> KeyPairVal;
	typedef typename std::multimap<KeyPair, ValType>::iterator iterator;

	// Insert value into map with two keys
	void insert(const Key1& key1, const Key2& key2, const ValType& val){
		KeyPair kp = make_pair(key1,key2);
		map1.insert(make_pair(key1,kp));
		map2.insert(make_pair(key2,kp));
		mainMap.insert(make_pair(kp,val));
	}

	// gets a list of all entries matching key1
	std::vector<iterator> get1(const Key1& key1){
		vector<iterator> vec;
		typename std::multimap<Key1, KeyPair>::iterator i;
		for(i = map1.lower_bound(key1); i != map1.upper_bound(key1); i++){
			KeyPair& kp = i->second;
			for(iterator j = mainMap.lower_bound(kp); j != mainMap.upper_bound(kp); j++){
				vec.push_back(j);
			}
		}
		return vec;
	}

	// gets a list of all entries matching key2
	std::vector<iterator> get2(const Key2& key2){
		vector<iterator> vec;
		typename std::multimap<Key2, KeyPair>::iterator i;
		for(i = map2.lower_bound(key2); i != map2.upper_bound(key2); i++){
			KeyPair& kp = i->second;
			for(iterator j = mainMap.lower_bound(kp); j != mainMap.upper_bound(kp); j++){
				vec.push_back(j);
			}
		}
		return vec;
	}

	// erase of all entries matching key1
	void erase1(const Key1& key1) { 
		std::vector<iterator> vec = get1(key1);
		for(size_t i=0;i<vec.size();i++){
			mainMap.erase(vec[i]);
		}
		map1.erase(key1);
	}

	// erase of all entries matching key2
	void erase2(const Key2& key2) { 
		std::vector<iterator> vec = get2(key2);
		for(size_t i=0;i<vec.size();i++){
			mainMap.erase(vec[i]);
		}
		map2.erase(key2);
	}

	// erase all entries in all 3 maps matching keypair
	void erase_keypair(const KeyPair& kp){
		mainMap.erase(kp);

		// erase from map1
		typename std::multimap<Key1, KeyPair>::iterator i1 = map1.lower_bound(kp.first);
		while(i1 != map1.upper_bound(kp.first)){
			if(kp == i1->second) i1=map1.erase(i1);
			else i1++;
		}

		// erase from map2
		typename std::multimap<Key2, KeyPair>::iterator i2 = map2.lower_bound(kp.second);
		while(i2 != map2.upper_bound(kp.second)){
			if(kp == i2->second) i2=map2.erase(i2);
			else i2++;
		}
	}

	// return number of entries matching key
	int count1(const Key1& key1) { return map1.count(key1); }
	int count2(const Key2& key2) { return map2.count(key2); }

	// Implementation of standard map methods
	size_t    size() { return mainMap.size();    }
	bool     empty() { return mainMap.size()==0; }
	iterator begin() { return mainMap.begin();   }
	iterator   end() { return mainMap.end();     }

private:
	// Maps keypair to value
	std::multimap<KeyPair, ValType> mainMap;
	// Maps key1 to keypair
	std::multimap<Key1, KeyPair>    map1;
	// Maps key2 to keypair
	std::multimap<Key2, KeyPair>    map2;
};

