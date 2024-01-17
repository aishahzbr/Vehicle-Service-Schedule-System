#include <iostream>
#include <mysql.h>
#include <ctime>
#include <string>
#include <iomanip>
#include <string.h>
#include <conio.h>
#pragma warning(disable : 4996)
using namespace std;

#include "Vehicle.h"
#include "VehicleManager.h"
#include "Service.h"
#include "RoadTax.h"
#include "Profile.h"
#include "ProfileManager.h"
#include "ServiceManager.h"
#include "RoadTaxManager.h"
#include "GenerateReport.h"

string username;

bool userLogin();
void mainmenu();
void managevehicle();
void manageservice();
void manageroadtax();
void generatereport();
void reminder();
void updateVehicle(string regID);
void deactivateVehicle(Vehicle* vehicle, string regID);
void updateService(string regID, string receiptno);
void updateRoadTax(string regID, string roadtaxid);
void vehicleReport();

int main()
{
	userLogin();
	mainmenu();
	return 0;
}

bool userLogin()
{
	system("cls");
	ProfileManager profileManager;
	Profile* profile = new Profile();
	int i = 0;
	char a;
	bool check = true;
	while (check)
	{
		cout << "   VEHICLE SCHEDULE SERVICE SYSTEM  \n\n";
		cout << "             LOGIN\n";
		cout << "          -----------\n";
		cout << "\n Username  : ";
		cin >> profile->userID;
		username = profile->userID;
		if (profile->userID == "0") {
			return "0";
		}
		system("cls");
		cout << "   VEHICLE SCHEDULE SERVICE SYSTEM  \n\n";
		cout << "             LOGIN\n";
		cout << "          -----------\n";
		cout << "\n Username  : " << username << endl;
		cout << "\n Password  : ";
		string pass;
		for (i = 0;;) {
			a = _getch();
			if (a >= 'a' && a <= 'z' || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9')) {

				pass += a;
				++i;
				cout << "*";

			}
			if (a == '\b' && i >= 1) {
				cout << "\b \b";
				--i;
			}
			if (a == '\r') {
				break;
			}
		}

		profile->password = pass;
		if (profile->password == "0") {
			return "0";
		}

		if (profileManager.login(profile))
		{
			check = false;
		}
		
		else
		{
			check = true;
		}
		system("cls");
	}
	return 0;
}

void mainmenu()
{
	int choicemainmenu = 0;
	do
	{
		cout << "   VEHICLE SCHEDULE SERVICE SYSTEM  \n\n";
		cout << "             MAIN MENU\n";
		cout << "            -----------\n";
		cout << " 1. Vehicle\n";
		cout << " 2. Service\n";
		cout << " 3. Road Tax\n";
		cout << " 4. Report\n";
		cout << " 5. Reminder\n";
		cout << " 6. Exit\n";
		cout << " Enter menu: ";
		cin >> choicemainmenu;
		system("cls");

		if (choicemainmenu < 1 || choicemainmenu > 6)
		{
			cout << "\n Sorry, wrong menu. Please re-enter menu.\n";
			cout << endl;
		}

	} while (choicemainmenu < 1 || choicemainmenu > 6);

	if (choicemainmenu == 1)
	{
		managevehicle();
	}

	else if (choicemainmenu == 2)
	{
		manageservice();
	}

	else if (choicemainmenu == 3)
	{
		manageroadtax();
	}

	else if (choicemainmenu == 4)
	{
		generatereport();
	}

	else if (choicemainmenu == 5)
	{
		reminder();
	}

	else
	{
		exit(0);
	}

}

