#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Legos
{
public: 
	double GetPrice()
	{
		return (double)price;
	}
	int GetParts()
	{
		return parts;
	}
	int GetMinifigs()
	{
		return minifig;
	}
	string GetName()
	{
		return name;
	}
	string GetTheme()
	{
		return theme;
	}
	int GetNumber()
	{
		return setNumber;
	}

	Legos(int _setNumber, string _theme, string _name, int _minifig, int _parts, double _price)
	{
		setNumber = _setNumber;
		theme = _theme;
		name = _name;
		minifig = _minifig;
		parts = _parts;
		price = _price;
	}
private: 
	int setNumber;
	string theme;
	string name;
	int parts;
	int minifig;
	double price = 0.0;
	int setCounter;

};

void GetDataFromFile(string filePath, vector<Legos>& legoinfo)
{
	ifstream inFile(filePath);
	string lineFromFile;
	if (inFile.is_open())
	{
		getline(inFile, lineFromFile); // Get the first line (Number, theme, Name, Minifigs, etc) 

		while (getline(inFile, lineFromFile))
		{
			istringstream stream(lineFromFile); // Create a stream from the line of data from the file 

			//Create temporary files to convert string to int
			string tempNumber;
			string tempMinifig;
			string tempParts;
			string tempPrice;
			//int setCounter;

			//Create the variables again for some reason
			int setNumber;
			string theme;
			string name;
			int minifig;
			int parts;
			double price;

			//Get setNumber
			getline(stream, tempNumber, ',');
			setNumber = stoi(tempNumber);
			//Get theme
			getline(stream, theme, ',');
			//Get name
			getline(stream, name, ',');
			//Get minifigs
			getline(stream, tempMinifig, ',');
			minifig = stoi(tempMinifig);
			//Get parts
			getline(stream, tempParts, ',');
			parts = stoi(tempParts);
			//Get price
			getline(stream, tempPrice, ',');
			price = (double)stod(tempPrice);

			Legos data(setNumber, theme, name, minifig, parts, price);
			legoinfo.push_back(data);

			//CREDIT TO PROFESSOR FOX'S VIDEO EXAMPLE 
			//setCounter++;
		}
	}
}

void MostExpensive(vector<Legos>& legoinfo)
{
	
	unsigned int counter = 0;
	Legos maximum = legoinfo[counter];
	while (counter < legoinfo.size())
	{
		if (legoinfo[counter].GetPrice() > maximum.GetPrice())
		{
			maximum = legoinfo[counter];
		}
		counter = counter + 1;
	}
	cout << "The most expensive set is: " << endl;
	cout << "Name: " << maximum.GetName() << endl;
	cout << "Number: " << maximum.GetNumber() << endl;
	cout << "Theme: " << maximum.GetTheme() << endl;
	cout << "Price: $" << maximum.GetPrice() << endl; 
	cout << "Minifigures: " << maximum.GetMinifigs() << endl;
	cout << "Piece count: " << maximum.GetParts() << endl;
}

void MaxPart(vector<Legos>& legoinfo)
{
	unsigned int counter = 0;
	Legos maximum = legoinfo[counter];
	while (counter < legoinfo.size())
	{
		if (legoinfo[counter].GetParts() > maximum.GetParts())
		{
			maximum = legoinfo[counter];
		}
		counter = counter + 1;
	}
	cout << "The set with the highest parts count: " << endl;
	cout << "Name: " << maximum.GetName() << endl;
	cout << "Number: " << maximum.GetNumber() << endl;
	cout << "Theme: " << maximum.GetTheme() << endl;
	cout << "Price: $" << maximum.GetPrice() << endl;
	cout << "Minifigures: " << maximum.GetMinifigs() << endl;
	cout << "Piece count: " << maximum.GetParts() << endl;
}

