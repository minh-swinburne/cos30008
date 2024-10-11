#include "BankAccount.h"

BankAccount::BankAccount(unsigned long long aNumber, 
							double aBalance, 
							double aInterestRate)
	: Account(aNumber, aBalance)
{
	fInterestRate = aInterestRate;
}

bool BankAccount::withdraw(double aAmount)
{
	if (Account::getBalance() >= aAmount)
	{
		return Account::withdraw(aAmount);
	}
	return false;
}

void BankAccount::setInterestRate(double aInterestRate)
{
	fInterestRate = aInterestRate;
}

double BankAccount::getInterestRate() const
{
	return fInterestRate;
}

bool BankAccount::creditInterest()
{
	double interest = getBalance() * fInterestRate;
	return deposit(interest);
}

bool BankAccount::applyServiceFee(double aFee)
{
	return withdraw(aFee);
}