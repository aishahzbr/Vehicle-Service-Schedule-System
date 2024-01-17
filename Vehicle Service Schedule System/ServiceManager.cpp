#include <string>
#include <sstream> 
#include <iomanip>
#include <conio.h>
#include <Windows.h>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "Service.h"
#include "Vehicle.h"
#include "VehicleManager.h"
#include "ServiceManager.h"
#include "DatabaseConnection.h"

void manageservice();

int ServiceManager::addService(Service* service)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Service VALUES (?, ?, ?, ?, ?, ?, ?, ?)");

	ps->setString(1, service->regID); // 1 referring to first ?
	ps->setString(2, service->receiptno);
	ps->setString(3, service->date);
	ps->setDouble(4, service->cost);
	ps->setDouble(5, service->servicemileage);
	ps->setDouble(6, service->nextmileage);
	ps->setString(7, service->datemileage);
	ps->setString(8, service->servicetype);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}

void ServiceManager::searchService(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Service WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	if (!rs->next())
	{
		cout << " Vehicle Service Details doesn't exists. " << endl << endl;
		manageservice();
	}

	cout << "-----------------------------------------------------------------------";
	cout << "----------------------------------------------------------------------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(10) << " Receipt No " << '|' << setw(15) << " Date " << '|' << setw(10) << " Service Cost (RM) " << '|' << setw(10) << " Service Mileage (km) " << '|' << setw(10) << " Next Service Mileage (km) " << '|' << setw(10) << " Date of Next Service Mileage " << '|' << setw(10) << " Service Type " << '|' << endl;
	cout << "-----------------------------------------------------------------------";
	cout << "----------------------------------------------------------------------------------\n";

	do
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(12) << rs->getString("ReceiptNo") << '|' << setw(15) << rs->getString("Date") << '|' << setw(19) << rs->getDouble("Cost") << '|'  << setw(22) << rs->getDouble("ServiceMileage") << '|' << setw(27) << rs->getDouble("NextMileage") << '|' << setw(30) << rs->getString("DateMileage") << '|' << setw(14) << rs->getString("ServiceType") << '|' << endl;
		cout << "-----------------------------------------------------------------------";
		cout << "----------------------------------------------------------------------------------\n";
	} while (rs->next());

	delete ps;
}

int ServiceManager::updateReceiptNo(Service* service, string regID, string receiptno)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Service SET ReceiptNo = (?) WHERE RegistrationNo = (?) AND ReceiptNo = (?)");

	ps->setString(1, service->receiptno);
	ps->setString(2, regID);
	ps->setString(3, receiptno);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

int ServiceManager::updateDate(Service* service, string regID, string receiptno)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Service SET Date = (?) WHERE RegistrationNo = (?) AND ReceiptNo = (?)");

	ps->setString(1, service->date);
	ps->setString(2, regID);
	ps->setString(3, receiptno);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

int ServiceManager::updateServiceCost(Service* service, string regID, string receiptno)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Service SET Cost = (?) WHERE RegistrationNo = (?) AND ReceiptNo = (?)");

	ps->setDouble(1, service->cost);
	ps->setString(2, regID);
	ps->setString(3, receiptno);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}


int ServiceManager::updateCurrentMileage(Service* service, string regID, string receiptno)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Service SET ServiceMileage = (?) WHERE RegistrationNo = (?) AND ReceiptNo = (?)");

	ps->setDouble(1, service->servicemileage);
	ps->setString(2, regID);
	ps->setString(3, receiptno);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

int ServiceManager::updateNextMileage(Service* service, string regID, string receiptno)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Service SET NextMileage = (?) WHERE RegistrationNo = (?) AND ReceiptNo = (?)");

	ps->setDouble(1, service->nextmileage);
	ps->setString(2, regID);
	ps->setString(3, receiptno);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

int ServiceManager::updateDateNextMileage(Service* service, string regID, string receiptno)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Service SET DateMileage = (?) WHERE RegistrationNo = (?) AND ReceiptNo = (?)");

	ps->setString(1, service->datemileage);
	ps->setString(2, regID);
	ps->setString(3, receiptno);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

int ServiceManager::updateServiceType(Service* service, string regID, string receiptno)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Service SET ServiceType = (?) WHERE RegistrationNo = (?) AND ReceiptNo = (?)");

	ps->setString(1, service->servicetype);
	ps->setString(2, regID);
	ps->setString(3, receiptno);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}


