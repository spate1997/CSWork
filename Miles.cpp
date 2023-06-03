#include <iostream>
using namespace std;

double convertMilesToKilometers(double miles) 

{
    const double conversionFactor = 1.60934;
    return miles * conversionFactor;
}

int main() 

{
    double miles;

    cout << "Please enter the distance in miles: ";
    cin >> miles;

    double kilometers = convertMilesToKilometers(miles);

    cout << "The distance in kilometers is " << kilometers << " km." << endl;

    return 0;
}
