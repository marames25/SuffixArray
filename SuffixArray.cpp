/******************************************************
 * IDs:
 * Names:
 *
 * Suffix Array – Prefix Doubling Construction
 *****************************************************/

#include <iostream>
using namespace std;

class SuffixArray
{
private:

    char* txt;
    int n;
    int* sa;

    struct Triple
    {
        int ind;
        int r1;
        int r2;
    };

    Triple* arr;

public:

    SuffixArray(const char* t)
    {
        // ...
    }

    ~SuffixArray()
    {
        // ...
    }

    void ConstructUsingPrefixDoubling()
    {
        // ...
    }

    static bool CompareByRank(const Triple& a, const Triple& b)
    {
        return false;
    }

    static bool CompareByIndex(const Triple& a, const Triple& b)
    {
        return false;
    }

    void Print() const
    {
        for (int i = 0; i < n; i++)
        {
            cout << sa[i] << " ";
        }
    }
};
