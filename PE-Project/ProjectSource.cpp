#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Optic {
private:
	string type;
	double thickness;
	double diopter;
	string materialName;
	double price;
public:
	Optic(const string& type, double thickness, double diopter,const string& materialName, double price) : 
		type(type), thickness(thickness), diopter(diopter), materialName(materialName), price(price) {
	}

	Optic() : type("Unknown") , thickness(0) , diopter(0) , materialName("Unknown") ,price(0) {}

	const string& getType() const {return type;}

	void setType(const string& type) {this->type = type;}

	double getThickness() const {return thickness;}

	void setThickness(double thickness) {this->thickness = thickness;}

	double getDiopter() const {return diopter;}

	void setDiopter(double diopter) {this->diopter = diopter;}

	const string& getMaterialName() const {return materialName;}

	void setMaterialName(const string& materialName) {this->materialName = materialName;}

	double getPrice() const {return price;}	

	void setPrice(double price) {this->price = price;}	

	friend ostream& operator<<(ostream& os, const Optic& o) {
		os << "Type: " << o.type
			<< "\nThickness: " << o.thickness
			<< "\nDiopter: " << o.diopter
			<< "\nMaterial: " << o.materialName
			<< "\nPrice: " << o.price << "\n";
		return os;
	}
};

class Vendor {
private:
	string bulstat;
	string name;
	string location;
	string phoneNumber;
	vector<Optic> optics;
public:
	Vendor(const string& bulstat, const string& name, const string& location, const string& phoneNumber) :
		bulstat(bulstat), name(name), location(location), phoneNumber(phoneNumber) { }
	
	Vendor() : bulstat("Unknown") , name("Unknown") , location("Unknown") , phoneNumber("Unknown") {}

	const string& getBulstat() const {return bulstat;}

	void setBulstat(const string& bulstat){this->bulstat = bulstat;}

	const string& getName() const {return name;}

	void setName(const string& name) {this->name = name;}

	const string& getLocation() const {return location;}

	void setLocation(const string& location) {this->location = location;}

	const string& getPhoneNumber() const {return phoneNumber;}

	void setPhoneNumber(const string& phoneNumber) {this->phoneNumber = phoneNumber;}

	const vector<Optic>& getOpticList() const {return optics;}

	void setOpticList(const vector<Optic>& optics) {this->optics = optics;}

	void addOptic(const Optic& optic) {optics.push_back(optic);}

	friend ostream& operator<<(ostream& os, const Vendor& v) {
		os << "Business ID: " << v.bulstat 
		<< "\nName: " << v.name 
		<< "\nLocation: " << v.location 
		<< "\nPhone number: " << v.phoneNumber << "\n";
		return os;
	}
};

class Order {
private:
	static int IDcounter;
	int orderID;
	Vendor vendor;
	vector<Optic> orderedOptics;
public:
	Order(const Vendor& vendor) : orderID(IDcounter++), vendor(vendor) {}

	Order() : orderID(IDcounter++) {}

	int getOrderID() const {return orderID;}

	void setOrderID(int orderID) {this->orderID = orderID;}

	const Vendor& getVendor() const {return vendor;}

	void setVendor(const Vendor& vendor) {this->vendor = vendor;}

	const vector<Optic>& getOrderedOptics() const{return orderedOptics;}

	void setOrderedOptics(const vector<Optic>& orderedOptics) {this->orderedOptics = orderedOptics;}

	void addOrderedOptic(const Optic& optic){orderedOptics.push_back(optic);}

	double calculateOrderTotalPrice() {
		double totalPrice = 0;
		for (auto optic : orderedOptics) {
			totalPrice += optic.getPrice();
		}
		return totalPrice;
	}

	friend ostream& operator<<(ostream& os, const Order& order) {
		os << "\nOrder ID: " << order.orderID <<
			"\nVendor name: " << order.vendor.getName() << "\n" <<
			"\nOrdered Optics:\n";
		for (const auto& optic : order.orderedOptics) {
			os << optic << "\n";
		}

		return os;
	}
};
int Order::IDcounter = 1;

class OpticSystem {
private:
	vector<Vendor> vendors;
	vector<Order> orders;

	bool isNumericOnly(const string& s) {
		if (s.empty()) return false;
		char* end = nullptr;
		strtod(s.c_str(), &end);
		return end != s.c_str() && *end == '\0';
	}

