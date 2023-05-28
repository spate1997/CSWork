#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// Gauss-Seidel method to solve a linear system Ax = b
pair<vector<double>, int> gauss_seidel(vector<vector<double>> A, vector<double> b, vector<double> x0, double tol=1e-5, int max_iter=1000)
{
    int n = b.size();
    vector<double> x = x0;
    vector<double> x_new(n);
    for (int k = 0; k < max_iter; k++)
    {
        for (int i = 0; i < n; i++)
        {
            double sum1 = 0;
            double sum2 = 0;
            for (int j = 0; j < i; j++)
            {
                sum1 += A[i][j] * x_new[j];
            }
            for (int j = i+1; j < n; j++)
            {
                sum2 += A[i][j] * x[j];
            }
            x_new[i] = (b[i] - sum1 - sum2) / A[i][i];
        }
        bool converged = true;
        for (int i = 0; i < n; i++)
        {
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
    throw runtime_error("Gauss-Seidel failed to converge");
}

int main()
{
    // Open the input file for reading
    ifstream infile("q14_data.txt");
    if (!infile.is_open())
    {
        cerr << "Unable to open input file" << endl;
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
        pair<vector<double>, int> solution = gauss_seidel(A, b, x0);
        vector<double> x = solution.first;
        int iterations = solution.second;

        // Open the output file for writing
        ofstream outfile("q14_solution.txt");
        if (!outfile.is_open())
        {
            cerr << "Unable to open output file" << endl;
            return 1;
        }

        // Write the solution vector to the output file
        outfile << "Solution :" << endl;
        for (int i = 0; i < n; i++)
        {
            outfile << x[i] << endl;
        }

        // Write the number of iterations required to solve the system to the output file
        outfile << "Total iterations: " << iterations << endl;

        // Close the output file
        outfile.close();

    }
    catch (runtime_error& e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

