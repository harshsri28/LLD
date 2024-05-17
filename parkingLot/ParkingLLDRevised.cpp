#include<bits/stdc++.h>
using namespace std;

enum class VehicleTypes{
    LARGE,
    MEDIUM,
    SMALL,
};

class ParkingSpot{
    private:
        int id;
        VehicleTypes spotType;
        bool isOccupied;
    public:
    ParkingSpot(int id,  VehicleTypes spotType, bool isOccupied){
        id = id;
        spotType = spotType;
        isOccupied = isOccupied;
    }

    int getId(){
        return id;
    }

    void setId(int setId){
        id = setId;
    }

    VehicleTypes getSpotType(){
        return spotType;
    }

    void setOccupiedStatus(bool occupyStatus){
        isOccupied = occupyStatus;
    }

    bool getOccupiedStatus(){
        return   isOccupied;
    }
};

class ParkingSpace{
    private:
    vector<ParkingSpot> parkingSpots;
    public:

   void addSpotinParkingSpace(ParkingSpot spot){
       parkingSpots.push_back(spot);
   }

    vector<ParkingSpot> getAvailableSpot(VehicleTypes vehicleType){
        vector<ParkingSpot> availableSpot;
        cout<<"size here is "<<parkingSpots.size()<<"\n";
        for(int i = 0; i < parkingSpots.size(); i++){
            if(vehicleType == parkingSpots[i].getSpotType() && !parkingSpots[i].getOccupiedStatus()){
                availableSpot.push_back(parkingSpots[i]);
            }
        }
        return availableSpot;
    }

    vector<ParkingSpot> getAllSpotStatus(){
        vector<ParkingSpot> allSpots;
        for(int i=0; i<parkingSpots.size(); i++){
                allSpots.push_back(parkingSpots[i]);
            
        }

        return allSpots;
    }
};

class ParkVehicle {
public:
    void parkVehicle(VehicleTypes vehicle,ParkingSpace space1){
        vector<ParkingSpot> availableSpot = space1.getAvailableSpot(vehicle);
        cout<<"availableSpot "<<availableSpot.size();
        if(availableSpot.size() == 0){
            cout<<"Empty Hai\n";
            return;
        } 

        availableSpot[0].setOccupiedStatus(true);
    }

    void freeSpot(VehicleTypes vehicle, ParkingSpace space1){
        vector<ParkingSpot> allSpots = space1.getAllSpotStatus();

        for(int i=0; i<allSpots.size() ; i++){
            if(allSpots[i].getSpotType() == vehicle){
                cout<<"free hogya\n";
                allSpots[i].setOccupiedStatus(false);
                return;
            }
        }
    }
};


int main(){
    ParkingSpace space1;
    ParkingSpot spot1(1, VehicleTypes::LARGE, false);
    ParkingSpot spot2(2, VehicleTypes::SMALL, false);
    space1.addSpotinParkingSpace(spot1);
    space1.addSpotinParkingSpace(spot1);
    ParkVehicle park1;
    park1.parkVehicle(VehicleTypes::SMALL, space1);


}
