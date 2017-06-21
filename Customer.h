#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include <string>

/**
The Bank has Customers.  Each Customer has a name, address, age, and telephone number.
Additionally, there are specialized types of Customers: Adult, Senior, and Student.
Each type of Customer has its own checking and savings interest rates, 
as well as its own checking and overdraft fees.

@author: Ed Walker
*/
class Customer {
private:
	std::string name;
	std::string address;
	int age;
	std::string telephone_number;
	int customer_number;
public:
	//Default and custom constructors
	Customer() : name(""), address(""), age(0), telephone_number(""), customer_number(0) {}
	Customer(std::string name, std::string address, int age, std::string telephone_number, int customer_number) :
		name(name), address(address), age(age), telephone_number(telephone_number), customer_number(customer_number) {}

	//Getters for all the private member variables
	std::string getName() { return name; }
	std::string getAddress() { return address; }
	int getAge() { return age; }
	std::string getTelephone_number() { return telephone_number; }
	int getCustomer_number() { return customer_number; }

	//Setters for all the private member variables
	void setName(std::string name) { this->name = name; }
	void setAddress(std::string address) { this->address = address; }
	void setAge(int age) { this->age = age; }
	void setTelephone_number(std::string tele_num) { this->telephone_number = tele_num; }
	void setCustomer_number(int new_num) { this->customer_number = new_num; }

	//Getters for the interest rates and penalties
	//Only made them virtual and void to ensure implementation of polymorphism as recquired
	//Has the side effect of meaning there can strictly be no Customer objects, which is nice self-guarding
	virtual int getSAVINGS_INTEREST() = 0;
	virtual int getCHECK_INTEREST() = 0;
	virtual int getCHECK_CHARGE() = 0;
	virtual int getOVERDRAFT_PENALTY() = 0;
};


class Senior : public Customer {
private:
	int SAVINGS_INTEREST = 5;
	int CHECK_INTEREST = 7;
	int CHECK_CHARGE = 15;
	int OVERDRAFT_PENALTY = 15;
public:
	//Default and custom constructors
	Senior() : Customer() {}
	Senior(std::string name, std::string address, int age, std::string telephone_number, int customer_number) :
		Customer(name, address, age, telephone_number, customer_number) {}
	
	//getters for all the interest rates
	int getSAVINGS_INTEREST() { return SAVINGS_INTEREST; };
	int getCHECK_INTEREST() { return CHECK_INTEREST; };
	int getCHECK_CHARGE() { return CHECK_CHARGE; };
	int getOVERDRAFT_PENALTY() { return OVERDRAFT_PENALTY; };
};

class Adult : public Customer {
private:
	int SAVINGS_INTEREST = 6;
	int CHECK_INTEREST = 8;
	int CHECK_CHARGE = 20;
	int OVERDRAFT_PENALTY = 25;
public:
	//Default and custom constructors
	Adult() : Customer() {}
	Adult(std::string name, std::string address, int age, std::string telephone_number, int customer_number) :
		Customer(name, address, age, telephone_number, customer_number) {}

	//getters for all the interest rates
	int getSAVINGS_INTEREST() { return SAVINGS_INTEREST; };
	int getCHECK_INTEREST() { return CHECK_INTEREST; };
	int getCHECK_CHARGE() { return CHECK_CHARGE; };
	int getOVERDRAFT_PENALTY() { return OVERDRAFT_PENALTY; };
};

class Student : public Customer {
private:
	int SAVINGS_INTEREST = 4;
	int CHECK_INTEREST = 6;
	int CHECK_CHARGE = 10;
	int OVERDRAFT_PENALTY = 15;
public:
	//Default and custom constructors
	Student() : Customer() {}
	Student(std::string name, std::string address, int age, std::string telephone_number, int customer_number) :
		Customer(name, address, age, telephone_number, customer_number) {}

	//getters for all the interest rates
	int getSAVINGS_INTEREST() { return SAVINGS_INTEREST; };
	int getCHECK_INTEREST() { return CHECK_INTEREST; };
	int getCHECK_CHARGE() { return CHECK_CHARGE; };
	int getOVERDRAFT_PENALTY() { return OVERDRAFT_PENALTY; };
};

#endif