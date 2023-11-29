#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

int main()
{
    fstream file;
    string radek;
    int freq = 0;
    unordered_set<int> seen_frequencies;
    bool found = false;

    while (!found)
    {
        file.open("inut.txt", ios::in);
        if (file.is_open())
        {
            while (getline(file, radek))
            {
                freq += stoi(radek);
                if (seen_frequencies.find(freq) != seen_frequencies.end())
                {
                    found = true;
                    cout << "First frequency reached twice: " << freq << endl;
                    break;
                }
                seen_frequencies.insert(freq);
            }
            file.close();
        }
    }
}