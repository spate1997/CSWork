#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// Jacobi method to solve a linear system Ax = b
pair<vector<double>, int> jacobi(vector<vector<double>> A, vector<double> b, vector<double> x0, double tol=1e-5, int max_iter=1000) {
    int n = b.size();
    vector<double> x = x0;
    vector<double> x_new(n);
    for (int k = 0; k < max_iter; k++)
    {
    for (int i = 0; i < n; i++)
        {
    double sum = 0;
    for (int j = 0; j < n; j++)
        {
        if (j != i)
        {
        sum += A[i][j] * x[j];
        }
        }
        x_new[i] = (b[i] - sum) / A[i][i];
        }
        bool converged = true;
        for (int i = 0; i < n; i++) {
        if (fabs(x_new[i] - x[i]) > tol)
            {
            converged = false;
            break;
            }
        }
        if (converged)
        {
        return make_pair(x_new, k+1);
        }
        x = x_new;
    }
    throw runtime_error("Jacobi method failed to converge");
}

int main()
{
    // Open the input file for reading
    ifstream infile("q10.txt");
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

    // Solve the linear system
    try
    {
        vector<double> x0(n, 0);
        pair<vector<double>, int> solution = jacobi(A, b, x0);
        vector<double> x = solution.first;
        int iterations = solution.second;

        // Print the solution vector
        cout << "Solution:" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << x[i] << endl;
        }

        // Print the number of iterations required to solve the system
        cout << "Iterations: " << iterations << endl;
    }

    catch (runtime_error& e)

    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

