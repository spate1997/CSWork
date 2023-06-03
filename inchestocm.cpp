#include <iostream>
using namespace std;

double convertInchesToCentimeters(double inches) 
{
    const double conversionFactor = 2.54;
    return inches * conversionFactor;
}

int main() 
{
    double inches;

    cout << "Please enter the distance in inches: ";
    cin >> inches;

    double centimeters = convertInchesToCentimeters(inches);

    cout << "The distance in centimeters is " << centimeters << " cm." << endl;

    return 0;
}
