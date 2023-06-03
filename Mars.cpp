#include <iostream>
using namespace std;

double calculateMarsWeight(double earthWeight)

{
    const double marsGravity = 0.38;
    return earthWeight * marsGravity;
}

int main()

{
    double earthWeight;

    cout << "Please enter the weight of the item on Earth (in kg): ";
    cin >> earthWeight;

    double marsWeight = calculateMarsWeight(earthWeight);

    cout << "The weight would be " << marsWeight << " kg on Mars." << endl;

    return 0;
}
