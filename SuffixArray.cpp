/******************************************************
 * IDs:
 * Names:
 *
 * Suffix Array – Prefix Doubling Construction
 *****************************************************/

#include <iostream>
#define inf int(1e9)
using namespace std;

class SuffixArray
{
private:

    char* txt;
    int length;
    int* suffixes;

    struct Triple
    {
        int ind;
        int r1;
        int r2;
    };

    Triple* arr;
    
    void computeInitialOrders()
    {
        int n = 128; // number of ASCII characters
        short* freq = new short[n] {}; // all the frequencies are initialized with 0

        // assigning the occurred elements in txt to 1,
        // so that we know them then we can construct their order form the freq array
        for (int i = 0; i < this->length; i++)
        {
            if (!freq[txt[i]]) freq[txt[i]]++;
        }

        int order = 0;
        // assigning each element to its order
        for (int i = 0; i < n; i++) 
        {
            if (freq[i]) 
                freq[i] = order++;
        }
        // now we have an array that takes the char and return its order
        
        // constructing the initial array
        for (int i = 0; i < length; i++) 
        {
            arr[i].ind = i;
            arr[i].r1 = freq[txt[i]];
            arr[i].r2 = -inf;
        }
    }
public:

    SuffixArray(const char* str)
    {
        length = 0;
        // counting characters of the original string 
        while(str[length] != '\0') length++;

        // length + 1 to include the terminator '\0' which we didn't count 
        txt = new char[length+1];
        
        suffixes = new int[length];
        arr = new Triple[length];
        // copying the characters 
        for (int i = 0; i < length; i++)
            txt[i] = str[i];
        
        // adding the terminator 
        txt[length] = '\0'; 

    }

    ~SuffixArray()
    {
        delete[] txt;
        delete[] suffixes;
        delete[] arr;
    }

    void ConstructUsingPrefixDoubling()
    {
        this->computeInitialOrders();
        
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
        for (int i = 0; i < length; i++)
        {
            cout << suffixes[i] << " ";
        }
    }
};


int main() 
{
    SuffixArray t("pappatpappatpappa$");
    t.ConstructUsingPrefixDoubling();
}