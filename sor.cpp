//libraries 
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

// SOR method to solve a linear system Ax = b
pair<vector<double>, int> sor(vector<vector<double>> A, vector<double> b, vector<double> x0, double omega, double tol=1e-5, int max_iter=1000)
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
            x_new[i] = (1 - omega) * x[i] + (omega / A[i][i]) * (b[i] - sum1 - sum2);
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
    throw runtime_error("SOR failed to converge");
}

int main()
{
    // Open the input file for reading
    ifstream infile("q13_data.txt");
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

    // Initialize the starting solution vector
    vector<double> x0(n, 0);

    // Display the results in a table
    cout << "Omega   Iterations" << endl;
    cout << "------------------" << endl;
    for (double omega = 1.05; omega <= 1.5; omega += 0.05)
        {
        try
        {
            pair<vector<double>, int> solution = sor(A, b, x0, omega);
            int iterations = solution.second;

            // Display omega and the number of iterations
            cout << fixed << setprecision(2) << omega << "   " << setw(6) << iterations << endl;
        } catch (runtime_error& e)
        {
            cerr << "Error for omega " << omega << ": " << e.what() << endl;
        }
    }

    return 0;
}