int ServiceManager:: deleteService(string regID, string receiptno)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Service WHERE RegistrationNo = (?) AND ReceiptNo = (?)");

	ps->setString(1, regID);
	ps->setString(2, receiptno);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

void ServiceManager::showReceiptNo(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Service WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << "--------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(10) << " Receipt No " << '|' << endl;
	cout << "--------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(12) << rs->getString("ReceiptNo") << '|' << endl;
		cout << "--------------------\n";
	}

	delete ps;
}

void ServiceManager::showDate(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Service WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << "------------------------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(10) << " Receipt No " << '|' << setw(15) << " Date " << '|' << endl;
	cout << "------------------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(12) << rs->getString("ReceiptNo") << '|' << setw(15) << rs->getString("Date") << '|' << endl;
		cout << "------------------------------------\n";
	}

	delete ps;
}

void ServiceManager::showServiceCost(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Service WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << "----------------------------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(10) << " Receipt No " << '|' << setw(15) << " Service Cost (RM) " << '|' << endl;
	cout << "----------------------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(12) << rs->getString("ReceiptNo") << '|' << setw(19) << rs->getDouble("Cost") << '|' << endl;
		cout << "----------------------------------------\n";
	}

	delete ps;
}

void ServiceManager::showServiceMileage(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Service WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << "-------------------------------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(10) << " Receipt No " << '|' << setw(15) << " Service Mileage (km) " << '|' << endl;
	cout << "-------------------------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(12) << rs->getString("ReceiptNo") << '|' << setw(22) << rs->getDouble("ServiceMileage") << '|' << endl;
		cout << "-------------------------------------------\n";
	}

	delete ps;
}

void ServiceManager::showNextMileage(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Service WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << "------------------------------------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(10) << " Receipt No " << '|' << setw(15) << " Next Service Mileage (km) " << '|' << endl;
	cout << "------------------------------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(12) << rs->getString("ReceiptNo") << '|' << setw(27) << rs->getDouble("NextMileage") << '|' << endl;
		cout << "------------------------------------------------\n";
	}

	delete ps;
}

void ServiceManager::showDateNextMileage(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Service WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << "---------------------------------------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(10) << " Receipt No " << '|' << setw(15) << " Date of Next Service Mileage " << '|' << endl;
	cout << "---------------------------------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(12) << rs->getString("ReceiptNo") << '|' << setw(30) << rs->getString("DateMileage") << '|' << endl;
		cout << "---------------------------------------------------\n";
	}

	delete ps;
}

void ServiceManager::showServiceType(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Service WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << "------------------------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(10) << " Receipt No " << '|' << setw(15) << " Service Type " << '|' << endl;
	cout << "------------------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(12) << rs->getString("ReceiptNo") << '|' << setw(15) << rs->getString("ServiceType") << '|' << endl;
		cout << "------------------------------------\n";
	}

	delete ps;
}

void ServiceManager::notifyServiceDate(string username)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Service INNER JOIN vehicle ON service.RegistrationNo = vehicle.RegistrationNo WHERE vehicle.UserID LIKE ? AND DateMileage BETWEEN DATE_SUB(CURDATE(), INTERVAL 1 WEEK) and DATE_ADD(CURDATE(), INTERVAL 1 WEEK)");
	ps->setString(1, username);
	ResultSet* rs = ps->executeQuery();

	while (rs->next())
	{
		c = a++;
		cout << "\n " << c << ". ";
		cout << "Registration No               : " << rs->getString("RegistrationNo") << endl
			 << "    Date of Next Service Mileage  : " << rs->getString("DateMileage") << endl << endl;
	}
	delete ps;
}

void ServiceManager::notifyMileage(string regID)
{
	double currentmileage;
	cout << " Enter Current Mileage in km (E.g: 10000): ";
	cin >> currentmileage;
	cout << endl;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT MAX(NextMileage) FROM Service WHERE RegistrationNo = (?)");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	while (rs->next())
	{
		cout << " Next Service Mileage: " << rs->getDouble("MAX(NextMileage)") << " km" << endl << endl;
		if (currentmileage < rs->getDouble("MAX(NextMileage)"))
		{
			cout << " * You have " << rs->getDouble("MAX(NextMileage)") - currentmileage << " km left until your next service. *\n";
		}

		else if (currentmileage > rs->getDouble("MAX(NextMileage)"))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "\t\t !! ATTENTION !!\n";
			cout << " Your Current Mileage has exceeded.\n Please send your car for service immediately!\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}

		else
		{
			cout << " Your current mileage is the same as next service mileage.\n";
		}
	}
	delete ps;
}
