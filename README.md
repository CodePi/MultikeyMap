# MultikeyMap
Similar to std::map but indexable by two keys.  Header-only.

Compiles with C++11 compatible compilers. Tested with gcc 4.7-9.0 and Visual Studio 2012.

### Example usage
``` cpp
  MultikeyMap < int, string, string > mm = {
    {1, "a", "red" },
    {2, "b", "green" },
    {2, "c", "blue" },
    {4, "c", "purple" }
  };

  mm.insert(5, "a", "yellow");

  cout << "Enumeration:\n";
  for(auto i = mm.begin1(); i != mm.end1(); i++){
    auto& e = i->second;
    cout << e->key1 << " " << e->key2 << " " << e->val << endl;
  }

  cout << "mm.count1(1): " << mm.count1(1) << endl;
  cout << "mm.count2(\"c\"): " << mm.count2("c") << endl;

  cout << "mm.get1(4)[0]->val: " << mm.get1(4)[0]->val << endl;

  cout << "all entries where key2==c\n";
  for(auto& e : mm.get2("c")){
    cout << e->key1 << " " << e->key2 << " " << e->val << endl;
  }
```

#### Useful methods
``` cpp
template <typename Key1, typename Key2, typename ValType>
class MultikeyMap{
public:

  // basic map entry
  struct Entry {
    Key1 key1;
    Key2 key2;
    ValType val;
  };

  // Constructor
  MultikeyMap(std::initializer_list<Entry> list);
  
  // Insert value into map with two keys
  void insert(const Key1& key1, const Key2& key2, ValType&& val);
  void insert(const Key1& key1, const Key2& key2, const ValType& val);
  void insert(Entry&& entry);  
  void insert(const Entry& entry);  

  // gets a list of all entries matching key1
  std::vector<EntryPtr> get1(const Key1& key1);
  
  // gets a list of all entries matching key2
  std::vector<EntryPtr> get2(const Key2& key2);
  
  // gets a list of all entries matching key1 and key2
  std::vector<EntryPtr> get(const Key1& key1, const Key1& key2);
  
  // erases entry matching EntryPtr
  void erase_entry(EntryPtr e);
  
  // erases each entry in list
  void erase_entry_list(const std::vector<EntryPtr>& list);
  
  // erase of all entries matching key
  void erase1(const Key1& key1);
  void erase2(const Key2& key2);
  void erase(const Key1& key1, const Key2& key2);

  // return number of entries matching key
  int count1(const Key1& key1);
  int count2(const Key2& key2);
  int count(const Key1& key1, const Key2& key2);

  // Implementation of standard map methods
  size_t      size();
  bool       empty();
  iterator   begin();
  iterator     end();
  iterator1 begin1();
  iterator1   end1();
  iterator2 begin2();
  iterator2   end2();
  void       clear();
};
```