	bool isNumber(const string& s) {
		if (s.empty()) { return false; };
		for (char ch : s) { if (isdigit(ch) == 0) return false; }
		return true;
	}

	string getValidBulstat() {
		string bulstat;
		while (true) {
			getline(cin, bulstat);
			if (checkForExit(bulstat)) { return ""; };
			if (isNumber(bulstat) && bulstat.length() == 8) return bulstat;
			cout << "\nInvalid input. Please enter an eight digit business ID number: ";
		}
	}
	
	string getValidPhoneNumber() {
		string phoneNumber;
		while (true) {
			getline(cin, phoneNumber);
			if (checkForExit(phoneNumber)) { return "";};
			if (isNumber(phoneNumber) && phoneNumber.length() == 10) return phoneNumber;
			cout << "\nInvalid input. Please enter a ten digit phone number: ";
		}
	}

	double getValidDiopter() {
		string input;
		while (true) {
			getline(cin, input);
			if (checkForExit(input)){ return -1; }
			if (isNumericOnly(input)) { return stod(input); };
			cout << "\nInvalid input. Please enter a valid number: ";
		}
	}

	int getValidInteger() {
		string input;
		while (true) {
			getline(cin, input);
			if (checkForExit(input)) { return 0; }
			if (isNumber(input) && input!="0") return stoi(input);
			cout << "\nInvalid input. Please enter a positive integer: ";
		}
	}

	double getValidDouble() {
		string input;
		while (true) {
			getline(cin, input);
			if (checkForExit(input)){ return -1; }
			if (isNumericOnly(input) && stod(input) > 0) { return stod(input); };
			cout << "\nInvalid input. Please enter a valid number: ";
		}
	}

	string getValidString() {
		string input;
		while (true) {
			getline(cin, input);
			if (checkForExit(input)){ return ""; }
			if (!input.empty() && !isNumericOnly(input)) return input;
			cout << "\nInvalid input. Please enter a valid text: ";
		}
	}	

	bool checkForExit(const string& input) {
		if (input == "q" || input == "Q") { return true; }
		return false;
	}
public:
	OpticSystem(vector<Vendor> vl, vector<Order> ol) : vendors(vl) , orders(ol) {}
	OpticSystem() {}
	
	void addVendors(vector<Vendor>& vendors) {
		cout << "\nEnter number of vendors: ";
		int vendorNumber = getValidInteger();

		for (int i = 0; i < vendorNumber; i++)
		{
			cout << "\nIf you want to return to the menu just type 'q'!";
			cout << "\nVendor #" << i + 1 << "\n";
			cout << "\n---------------------\n";

			cout << "Business ID: ";
			string bulstat = getValidBulstat();
			if (bulstat == "") { return; }

			cout << "Name: ";
			string name = getValidString();
			if (name == "") { return; }

			cout << "Location: ";
			string location = getValidString();
			if (location == "") { return; }

			cout << "Phone number: ";
			string phoneNumber = getValidPhoneNumber();
			if (phoneNumber == "") { return; }

			Vendor vendor(bulstat, name, location, phoneNumber);
			vendors.push_back(vendor);
		}
	}

	void viewVendors(const vector<Vendor>& vendors) {
		if (vendors.empty()) { cout << "\nNo vendors available to display.\n"; return; }
		cout << "\nList of Vendors:\n";
		cout << "\n----------------------\n";
		for (const auto& vendor : vendors) {
			cout << vendor << "\n";
		}
	}