void SearchName(vector<Legos>& legoinfo, string search) //Search and show all lego sets with the matching search name 
{
	//cout << "Yo!" << search << endl;
	unsigned int counter = 0;
	bool setMatchCout = true; //boolean so the "Sets matching" only prints once
	bool match = false;
	while (counter < legoinfo.size())
	{

		
		if (legoinfo.at(counter).GetName().find(search) != std::string::npos)
		{
			match = true;
			if (setMatchCout == true)
			{
				cout << "Sets matching \"" << search << "\" :" << endl;
			}
			
			cout << legoinfo[counter].GetNumber() << " " << legoinfo[counter].GetName() << " $" << (double)legoinfo[counter].GetPrice() << endl;
			setMatchCout = false;
		
		}
		counter = counter + 1;
	}
	if (match == false)
	{
		cout << "No sets found matching that search term" << endl;
	}
}

void SearchTheme(vector<Legos>& legoinfo, string search)
{
	unsigned int counter = 0;
	bool setMatchCout = true; //boolean so the "Sets matching" only prints once
	bool match = false;
	while (counter < legoinfo.size())
	{


		if (legoinfo.at(counter).GetTheme().find(search) != std::string::npos)
		{
			match = true;
			if (setMatchCout == true)
			{
				cout << "Sets matching \"" << search << "\" :" << endl;
			}

			cout << legoinfo[counter].GetNumber() << " " << legoinfo[counter].GetName() << " $" << (double)legoinfo[counter].GetPrice() << endl;
			setMatchCout = false;

		}
		counter = counter + 1;
	}
	if (match == false)
	{
		cout << "No sets found matching that search term" << endl;
	}
}

void PartCount(vector<Legos>& legoinfo) //Show the average parts for all the loaded sets
{
	unsigned int counter = 0;
	int setCount = 0;
	while (counter < legoinfo.size())
	{
		setCount = setCount + legoinfo[counter].GetParts();
		counter = counter + 1;
	}
	cout << "Average part count for " << legoinfo.size() << " sets: " << setCount / legoinfo.size() << endl;
}

void PriceInfo(vector <Legos>& legoinfo) //Show the average, minimum and maximum prices
{
	unsigned int counter = 0;
	double priceCount = 0;
	Legos maximumPrice = legoinfo[counter];
	Legos minimumPrice = legoinfo[counter];


	// Search the maximum and minimum prices
	while (counter < legoinfo.size())
	{
		//Get the maximum price
		if (legoinfo[counter].GetPrice() > maximumPrice.GetPrice())
		{
			maximumPrice = legoinfo[counter];
		}
		//Get the minimum price
		if (legoinfo[counter].GetPrice() < minimumPrice.GetPrice())
		{
			minimumPrice = legoinfo[counter];
		}
		//Get the sum of all prices
		priceCount = priceCount + legoinfo[counter].GetPrice();
		counter = counter + 1;
	}
	cout << "Average price for " << legoinfo.size() << " sets: $" << priceCount / legoinfo.size() << endl;

	cout << "Least expensive set: " << endl;
	cout << "Name: " << minimumPrice.GetName() << endl;
	cout << "Number: " << minimumPrice.GetNumber() << endl;
	cout << "Theme: " << minimumPrice.GetTheme() << endl;
	cout << "Price: $" << minimumPrice.GetPrice() << endl;
	cout << "Minifigures: " << minimumPrice.GetMinifigs() << endl;
	cout << "Piece count: " << minimumPrice.GetParts() << endl;
	cout << endl;
	cout << "Most expensive set: " << endl;
	cout << "Name: " << maximumPrice.GetName() << endl;
	cout << "Number: " << maximumPrice.GetNumber() << endl;
	cout << "Theme: " << maximumPrice.GetTheme() << endl;
	cout << "Price: $" << maximumPrice.GetPrice() << endl;
	cout << "Minifigures: " << maximumPrice.GetMinifigs() << endl;
	cout << "Piece count: " << maximumPrice.GetParts() << endl;
}

