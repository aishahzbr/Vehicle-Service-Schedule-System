#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

class VehicleManager
{
public:
	int registerVehicle(Vehicle* vehicle, string username);
	int updateVehicleID(Vehicle* vehicle, string regID);
	int updateVehicleType(Vehicle* vehicle, string regID);
	int updateVehicleColour(Vehicle* vehicle, string regID);
	int updateVehicleModel(Vehicle* vehicle, string regID);
	void searchVehicles(string regID);
	int deactivateVehicle(Vehicle* vehicle, string regID);
	int displayID(string username);
	int deactivateID(string status, string username);

	void showupdateVehicleID(string regID);
	void showupdateVehicleType(string regID);
	void showupdateVehicleColour(string regID);
	void showupdateVehicleModel(string regID);
};

#endif 

