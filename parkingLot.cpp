#include <iostream>
#include <vector>

enum class VehicleType
{
    CAR,
    MOTORCYCLE
};

class Vehicle
{
public:
    virtual VehicleType getType() const = 0;
};

class Car : public Vehicle
{
public:
    VehicleType getType() const override
    {
        return VehicleType::CAR;
    }
};

class Motorcycle : public Vehicle
{
public:
    VehicleType getType() const override
    {
        return VehicleType::MOTORCYCLE;
    }
};

class ParkingSpot
{
private:
    int spotNumber;
    bool occupied;
    Vehicle *parkedVehicle;

public:
    ParkingSpot(int number) : spotNumber(number), occupied(false), parkedVehicle(nullptr) {}

    int getSpotNumber() const
    {
        return spotNumber;
    }

    bool isOccupied() const
    {
        return occupied;
    }

    void occupySpot(Vehicle *vehicle)
    {
        parkedVehicle = vehicle;
        occupied = true;
    }

    void vacateSpot()
    {
        parkedVehicle = nullptr;
        occupied = false;
    }

    Vehicle *getParkedVehicle() const
    {
        return parkedVehicle;
    }
};

class ParkingLot
{
private:
    static ParkingLot *instance;
    int capacity;
    std::vector<ParkingSpot *> spots;

    ParkingLot(int capacity) : capacity(capacity)
    {
        for (int i = 1; i <= capacity; i++)
        {
            spots.push_back(new ParkingSpot(i));
        }
    }

public:
    static ParkingLot *getInstance(int capacity)
    {
        if (!instance)
        {
            instance = new ParkingLot(capacity);
        }
        return instance;
    }

    ParkingSpot *parkVehicle(Vehicle *vehicle)
    {
        for (auto spot : spots)
        {
            if (!spot->isOccupied())
            {
                spot->occupySpot(vehicle);
                return spot;
            }
        }
        return nullptr; // No available spots
    }

    void vacateSpot(ParkingSpot *spot)
    {
        spot->vacateSpot();
    }

    static void destroyInstance()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }
};

ParkingLot *ParkingLot::instance = nullptr;

int main()
{
    int capacity = 10; // Example parking lot capacity
    ParkingLot *parkingLot = ParkingLot::getInstance(capacity);

    // Create vehicles
    Car car1;
    Motorcycle motorcycle1;
    Car car2;

    // Park vehicles
    ParkingSpot *car1Spot = parkingLot->parkVehicle(&car1);
    ParkingSpot *motorcycle1Spot = parkingLot->parkVehicle(&motorcycle1);
    ParkingSpot *car2Spot = parkingLot->parkVehicle(&car2);

    if (car1Spot)
        std::cout << "Car 1 parked at spot " << car1Spot->getSpotNumber() << "\n";
    else
        std::cout << "No available spot for Car 1\n";

    if (motorcycle1Spot)
        std::cout << "Motorcycle 1 parked at spot " << motorcycle1Spot->getSpotNumber() << "\n";
    else
        std::cout << "No available spot for Motorcycle 1\n";

    if (car2Spot)
        std::cout << "Car 2 parked at spot " << car2Spot->getSpotNumber() << "\n";
    else
        std::cout << "No available spot for Car 2\n";

    // Vacate a spot
    parkingLot->vacateSpot(car1Spot);

    ParkingLot::destroyInstance();

    return 0;
}