void managevehicle()
{
	int choice;
	int menu;
	int choicemanagevehicle;
	VehicleManager vehicleManager;
	Profile* profile = new Profile();
	Vehicle* vehicle = new Vehicle();
	string regID, type, model, colour;
	do
	{
		cout << "-MANAGE VEHICLE-";
		cout << "\n 1 Register Vehicle\n 2 Search Vehicle\n 3 Deactivate Vehicle\n 4 Update Vehicle\n 5 Return to Main Menu\n";
		cout << " Enter choice: ";
		cin >> choicemanagevehicle;
		system("cls");

		if (choicemanagevehicle == 1)
		{
			// add vehicle
			cout << " Add Vehicle's Information is chosen.";
			cout << "\n---------------------------------------";
			cout << "\n -Please Fill in Information Below-";
			cout << "\n---------------------------------------";
			cout << "\n Registration No [Press c to Cancel]: ";
			cin >> vehicle->regID;
				if (vehicle->regID == "c" || vehicle->regID == "C")
				{	
					system("cls");
					managevehicle();
				}
			cout << "\n -Choose Vehicle Type-\n 1 Hatchback\n 2 Sedan\n 3 Van\n 4 Pickup\n 5 SUV\n 6 Others (Please Specify)";
			cout << "\n Vehicle Type: ";
			cin >> choice;

			if (choice == 1)
			{
				vehicle->type = "Hatchback";
			}

			else if (choice == 2)
			{
				vehicle->type = "Sedan";
			}

			else if (choice == 3)
			{
				vehicle->type = "Van";
			}

			else if (choice == 4)
			{
				vehicle->type = "Pickup";
			}

			else if (choice == 5)
			{
				vehicle->type = "SUV";
			}

			else if (choice == 6)
			{
				cout << "      (Specify): ";
				cin >> vehicle->type;
			}

			cout << "\n Vehicle Model (E.g: Toyota): ";
			cin >> vehicle->model;
			cout << "\n Vehicle Colour: ";
			cin >> vehicle->colour;
			cout << "\n Vehicle Status: Registered ";
			vehicle->status = "Registered";
			username;

			cout << endl;

			int status = vehicleManager.registerVehicle(vehicle, username);

			if (status != 0)
				cout << "\nSuccessfully add New Vehicle.\n\n";
			else
				cout << "Failed to add New vehicle.\n";

			system("pause");
			system("cls");
		}

		else if (choicemanagevehicle == 2)
		{
			// search vehicle
			cout << "-------Search Vehicle-------";
			cout << "\n----------------------------\n ";
			cout << " -Registration No List-\n\n";
			vehicleManager.displayID(username);
			cout << "\n Enter Vehicle's Registration No (E.g: XXX0000) [Press c to Cancel]: ";
			cin >> regID;
				if (regID == "c" || regID == "C")
				{
					system("cls");
					managevehicle();
				}
			cout << endl;
			vehicleManager.searchVehicles(regID);
			cout << endl;

			do {
				cout << " --Please Choose--\n 1 Deactivate Vehicle\n 2 Update Vehicle\n 3 Return to Menu\n";
				cout << " Enter choice: ";
				cin >> menu;
				system("cls");
				if (menu == 1)
				{
					// deactivate
					cout << " - Deactivate Vehicle-\n";
					deactivateVehicle(vehicle, regID);
					system("pause");
					system("cls");
				}

				else if (menu == 2)
				{
					updateVehicle(regID);
				}

				else if (menu == 3)
				{
					managevehicle();
				}

				else
				{
					cout << "\n Sorry, wrong menu. Please re-enter menu.\n";
					cout << endl;
				}
			} while (menu < 1 || menu > 3);
		}

		else if (choicemanagevehicle == 3)
		{
			// deactivate vehicle
			cout << " -To Deactivate Vehicle-\n";
			cout << "\n -Choose from the Registration No List-\n\n";
			vehicleManager.deactivateID("Registered", username);
			cout << "\n Enter Vehicle's Registration No (E.g: XXX0000) [Press c to Cancel]: ";
			cin >> regID;
				if (regID == "c" || regID == "C")
				{
					system("cls");
					managevehicle();
				}
			cout << endl;

			deactivateVehicle(vehicle, regID);
		}

		else if (choicemanagevehicle == 4)
		{
			// update vehicle
			cout << " -To Update Vehicle's Information-\n";
			cout << "\n -Choose from the Registration No List-\n\n";
			vehicleManager.deactivateID("Registered", username);

			cout << "\n Enter Vehicle's Registration No (E.g: XXX0000) [Press c to Cancel]: ";
			cin >> regID;
				if (regID == "c" || regID == "C")
				{
					system("cls");
					managevehicle();
				}
			cout << endl;
			vehicleManager.searchVehicles(regID);
			cout << endl;

			updateVehicle(regID);
		}

		else if (choicemanagevehicle == 5)
		{
			mainmenu();
			return;
		}

		else
		{
			cout << "\n Sorry, wrong menu. Please re-enter menu.\n";
			cout << endl;
		}

	} while (choicemanagevehicle >= 1 || choicemanagevehicle <= 5);
}

void deactivateVehicle(Vehicle* vehicle, string regID)
{
	VehicleManager vehicleManager;

	cout << "\n Vehicle Status: Deactivate";
	vehicle->status = "Deactivate";

	int status = vehicleManager.deactivateVehicle(vehicle, regID);

	if (status != 0) {
		cout << "\n Successfully Deactivate Vehicle.\n\n";
	}
	else
		cout << "\nFailed to Deactivate Vehicle.\n\n";

	return;
}

