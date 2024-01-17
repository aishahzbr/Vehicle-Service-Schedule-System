#ifndef ROADTAXMANAGER_H
#define ROADTAXMANAGER_H

class RoadTaxManager
{
public:
	int addroadtax(RoadTax* roadtax);
	int updateRoadTaxID(RoadTax* roadtax, string regID, string roadtaxid);
	int updateEffectiveDate(RoadTax* roadtax, string regID, string roadtaxid);
	int updateExpiryDate(RoadTax* roadtax, string regID, string roadtaxid);
	int updatePolicyNo(RoadTax* roadtax, string regID, string roadtaxid);
	int updateStartDate(RoadTax* roadtax, string regID, string roadtaxid);
	int updateEndDate(RoadTax* roadtax, string regID, string roadtaxid);
	void searchroadtax(string regID);
	int deleteroadtax(string regID, string roadtaxid);
	void notifyRoadTax(string username);

	void showRoadTaxID(string regID);
	void showEffectiveDate(string regID);
	void showExpiryDate(string regID);
	void showPolicyNo(string regID);
	void showStartDate(string regID);
	void showEndDate(string regID);
};
#endif // !ROADTAXMANAGER_H