void MiniInfo(vector <Legos>& legoinfo) //Show average number of minifigures and the set info for the one with the most minifigures
{
	unsigned int counter = 0;
	int minifigCount = 0;
	Legos maximumFig = legoinfo[0];
	while (counter < legoinfo.size())
	{
		//Find the maximum
		if (legoinfo[counter].GetMinifigs() > maximumFig.GetMinifigs())
		{
			maximumFig = legoinfo[counter];
		}
		//Get the average
		minifigCount = minifigCount + legoinfo[counter].GetMinifigs();
		counter = counter + 1;
	}
	cout << "Average number of minifigures: " << minifigCount / legoinfo.size() << endl;
	cout << "Set with the most minifigures: " << endl;
	cout << "Name: " << maximumFig.GetName() << endl;
	cout << "Number: " << maximumFig.GetNumber() << endl;
	cout << "Theme: " << maximumFig.GetTheme() << endl;
	cout << "Price: $" << maximumFig.GetPrice() << endl;
	cout << "Minifigures: " << maximumFig.GetMinifigs() << endl;
	cout << "Piece count: " << maximumFig.GetParts() << endl;

}

void BuyAll(vector<Legos>& legoinfo) //If you bought one of everything, what would be total cost, pieces, and minifigs?
{
	unsigned int counter = 0;
	double totalCost = 0;
	int totalFigs = 0;
	int totalParts = 0;
	while (counter < legoinfo.size())
	{
		totalCost = totalCost + legoinfo[counter].GetPrice();
		totalFigs = totalFigs + legoinfo[counter].GetMinifigs();
		totalParts = totalParts + legoinfo[counter].GetParts();
		counter = counter + 1;
	}
	cout << "If you bought one of everything..." << endl;
	cout << "It would cost: $" << totalCost << endl;
	cout << "You would have " << totalParts << " pieces in your collection" << endl;
	cout << "You would have an army of " << totalFigs << " minifigures!" << endl;
}


int main()
{
	vector<Legos> legoinfo;

	cout << std::fixed << setprecision(2);
	cout << "Which file(s) to open?\n";
	cout << "1. lego1.csv" << endl;
	cout << "2. lego2.csv" << endl;
	cout << "3. lego3.csv" << endl;
	cout << "4. All 3 files" << endl;
	int option;
	cin >> option;

	if (option == 1)
	{
		GetDataFromFile("lego1.csv", legoinfo);
	}
	if (option == 2)
	{
		GetDataFromFile("lego2.csv", legoinfo);
	}
	if (option == 3)
	{
		GetDataFromFile("lego3.csv", legoinfo);
	}
	if (option == 4)
	{
		GetDataFromFile("lego1.csv", legoinfo);
		GetDataFromFile("lego2.csv", legoinfo);
		GetDataFromFile("lego3.csv", legoinfo);

	}
	cout << "Total number of sets: " << legoinfo.size() << endl;
	/*======= Load data from file(s) =======*/


	//cout << "1. Most Expensive set" << endl;
	//cout << "2. Largest piece count" << endl;
	//cout << "3. Search for set name containing..." << endl;
	//cout << "4. Search themes..." << endl;
	//cout << "5. Part count information" << endl;
	//cout << "6. Price information" << endl;
	//cout << "7. Minifigure information" << endl;
	//cout << "8. If you bought one of everything..." << endl;
	//cout << "0. Exit" << endl;

	int choice;
	cin >> choice;
	cin.get();  // Clear newline character for any later input

	if (choice == 1)
	{
		MostExpensive(legoinfo);
	}
	if (choice == 2)
	{
		MaxPart(legoinfo);
	}
	if (choice == 3)
	{
		string search;
		getline(cin, search);
		SearchName(legoinfo, search);
	}
	if (choice == 4)
	{
		string search;
		getline(cin, search);
		SearchTheme(legoinfo, search);
	}
	if (choice == 5)
	{
		PartCount(legoinfo);
	}
	if (choice == 6)
	{
		PriceInfo(legoinfo);
	}
	if (choice == 7)
	{
		MiniInfo(legoinfo);
	}
	if (choice == 8)
	{
		BuyAll(legoinfo);
	}


	/*======= Print out how many sets were loaded =======*/
	/*======= Based on the choice, execute the appropriate task and show the results =======*/

	return 0;
}




