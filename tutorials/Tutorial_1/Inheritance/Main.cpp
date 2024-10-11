#include <iostream>
#include "BankAccount.h"

using namespace std;

int main()
{
	cout << "A simple bank account simulation\n" << endl;

	BankAccount account(1234567890, 100.0, 0.05);
	cout << "Initial balance: " << account.getBalance() << endl;
	cout << "Initial interest rate: " << account.getInterestRate() << endl;

	account.deposit(1000.0);
	cout << "After depositing 1000.0: " << account.getBalance() << endl;

	account.withdraw(500.0);
	cout << "After withdrawing 500.0: " << account.getBalance() << endl;

	account.creditInterest();
	cout << "After crediting interest: " << account.getBalance() << endl;

	account.applyServiceFee(10.0);
	cout << "After applying service fee: " << account.getBalance() << endl;
	return 0;
}