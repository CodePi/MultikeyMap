#include <map>
#include <stdexcept>

// MultikeyMap: Similar to std::map, but with two keys

template <typename Key1, typename Key2, typename ValType>
class MultikeyMap{
public:

	// typedefs used below
	typedef std::pair<Key1,Key2> KeyPair;
	typedef std::pair<const KeyPair, ValType> KeyPairVal;

	// Insert value into map with two keys
	void insert(const Key1& key1, const Key2& key2, const ValType& val){
		KeyPair kp = make_pair(key1,key2);
		map1[key1] = kp;
		map2[key2] = kp;
		mainMap[kp] = val;
	}

	// Retrieve entry by key1 
	KeyPairVal& get1(const Key1& key1){
		return *mainMap.find(map1.at(key1));
	}

	// Retrieve entry by key2 
	KeyPairVal& get2(const Key2& key2){
		return *mainMap.find(map2.at(key2));
	}

	// Returns 1 if key1 exists (0 otherwise)
	int count1(const Key1& key1){
		return map1.count(key1);
	}

	// Returns 1 if key2 exists (0 otherwise)
	int count2(const Key2& key2){
		return map2.count(key2);
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
	std::map<Key1, KeyPair>      map1;
	// Maps key2 to keypair
	std::map<Key2, KeyPair>      map2;

};