void updateVehicle(string regID)
{
	int choiceupdate;
	VehicleManager vehicleManager;
	Vehicle* vehicle = new Vehicle();
	do {
		cout << " Update Vehicle is chosen.";
		cout << "\n----------------------------";
		cout << "\n --Please Choose--\n 1 Update Registration No\n 2 Update Vehicle Type\n 3 Update Vehicle Model\n 4 Update Vehicle Colour\n 5 Return to Menu\n";
		cout << " Enter Choice: ";
		cin >> choiceupdate;
		system("cls");

		if (choiceupdate == 1)
		{
			vehicleManager.showupdateVehicleID(regID);
			cout << "\n -Update Registration No-";
			cout << "\n---------------------------";
			cout << "\n Enter New Registration No: ";
			cin >> vehicle->regID;

			int status = vehicleManager.updateVehicleID(vehicle, regID);
			if (status != 0)
				cout << "\nSuccessfully update Vehicle's Registration No.\n\n";
			else
				cout << "\nFailed to update Vehicle's Registration No.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdate == 2)
		{
			int choice;
			vehicleManager.showupdateVehicleType(regID);
			cout << "\n -Update Vehicle Type-";
			cout << "\n-----------------------";
			cout << "\n -Choose Vehicle Type-\n 1 Hatchback\n 2 Sedan\n 3 Van\n 4 Pickup\n 5 SUV\n 6 Others (Please Specify)";
			cout << "\n Enter New Vehicle Type: ";
			cin >> choice;

			if (choice == 1)
			{
				vehicle->type = "Hatchback";
			}

			else if (choice == 2)
			{
				vehicle->type = "Sedan";
			}

			else if (choice == 3)
			{
				vehicle->type = "Van";
			}

			else if (choice == 4)
			{
				vehicle->type = "Pickup";
			}

			else if (choice == 5)
			{
				vehicle->type = "SUV";
			}

			else if (choice == 6)
			{
				cout << "      (Specify): ";
				cin >> vehicle->type;
			}

			int status = vehicleManager.updateVehicleType(vehicle, regID);
			if (status != 0)
				cout << "\nSuccessfully update Vehicle's Type.\n\n";
			else
				cout << "\nFailed to update Vehicle's Type.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdate == 3)
		{
			vehicleManager.showupdateVehicleModel(regID);
			cout << "\n -Update Vehicle Model-";
			cout << "\n-----------------------";
			cout << "\n Enter New Vehicle Model (E.g: Toyota): ";
			cin >> vehicle->model;

			int status = vehicleManager.updateVehicleModel(vehicle, regID);
			if (status != 0)
				cout << "\nSuccessfully update Vehicle's Model.\n\n";
			else
				cout << "\nFailed to update Vehicle's Model.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdate == 4)
		{
			vehicleManager.showupdateVehicleColour(regID);
			cout << "\n -Update Vehicle Colour-";
			cout << "\n--------------------------";
			cout << "\n Enter New Vehicle Colour: ";
			cin >> vehicle->colour;

			int status = vehicleManager.updateVehicleColour(vehicle, regID);
			if (status != 0)
				cout << "\nSuccessfully update Vehicle's Colour.\n\n";
			else
				cout << "\nFailed to update Vehicle's Colour.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdate == 5)
		{
			managevehicle();
			return;
		}

		else
		{
			cout << "\n Sorry, wrong menu. Please re-enter menu.\n";
			cout << endl;
		}
	} while (choiceupdate >= 1 || choiceupdate <= 5);
}

void manageservice()
{
	int choicemanageservice, menu;
	string regID, receiptno;

	VehicleManager vehicleManager;
	Vehicle* vehicle = new Vehicle();

	ServiceManager serviceManager;
	Service* service = new Service();
	do {
		cout << "-MANAGE SERVICE-";
		cout << "\n 1 Add Vehicle Service Details\n 2 Search Vehicle Service Details\n 3 Update Vehicle Service Details\n";
		cout << " 4 Delete Vehicle Service Details\n 5 Return to Main Menu\n";
		cout << " Enter choice: ";
		cin >> choicemanageservice;
		cout << endl;
		system("cls");

		if (choicemanageservice == 1)
		{
			cout << " Add Vehicle Service Details is chosen.";
			cout << "\n---------------------------------------";
			cout << "\n-Choose from the Registration No List-\n\n";
			vehicleManager.deactivateID("Registered", username);
			cout << "\n -Please Fill in Information Below-";
			cout << "\n---------------------------------------";
			cout << "\n Registration No (E.g: XXX0000) [Press c to Cancel]: ";
			cin >> service->regID;
				if (service->regID == "c" || service->regID == "C")
				{
					system("cls");
					manageservice();
				}
			cout << " Receipt No: ";
			cin >> service->receiptno; 
			cout << " Date (E.g: YYYY-MM-DD): ";
			cin >> service->date;
			cout << " Service Cost: RM ";
			cin >> service->cost;
			cout << " Service Mileage in km (E.g: 10000): ";
			cin >> service->servicemileage;
			cout << " Next Service Mileage in km (E.g: 10000): ";
			cin >> service->nextmileage;
			cout << " Date of Next Service Mileage: ";
			cin >> service->datemileage;
			cout << " Service Type (Major / Minor): ";
			cin >> service->servicetype;

			int status = serviceManager.addService(service);

			if (status != 0)
				cout << "\nSuccessfully add Vehicle's Service Details.\n\n";
			else
				cout << "\nFailed to add Vehicle's Service Details.\n\n";

			system("pause");
			system("cls");
		}

		else if (choicemanageservice == 2)
		{
			//search service
			cout << "-----Search Service Details-----";
			cout << "\n--------------------------------\n ";
			cout << " -Registration No List-\n\n";
			vehicleManager.deactivateID("Registered", username);
			cout << "\n Enter Vehicle's Registration No (E.g: XXX0000) [Press c to Cancel]: ";
			cin >> regID;
				if (regID == "c" || regID == "C")
				{
					system("cls");
					manageservice();
				}
			cout << endl;
			serviceManager.searchService(regID);
			cout << endl;

			do {
				cout << " --Please Choose--\n 1 Delete Service Details\n 2 Update Service Details\n 3 Return to Menu\n";
				cout << " Enter choice: ";
				cin >> menu;
				system("cls");
				if (menu == 1)
				{
					// delete
					cout << " Delete Vehicle Service Details is chosen.";
					cout << "\n------------------------------------------\n";
					serviceManager.showReceiptNo(regID);
					cout << "\n Enter Receipt No: ";
					cin >> receiptno;

					int status = serviceManager.deleteService(regID, receiptno);

					if (status != 0)
						cout << "\nSuccessfully delete Vehicle's Service Details.\n\n";
					else
						cout << "\nFailed to delete Vehicle's Service Details.\n\n";

					system("pause");
					system("cls");
				}

				else if (menu == 2)
				{
					// update
					updateService(regID, receiptno);
				}

				else if (menu == 3)
				{
					manageservice();
					return;
				}

				else
				{
					cout << "\n Sorry, wrong menu. Please re-enter menu.\n";
					cout << endl;
				}
			} while (menu < 1 || menu > 3);
		}

		else if (choicemanageservice == 3)
		{
			//update service
			cout << " -To Update Vehicle's Service Details-\n";
			cout << "\n -Choose from the Registration No List-\n\n";
			vehicleManager.deactivateID("Registered", username);

			cout << "\n Enter Vehicle's Registration No (E.g: XXX0000) [Press c to Cancel]: ";
			cin >> regID;
				if (regID == "c" || regID == "C")
				{
					system("cls");
					manageservice();
				}
			cout << endl;
			serviceManager.searchService(regID);
			cout << endl;
			updateService(regID, receiptno);
		}

		else if (choicemanageservice == 4)
		{
			//delete service
			cout << " -To Delete Vehicle's Service Details-\n";
			cout << "\n -Choose from the Registration No List-\n\n";
			vehicleManager.deactivateID("Registered", username);
			cout << "\n Enter Vehicle's Registration No (E.g: XXX0000) [Press c to Cancel]: ";
			cin >> regID;
			cout << endl;
				if (regID == "c" || regID == "C")
				{
					system("cls");
					manageservice();
				}
			serviceManager.showReceiptNo(regID);
			cout << "\n Enter Receipt No [Press c to Cancel]: ";
			cin >> receiptno;
			cout << endl;
				if (receiptno == "c" || receiptno == "C")
				{
					system("cls");
					manageservice();
				}
			int status = serviceManager.deleteService(regID, receiptno);

			if (status != 0)
				cout << "\nSuccessfully delete Vehicle's Service Details.\n\n";
			else
				cout << "\nFailed to delete Vehicle's Service Details.\n\n";

			system("pause");
			system("cls");
		}

		else if (choicemanageservice == 5)
		{
			mainmenu();
			return;
		}

		else
		{
			cout << "\n Sorry, wrong menu. Please re-enter menu.\n";
			cout << endl;
		}
	} while (choicemanageservice >= 1 || choicemanageservice <= 5);
}

void updateService(string regID, string receiptno)
{
	int choiceupdateservice;

	ServiceManager serviceManager;
	Service* service = new Service();
	do
	{
		cout << " Update Service Details is chosen.";
		cout << "\n-----------------------------------";
		cout << "\n --Please Choose--\n 1 Update Receipt No\n 2 Update Date\n 3 Update Service Cost\n 4 Update Service Mileage";
		cout << "\n 5 Update Next Service Mileage\n 6 Update Date of Next Service Mileage\n 7 Update Service Type\n 8 Return to Menu\n";
		cout << " Enter Choice: ";
		cin >> choiceupdateservice;
		system("cls");

		if (choiceupdateservice == 1)
		{
			serviceManager.showReceiptNo(regID);
			cout << "\n   -Update Receipt No-";
			cout << "\n---------------------------";
			cout << " \n Enter Receipt No: ";
			cin >> receiptno;
			cout << "\n Enter new Receipt No: ";
			cin >> service->receiptno;

			int status = serviceManager.updateReceiptNo(service, regID, receiptno);
			if (status != 0)
				cout << "\nSuccessfully update Receipt No.\n\n";
			else
				cout << "\nFailed to update Receipt No.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdateservice == 2)
		{
			serviceManager.showDate(regID);
			cout << "\n     -Update Date-";
			cout << "\n---------------------------";
			cout << " \n Enter Receipt No: ";
			cin >> receiptno;
			cout << "\n New Date (E.g: YYYY-MM-DD): ";
			cin >> service->date;

			int status = serviceManager.updateDate(service, regID, receiptno);
			if (status != 0)
				cout << "\nSuccessfully update Date.\n\n";
			else
				cout << "\nFailed to update Date.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdateservice == 3)
		{
			serviceManager.showServiceCost(regID);
			cout << "\n -Update Service Cost-";
			cout << "\n---------------------------";
			cout << " \n Enter Receipt No: ";
			cin >> receiptno;
			cout << "\n New Service Cost: RM ";
			cin >> service->cost;

			int status = serviceManager.updateServiceCost(service, regID, receiptno);
			if (status != 0)
				cout << "\nSuccessfully update Service Cost.\n\n";
			else
				cout << "\nFailed to update Service Cost.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdateservice == 4)
		{
			serviceManager.showServiceMileage(regID);
			cout << "\n -Update Service Mileage-";
			cout << "\n------------------------------------";
			cout << " \n Enter Receipt No: ";
			cin >> receiptno;
			cout << "\n New Service Mileage in km (E.g: 10000): ";
			cin >> service->servicemileage;

			int status = serviceManager.updateCurrentMileage(service, regID, receiptno);
			if (status != 0)
				cout << "\nSuccessfully update Service Mileage.\n\n";
			else
				cout << "\nFailed to update Service Mileage.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdateservice == 5)
		{
			serviceManager.showNextMileage(regID);
			cout << "\n -Update Next Service Mileage-";
			cout << "\n---------------------------------";
			cout << " \n Enter Receipt No: ";
			cin >> receiptno;
			cout << "\n New Next Service Mileage in km (E.g: 10000): ";
			cin >> service->nextmileage;

			int status = serviceManager.updateNextMileage(service, regID, receiptno);
			if (status != 0)
				cout << "\nSuccessfully update Next Service Mileage.\n\n";
			else
				cout << "\nFailed to update Next Service Mileage.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdateservice == 6)
		{
			serviceManager.showDateNextMileage(regID);
			cout << "\n -Update Date of Next Service Mileage-";
			cout << "\n---------------------------------";
			cout << " \n Enter Receipt No: ";
			cin >> receiptno;
			cout << "\n Date of Next Service Mileage (E.g: YYYY-MM-DD): ";
			cin >> service->datemileage;

			int status = serviceManager.updateDateNextMileage(service, regID, receiptno);
			if (status != 0)
				cout << "\nSuccessfully update Date of Next Service Mileage.\n\n";
			else
				cout << "\nFailed to update Date of Next Service Mileage.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdateservice == 7)
		{
			serviceManager.showServiceType(regID);
			cout << "\n  -Update Service Type-";
			cout << "\n---------------------------";
			cout << " \n Enter Receipt No: ";
			cin >> receiptno;
			cout << "\n New Service Type (Major / Minor): ";
			cin >> service->servicetype;

			int status = serviceManager.updateServiceType(service, regID, receiptno);
			if (status != 0)
				cout << "\nSuccessfully update Service Type.\n\n";
			else
				cout << "\nFailed to update Service Type.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdateservice == 8)
		{
			manageservice();
			return;
		}

		else
		{
			cout << "\n Sorry, wrong menu. Please re-enter menu.\n";
			cout << endl;
		}
	} while (choiceupdateservice >= 1 || choiceupdateservice <= 8);
}

void manageroadtax()
{
	int menu;
	int choicemanageroadtax;
	string regID, roadtaxid;

	VehicleManager vehicleManager;

	RoadTaxManager roadtaxManager;
	RoadTax* roadtax = new RoadTax();

	do
	{
		cout << "-MANAGE ROAD TAX-\n";
		cout << " 1 Add Road Tax Details\n 2 Search Vehicle Road Tax\n 3 Update Road Tax Details\n 4 Delete Road Tax Details\n 5 Return to Main Menu\n";
		cout << " Enter choice: ";
		cin >> choicemanageroadtax;
		cout << endl;
		system("cls");

		if (choicemanageroadtax == 1)
		{
			//add road tax
			cout << " Add Vehicle Road Tax Details is chosen.";
			cout << "\n----------------------------------------\n";
			cout << " -Choose from the Registration No List-\n\n";
			vehicleManager.deactivateID("Registered", username);
			cout << "\n -Please Fill in Information Below-";
			cout << "\n----------------------------------------";
			cout << "\n Registration No (E.g: XXX0000) [Press c to Cancel]: ";
			cin >> roadtax->regID;
				if (roadtax->regID == "c" || roadtax->regID == "C")
				{
					system("cls");
					manageroadtax();
				}
			cout << " Road Tax ID: ";
			cin >> roadtax->roadtaxid;
			cout << " Vehicle Effective Date (E.g: YYYY-MM-DD): ";
			cin >> roadtax->effectivedate;
			cout << " Road Tax Expiry Date (E.g: YYYY-MM-DD): ";
			cin >> roadtax->exdate;
			cout << " Policy No: ";
			cin >> roadtax->policy;
			cout << " Policy / Insurance Start Date (E.g: YYYY-MM-DD): ";
			cin >> roadtax->startdate;
			cout << " Policy / Insurance End Date (E.g: YYYY-MM-DD): ";
			cin >> roadtax->enddate;

			int status = roadtaxManager.addroadtax(roadtax);
			if (status != 0)
				cout << "\nSuccessfully add Vehicle's Road Tax details.\n\n";
			else
				cout << "\n Failed to add Vehicle's Road Tax details.\n\n";

			system("pause");
			system("cls");
		}

		else if (choicemanageroadtax == 2)
		{
			//search road tax
			cout << "-----Search Road Tax Details-----";
			cout << "\n---------------------------------\n ";
			cout << " -Registration No List-\n\n";
			vehicleManager.deactivateID("Registered", username);
			cout << "\n Enter Vehicle's Registration No (E.g: XXX0000) [Press c to Cancel]: ";
			cin >> regID;
				if (regID == "c" || regID == "C")
				{
					system("cls");
					manageroadtax();
				}
			cout << endl;
			roadtaxManager.searchroadtax(regID);
			cout << endl;

			do {
				cout << " --Please Choose--\n 1 Delete Road Tax Details\n 2 Update Road Tax Details\n 3 Return to Menu\n";
				cout << " Enter choice: ";
				cin >> menu;
				system("cls");
				if (menu == 1)
				{
					// delete
					cout << " Delete Vehicle Road Tax Details is chosen.";
					cout << "\n------------------------------------------------\n";

					roadtaxManager.showRoadTaxID(regID);
					cout << "\n Enter Road Tax ID: ";
					cin >> roadtaxid;
					cout << endl;

					int status = roadtaxManager.deleteroadtax(regID, roadtaxid);

					if (status != 0)
						cout << "Successfully delete Vehicle's Road Tax details.\n\n";
					else
						cout << "\nFailed to delete Vehicle's Road Tax details.\n\n";

					system("pause");
					system("cls");
				}

				else if (menu == 2)
				{
					// update
					updateRoadTax(regID, roadtaxid);
				}

				else if (menu == 3)
				{
					manageroadtax();
				}

				else
				{
					cout << "\n Sorry, wrong menu. Please re-enter menu.\n";
					cout << endl;
				}
			} while (menu < 1 || menu > 3);
		}

		else if (choicemanageroadtax == 3)
		{
			//update road tax
			cout << " -To Update Vehicle's Road Tax Details-\n";
			cout << "\n -Choose from the Registration No List-\n\n";
			vehicleManager.deactivateID("Registered", username);

			cout << "\n Enter Vehicle's Registration No (E.g: XXX0000) [Press c to Cancel]: ";
			cin >> regID;
				if (regID == "c" || regID == "C")
				{
					system("cls");
					manageroadtax();
				}
			cout << endl;
			roadtaxManager.searchroadtax(regID);
			cout << endl;

			updateRoadTax(regID, roadtaxid);
		}

		else if (choicemanageroadtax == 4)
		{
			//delete road tax
			cout << " -To Delete Vehicle's Road Tax Details-\n";
			cout << "\n -Choose from the Registration No List-\n\n";
			vehicleManager.deactivateID("Registered", username);
			cout << "\n Enter Vehicle's Registration No (E.g: XXX0000) [Press c to Cancel]: ";
			cin >> regID;
			cout << endl;
				if (regID == "c" || regID == "C")
				{
					system("cls");
					manageroadtax();
				}
			
			roadtaxManager.showRoadTaxID(regID);
			cout << "\n Enter Road Tax ID [Press c to Cancel]: ";
			cin >> roadtaxid;
			cout << endl;
				if (roadtaxid == "c" || roadtaxid == "C")
				{
					system("cls");
					manageservice();
				}

			int status = roadtaxManager.deleteroadtax(regID, roadtaxid);

			if (status != 0)
				cout << "\nSuccessfully delete Vehicle's Road Tax details.\n\n";
			else
				cout << "\nFailed to delete Vehicle's Road Tax details.\n\n";

			system("pause");
			system("cls");
		}

		else if (choicemanageroadtax == 5)
		{
			mainmenu();
			return;
		}

		else
		{
			cout << "\n Sorry, wrong menu. Please re-enter menu.\n";
			cout << endl;
		}
	} while (choicemanageroadtax >= 1 || choicemanageroadtax <= 5);
}

void updateRoadTax(string regID, string roadtaxid)
{
	int choiceupdateroadtax;

	RoadTaxManager roadtaxManager;
	RoadTax* roadtax = new RoadTax();

	cout << " Update Road Tax Details is chosen.";
	cout << "\n-----------------------------------";
	cout << "\n --Please Choose--\n 1 Update Road Tax ID\n 2 Update Vehicle Effective Date\n 3 Update Road Tax Expiry Date\n 4 Update Policy No";
	cout << "\n 5 Update Policy / Insurance Start Date\n 6 Update Policy / Insurance End Date\n 7 Return to Menu\n";
	cout << " Enter Choice: ";
	cin >> choiceupdateroadtax;
	system("cls");

	do
	{
		if (choiceupdateroadtax == 1)
		{
			roadtaxManager.showRoadTaxID(regID);
			cout << "\n -Update Road Tax ID-";
			cout << "\n---------------------------";
			cout << " \n Enter Road Tax ID: ";
			cin >> roadtaxid;
			cout << "\n New Road Tax ID: ";
			cin >> roadtax->roadtaxid;

			int status = roadtaxManager.updateRoadTaxID(roadtax, regID, roadtaxid);
			if (status != 0)
				cout << "\nSuccessfully update Road Tax ID.\n\n";
			else
				cout << "\nFailed to update Road Tax ID.\n\n";

			system("pause");
			system("cls");

			manageroadtax();
		}

		else if (choiceupdateroadtax == 2)
		{
			roadtaxManager.showEffectiveDate(regID);
			cout << "\n -Update Vehicle Effective Date-";
			cout << "\n---------------------------------";
			cout << " \n Enter Road Tax ID: ";
			cin >> roadtaxid;
			cout << "\n New Vehicle Effective Date (E.g: YYYY-MM-DD): ";
			cin >> roadtax->effectivedate;

			int status = roadtaxManager.updateEffectiveDate(roadtax, regID, roadtaxid);
			if (status != 0)
				cout << "\nSuccessfully update Vehicle Effective Date.\n\n";
			else
				cout << "Failed to update Vehicle Effective Date.\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdateroadtax == 3)
		{
			roadtaxManager.showExpiryDate(regID);
			cout << "\n -Update Road Tax Expiry Date-";
			cout << "\n---------------------------------";
			cout << " \n Enter Road Tax ID: ";
			cin >> roadtaxid;
			cout << "\n New Road Tax Expiry Date (E.g: YYYY-MM-DD): ";
			cin >> roadtax->exdate;

			int status = roadtaxManager.updateExpiryDate(roadtax, regID, roadtaxid);
			if (status != 0)
				cout << "\nSuccessfully update Road Tax Expiry Date.\n\n";
			else
				cout << "\nFailed to update Road Tax Expiry Date.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdateroadtax == 4)
		{
			roadtaxManager.showPolicyNo(regID);
			cout << "\n -Update Policy No-";
			cout << "\n----------------------";
			cout << " \n Enter Road Tax ID: ";
			cin >> roadtaxid;
			cout << "\n New Policy No: ";
			cin >> roadtax->policy;

			int status = roadtaxManager.updatePolicyNo(roadtax, regID, roadtaxid);
			if (status != 0)
				cout << "\nSuccessfully update Policy No.\n\n";
			else
				cout << "\nFailed to update Policy No.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdateroadtax == 5)
		{
			roadtaxManager.showStartDate(regID);
			cout << "\n -Update Policy / Insurance Start Date-";
			cout << "\n-------------------------------------------";
			cout << " \n Enter Road Tax ID: ";
			cin >> roadtaxid;
			cout << "\n New Policy / Insurance Start Date (E.g: YYYY-MM-DD): ";
			cin >> roadtax->startdate;

			int status = roadtaxManager.updateStartDate(roadtax, regID, roadtaxid);
			if (status != 0)
				cout << "\nSuccessfully update Policy / Insurance Start Date.\n\n";
			else
				cout << "\nFailed to update Policy / Insurance Start Date.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdateroadtax == 6)
		{
			roadtaxManager.showEndDate(regID);
			cout << "\n -Update Policy / Insurance End Date-";
			cout << "\n-------------------------------------------";
			cout << " \n Enter Road Tax ID: ";
			cin >> roadtaxid;
			cout << "\n New Policy / Insurance End Date (E.g: YYYY-MM-DD): ";
			cin >> roadtax->enddate;

			int status = roadtaxManager.updateEndDate(roadtax, regID, roadtaxid);
			if (status != 0)
				cout << "\nSuccessfully update Policy / Insurance End Date.\n\n";
			else
				cout << "\nFailed to update Policy / Insurance End Date.\n\n";

			system("pause");
			system("cls");
		}

		else if (choiceupdateroadtax == 7)
		{
			manageroadtax();
			return;
		}

		else
		{
			cout << "\n Sorry, wrong menu. Please re-enter menu.\n";
			cout << endl;
		}
	} while (choiceupdateroadtax >= 1 || choiceupdateroadtax <= 7);
}

void generatereport()
{
	string regID;
	double cost = 0.0;
	Service* service = new Service();
	int choicegeneratereport;
	//VehicleManager vehicleManager;
	GenerateReport generateReport;

	do
	{
		cout << "-GENERATE REPORT-\n";
		cout << " 1 Vehicle Report\n 2 Vehicle Service Report\n 3 Vehicle Road Tax Report\n 4 Return to Main Menu\n";
		cout << " Enter choice: ";
		cin >> choicegeneratereport;
		cout << endl;
		system("cls");

		if (choicegeneratereport == 1)
		{
			vehicleReport();
		}

		else if (choicegeneratereport == 2)
		{
			//view service report
			cout << "\t\t\t  -Vehicles' Services Report-";
			cout << "\n-----------------------------------------------------------------------------";
			cout << "\n-----------------------------------------------------------------------------\n";
			generateReport.viewServiceReport(cost, username);
			cout << "\n-----------------------------------------------------------------------------";
			generateReport.grandCost(cost, username);
			cout << "\n-----------------------------------------------------------------------------\n";
			cout << endl;
			system("pause");
			system("cls");
		}

		else if (choicegeneratereport == 3)
		{
			// view road tax report
			cout << "\t\t\t  -Vehicles' Road Tax Report-";
			cout << "\n--------------------------------------------------------------------------------------";
			cout << "\n--------------------------------------------------------------------------------------\n";
			generateReport.viewRoadTaxReport(username);

			cout << endl;
			system("pause");
			system("cls");
		}

		else if (choicegeneratereport == 4)
		{
			mainmenu();
			return;
		}

		else
		{
			cout << "\n Sorry, wrong menu. Please re-enter menu.\n";
			cout << endl;
		}
	} while (choicegeneratereport >= 1 || choicegeneratereport <= 4);
}

void vehicleReport()
{
	int choiceviewreport;
	GenerateReport generateReport;

	cout << "   View Vehicle Report is chosen.";
	cout << "\n-----------------------------------";
	cout << "\n --Please Choose--\n 1 Registered Vehicles\n 2 Deactivate Vehicles\n 3 All Vehicles\n 4 Return to Menu\n";
	cout << " Enter Choice: ";
	cin >> choiceviewreport;
	system("cls");

	do
	{
		if (choiceviewreport == 1)
		{
			cout << "\t\t\t  -Registered Vehicles Report-";
			cout << "\n------------------------------------------------------------------------------------------";
			cout << "\n------------------------------------------------------------------------------------------\n";
			generateReport.viewVehicleRegistered("Registered", username);
			system("pause");
			system("cls");
			generatereport();
		}

		else if (choiceviewreport == 2)
		{
			cout << "\t\t\t  -Deactivate Vehicles Report-";
			cout << "\n------------------------------------------------------------------------------------------";
			cout << "\n------------------------------------------------------------------------------------------\n";
			generateReport.viewVehicleHistory("Deactivate", username);
			system("pause");
			system("cls");
			generatereport();
		}

		else if (choiceviewreport == 3)
		{
			cout << "\t\t\t    -List of All Vehicles-";
			cout << "\n------------------------------------------------------------------------------------------";
			cout << "\n------------------------------------------------------------------------------------------\n";
			generateReport.viewVehicleReport(username);
			system("pause");
			system("cls");
		}

		else if (choiceviewreport == 4)
		{
			generatereport();
			return;
		}

		else
		{
			cout << "\n Sorry, wrong menu. Please re-enter menu.\n";
			cout << endl;
		}
	} while (choiceviewreport >= 1 || choiceviewreport <= 4);
}

void reminder()
{
	int choiceviewreminder = 3;
	VehicleManager vehicleManager;
	ServiceManager serviceManager;
	Service* service = new Service();
	RoadTaxManager roadtaxManager;
	time_t now = time(0);
	string regID;
	tm* timeStruct = localtime(&now);

	cout << setw(16);
	cout << "-REMINDER-";
	cout << "\n-----------------------";
	cout << "\n --Please Choose--\n 1 Reminder by Date\n 2 Reminder by Mileage\n 3 Return to Menu\n";
	cout << " Enter Choice: ";
	cin >> choiceviewreminder;
	system("cls");

	switch (choiceviewreminder)
	{
		case 1:
		{
			cout << setw(10);
			cout << "\n Today's Date : " << 1900 + timeStruct->tm_year << "-" << 1 + timeStruct->tm_mon << "-" << timeStruct->tm_mday << endl;

			cout << "\n                -Upcoming Service Date-\n";
			cout << "----------------------------------------------------------\n";
			serviceManager.notifyServiceDate(username);
			cout << "----------------------------------------------------------\n\n";

			cout << "\n	    -Upcoming Road Tax Expiry Date-\n";
			cout << "----------------------------------------------------------\n";
			roadtaxManager.notifyRoadTax(username);
			cout << "----------------------------------------------------------\n\n";

			system("pause");
			system("cls");
			reminder();
		}

		case 2:
		{
			// reminder by mileage
			cout << "-----Reminder by Mileage-----";
			cout << "\n--------------------------------\n ";
			cout << " -Registration No List-\n\n";
			vehicleManager.deactivateID("Registered", username);
			cout << "\n Enter Vehicle's Registration No (E.g: XXX0000) [Press c to Cancel]: ";
			cin >> regID;
			if (regID == "c" || regID == "C")
			{
				system("cls");
				reminder();
			}
			cout << endl;

			serviceManager.notifyMileage(regID);
			cout << endl;
			system("pause");
			system("cls");
			reminder();
		}

		case 3:
		{
			mainmenu();
			return;
		}

		default:
		{
			cout << "\n Sorry, wrong menu. Please re-enter menu.\n";
			cout << endl;
			reminder();
		}
	}
}