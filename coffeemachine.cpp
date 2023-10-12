// need to add the state of brewCofeee

#include <iostream>
#include <map>

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
        std::cout << "Welcome to the Coffee Machine!\n";
        std::cout << "Available options:\n";
        std::cout << "1. Espresso\n2. Latte\n3. Cappuccino\n";
    }

    void selectCoffee(CoffeeType type, CoffeeSize size) override
    {
        std::cout << "Selected coffee: ";
        switch (type)
        {
        case CoffeeType::ESPRESSO:
            std::cout << "Espresso, ";
            break;
        case CoffeeType::LATTE:
            std::cout << "Latte, ";
            break;
        case CoffeeType::CAPPUCCINO:
            std::cout << "Cappuccino, ";
            break;
        default:
            break;
        }

        switch (size)
        {
        case CoffeeSize::SMALL:
            std::cout << "Size: Small\n";
            break;
        case CoffeeSize::MEDIUM:
            std::cout << "Size: Medium\n";
            break;
        case CoffeeSize::LARGE:
            std::cout << "Size: Large\n";
            break;
        default:
            break;
        }
    }

    void brewCoffee() override
    {
        std::cout << "Brewing the coffee...\n";
    }

    void cancel() override
    {
        std::cout << "Cancelling the selection.\n";
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
