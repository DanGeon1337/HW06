//
// Created by Daniil's PC on 4/26/2019.
//

#ifndef HW06_HOMEWORK06_H
#define HW06_HOMEWORK06_H

#endif //HW06_HOMEWORK06_H
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;

class Customer
{
public:

    int arrivalTime;
    int processTime;

    Customer (int at = 0)
            : arrivalTime (at),
              processTime (1) {}

    // are we done with our transaction?
    bool done () {
        return --processTime < 0;
    }

    // order by arrival time
    bool operator< (const Customer& c) const {
        return arrivalTime < c.arrivalTime;
    }
};

class Teller
{
public:
    Teller (): free (true) { }

    bool isFree () {   // are we free to service new customer?
        if (free)
            return true;
        if (customer.done())
            free = true;
        return free;
    }

    // start serving new customer

    void addCustomer (const Customer &c) {
        customer = c;
        free = false;
    }

private:

    bool     free;
    Customer customer;
};

int main ()
{
    const int numberOfTellers = 2;
    const int numberOfMinutes = 10;
    const int custPerMin = 10;
    double totalWait          = 0;
    int numberOfCustomers     = 0;

    vector<Teller> teller (numberOfTellers);
    queue<Customer> line;

    for (int t = 0; t < numberOfMinutes; t++)
    {
        for (int j = 0; j < custPerMin; j++) // 10 Customers per minute
        {
            line.push (Customer (t));
            for (int i = 0; i < numberOfTellers; i++)
            {
                if (teller[i].isFree () && !line.empty ())
                {
                    Customer& frontCustomer = line.front ();
                    numberOfCustomers++;
                    totalWait += t - frontCustomer.arrivalTime;
                    teller[i].addCustomer (frontCustomer);
                    line.pop ();
                }
            }
        }
    }

    cout << "average wait: " << (totalWait / numberOfCustomers) << endl;
}