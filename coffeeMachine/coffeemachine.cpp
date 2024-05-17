// need to add the state of brewCofeee

#include<bits/stdc++.h>
using namespace std;

enum class CoffeeType
{
    ESPRESSO,
    LATTE,
    CAPPUCCINO
};

enum class CoffeeSize
{
    SMALL,
    MEDIUM,
    LARGE
};

class Coffee
{
private:
    CoffeeType type;
    CoffeeSize size;
    double price;

public:
    Coffee(CoffeeType type, CoffeeSize size, double price)
        : type(type), size(size), price(price) {}

    CoffeeType getType() const
    {
        return type;
    }

    CoffeeSize getSize() const
    {
        return size;
    }

    double getPrice() const
    {
        return price;
    }
};

class CoffeeMachineState
{
public:
    virtual void displayOptions() = 0;
    virtual void selectCoffee(CoffeeType type, CoffeeSize size) = 0;
    virtual void brewCoffee() = 0;
    virtual void cancel() = 0;
};

class ReadyState : public CoffeeMachineState
{
public:
    void displayOptions() override
    {
         cout << "Welcome to the Coffee Machine!\n";
         cout << "Available options:\n";
         cout << "1. Espresso\n2. Latte\n3. Cappuccino\n";
    }

    void selectCoffee(CoffeeType type, CoffeeSize size) override
    {
         cout << "Selected coffee: ";
        switch (type)
        {
        case CoffeeType::ESPRESSO:
             cout << "Espresso, ";
            break;
        case CoffeeType::LATTE:
             cout << "Latte, ";
            break;
        case CoffeeType::CAPPUCCINO:
             cout << "Cappuccino, ";
            break;
        default:
            break;
        }

        switch (size)
        {
        case CoffeeSize::SMALL:
             cout << "Size: Small\n";
            break;
        case CoffeeSize::MEDIUM:
             cout << "Size: Medium\n";
            break;
        case CoffeeSize::LARGE:
             cout << "Size: Large\n";
            break;
        default:
            break;
        }
    }

    void brewCoffee() override
    {
         cout << "Brewing the coffee...\n";
    }

    void cancel() override
    {
         cout << "Cancelling the selection.\n";
    }
};

class CoffeeMachine
{
private:
    CoffeeMachineState *currentState;

public:
    CoffeeMachine() : currentState(new ReadyState()) {}

    ~CoffeeMachine()
    {
        delete currentState;
    }

    void setState(CoffeeMachineState *state)
    {
        delete currentState;
        currentState = state;
    }

    void displayOptions()
    {
        currentState->displayOptions();
    }

    void selectCoffee(CoffeeType type, CoffeeSize size)
    {
        currentState->selectCoffee(type, size);
    }

    void brewCoffee()
    {
        currentState->brewCoffee();
    }

    void cancel()
    {
        currentState->cancel();
    }
};

int main()
{
    CoffeeMachine coffeeMachine;

    // Display options
    coffeeMachine.displayOptions();

    // Select coffee
    coffeeMachine.selectCoffee(CoffeeType::ESPRESSO, CoffeeSize::SMALL);

    // Brew coffee
    coffeeMachine.brewCoffee();

    // Cancel
    coffeeMachine.cancel();

    return 0;
}
