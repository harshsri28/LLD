#include <iostream>
#include <vector>
#include <queue>

enum class Direction
{
    UP,
    DOWN,
    NONE
};

class Request
{
private:
    int floor;
    Direction direction;

public:
    Request(int floor, Direction direction) : floor(floor), direction(direction) {}

    int getFloor() const
    {
        return floor;
    }

    Direction getDirection() const
    {
        return direction;
    }
};

class ElevatorState
{
public:
    virtual void handleRequest(Request request) = 0;
};

class ElevatorIdleState : public ElevatorState
{
public:
    void handleRequest(Request request) override
    {
        std::cout << "Elevator is now moving to floor " << request.getFloor() << ".\n";
    }
};

class ElevatorMovingState : public ElevatorState
{
public:
    void handleRequest(Request request) override
    {
        std::cout << "Elevator is already moving. Cannot handle request right now.\n";
    }
};

class Elevator
{
private:
    int currentFloor;
    Direction direction;
    ElevatorState *currentState;

public:
    Elevator() : currentFloor(0), direction(Direction::NONE), currentState(new ElevatorIdleState()) {}

    int getCurrentFloor() const
    {
        return currentFloor;
    }

    Direction getDirection() const
    {
        return direction;
    }

    void move()
    {
        // Simulate elevator movement
        std::cout << "Elevator is moving.\n";
    }

    void handleRequest(Request request)
    {
        currentState->handleRequest(request);
    }

    void setCurrentState(ElevatorState *state)
    {
        delete currentState;
        currentState = state;
    }
};

class ElevatorSystem
{
private:
    std::vector<Elevator> elevators;

public:
    ElevatorSystem(int numElevators)
    {
        for (int i = 0; i < numElevators; ++i)
        {
            elevators.emplace_back();
        }
    }

    void requestElevator(int floor, Direction direction)
    {
        // Select the first elevator for simplicity
        elevators[0].handleRequest(Request(floor, direction));
    }
};

int main()
{
    ElevatorSystem elevatorSystem(1);

    // Request the elevator to go to floor 5
    elevatorSystem.requestElevator(5, Direction::UP);

    // Request again while the elevator is moving
    elevatorSystem.requestElevator(3, Direction::DOWN);

    return 0;
}
