#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int rowDifference(const vector<int>& X, const vector<int>& Y)
{
    int J = X.size();
    int K = Y.size();

    vector<vector<int>> D(J + 1, vector<int>(K + 1));

    for(int j = 0; j <= J; j++)
        D[j][0] = j;

    for(int k = 0; k <= K; k++)
        D[0][k] = k;

    for(int j = 1; j <= J; j++)
    {
        for(int k = 1; k <= K; k++)
        {
            int cost = (X[j-1] == Y[k-1]) ? 0 : 1;

            D[j][k] = min({
                D[j-1][k-1] + cost,
                D[j-1][k] + 1,
                D[j][k-1] + 1
            });
        }
    }

    int minVal = D[J][0];

    for(int k = 1; k <= K; k++)
        minVal = min(minVal, D[J][k]);

    return minVal;
}

int main()
{
    vector<vector<int>> X =
    {
        {0,0,1,1,0},
        {1,1,0,0,1},
        {0,0,1,1,1}
    };

    vector<vector<int>> Y =
    {
        {0,0,1,1,0},
        {0,1,0,0,1},
        {1,0,1,1,1}
    };

    int thresh = 3;

    int totalDifference = 0;

    for(int i = 0; i < X.size(); i++)
    {
        int minVal = rowDifference(X[i], Y[i]);
        totalDifference += minVal;
    }

    cout << "Total Difference: " << totalDifference << endl;

    if(totalDifference > thresh)
    cout << "Not hot dog" << endl;
else
    cout << "Hot dog" << endl;

return 0;
}