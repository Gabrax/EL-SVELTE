/*In C++, a set is a data structure that contains a collection of unique elements. 
Elements of a set are index by their own values, or keys.

A set cannot contain duplicate elements. 
Once an element has been added to a set, that element cannot be modified.*/

#include <iostream>
#include <unordered_set>
#include <set>

int main()
{
  std::unordered_set<int> primes({2, 3, 5, 7});
  
  primes.insert(11);
  primes.insert(13);
  primes.insert(11);  //Duplicates are not inserted
  
  primes.erase(2);
  primes.erase(13);
  
  // Outputs: primes does not contain 2.
  if(primes.count(2))
    std::cout << "primes contains 2.\n";
  else
    std::cout << "primes does not contain 2.\n";
  
  // Outputs: Size of primes: 4
  std::cout << "Size of primes: " << primes.size() << "\n";
  
  return 0;
}
