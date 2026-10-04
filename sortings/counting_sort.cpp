#include <vector>
#include <iostream>
#include <algorithm>

std::vector<int> counting_sort(const std::vector<int> &vec, int rank)
{
    if (vec.size() < 2)
    {
        return vec;
    }
    std::vector<int> counts(10, 0);
    for (int elem : vec)
    {
        counts[(elem/rank)%10]++;
    }
    for (int i = 1; i < counts.size(); ++i)
    {
        counts[i] += counts[i - 1];
    }
    std::vector<int> result(vec.size());
    for (int i = vec.size()-1; i >= 0; i--) {
        result[--counts[(vec[i]/rank)%10]] = vec[i];
    }
    return result;
}

std::vector<int> radix_sort(std::vector<int> vec) {
    if (vec.size() < 2) return vec;

    int min_elem = *std::min_element(vec.begin(), vec.end());
    int offset = (min_elem < 0) ? -min_elem : 0;

    for (int &x : vec) x += offset;

    int max_elem = *std::max_element(vec.begin(), vec.end());
    int rank = 1;
    while (max_elem > 0) {
        vec = counting_sort(vec, rank);
        max_elem /= 10;
        rank *= 10;
    }

    for (int &x : vec) x -= offset;
    return vec;
}


int main(void)
{
    std::vector<int> test = {11, 0, -7, 2, 300, 0, 3};
    for (int elem : radix_sort(test))
    {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}