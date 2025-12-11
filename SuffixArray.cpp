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
        // used in the comparison of ranks
        bool operator!=(Triple& other)
        {
            return this->r1 != other.r1 || this->r2 != other.r2;
        }
    };

    Triple* arr;

    static bool CompareByRank(const Triple& a, const Triple& b)
    {
        if (a.r1 == b.r1) return a.r2 < b.r2;
        return a.r1 < b.r1;
    }

    static bool CompareByIndex(const Triple& a, const Triple& b)
    {
        return a.ind < b.ind;
    }
    
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

    // Simple pseudo-random generator
    unsigned int randState = 123456789;  // seed

    int RandomInt(int l, int r)
    {
        randState = randState * 1664525 + 1013904223; // LCG formula
        unsigned int val = randState % (r - l + 1);
        return l + val;
    }

    // Partition function for quicksort
    Triple* Partition(Triple* start, Triple* end, bool (*comp)(const Triple&, const Triple&))
    {
        // Random pivot
        int len = end - start;
        int pivotIndex = RandomInt(0, len - 1);
        Triple pivot = start[pivotIndex];

        // Move pivot to end
        start[pivotIndex] = start[len - 1];
        start[len - 1] = pivot;

        int i = 0; // pointer for the element smaller than pivot

        for (int j = 0; j < len - 1; j++)
        {
            if (comp(start[j], pivot))
            {
                // swap start[i] and start[j]
                Triple temp = start[i];
                start[i] = start[j];
                start[j] = temp;
                i++;
            }
        }

        // Place pivot in correct position
        start[len - 1] = start[i];
        start[i] = pivot;

        return start + i;
    }

    // Quicksort recursive function
    void QuickSort(Triple* start, Triple* end, bool (*comp)(const Triple&, const Triple&))
    {
        if (start >= end || start + 1 == end)
            return;

        Triple* pivotPos = Partition(start, end, comp);
        QuickSort(start, pivotPos, comp);
        QuickSort(pivotPos + 1, end, comp);
    }

    void sort(bool (*comp)(const Triple& , const Triple&))
    {
        QuickSort(this->arr, this->arr+length, comp);
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
        // get the initial ranks
        this->computeInitialOrders();
        
        bool cont = true; // used to terminate the loop of the prefix doubling
        for (int k = 1; cont; k <<= 1)
        {
            // update values of r2 
            // we started with r2 as we already have the array with sorted indices and r1
            // thands to the freq array
            for (int i = 0; i < length; i++) 
            {
                // taking care of indices 
                // (I know we could have made use of garbage values but I am afraid of seg faults)
                arr[i].r2 = i+k < length ? arr[i+k].r1 : inf;
            }

            // sort by rank to move to the next comparison
            sort(CompareByRank);

            int newRank = 0;
            Triple prevT = arr[0];
            for (int i = 1; i < length; i++)
            {
                // if an element is the same as its prevoius, no new rank is given
                if (arr[i] != prevT)
                    newRank++;

                prevT = arr[i]; // storing the proper previous value
                arr[i].r1 = newRank; // update after store so we compare with the real prevoius
                    
                     
                if (arr[i].r1 == length-1)
                {
                    // that means we have reached the last suffix
                    //  so there is no two suffix with the same order
                    cont = false;
                }
            }
            // sort by index so that we can update r2 properly in the next iteration
            sort(CompareByIndex);
        }

        // constructing the real suffix array
        for (int i = 0; i < length; i++)
        {
            suffixes[arr[i].r1] = arr[i].ind;
        }
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
    /*
        ****************************************************************************************
        elly haysalem yshel elmain 3shan el-doctor 2al don't include the main in your submission
        ****************************************************************************************
    */
    SuffixArray t("ACGACTACGATAAC$");
    t.ConstructUsingPrefixDoubling();
    t.Print();
}