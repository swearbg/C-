#include <vector>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Account;
class Processor{
public:
	void virtual process(Account * acc, int month,int year) = 0;
};
class Account{
protected:
	string name, type;
	double balance;
	int size1;
public:
	Account(string name, string type, double balance) : name(name), type(type), balance(balance){ size1++; };
	void print(ostream & out){
		out << name << " " << type << " " << balance << endl;
	}
	string getType(){
		return type;
	}
	double getBalance(){
		return balance;
	}
	void setBalance(double sal){
		balance = sal;
	}
	int size(){
		return size1;
	}
};
class CardMonthlyTaxProcessor : public Processor{
private:
	double interest;
public:
	CardMonthlyTaxProcessor(double interest) : interest(interest){};
	void process(Account * acc, int month, int year)
	{
		//type validation
		if (acc->getType() != "card")
			return;

		double accBalance = acc->getBalance();

		if (accBalance >= interest){
			acc->setBalance(accBalance - interest);
		}
	}

};
class InterestProcessor : public Processor{
private:
	string type;
	double interest = 0;
public:
	InterestProcessor(string type,double interest){
		this->interest = interest;
		this->type = type;
	}
		void process(Account * acc, int month, int year){
			//month validation
			if (month != 12)
				return;
			// account validation
			if (acc->getType() != type)
				return;

			double AccountBalance = acc->getBalance();
			double InterestValue = AccountBalance * (interest / 100);
			acc->setBalance(AccountBalance + InterestValue);
		}
};

vector<Account *> loadAccounts(string path){
	vector<Account *> result;
	string name, type, salary;
	double balance = 0;

	ifstream inp_data;
	inp_data.open(path);

	if (inp_data.fail()){
		cout << "Error" << endl;
		return result;
	}

	while (inp_data.good()){
		getline(inp_data, name, ',');
		getline(inp_data, type, ',');
		getline(inp_data, salary);
		balance = stod(salary);
		
		Account * account = new Account(name, type, balance);
		result.push_back(account);
	}
	

	inp_data.close();
	return result;

}
vector<Processor *> loadProcessors(){
	vector<Processor *> result;
	Processor * Card = new CardMonthlyTaxProcessor(3);
	Processor * second = new InterestProcessor("card", 0.1);
	Processor * third = new InterestProcessor("deposit", 2.5);
	result.push_back(Card);
	result.push_back(second);
	result.push_back(third);
	return result;
}
void prepareIniFile()
{
	int configLinesCount;
	string configLine;
	ofstream fout("accounts.dat");
	while (getline(cin, configLine))
	{
		fout << configLine << endl;
	}
	fout.close();
}

int main(int argc, char* argv[])
{
	prepareIniFile();

	vector<Account *> accounts = loadAccounts("accounts.dat");
	vector<Processor *> processors = loadProcessors();

	for (int year = 2012; year < 2014; year++)
	{
		for (int month = 1; month <= 12; month++)
		{
			cout << month << ", " << year << endl;
			cout << "----------------------------" << endl;
			for (int i = 0; i < accounts.size(); i++)
			{
				Account* account = accounts[i];
				for (int j = 0; j < processors.size(); j++)
				{
					processors[j]->process(account, month, year);
				}

				account->print(cout);
			}
			cout << endl;
		}
	}
	
	system("pause");
	return 0;
}
