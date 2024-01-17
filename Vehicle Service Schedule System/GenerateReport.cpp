#include <string>
#include <iomanip>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "Service.h"
#include "Vehicle.h"
#include "VehicleManager.h"
#include "ServiceManager.h"
#include "GenerateReport.h"
#include "DatabaseConnection.h"

int GenerateReport::viewVehicleReport(string username)
{
	int a = 1;
	int c = -1;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Vehicle WHERE UserID = (?)");
	ps->setString(1, username);
	ResultSet* rs = ps->executeQuery();

	cout << '|' << setw(5) << "No " << '|' << setw(10) << " Registration No " << '|' << setw(10) << " Vehicle Type " << '|' << setw(10) << " Vehicle Model " << '|' << setw(10) << " Vehicle Colour " << '|' << setw(10) << " Vehicle Status " << '|' << endl;
	cout << "------------------------------------------------------------------------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(17) << rs->getString("RegistrationNo") << '|' << setw(14) << rs->getString("VehicleType") << '|' << setw(15) << rs->getString("VehicleModel") << '|' << setw(16) << rs->getString("VehicleColour") << '|' << setw(16) << rs->getString("VehicleStatus") << '|' << endl;
		cout << "------------------------------------------------------------------------------------------\n";
	}
	cout << "\n------------------------------------------------------------------------------------------\n";
	cout << "\t\t\t\t\t\t\t\t\tTotal Vehicles: " << c << endl;
	cout << "------------------------------------------------------------------------------------------\n";
	
	delete ps;
	return 0;
}

int GenerateReport::viewVehicleRegistered(string status, string username)
{
	int a = 1;
	int c = -1;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Vehicle WHERE VehicleStatus LIKE ? AND UserID LIKE ?");

	ps->setString(1, "%" + status + "%");
	ps->setString(2, username);
	
	ResultSet* rs = ps->executeQuery();

	cout << '|' << setw(5) << "No " << '|' << setw(10) << " Registration No " << '|' << setw(10) << " Vehicle Type " << '|' << setw(10) << " Vehicle Model " << '|' << setw(10) << " Vehicle Colour " << '|' << setw(10) << " Vehicle Status " << '|' << endl;
	cout << "------------------------------------------------------------------------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(17) << rs->getString("RegistrationNo") << '|' << setw(14) << rs->getString("VehicleType") << '|' << setw(15) << rs->getString("VehicleModel") << '|' << setw(16) << rs->getString("VehicleColour") << '|' << setw(16) << rs->getString("VehicleStatus") << '|' << endl;
		cout << "------------------------------------------------------------------------------------------\n";
	}
	
	cout << "\n------------------------------------------------------------------------------------------\n";
	cout << "\t\t\t\t\t\t\tTotal Registered Vehicles: " << c << endl;
	cout << "------------------------------------------------------------------------------------------\n";

	delete ps;
	return 0;
}

int GenerateReport::viewVehicleHistory(string status, string username)
{
	int a = 1;
	int c = -1;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Vehicle WHERE VehicleStatus LIKE ? AND UserID LIKE ?");

	ps->setString(1, "%" + status + "%");
	ps->setString(2, username);

	ResultSet* rs = ps->executeQuery();

	cout << '|' << setw(5) << "No " << '|' << setw(10) << " Registration No " << '|' << setw(10) << " Vehicle Type " << '|' << setw(10) << " Vehicle Model " << '|' << setw(10) << " Vehicle Colour " << '|' << setw(10) << " Vehicle Status " << '|' << endl;
	cout << "------------------------------------------------------------------------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(17) << rs->getString("RegistrationNo") << '|' << setw(14) << rs->getString("VehicleType") << '|' << setw(15) << rs->getString("VehicleModel") << '|' << setw(16) << rs->getString("VehicleColour") << '|' << setw(16) << rs->getString("VehicleStatus") << '|' << endl;
		cout << "------------------------------------------------------------------------------------------\n";
	}
	cout << "\n------------------------------------------------------------------------------------------\n";
	cout << "\t\t\t\t\t\t\tTotal Deactivate Vehicles: " << c << endl;
	cout << "------------------------------------------------------------------------------------------\n";

	delete ps;
	return 0;
}

int GenerateReport::viewServiceReport(double cost, string username)
{
	int a = 1;
	int c = -1;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT service.RegistrationNo, SUM(Cost), COUNT(*) FROM Service INNER JOIN vehicle ON service.RegistrationNo = vehicle.RegistrationNo WHERE vehicle.UserID LIKE ? GROUP BY RegistrationNo;");
	ps->setString(1, username);
	ResultSet* rs = ps->executeQuery();
	
	cout << '|' << setw(5) << "No " << '|' << setw(10) << " Registration No " << '|' << setw(10) << " Number of times Service " << '|' << setw(10) << " Total Service Cost (RM) " << '|' << endl;
	cout << "-----------------------------------------------------------------------------\n";
	
	while (rs->next())
	{
		c = a++;

		cout << '|' << setw(5) << c << '|' << setw(17) << rs->getString("RegistrationNo") << '|' << setw(25) << rs->getDouble("COUNT(*)") << '|' << setw(25) << rs->getDouble("SUM(Cost)") << '|' <<  endl;
		cout << "-----------------------------------------------------------------------------\n";
	}
	delete ps;
	return 0;
}

void GenerateReport::grandCost(double cost, string username)
{
	int a = 1;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT SUM(Cost) FROM service INNER JOIN vehicle ON service.RegistrationNo = vehicle.RegistrationNo WHERE vehicle.UserID LIKE ?");
	ps->setString(1, username);
	ResultSet* rs = ps->executeQuery();

	while (rs->next())
	{
		cout << "\n\t\t\t\t\t    Grand Total Cost : RM " << rs->getDouble("SUM(Cost)");
	}
	delete ps;
}

void GenerateReport::viewRoadTaxReport(string username)
{
	int a = 1;
	int c = -1;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT roadtax.RegistrationNo, MAX(EffectiveDate), MAX(ExpiryDate), COUNT(*) FROM roadtax INNER JOIN vehicle ON roadtax.RegistrationNo = vehicle.RegistrationNo WHERE vehicle.UserID LIKE ? GROUP BY roadtax.RegistrationNo");
	ps->setString(1, username);
	ResultSet* rs = ps->executeQuery();
	
	cout << '|' << setw(5) << "No " << '|' << setw(10) << " Registration No " << '|' << setw(10) << " Effective Date " << '|' << setw(10) << " Road Tax Expiry Date " << '|' << setw(10) << " Vehicle Age (Year) " << '|' << endl;
	cout << "--------------------------------------------------------------------------------------\n";
	
	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(17) << rs->getString("RegistrationNo") << '|' << setw(16) << rs->getString("MAX(EffectiveDate)") << '|' << setw(22) << rs->getString("MAX(ExpiryDate)") << '|' << setw(20) << rs->getDouble("COUNT(*)") << '|' << endl;
		cout << "--------------------------------------------------------------------------------------\n";
	}

	delete ps;
}


