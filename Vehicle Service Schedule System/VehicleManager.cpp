#include <string>
#include <iomanip>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "Vehicle.h"
#include "VehicleManager.h"
#include "Profile.h"
#include "ProfileManager.h"
#include "DatabaseConnection.h"

void managevehicle();

int VehicleManager::registerVehicle(Vehicle* vehicle, string username)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Vehicle VALUES (?, ?, ?, ?, ?, ?)");

	ps->setString(1, vehicle->regID); // 1 referring to first ?
	ps->setString(2, vehicle->type);
	ps->setString(3, vehicle->model);
	ps->setString(4, vehicle->colour);
	ps->setString(5, vehicle->status);
	ps->setString(6, username);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int VehicleManager::deactivateID(string status, string username)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Vehicle WHERE VehicleStatus LIKE ? AND UserID LIKE ?");
	
	ps->setString(1, "%" + status + "%");
	ps->setString(2, username);

	ResultSet* rs = ps->executeQuery();
	
	if (!rs->next())
	{
		cout << " Vehicle doesn't exists. " << endl << endl;
	}

	do
	{
		c = a++;
		cout << " " << c << ". " << rs->getString("RegistrationNo") << endl;
	} while (rs->next());
	delete ps;
	return 0;
}

void VehicleManager::searchVehicles(string regID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Vehicle WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	if (!rs->next())
	{
		cout << " Vehicle doesn't exist." << endl << endl;
		managevehicle();
	}

	cout << " -------------------------------------------------\n";
	cout << " " << '|' << setw(10) << " Type " << '|' << setw(10) << " Model " << '|' << setw(10) << " Colour " << '|' << setw(14) << " Status " << '|' << endl;
	cout << " -------------------------------------------------\n";

	do
	{
		cout << " " << '|' << setw(10) << rs->getString("VehicleType") << '|' << setw(10) << rs->getString("VehicleModel") << '|' << setw(10) << rs->getString("VehicleColour") << '|' << setw(14) << rs->getString("VehicleStatus") << '|' << endl;
		cout << " -------------------------------------------------\n";
	} while (rs->next());

	delete ps;
}

int VehicleManager::deactivateVehicle(Vehicle* vehicle, string regID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Vehicle SET VehicleStatus = (?) WHERE RegistrationNo = (?)");

	ps->setString(1, vehicle->status);
	ps->setString(2, regID);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

int VehicleManager::displayID(string username)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Vehicle WHERE UserID = (?)");
	ps->setString(1, username);
	ResultSet* rs = ps->executeQuery();

	while (rs->next())
	{
		c = a++;
		cout << " " << c << ". " << rs->getString("RegistrationNo") << endl;
	}
	delete ps;
	return 0;
}

int VehicleManager::updateVehicleID(Vehicle* vehicle, string regID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Vehicle SET RegistrationNo = (?) WHERE RegistrationNo = (?)");

	ps->setString(1, vehicle->regID);
	ps->setString(2, regID);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

int VehicleManager::updateVehicleModel(Vehicle* vehicle, string regID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Vehicle SET VehicleModel = (?) WHERE RegistrationNo = (?)");

	ps->setString(1, vehicle->model);
	ps->setString(2, regID);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

int VehicleManager::updateVehicleType(Vehicle* vehicle, string regID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Vehicle SET VehicleType = (?) WHERE RegistrationNo = (?)");

	ps->setString(1, vehicle->type);
	ps->setString(2, regID);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

int VehicleManager::updateVehicleColour(Vehicle* vehicle, string regID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Vehicle SET VehicleColour = (?) WHERE RegistrationNo = (?)");

	ps->setString(1, vehicle->colour);
	ps->setString(2, regID);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

void VehicleManager::showupdateVehicleID(string regID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Vehicle WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << '|' << setw(10) << " Registration No " << '|' << endl;
	cout << "-------------------\n";

	while (rs->next())
	{
		cout << '|' << setw(17) << rs->getString("RegistrationNo") << '|' << endl;
		cout << "-------------------\n";
	}

	delete ps;
}

void VehicleManager::showupdateVehicleType(string regID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Vehicle WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << '|' << setw(10) << " Registration No " << '|' << setw(10) << " Vehicle Type " << '|' << endl;
	cout << "----------------------------------\n";

	while (rs->next())
	{
		cout << '|' << setw(17) << rs->getString("RegistrationNo") << '|' << setw(14) << rs->getString("VehicleType") << '|' << endl;
		cout << "----------------------------------\n";
	}

	delete ps;
}

void VehicleManager::showupdateVehicleModel(string regID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Vehicle WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << '|' << setw(10) << " Registration No " << '|' << setw(10) << " Vehicle Model " << '|' << endl;
	cout << "-----------------------------------\n";

	while (rs->next())
	{
		cout << '|' << setw(17) << rs->getString("RegistrationNo") << '|' << setw(15) << rs->getString("VehicleModel") << '|' << endl;
		cout << "-----------------------------------\n";
	}

	delete ps;
}

void VehicleManager::showupdateVehicleColour(string regID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Vehicle WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << '|' << setw(10) << " Registration No " << '|' << setw(10) << " Vehicle Colour " << '|' << endl;
	cout << "------------------------------------\n";

	while (rs->next())
	{
		cout << '|' << setw(17) << rs->getString("RegistrationNo") << '|' << setw(16) << rs->getString("VehicleColour") << '|' << endl;
		cout << "------------------------------------\n";
	}

	delete ps;
}

