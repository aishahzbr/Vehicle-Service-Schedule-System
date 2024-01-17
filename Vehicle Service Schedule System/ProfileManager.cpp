#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "Vehicle.h"
#include "Profile.h"
#include "ProfileManager.h"
#include "VehicleManager.h"
#include "DatabaseConnection.h"

string userID;

bool ProfileManager::login(Profile* profile)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM User WHERE UserID = (?)");
	ps->setString(1, profile->userID);
	ResultSet* rs = ps->executeQuery();
	
	if (!(rs->next()))
	{
		system("cls");
		cout << "Username is wrong. Please insert again." << endl;
		system("pause");
		return false;
		delete rs;
		delete ps;
	}
	
	else
	{
		delete rs;
		delete ps;
		ps = dbConn.prepareStatement("SELECT * FROM User WHERE UserID = (?) AND Password = (?)");
		ps->setString(1, profile->userID);
		ps->setString(2, profile->password);
		rs = ps->executeQuery();
		
		if (!(rs->next())) {
			system("cls");
			cout << "Password is wrong. Please insert again." << endl;
			system("pause");
			return false;
			delete rs;
			delete ps;
		}
		delete rs;
		delete ps;
	}
	return true;
}