	void addOpticToVendor(vector<Vendor>& vendors)    {

		if (vendors.empty()) { cout << "\nYou need to add a vendor before choosing an optic!\n"; return; }

		cout << "\nChoose a vendor to add an optic to: ";
		viewVendors(vendors);

		cout << "\nIf you want to return to the menu just type 'q'!";
		cout << "\nEnter the desired vendor's Business ID: ";

		string businessID;
		Vendor* vendorPtr = nullptr;
		while (true) {
			getline(cin, businessID);
			if (checkForExit(businessID)) { return; }

			for (auto& v : vendors) {
				if (v.getBulstat() == businessID) {
					vendorPtr = &v;
					break;
				}
			}

			if (vendorPtr!=nullptr){break;}

			cout << "Invalid Business ID. Please enter a valid Business ID: ";
		}
		Vendor& vendor = *vendorPtr;

		cout << "\nEnter number of optics for this vendor: ";
		int opticsNumber = getValidInteger();

		for (int j = 0; j < opticsNumber; j++)
		{
			cout << "\nOptic #" << j + 1 << "\n";
			cout << "\n---------------------\n";

			cout << "Type: ";
			string type = getValidString();
			if (type == "") { return; }

			cout << "Thickness: ";
			double thickness = getValidDouble(); 
			if (thickness == -1) { return; }

			cout << "Diopter: ";
			double diopter = getValidDiopter();
			if (diopter == -1) { return; }

			cout << "Material name: ";
			string materialName = getValidString();
			if (materialName == "") { return; }

			cout << "Price: ";
			double price = getValidDouble();
			if (price == -1) { return; }

			Optic optic(type, thickness, diopter, materialName, price);
			vendor.addOptic(optic);
		}
	}

	void makeOrder(vector<Vendor>& vendors, vector<Order>& orders) {
		if (vendors.empty()) { cout << "No available vendors to choose from!\n"; return; }

		cout << "\nChoose a vendor to make an order : ";
		viewVendors(vendors);

		cout << "\nIf you want to return to the menu just type 'q'!";
		cout << "\nEnter the desired vendor's Business ID: ";
		
		string businessID;
		Vendor* vendorPtr = nullptr;
		while (true) {
			getline(cin, businessID);
			if (checkForExit(businessID)) { return; }

			for (auto& v : vendors) {
				if (v.getBulstat() == businessID) {
					vendorPtr = &v;
					break;
				}
			}

			if (vendorPtr != nullptr) {
				if (vendorPtr->getOpticList().empty())
				{
					cout << "This vendor has no available optics!";
					return;
				}
				else { break; }
			}

			cout << "Invalid Business ID. Please enter a valid Business ID: ";
		}
		Vendor& vendor = *vendorPtr;


		cout << "\nAvailable optics from " << vendor.getName() << ":\n";
		const vector<Optic>& optics = vendor.getOpticList();
		for (int i = 0; i < optics.size(); i++) {
			cout << i + 1 << ". " << optics[i] << "\n";
		}

		Order order(vendor);
		cout << "\nType the number of the desired optic or type 'q' if you want to exit: ";
		
		while (true) {
			int opticChoice = getValidInteger();

			Optic optic;
			if (opticChoice > 0 && opticChoice <= optics.size())
			{
				optic = optics[opticChoice - 1];
				cout << "\nYou have selected: \n" << optic;
				order.addOrderedOptic(optic);
				cout << "\nType the number of the desired optic or type 'q' if you want to exit: ";
				continue;
			}else if (opticChoice==0)
			{
				break;
			}

			cout << "Invalid number. Try again or type 'q' to exit.";
		}
		if (!order.getOrderedOptics().empty())
		{
			orders.push_back(order);
		}
	}

	void viewOrders(vector<Order>& orders) {
		if (orders.empty()) { cout << "\nYou have not made an order yet!"; return; }
		cout << "\nTotal orders: " << orders.size() << "\n";
		cout << "\n----------------\n";
		for (auto& order : orders) {
			cout << order;
			cout << "Total price of order: " << order.calculateOrderTotalPrice() << "\n";
		}
	}

	void writeToFile(const vector<Vendor>& vendors, const vector<Order>& orders) {

		if (vendors.empty() && orders.empty()) {
			cout << "\nThere is no data available to write!\n";
			return;
		}

		ofstream file("data.text");
		if (!file) {
			cout << "Error opening file for writing!\n";
			return;
		}

		file << vendors.size() << "\n";
		for (const auto& v : vendors) {
			file << v.getBulstat() << '\n';
			file << v.getName() << '\n';
			file << v.getLocation() << '\n';
			file << v.getPhoneNumber() << '\n';

			const auto& optics = v.getOpticList();
			file << optics.size() << "\n";
			for (const auto& o : optics) {
				file << o.getType() << '\n';
				file << o.getThickness() << '\n';
				file << o.getDiopter() << '\n';
				file << o.getMaterialName() << '\n';
				file << o.getPrice() << '\n';
			}
		}

		file << orders.size() << "\n";
		for (const auto& order : orders) {
			file << order.getOrderID() << "\n";

			file << order.getVendor().getBulstat() << "\n";

			const auto& orderedOptics = order.getOrderedOptics();
			file << orderedOptics.size() << "\n";

			for (const auto& o : orderedOptics) {
				file << o.getType() << '\n';
				file << o.getThickness() << '\n';
				file << o.getDiopter() << '\n';
				file << o.getMaterialName() << '\n';
				file << o.getPrice() << '\n';
			}
		}

		cout << "\nData successfully written to file.\n";
	}

