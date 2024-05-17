#include <bits/stdc++.h>
using namespace std;

class User
{
private:
    int id;
     string name;
    double balance;

public:
    User(int id, const  string &name);

    int getID() const;
     string getName() const;
    double getBalance() const;

    void updateBalance(double amount);
};

class ExpenseSplit
{
public:
    virtual void calculateAmounts(double totalAmount, int numParticipants) = 0;
};

class EqualExpenseSplit : public ExpenseSplit
{
public:
    void calculateAmounts(double totalAmount, int numParticipants) override;
};

class PercentageExpenseSplit : public ExpenseSplit
{
private:
     vector<double> percentages;

public:
    PercentageExpenseSplit(const  vector<double> &percentages);

    void calculateAmounts(double totalAmount, int numParticipants) override;
};

class ExactExpenseSplit : public ExpenseSplit
{
private:
     vector<double> amounts;

public:
    ExactExpenseSplit(const  vector<double> &amounts);

    void calculateAmounts(double totalAmount, int numParticipants) override;
};

class Expense
{
private:
    double amount;
     string description;
    int payerID;
    ExpenseSplit *expenseSplit;

public:
    Expense(double amount, const  string &description, int payerID, ExpenseSplit *expenseSplit);
    ~Expense();

    double getAmount() const;
     string getDescription() const;
    int getPayerID() const;
    ExpenseSplit *getExpenseSplit() const;
};

class ExpenseManager
{
private:
     vector<User> users;
     vector<Expense> expenses;

public:
    void addUser(const User &user);
    void addExpense(const Expense &expense);
    void calculateUserBalances();
    void showUserBalances() const;
    void settleExpenses();
};

