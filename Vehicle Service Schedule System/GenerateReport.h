#ifndef GENERATEREPORT_H
#define GENERATEREPORT_H

class GenerateReport
{
public:
	int viewVehicleReport(string username);
	int viewVehicleHistory(string status, string username);
	int viewServiceReport(double cost, string usename);
	int viewVehicleRegistered(string status, string username);
	void viewRoadTaxReport(string username);
	void grandCost(double cost, string username);
};
#endif // !GENERATEREPORT_H
