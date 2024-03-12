/*In C++, a hash map is a data structure that contains a collection of unique elements in the form of key-value pairs. 
Elements of a hash map are identified by key values, while the mapped values are the content associated with the keys.

Each element of a map or unordered_map is an object of type pair. A pair object has two member variables:
The following methods apply to both unordered_map and map:

.insert(): add an element to the map.
.erase(): removes an element from the map.
.count(): check whether an element exists in the map.
.size(): return the size of the map.
[] operator:
If the specified key matches an element in the map, then access the mapped value associated with that key.
If the specified key doesn’t match any element in the map, add a new element to the map with that key.

std::map is typically implemented as a self-balancing binary search tree (usually a Red-Black Tree).
This ensures that the elements are always sorted by their keys.
std::unordered_map, on the other hand, is implemented as a hash table. 
It does not maintain any particular order of elements; instead, it provides fast access to elements using a hash function.*/

#include <iostream>
#include <unordered_map>
#include <map>

int main() {
  std::unordered_map<std::string, int> country_codes;

  country_codes.insert({"Thailand", 65});
  country_codes.insert({"Peru", 51});
  country_codes["Japan"] = 81;		// Add a new element
  country_codes["Thailand"] = 66; // Access an element
  
  country_codes.erase("Peru");
  
  // Outputs: There isn't a code for Belgium
  if (country_codes.count("Belgium")) {
    std::cout << "There is a code for Belgium\n";
  }
  else {
   std::cout << "There isn't a code for Belgium\n";
  }

  // Outputs: 81
  std::cout << country_codes["Japan"] << "\n";
  
  // Outputs: 2
  std::cout << country_codes.size() << "\n";
  
  // Outputs: Japan 81
  //          Thailand 66
  for(auto it: country_codes){
    std::cout << it.first << " " << it.second << "\n";
  }
  
  return 0;
}
