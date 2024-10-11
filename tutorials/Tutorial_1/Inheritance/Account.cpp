#include "Account.h"

Account::Account(unsigned long long aNumber, double aBalance)
{
	fNumber = aNumber;
	fBalance = aBalance;
}

bool Account::deposit(double aAmount)
{
	fBalance += aAmount;
	return true;
}

bool Account::withdraw(double aAmount)
{
	fBalance -= aAmount;
	return true;
}

double Account::getBalance() const
{
	return fBalance;
}