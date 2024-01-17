#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

class ServiceManager
{
public:
	int addService(Service* service);
	void searchService(string regID);
	int updateReceiptNo(Service* service, string regID, string receiptno);
	int updateDate(Service* service, string regID, string receiptno);
	int updateServiceCost(Service* service, string regID, string receiptno);
	int updateCurrentMileage(Service* service, string regID, string receiptno);
	int updateNextMileage(Service* service, string regID, string receiptno);
	int updateDateNextMileage(Service* service, string regID, string receiptno);
	int updateServiceType(Service* service, string regID, string receiptno);
	int deleteService(string regID, string receiptno);
	void notifyServiceDate(string username);
	void notifyMileage(string regID);

	void showReceiptNo(string regID);
	void showDate(string regID);
	void showServiceCost(string regID);
	void showServiceMileage(string regID);
	void showNextMileage(string regID);
	void showDateNextMileage(string regID);
	void showServiceType(string regID);
};
#endif 

