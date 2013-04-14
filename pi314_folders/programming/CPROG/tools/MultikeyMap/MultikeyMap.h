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
#include <memory>

// MultikeyMap: Similar to std::multimap, but with two keys

template <typename Key1, typename Key2, typename ValType>
class MultikeyMap{
public:

	// basic map entry
	struct Entry {
		Key1 key1;
		Key2 key2;
		ValType val;
	};

	// Typedefs used later
	typedef std::tr1::shared_ptr<Entry> EntryPtr;
	typedef typename std::multimap<Key1, EntryPtr>::iterator iterator1;
	typedef typename std::multimap<Key2, EntryPtr>::iterator iterator2;

	// Insert value into map with two keys
	void insert(const Key1& key1, const Key2& key2, const ValType& val){
		EntryPtr e(new Entry);
		e->key1 = key1;
		e->key2 = key2;
		e->val = val;
		map1.insert(make_pair(key1,e));
		map2.insert(make_pair(key2,e));
	}

	// gets a list of all entries matching key1
	std::vector<EntryPtr> get1(const Key1& key1){
		vector<EntryPtr> vec;
		iterator1 i;
		for(i = map1.lower_bound(key1); i != map1.upper_bound(key1); i++){
			vec.push_back(i->second);
		}
		return vec;
	}

	// gets a list of all entries matching key2
	std::vector<EntryPtr> get2(const Key2& key2){
		vector<EntryPtr> vec;
		iterator2 i;
		for(i = map2.lower_bound(key2); i != map2.upper_bound(key2); i++){
			vec.push_back(i->second);
		}
		return vec;
	}

	// gets a list of all entries matching key1 and key2
	std::vector<EntryPtr> get(const Key1& key1, const Key1& key2){
		vector<EntryPtr> vec;
		iterator1 i;
		for(i = map1.lower_bound(key1); i != map1.upper_bound(key1); i++){
			if(i->second->key2 == key2) vec.push_back(i->second);
		}
		return vec;
	}

	// erases entry matching EntryPtr
	void erase_entry(EntryPtr e){
		// remove entry from map1
		iterator1 i1 = map1.lower_bound(e->key1);
		while(i1 != map1.upper_bound(e->key1)){
			if(i1->second == e) i1 = map1.erase(i1);
			else i1++;
		}

		// remove entry from map2
		iterator2 i2 = map2.lower_bound(e->key2);
		while(i2 != map2.upper_bound(e->key2)){
			if(i2->second == e) i2 = map2.erase(i2);
			else i2++;
		}
	}

	// erases each entry in list
	void erase_entry_list(const std::vector<EntryPtr>& list){
		for(size_t i=0;i<list.size(); i++) erase_entry(list[i]);
	}

	// erase of all entries matching key
	void erase1(const Key1& key1) { erase_entry_list(get1(key1)); }
	void erase2(const Key2& key2) { erase_entry_list(get2(key2)); }
	void erase(const Key1& key1, const Key2& key2) { erase_entry_list(get(key1,key2)); }

	// return number of entries matching key
	int count1(const Key1& key1) { return map1.count(key1); }
	int count2(const Key2& key2) { return map2.count(key2); }

	// Implementation of standard map methods
	size_t      size() { assert(map1.size()==map2.size()); return map1.size(); }
	bool       empty() { return size()==0; }
	iterator1 begin1() { return map1.begin(); }
	iterator1   end1() { return map1.end();   }
	iterator2 begin2() { return map2.begin(); }
	iterator2   end2() { return map2.end();   }
	void       clear() { map1.clear(); map2.clear(); }

private:
	// Maps key1 to keypair
	std::multimap<Key1, EntryPtr> map1;
	// Maps key2 to keypair
	std::multimap<Key2, EntryPtr> map2;
};