	void readFromFile(vector<Vendor>& vendors, vector<Order>& orders) {
		ifstream file("data.txt");
		if (!file) {
			cout << "Error opening file for reading!\n";
			return;
		}

		vendors.clear();
		orders.clear();

		int vendorCount;
		file >> vendorCount;
		file.ignore();

		for (int i = 0; i < vendorCount; i++) {
			string bulstat, name, location, phone;
			getline(file, bulstat);
			getline(file, name);
			getline(file, location);
			getline(file, phone);

			Vendor v(bulstat, name, location, phone);

			int opticCount;
			file >> opticCount;
			file.ignore();

			for (int j = 0; j < opticCount; j++) {
				string type, material;
				double thickness, diopter, price;

				getline(file, type);
				file >> thickness;
				file >> diopter;
				file.ignore();

				getline(file, material);
				file >> price;
				file.ignore();

				v.addOptic(Optic(type, thickness, diopter, material, price));
			}

			vendors.push_back(v);
		}

		int orderCount;
		file >> orderCount;
		file.ignore();

		for (int i = 0; i < orderCount; i++) {
			int orderID;
			string vendorBulstat;

			file >> orderID;
			file.ignore();

			getline(file, vendorBulstat);

			Vendor* vendorPtr = nullptr;
			for (auto& v : vendors) {
				if (v.getBulstat() == vendorBulstat) {
					vendorPtr = &v;
					break;
				}
			}

			if (!vendorPtr) {
				cout << "Error: Vendor not found when loading order!\n";
				return;
			}

			Order order(*vendorPtr);
			order.setOrderID(orderID);

			int optCount;
			file >> optCount;
			file.ignore();

			for (int j = 0; j < optCount; j++) {
				string type, material;
				double thickness, diopter, price;

				getline(file, type);
				file >> thickness;
				file >> diopter;
				file.ignore();

				getline(file, material);
				file >> price;
				file.ignore();

				order.addOrderedOptic(Optic(type, thickness, diopter, material, price));
			}

			orders.push_back(order);
		}

		cout << "\nData successfully loaded from file.\n";
	}
	
	void helloMessage() {
		cout << "Welcome to the Optic Vendor Management System!\n";
		cout << "You can manage vendors, optics, and orders efficiently.\n";
		cout << "Let's get started!\n";
		cout << "-----------------------------------------------\n";
	}
	void menu() {
		cout
			<< "\n=================== MENU ==================="	
			<< "\n1. Add Vendor\n"
			<< "2. View Vendors\n"
			<< "3. Add optic to existing vendor\n"
			<< "4. Make an order\n"
			<< "5. View Orders\n"
			<< "6. Write to file\n"
			<< "7. Read from file\n"
			<< "Q. Exit\n"
			<< "Type the number of desired action in the terminal: ";
	}
	void run() {
		helloMessage();
		while (true) {
			menu();
			int input = getValidInteger(); // Returns 0 if 'q' or 'Q' is entered
			switch (input) {
			case 1: {
				// Add Vendor
				addVendors(vendors);
				break;
			}case 2: {
				// View Vendors
				viewVendors(vendors);
				break;
			}case 3: {
				// Add optic to existing vendor 
				addOpticToVendor(vendors);
				break;
			}case 4: {
				// Make an order
				makeOrder(vendors, orders);
				break;
			}case 5: {
				// View Orders
				viewOrders(orders);
				break;
			}case 6: {
				// Write to file
				writeToFile(vendors, orders);
				break;
			}case 7: {
				// Read from file
				readFromFile(vendors, orders);
				break;
			}case 0: {
				// Exit
				cout << "\nExiting the program. Goodbye!\n";
				return;
			}default: {
				cout << "\nInvalid input. Please try again!\n";
				break;
			}
			}
		}
	}
};

int main() {
	OpticSystem system;
	system.run();
	return 1;
}
