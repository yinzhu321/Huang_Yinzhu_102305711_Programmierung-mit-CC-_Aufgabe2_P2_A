#include <iostream>
#include"connection.h"

using namespace std;


int main()
{	
	if (!verbindung())
	{
		return 1;
	}

	while (1)
	{
		//Zahlen eingeben
		int zahl_1 = 0;
		int zahl_2 = 0;

		cout << "Geben sie bitte eine Zahl ein" << endl;

		if (!(cin >> zahl_1))
		{
			//Wenn ungültige Zahl eingegeben wird, fängt der Zyklus von vorne an.
			cout << "Ungueltige Eingabe." << endl;

			cin.clear();
			cin.ignore(1000, '\n');

			continue;
		}

		cout << "Geben Sie bitte zweite Zahl ein" << endl;

		if (!(cin >> zahl_2))
		{
			//Wenn ungültige Zahl eingegeben wird, fängt der Zyklus von vorne an.
			cout << "Ungueltige Eingabe." << endl;

			cin.clear();
			cin.ignore(1000, '\n');

			continue;
		}

		//int zu string umwandeln
		ostringstream os;
		os << zahl_1 << " * " << zahl_2 << "\n";
		
		// string zum Microkontroller schicken
		sendToMCU(os.str());
		
		//Ergebniss ausdrucken
		cout << "Ergebniss = " << receiveFromMCU() << endl;
		

		//Rechnungsweg im TXT Datei speichern
		speichern(zahl_1, zahl_2);

	}
	
	return 0;
}