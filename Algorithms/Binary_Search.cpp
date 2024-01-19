#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

bool Binary_Search(std::vector<int> arr, int number)
{
 int low = 0;
 int high = arr.size();

    while( low < high)
    {
        const int midpoint = floor(low + (high - low) / 2);
        const int v = arr[midpoint];

        if(v == number)
        {
            return true;
        }
        else if (v > number)
        {
            high = midpoint;
        }
        else
        {
            low = midpoint + 1;
        }
    }
    return false;

}




int main()
{


std::vector<int> arr;

std::cout << "Enter the size of array: " << '\n';

int k;
std::cin >> k;

std::cout << "Enter the numbers " << '\n';

for( int i = 0; i < k; i++)
{
    int n;
    std::cin >> n;
    arr.push_back(n);
}

// in Binary_Search, array/vector has to be sorted
std::sort(arr.begin(), arr.end());

std::cout << "Search for a number: " << '\n';
int l;
std::cin >> l;

bool res = Binary_Search(arr, l);

if(res == true)
{
    std::cout << "FOUND" << '\n';
}
else
{
    std::cout << "NOT FOUND" << '\n';
}



std::cin.get();
}