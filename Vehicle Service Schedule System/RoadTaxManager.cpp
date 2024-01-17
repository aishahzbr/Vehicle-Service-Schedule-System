#include <string>
#include <iomanip>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "Vehicle.h"
#include "VehicleManager.h"
#include "RoadTax.h"
#include "RoadTaxManager.h"
#include "DatabaseConnection.h"

void manageroadtax();

int RoadTaxManager::addroadtax(RoadTax* roadtax)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO roadtax VALUES (?, ?, ?, ?, ?, ?, ?)");

	ps->setString(1, roadtax->regID); // 1 referring to first ?
	ps->setString(2, roadtax->roadtaxid);
	ps->setString(3, roadtax->effectivedate);
	ps->setString(4, roadtax->exdate);
	ps->setString(5, roadtax->policy);
	ps->setString(6, roadtax->startdate);
	ps->setString(7, roadtax->enddate);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int RoadTaxManager::updateRoadTaxID(RoadTax* roadtax, string regID, string roadtaxid)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE roadtax SET RoadTaxID = (?) WHERE RegistrationNo = (?) AND RoadTaxID = (?)");

	ps->setString(1, roadtax->roadtaxid);
	ps->setString(2, regID);
	ps->setString(3, roadtaxid);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

int RoadTaxManager::updateEffectiveDate(RoadTax* roadtax, string regID, string roadtaxid)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE roadtax SET EffectiveDate = (?) WHERE RegistrationNo = (?) AND RoadTaxID = (?)");

	ps->setString(1, roadtax->effectivedate);
	ps->setString(2, regID);
	ps->setString(3, roadtaxid);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}


int RoadTaxManager::updateExpiryDate(RoadTax* roadtax, string regID, string roadtaxid)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE roadtax SET ExpiryDate = (?) WHERE RegistrationNo = (?) AND RoadTaxID = (?)");

	ps->setString(1, roadtax->exdate);
	ps->setString(2, regID);
	ps->setString(3, roadtaxid);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

int RoadTaxManager::updatePolicyNo(RoadTax* roadtax, string regID, string roadtaxid)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE roadtax SET PolicyNo = (?) WHERE RegistrationNo = (?) AND RoadTaxID = (?)");

	ps->setString(1, roadtax->policy);
	ps->setString(2, regID);
	ps->setString(3, roadtaxid);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

int RoadTaxManager::updateStartDate(RoadTax* roadtax, string regID, string roadtaxid)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE roadtax SET StartDate = (?) WHERE RegistrationNo = (?) AND RoadTaxID = (?)");

	ps->setString(1, roadtax->startdate);
	ps->setString(2, regID);
	ps->setString(3, roadtaxid);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

int RoadTaxManager::updateEndDate(RoadTax* roadtax, string regID, string roadtaxid)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE roadtax SET EndDate = (?) WHERE RegistrationNo = (?) AND RoadTaxID = (?)");

	ps->setString(1, roadtax->enddate);
	ps->setString(2, regID);
	ps->setString(3, roadtaxid);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

void RoadTaxManager::searchroadtax(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM roadtax WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	if (!rs->next())
	{
		cout << " Vehicle Road Tax Details doesn't exist." << endl << endl;
		manageroadtax();
	}

	cout << "-----------------------------------------------------------------------";
	cout << "----------------------------------------------------------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(15) << " Road Tax ID " << '|' << setw(15) << " Effective Date " << '|' << setw(10) << " Road Tax Expiry Date " << '|' << setw(15) << " Policy No " << '|' << setw(10) << " Policy / Insurance Start Date " << '|' << setw(10) << " Policy / Insurance End Date " << '|' << endl;
	cout << "-----------------------------------------------------------------------";
	cout << "----------------------------------------------------------------------\n";

	do
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(15) << rs->getString("RoadTaxID") << '|' << setw(16) << rs->getString("EffectiveDate") << '|' << setw(22) << rs->getString("ExpiryDate") << '|' << setw(15) << rs->getString("PolicyNo") << '|' << setw(31) << rs->getString("StartDate") << '|' << setw(29) << rs->getString("EndDate") << '|' << endl;
		cout << "-----------------------------------------------------------------------";
		cout << "----------------------------------------------------------------------\n";
	} while (rs->next());

	delete ps;
}

