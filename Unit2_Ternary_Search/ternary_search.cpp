#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Ternary Search Function
int ternarySearch(const vector<string>& playlist, const string& target, int left, int right) {
    if (right >= left) {

        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        if (playlist[mid1] == target)
            return mid1;

        if (playlist[mid2] == target)
            return mid2;

        if (target < playlist[mid1])
            return ternarySearch(playlist, target, left, mid1 - 1);

        else if (target > playlist[mid2])
            return ternarySearch(playlist, target, mid2 + 1, right);

        else
            return ternarySearch(playlist, target, mid1 + 1, mid2 - 1);
    }

    return -1;
}

int main() {

    // Alphabetically sorted playlist (required for ternary search)
    vector<string> playlist = {
        "A Warning (Remastered 2022)",
        "Ankh Udja Seneb (feat. Lawa)",
        "Aveceitos (feat. Shira Netanya & Avi Burg)",
        "Gentleman",
        "Insum",
        "Intro (Live)",
        "Kaiser",
        "Kundalini Rising",
        "Live Your Life",
        "Nahra",
        "Romano",
        "Scheiße (DJ White Shadow Mugler)",
        "Sol Tapado (feat. Patrick de Santos)",
        "The Foundation (Remastered 2022)",
        "The Movie"
    };

    string song;
    cout << "Enter song to search: ";
    getline(cin, song);

    int result = ternarySearch(playlist, song, 0, playlist.size() - 1);

    if (result != -1)
        cout << "Song found at index: " << result << endl;
    else
        cout << "Song not found." << endl;

    return 0;
}

/*
========================
Part 2 – Time Complexity
========================

The ternary search algorithm divides the playlist into three sublists at each step.
Each recursive call reduces the problem size to approximately n/3 while performing
constant work.

Recurrence:
T(n) = T(n/3) + O(1)

Therefore, the time complexity is:
O(log n)

Binary search divides into two sublists per step:
T(n) = T(n/2) + O(1)

Binary search is also:
O(log n)

Thus, both ternary search and binary search have logarithmic time complexity,
though binary search may perform slightly fewer comparisons in practice.
*/