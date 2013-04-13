#include <map>
#include <stdexcept>

template <typename K1, typename K2, typename ValType>
class MultikeyMap{
public:
	typedef std::pair<K1,K2> KeyPair;
	typedef std::pair<const KeyPair, ValType> PairPair;

	void insert(const K1& k1, const K2& k2, const ValType& val){
		KeyPair kp = make_pair(k1,k2);
		map1[k1] = kp;
		map2[k2] = kp;
		mainMap[kp] = val;
	}

	PairPair& get1(const K1& k1){
		return *mainMap.find(map1.at(k1));
	}

	PairPair& get2(const K2& k2){
		return *mainMap.find(map2.at(k2));
	}

	int count1(const K1& k1){
		return map1.count(k1);
	}

	int count2(const K2& k2){
		return map2.count(k2);
	}

	void erase(const KeyPair kp){ // need a copy, not ref
		map1.erase(kp.first);
		map2.erase(kp.second);
		mainMap.erase(kp);
	}

	void erase1(const K1& k1){
		if(!map1.count(k1)) return;
		erase(map1[k1]);
	}

	void erase2(const K2& k2){
		if(!map2.count(k2)) return;
		erase(map2[k2]);
	}

private:
	std::map<KeyPair, ValType> mainMap;
	std::map<K1, KeyPair>      map1;
	std::map<K2, KeyPair>      map2;

};

