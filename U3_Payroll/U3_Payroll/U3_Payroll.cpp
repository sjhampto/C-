//Steven Hampton
//09-4-2020

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{

    //Declare constants
    const double FEDERAL_TAX_RATE = 0.15;
    const double STATE_TAX_RATE = 0.05;

    //Declare variables
    string firstName;
    string lastName;
    int hoursWorked;
    double payPerHour;

    //Prompt user for first name
    cout << "Enter the employee's first name: ";
    cin >> firstName;

    //Prompt user for last name
    cout << "Enter the employee's last name: ";
    cin >> lastName;

    //Create fullName by adding firstName a space and lastName
    string fullName = firstName + " " + lastName;

    //Prompt user for hours worked
    cout << "Enter the number of hours worked by " << fullName << ": ";
    cin >> hoursWorked;

    //Prompt user for rate per hour
    cout << "Enter " << fullName << "'s hourly wage rate: ";
    cin >> payPerHour;

    //Initialize grossPay by multiplying hoursWorked by payPerHour
    double grossPay = hoursWorked * payPerHour;

    //Initialize fedWithheld by multiplying FEDERAL_TAX_RATE by grossPay
    double fedWithheld = FEDERAL_TAX_RATE * grossPay;

    //Initialize stateWithheld by multiplying STATE_TAX_RATE by grossPay
    double stateWithheld = STATE_TAX_RATE * grossPay;

    //Initialize totalWithheld by adding fedWithheld and stateWithheld
    double totalWithheld = fedWithheld + stateWithheld;

    //Initialize netPay by totalWithheld from grossPay
    double netPay = grossPay - totalWithheld;


    //Create final payroll display
    cout << "Payroll information for: " << fullName << endl;
    cout << "Hours worked: " << hoursWorked << endl;
    cout << "Hourly wage rate: " << payPerHour << endl;
    cout << "Gross pay: $" << setprecision(2) << fixed << grossPay << endl;
    cout << "Federal tax withheld: $" << setprecision(2) << fixed << fedWithheld << endl;
    cout << "State tax withheld: $" << setprecision(2) << fixed << stateWithheld << endl;
    cout << "Total tax withheld: $" << setprecision(2) << fixed << totalWithheld << endl;
    cout << "Net pay: $" << setprecision(2) << fixed << netPay << endl;



    /*
    Program should display as below

    Enter the employee's first name: firstName
    Enter the employee's last name: lastName
    Enter the number of hours worked by fullName: hoursWorked
    Enter fullName's hourly wage rate: payPerHour
    Payroll information for: fullName
    Hours worked: hoursWorked
    Hourly wage rate: payPerHour
    Gross pay: grossPay
    Federal tax withheld: fedWithheld
    State tax withheld: stateWithheld
    Total tax withheld: totalWithheld
    Net pay: netPay

    */


    
}
