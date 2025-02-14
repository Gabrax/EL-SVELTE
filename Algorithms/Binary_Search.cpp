#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

constexpr bool Binary_Search(const std::vector<int>& arr, int target)
{
    int low = 0;
    int high = arr.size()-1;

    while(low < high)
    {
        const int midpoint = low + ((high - low) / 2);

        if(arr[midpoint] == target) return true;
        else if (arr[midpoint] > target) high = midpoint;
        else low = midpoint + 1;
    }
    return false;
}

constexpr int Rec_BinSearch(const std::vector<int>& arr, int lo, int hi)
{
    if(lo == hi)
    {
        return arr[lo];
    }

    int mid = (lo + hi)/2;

    if(arr[mid] < arr[mid + 1]) // change to ">" to search for smallest value
    {
        return Rec_BinSearch(arr, mid+1,hi);
    }
    else
    {
        return Rec_BinSearch(arr,lo,mid);
    }

}



int main()
{

  std::vector<int> arr = {4,2,3,1,5,25};

  std::sort(arr.begin(), arr.end());

  std::cout << Binary_Search(arr, 5) << '\n';

  //Recursive Binary Search
  std::cout << Rec_BinSearch(arr,0,arr.size()-1); 
}
