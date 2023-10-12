#include <iostream>
#include <vector>
#include <string>

class User
{
private:
    int id;
    std::string name;
    double balance;

public:
    User(int id, const std::string &name);

    int getID() const;
    std::string getName() const;
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
    std::vector<double> percentages;

public:
    PercentageExpenseSplit(const std::vector<double> &percentages);

    void calculateAmounts(double totalAmount, int numParticipants) override;
};

class ExactExpenseSplit : public ExpenseSplit
{
private:
    std::vector<double> amounts;

public:
    ExactExpenseSplit(const std::vector<double> &amounts);

    void calculateAmounts(double totalAmount, int numParticipants) override;
};

class Expense
{
private:
    double amount;
    std::string description;
    int payerID;
    ExpenseSplit *expenseSplit;

public:
    Expense(double amount, const std::string &description, int payerID, ExpenseSplit *expenseSplit);
    ~Expense();

    double getAmount() const;
    std::string getDescription() const;
    int getPayerID() const;
    ExpenseSplit *getExpenseSplit() const;
};

class ExpenseManager
{
private:
    std::vector<User> users;
    std::vector<Expense> expenses;

public:
    void addUser(const User &user);
    void addExpense(const Expense &expense);
    void calculateUserBalances();
    void showUserBalances() const;
    void settleExpenses();
};

