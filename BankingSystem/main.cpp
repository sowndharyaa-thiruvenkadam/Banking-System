#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Forward declarations
class Account;
class Transaction;

// Customer Class
class Customer
{
private:
  string name;
  int customerID;
  vector<Account *> accounts;

public:
  Customer(string name, int customerID) : name(name), customerID(customerID) {}

  void addAccount(Account *account);
  void displayAccounts() const;
  string getName() const { return name; }
  int getCustomerID() const { return customerID; }
  Account *getAccountByNumber(int accountNumber) const;
};

// Account Class
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
  void addTransaction(const Transaction &transaction);
  double getBalance() const { return balance; }
  int getAccountNumber() const { return accountNumber; }
  void displayTransactions() const;
};

// Transaction Class
class Transaction
{
private:
  string type;
  double amount;
  string date;

public:
  Transaction(string type, double amount, string date) : type(type), amount(amount), date(date) {}

  void displayTransaction() const
  {
    cout << "Type: " << type << ", Amount: " << amount << ", Date: " << date << endl;
  }
};

// BankingService Class
class BankingService
{
private:
  vector<Customer> customers;

public:
  void createCustomer(const string &name, int customerID);
  Customer &getCustomerByID(int customerID);
  void createAccount(Customer &customer, int accountNumber, double initialBalance);
  void performDeposit(Account &account, double amount);
  void performWithdrawal(Account &account, double amount);
  void transferFunds(Account &fromAccount, Account &toAccount, double amount);
  void displayCustomerDetails(const Customer &customer) const;
};

// Customer Class Method Definitions

void Customer::addAccount(Account *account)
{
  accounts.push_back(account);
}

void Customer::displayAccounts() const
{
  cout << "Accounts for customer " << name << " (ID: " << customerID << "):" << endl;
  for (const Account *account : accounts)
  {
    cout << "Account Number: " << account->getAccountNumber() << ", Balance: " << account->getBalance() << endl;
    account->displayTransactions();
  }
}

Account *Customer::getAccountByNumber(int accountNumber) const
{
  for (Account *account : accounts)
  {
    if (account->getAccountNumber() == accountNumber)
    {
      return account;
    }
  }
  return nullptr;
}

// Account Class Method Definitions

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

void Account::addTransaction(const Transaction &transaction)
{
  transactions.push_back(transaction);
}

void Account::displayTransactions() const
{
  cout << "Transaction history for account " << accountNumber << ":" << endl;
  for (const Transaction &transaction : transactions)
  {
    transaction.displayTransaction();
  }
}

// BankingService Class Method Definitions

void BankingService::createCustomer(const string &name, int customerID)
{
  customers.push_back(Customer(name, customerID));
}

Customer &BankingService::getCustomerByID(int customerID)
{
  for (Customer &customer : customers)
  {
    if (customer.getCustomerID() == customerID)
    {
      return customer;
    }
  }
  throw invalid_argument("Customer ID not found");
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

void BankingService::displayCustomerDetails(const Customer &customer) const
{
  cout << "Customer Name: " << customer.getName() << ", ID: " << customer.getCustomerID() << endl;
  customer.displayAccounts();
}

// Main Function
int main()
{
  BankingService service;

  int choice;
  do
  {
    cout << "\nBanking Service Menu:\n";
    cout << "1. Create Customer\n";
    cout << "2. Create Account\n";
    cout << "3. Deposit\n";
    cout << "4. Withdraw\n";
    cout << "5. Transfer Funds\n";
    cout << "6. Display Customer Details\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
      string name;
      int customerID;
      cout << "Enter customer name: ";
      cin.ignore(); // To ignore the newline character left by previous input
      getline(cin, name);
      cout << "Enter customer ID: ";
      cin >> customerID;
      service.createCustomer(name, customerID);
      break;
    }
    case 2:
    {
      int customerID, accountNumber;
      double initialBalance;
      cout << "Enter customer ID: ";
      cin >> customerID;
      cout << "Enter account number: ";
      cin >> accountNumber;
      cout << "Enter initial balance: ";
      cin >> initialBalance;
      Customer &customer = service.getCustomerByID(customerID);
      service.createAccount(customer, accountNumber, initialBalance);
      break;
    }
    case 3:
    {
      int accountNumber;
      double amount;
      cout << "Enter account number: ";
      cin >> accountNumber;
      cout << "Enter deposit amount: ";
      cin >> amount;
      Customer &customer = service.getCustomerByID(customerID); // Get customer details first
      Account *account = customer.getAccountByNumber(accountNumber);
      if (account)
      {
        service.performDeposit(*account, amount);
      }
      else
      {
        cout << "Account not found!" << endl;
      }
      break;
    }
    case 4:
    {
      int accountNumber;
      double amount;
      cout << "Enter account number: ";
      cin >> accountNumber;
      cout << "Enter withdrawal amount: ";
      cin >> amount;
      Customer &customer = service.getCustomerByID(customerID); // Get customer details first
      Account *account = customer.getAccountByNumber(accountNumber);
      if (account)
      {
        service.performWithdrawal(*account, amount);
      }
      else
      {
        cout << "Account not found!" << endl;
      }
      break;
    }
    case 5:
    {
      int fromAccountNumber, toAccountNumber;
      double amount;
      cout << "Enter from account number: ";
      cin >> fromAccountNumber;
      cout << "Enter to account number: ";
      cin >> toAccountNumber;
      cout << "Enter transfer amount: ";
      cin >> amount;
      Customer &customer = service.getCustomerByID(customerID); // Get customer details first
      Account *fromAccount = customer.getAccountByNumber(fromAccountNumber);
      Account *toAccount = customer.getAccountByNumber(toAccountNumber);
      if (fromAccount && toAccount)
      {
        service.transferFunds(*fromAccount, *toAccount, amount);
      }
      else
      {
        cout << "One or both accounts not found!" << endl;
      }
      break;
    }
    case 6:
    {
      int customerID;
      cout << "Enter customer ID: ";
      cin >> customerID;
      Customer &customer = service.getCustomerByID(customerID);
      service.displayCustomerDetails(customer);
      break;
    }
    case 7:
      cout << "Exiting..." << endl;
      break;
    default:
      cout << "Invalid choice, please try again." << endl;
      break;
    }

  } while (choice != 7);

  return 0;
}
