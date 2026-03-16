#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct FileItem {
    int originalIndex;
    int size;
};

int main() {
    // Example input
    int n = 8;
    int m = 4;

    vector<int> fileSizes = {400, 350, 300, 250, 200, 150, 100, 50};
    vector<int> diskCapacities = {700, 600, 500, 400};

    vector<int> remaining = diskCapacities;
    vector<int> map(n, -1);

    vector<FileItem> files;
    for (int i = 0; i < n; i++) {
        files.push_back({i, fileSizes[i]});
    }

    // Sort files in decreasing order
    sort(files.begin(), files.end(), [](const FileItem& a, const FileItem& b) {
        return a.size > b.size;
    });

    // Best-Fit Decreasing Greedy Algorithm
    for (const auto& file : files) {
        int bestDisk = -1;
        int smallestWaste = INT_MAX;

        for (int j = 0; j < m; j++) {
            if (remaining[j] >= file.size) {
                int waste = remaining[j] - file.size;
                if (waste < smallestWaste) {
                    smallestWaste = waste;
                    bestDisk = j;
                }
            }
        }

        if (bestDisk != -1) {
            map[file.originalIndex] = bestDisk;
            remaining[bestDisk] -= file.size;
        }
    }

    cout << "Greedy Disk Allocation Result" << endl;
    cout << "-----------------------------" << endl;

    for (int i = 0; i < n; i++) {
        cout << "File " << i
             << " (" << fileSizes[i] << " MB) -> Disk "
             << map[i] << endl;
    }

    cout << endl;
    cout << "Remaining disk space:" << endl;
    for (int j = 0; j < m; j++) {
        cout << "Disk " << j << ": " << remaining[j] << " MB left" << endl;
    }

    return 0;
}