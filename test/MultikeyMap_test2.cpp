#include "../MultikeyMap.h"
#include <iostream>

using namespace std;
using namespace codepi;

int main(){
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
}
