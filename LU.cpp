#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

// Function to perform LU decomposition
void lu_decomposition(const vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U)
{
    int n = A.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            double sum = 0;
            for (int k = 0; k < i; k++)
            {
                sum += L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - sum;
        }
        for (int j = i; j < n; j++)
        {
            if (i == j)
            {
                L[i][i] = 1;
            } else
            {
                double sum = 0;
                for (int k = 0; k < i; k++)
                {
                    sum += L[j][k] * U[k][i];
                }
                L[j][i] = (A[j][i] - sum) / U[i][i];
            }
        }
    }
}

// Function to solve a lower triangular system Lx = b
vector<double> forward_substitution(const vector<vector<double>>& L, const vector<double>& b)
{
    int n = L.size();
    vector<double> x(n);
    for (int i = 0; i < n; i++)
    {
        double sum = 0;
        for (int j = 0; j < i; j++)
        {
            sum += L[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / L[i][i];
    }
    return x;
}

// Function to solve an upper triangular system Ux = b
vector<double> back_substitution(const vector<vector<double>>& U, const vector<double>& b)
{
    int n = U.size();
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i + 1; j < n; j++)
        {
            sum += U[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / U[i][i];
    }
    return x;
}

int main()
{
    // Open the input file for reading
    ifstream infile("q12_data.txt");
    if (!infile.is_open())
    {
        cerr << "Error: Unable to open input file" << endl;
        return 1;
    }

    // Read the problem data
    int n;
    infile >> n;
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            infile >> A[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        infile >> b[i];
    }

    // Close the input file
    infile.close();

    // Perform LU decomposition
    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));
    lu_decomposition(A, L, U);

    // Solve the lower triangular system Ly = b
    vector<double> y = forward_substitution(L, b);
    // Solve the upper triangular system Ux = y
    vector<double> x = back_substitution(U, y);

// Print the solution
cout << "Solution:" << endl;
    for (int i = 0; i < n; i++)
{
        cout << x[i] << endl;
}

return 0;
}
