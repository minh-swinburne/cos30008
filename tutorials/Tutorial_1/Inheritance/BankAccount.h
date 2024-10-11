#pragma once
#include "Account.h"

class BankAccount : public Account
{
private:
	double fInterestRate;

public:
	BankAccount(unsigned long long aNumber, double aBalance = 0.0, double aInterestRate = 0.0);
	virtual ~BankAccount() {};

	bool withdraw(double aAmount) override;

	void setInterestRate(double aInterestRate);
	double getInterestRate() const;

	bool creditInterest();
	bool applyServiceFee(double aFee);

	// inherited from Account:
	// bool deposit( double aAmount );
	// bool withdraw( double aAmount );
	// double getBalance() const;
};

