#include <iostream>
#include <vector>

void InsertionSort(std::vector<int>& array)
{
  for(int i = 1;i < array.size();i++)
  {
      int key = array[i];
      int j = i - 1;
      while(j >= 0 && array[j] > key)
      {
        array[j+1] = array[j];
        j--;
      }
    array[j+1] = key;
  }
}

int main(){

    std::vector<int> vec = {5,2,4,6,1,3};
    InsertionSort(vec);
    for(const auto& i : vec) std::cout << i << " ";

}
