#include "connection.h"
HANDLE hComm;

//mit Microkontroller verbinden
 bool verbindung()
 {
	 //serielle Schnittstelle öffnen 
		 hComm = CreateFileA("\\\\.\\COM3",
				 GENERIC_READ | GENERIC_WRITE,
				 0,
				 NULL,
				 OPEN_EXISTING,
				 0,
				 NULL);
			 if (hComm == INVALID_HANDLE_VALUE)
			 {
				 cout << "Fehler beim Oeffnen der seriellen Schnittstelle." << endl;
				 return false;
			 }
			 else
			 {
				 cout << "Serielle Schnittstelle erfolgreich geoeffnet." << endl;
			 }
	

	 //Schnittstelle konfigurieren: 9600 8N1
	 DCB dcbSeralParams = { 0 };
	 dcbSeralParams.DCBlength = sizeof(dcbSeralParams);

	 if (!GetCommState(hComm, &dcbSeralParams))
	 {
		 cout << "Fehler beim Lesen des Status der seriellen Schnittstelle." << endl;
		 CloseHandle(hComm);
	 }

	 dcbSeralParams.BaudRate = CBR_9600;
	 dcbSeralParams.ByteSize = 8;
	 dcbSeralParams.StopBits = ONESTOPBIT;
	 dcbSeralParams.Parity = NOPARITY;

	 if (!SetCommState(hComm, &dcbSeralParams))
	 {
		 cout << "Fehler: Serielle Schnittstelle kann nicht konfiguriert werden." << endl;
		 CloseHandle(hComm);
	 }

	 COMMTIMEOUTS timeouts = { 0 };

	 timeouts.ReadIntervalTimeout = 50;
	 timeouts.ReadTotalTimeoutConstant = 2000;
	 timeouts.ReadTotalTimeoutMultiplier = 10;

	 timeouts.WriteTotalTimeoutConstant = 500;
	 timeouts.WriteTotalTimeoutMultiplier = 10;

	 if (!SetCommTimeouts(hComm, &timeouts))
	 {
		 cout << "SetCommTimeouts Fehler: "
			 << GetLastError() << endl;
		 CloseHandle(hComm);
	 }
	 return true;
 }

	//String zum Microkontroller transpotieren
 void sendToMCU(const std::string& text)
 {
	 DWORD bytesWritten = 0;
	 if (!WriteFile(
		 hComm,
		 text.c_str(),
		 static_cast<DWORD>(text.size()),
		 &bytesWritten,
		 NULL))

	 {
		 cout << "Fehler beim Senden der Daten." << endl;
	 }
 }

	//Ergebniss vom Microkontroller bekommen
	char buffer[100] = { 0 };
 std::string  receiveFromMCU()
 {
	 Sleep(100);

	 DWORD bytesRead = 0;

	 BOOL ok = ReadFile(
		 hComm,
		 buffer,
		 sizeof(buffer) - 1,
		 &bytesRead,
		 NULL
	 );

	 if (!ok)
	 {
		 cout << "ReadFile Fehler: " << GetLastError() << endl;
		 return "";
	 }
	 
		 buffer[bytesRead] = '\0';
		 return std::string(buffer);
		 
 }

 void speichern(int s_zahl_1, int s_zahl_2)
 {
	 //Daten speichern
	 ofstream ofs;
	 ofs.open("Berechnungsprotokoll.txt", ios::app);
	 ofs << s_zahl_1 << " * " << s_zahl_2 << " = " << buffer << endl;
	 ofs.close();
 }