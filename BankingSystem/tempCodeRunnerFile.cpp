#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Account; // Forward declaration

class Customer
{
private:
  string name;
  int customerID;
  vector<Account *> accounts;

public:
  Customer(string name, int customerID) : name(name), customerID(customerID) {}

  void addAccount(Account *account);
  void displayAccounts();
  string getName() { return name; }
  int getCustomerID() { return customerID; }
};

class Transaction; // Forward declaration

class Account
{
private:
  int accountNumber;
  double balance;
  vector<Transaction> transactions;

public:
  Account(int accountNumber, double initialBalance) : accountNumber(accountNumber), balance(initialBalance) {}

  void deposit(double amount);
  void withdraw(double amount);
  void addTransaction(Transaction transaction);
  double getBalance() { return balance; }
  void displayTransactions();
};

class Transaction
{
private:
  string type;
  double amount;
  string date;

public:
  Transaction(string type, double amount, string date) : type(type), amount(amount), date(date) {}

  void displayTransaction()
  {
    cout << "Type: " << type << ", Amount: " << amount << ", Date: " << date << endl;
  }
};

class BankingService
{
private:
  vector<Customer> customers;

public:
  void createCustomer(string name, int customerID);
  void createAccount(Customer &customer, int accountNumber, double initialBalance);
  void performDeposit(Account &account, double amount);
  void performWithdrawal(Account &account, double amount);
  void transferFunds(Account &fromAccount, Account &toAccount, double amount);
  void displayCustomerDetails(Customer &customer);
};

void Customer::addAccount(Account *account)
{
  accounts.push_back(account);
}

void Customer::displayAccounts()
{
  cout << "Accounts for customer " << name << " (ID: " << customerID << "):" << endl;
  for (Account *account : accounts)
  {
    cout << "Account Number: " << account->getBalance() << ", Balance: " << account->getBalance() << endl;
    account->displayTransactions();
  }
}

void Account::deposit(double amount)
{
  balance += amount;
  addTransaction(Transaction("Deposit", amount, "2024-08-30"));
}

void Account::withdraw(double amount)
{
  if (amount <= balance)
  {
    balance -= amount;
    addTransaction(Transaction("Withdrawal", amount, "2024-08-30"));
  }
  else
  {
    cout << "Insufficient balance!" << endl;
  }
}

void Account::addTransaction(Transaction transaction)
{
  transactions.push_back(transaction);
}

void Account::displayTransactions()
{
  cout << "Transaction history for account " << accountNumber << ":" << endl;
  for (Transaction &transaction : transactions)
  {
    transaction.displayTransaction();
  }
}

void Account::deposit(double amount)
{
  balance += amount;
  addTransaction(Transaction("Deposit", amount, "2024-08-30"));
}

void Account::withdraw(double amount)
{
  if (amount <= balance)
  {
    balance -= amount;
    addTransaction(Transaction("Withdrawal", amount, "2024-08-30"));
  }
  else
  {
    cout << "Insufficient balance!" << endl;
  }
}

void Account::addTransaction(Transaction transaction)
{
  transactions.push_back(transaction);
}

void Account::displayTransactions()
{
  cout << "Transaction history for account " << accountNumber << ":" << endl;
  for (Transaction &transaction : transactions)
  {
    transaction.displayTransaction();
  }
}

void BankingService::createCustomer(string name, int customerID)
{
  customers.push_back(Customer(name, customerID));
}

void BankingService::createAccount(Customer &customer, int accountNumber, double initialBalance)
{
  Account *newAccount = new Account(accountNumber, initialBalance);
  customer.addAccount(newAccount);
}

void BankingService::performDeposit(Account &account, double amount)
{
  account.deposit(amount);
}

void BankingService::performWithdrawal(Account &account, double amount)
{
  account.withdraw(amount);
}

void BankingService::transferFunds(Account &fromAccount, Account &toAccount, double amount)
{
  if (fromAccount.getBalance() >= amount)
  {
    fromAccount.withdraw(amount);
    toAccount.deposit(amount);
    cout << "Transfer successful!" << endl;
  }
  else
  {
    cout << "Insufficient funds for transfer!" << endl;
  }
}

void BankingService::displayCustomerDetails(Customer &customer)
{
  cout << "Customer Name: " << customer.getName() << ", ID: " << customer.getCustomerID() << endl;
  customer.displayAccounts();
}

int main()
{
  BankingService service;

  // Create customers
  service.createCustomer("John Doe", 101);
  service.createCustomer("Jane Smith", 102);

  // Create accounts
  Customer &customer1 = service.getCustomerByID(101);
  service.createAccount(customer1, 1001, 500.00);

  Customer &customer2 = service.getCustomerByID(102);
  service.createAccount(customer2, 1002, 1000.00);

  // Perform transactions
  Account &account1 = customer1.getAccountByNumber(1001);
  service.performDeposit(account1, 200.00);
  service.performWithdrawal(account1, 100.00);

  // Transfer funds
  Account &account2 = customer2.getAccountByNumber(1002);
  service.transferFunds(account1, account2, 150.00);

  // Display customer details
  service.displayCustomerDetails(customer1);
  service.displayCustomerDetails(customer2);

  return 0;
}
