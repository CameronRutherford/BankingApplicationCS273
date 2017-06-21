#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>
#include <vector>
#include <sstream>
#include "Customer.h"
#include "Transaction.h"

/**
The Bank has Accounts and an Account belongs to a Customer.
Additionally, there are specialized types of accounts: Checking_Account and Savings_Account.
Checking_Account and Savings_Account have specialized ways of adding interest, and describing itself.

@author: Ed Walker
*/

class Account {
protected:
	Customer *customer;		// The customer who owns this account
	double balance;			// The available balance in this account
	int account_number;		// A unique number identifying this account
	std::vector<Transaction *> transactions;  // The record of transactions that have occured with this account

	/**
	Describe fees associated with the customer who owns this account.
	The fee will depend on the specific type of customer.
	@return string showing checking and overdraft fees
	*/
	std::string get_fees()
	{
		int overdraft, charge;

		// Polymorphism: calls the correct virtual methods from the specific customer type
		overdraft = customer->getOVERDRAFT_PENALTY();
		charge = customer->getCHECK_CHARGE();

		std::stringstream ss;
		ss << "Check Charge: " << charge << " Overdraft Fee: " << overdraft;
		return ss.str();
	}

protected:
	/**
	Add interest based on a specified interest rate to account
	@param interest	The interest rate
	*/
	void add_interest(double interest) {
		double amt = balance*interest;
		balance = balance + amt;
		std::string fees = get_fees();
		Transaction *tran = NULL;

		tran = new Transaction(customer->getCustomer_number(), "Interest", amt, fees);

		transactions.push_back(tran);
	}

public:
	/**
	Constructor requires a customer to create an account
	Balance always starts with 0 when account is created.
	*/
	Account(Customer *cust, int id) : customer(cust), account_number(id), balance(0) {}

	/**
	Generic accesser and setter methods for properties customer, balance, and account_number
	*/

	Customer *get_customer() {
		return customer;
	}

	void set_customer(Customer *cust) {
		customer = cust;
	}

	int get_account() {
		return account_number;
	}

	void set_balance(double new_balance) {
		balance = new_balance;
	}

	void set_account(int account_number) {
		this->account_number = account_number;
	}

	double get_balance() {
		return balance;
	}

	/**
	Generic method describing the account information.

	Remember that you will need to indicate if an account is Savings or Checking in 
	an overridden version of to_string() in the derived classes. 

	@return string describing generic information about the account
	*/
	virtual std::string to_string() {
		std::stringstream ss; // for composing the string that describes this account

		ss << "  Customer Number: " << customer->getCustomer_number() << std::endl;
		ss << "  Customer Name: " << customer->getName() << std::endl;
		ss << "  Balance: " << balance << std::endl;
		ss << "  Account ID: " << account_number << std::endl;
		return ss.str();
	}

	/**
	Deposits amount into account
	@param amt The deposit amount
	*/
	virtual void deposit(double amt) {
		balance += amt;
		std::string fees = get_fees();
		Transaction *tran = NULL;

		tran = new Transaction(customer->getCustomer_number(), "Deposit", amt, fees);

		transactions.push_back(tran);
	}

	/**
	Withdraws amount from account
	@param amt The withdrawal amount
	*/
	virtual void withdraw(double amt) {
		balance -= amt;
		std::string fees = get_fees();
		Transaction *tran = NULL;

		tran = new Transaction(customer->getCustomer_number(), "Withdrawal", amt, fees);

		transactions.push_back(tran);
	}

	// We want the Savings_Account and Checking_Account to implement this.
	virtual void add_interest() = 0;

};

class Savings_Account : public Account {
public:
	Savings_Account(Customer *cust, int id) : Account(cust, id) {};
	std::string to_string() {
		std::stringstream ss; // for composing the string that describes this account
		ss << " Account Type: Savings Account" << std::endl;
		ss << Account::to_string(); //using the previously defined to_string() should work...
		return ss.str();
	}
	void withdraw(double amt) { //am still unsure if this implementation is correct but I'm going with it
		if (balance - amt < 0) { //check to see if the customer were to overdraw the account
			amt += customer->getOVERDRAFT_PENALTY(); //if they do add the Overdraft charge
		}
		Account::withdraw(amt);
	}
	void add_interest() {
		Account::add_interest(0.01 * customer->getSAVINGS_INTEREST()); //this should work?
																	   //the werid numbers are used to convert the in customer interest rate into the correct form
	}
};
class Checking_Account : public Account {
public:
	Checking_Account(Customer *cust, int id) : Account(cust, id) {};
	std::string to_string() {
		std::stringstream ss; // for composing the string that describes this account
		ss << " Account Type: Checking Account" << std::endl;
		ss << Account::to_string(); //using the previously defined to_string() should work...
		return ss.str();
	}
	void withdraw(double amt) { //am still unsure if this implementation is correct but I'm going with it
		if (balance - amt < 0) { //check to see if the customer were to overdraw the account
			amt += customer->getCHECK_CHARGE(); //if they do add the checking charge
		}
		Account::withdraw(amt);
	}
	void add_interest() {
		Account::add_interest(0.01 * customer->getCHECK_INTEREST()); //this should work?
																	 //the werid numbers are used to convert the in customer interest rate into the correct form
	}
};

#endif