void RoadTaxManager::showRoadTaxID(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM roadtax WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << "------------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(15) << " Road Tax ID " << '|' << endl;
	cout << "------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(15) << rs->getString("RoadTaxID") << '|' << endl;
		cout << "------------------------\n";
	}

	delete ps;
}

void RoadTaxManager::showEffectiveDate(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM roadtax WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << "----------------------------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(15) << " Road Tax ID " << '|' << setw(15) << " Effective Date " << '|' << endl;
	cout << "----------------------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(15) << rs->getString("RoadTaxID") << '|' << setw(16) << rs->getString("EffectiveDate") << '|' << endl;
		cout << "----------------------------------------\n";
	}

	delete ps;
}

void RoadTaxManager::showExpiryDate(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM roadtax WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << "---------------------------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(15) << " Road Tax ID " << '|' << setw(15) << " Expiry Date " << '|' << endl;
	cout << "---------------------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(15) << rs->getString("RoadTaxID") << '|' << setw(15) << rs->getString("ExpiryDate") << '|' << endl;
		cout << "---------------------------------------\n";
	}

	delete ps;
}

void RoadTaxManager::showPolicyNo(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM roadtax WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << "---------------------------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(15) << " Road Tax ID " << '|' << setw(15) << " Policy No " << '|' << endl;
	cout << "---------------------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(15) << rs->getString("RoadTaxID") << '|' << setw(15) << rs->getString("PolicyNo") << '|' << endl;
		cout << "---------------------------------------\n";
	}

	delete ps;
}

void RoadTaxManager::showStartDate(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM roadtax WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << "-------------------------------------------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(15) << " Road Tax ID " << '|' << setw(15) << " Policy / Insurance Start Date " << '|' << endl;
	cout << "-------------------------------------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(15) << rs->getString("RoadTaxID") << '|' << setw(31) << rs->getString("StartDate") << '|' << endl;
		cout << "-------------------------------------------------------\n";
	}

	delete ps;
}

void RoadTaxManager::showEndDate(string regID)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM roadtax WHERE RegistrationNo LIKE ?");

	ps->setString(1, regID);

	ResultSet* rs = ps->executeQuery();

	cout << "-----------------------------------------------------\n";
	cout << '|' << setw(5) << "No " << '|' << setw(15) << " Road Tax ID " << '|' << setw(15) << " Policy / Insurance End Date " << '|' << endl;
	cout << "-----------------------------------------------------\n";

	while (rs->next())
	{
		c = a++;
		cout << '|' << setw(5) << c << '|' << setw(15) << rs->getString("RoadTaxID") << '|' << setw(29) << rs->getString("EndDate") << '|' << endl;
		cout << "-----------------------------------------------------\n";
	}

	delete ps;
}

int RoadTaxManager::deleteroadtax(string regID, string roadtaxid)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM roadtax WHERE RegistrationNo = (?) AND RoadTaxID = (?)");

	ps->setString(1, regID);
	ps->setString(2, roadtaxid);

	int status = ps->executeUpdate();
	delete ps;
	return status;
}

void RoadTaxManager::notifyRoadTax(string username)
{
	int a = 1;
	int c;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM roadtax INNER JOIN vehicle ON roadtax.RegistrationNo = vehicle.RegistrationNo WHERE vehicle.UserID LIKE ? AND ExpiryDate BETWEEN DATE_SUB(CURDATE(), INTERVAL 1 WEEK) and DATE_ADD(CURDATE(), INTERVAL 1 WEEK)");
	ps->setString(1, username);
	ResultSet* rs = ps->executeQuery();

	while (rs->next())
	{
		c = a++;
		cout << "\n " << c << ". ";
		cout << "Registration No       : " << rs->getString("RegistrationNo") << endl
			<< "    Road Tax Expiry Date  : " << rs->getString("ExpiryDate") << endl << endl;
	}
	delete ps;
}

