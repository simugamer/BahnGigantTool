//============================================================================
// Name         : BahnGigantTool.cpp
// Author       : simugamer
// Version      : 0.1
// Copyright    : GNU 3 Public Licence
// Beschreibung : Erzeugt eine BMP sowie eine CSV Datei aus einem Memorydump.
//                Der Memorydump kann z.B mit UsaMimi Hurricane erstellt
//                werden. In Bahngigant mit installiertem Fanpatch muss der
//                Bereich von 00C07554 bis 00D07553 gedumpt werden.
//                Zum Kompilieren wird CIMG.h benötigt, was es auf
//                http://cimg.sourceforge.net zum Download gibt.
//                Weitere Informationen auf
//                http://www.bahngigant.de/forum/index.php?a=vtopic&t=282
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include "CImg.h"
#include <stdint.h>
#include <windows.h>
#include <Commdlg.h>
using namespace std;

const unsigned char AE = static_cast<unsigned char>(142); 
const unsigned char ae = static_cast<unsigned char>(132); 
const unsigned char OE = static_cast<unsigned char>(153); 
const unsigned char oe = static_cast<unsigned char>(148); 
const unsigned char UE = static_cast<unsigned char>(154); 
const unsigned char ue = static_cast<unsigned char>(129); 
const unsigned char ss = static_cast<unsigned char>(225);

static uint8_t color_table[7][3] = {// in RGB format
	{0,		192,	0},		//Gras 
	{0,		255,	0},		//Übergang Sand/Gras
	{255,	255,	128},	//Sand 
	{0,		0,		255},	//Unterwasserfels 
	{92,	92,		92},	//Fels
	{128,	128,	128},	//Parks, Felder, Pfeiler
	{192,	192,	192},	//Gebäude, Schienen, Straßen
	};

string openfilename(char *filter = "All Files (*.*)\0*.*\0", HWND owner = NULL) {
  OPENFILENAME ofn;
  char fileName[MAX_PATH] = "";
  ZeroMemory(&ofn, sizeof(ofn));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = owner;
  ofn.lpstrFilter = filter;
  ofn.lpstrFile = fileName;
  ofn.nMaxFile = MAX_PATH;
  ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
  ofn.lpstrDefExt = "";

  string fileNameStr;

  if ( GetOpenFileName(&ofn) )
    fileNameStr = fileName;

  return fileNameStr;
}

int main(int argc, char *argv[]) {
	//Eingabedatei auswählen
	string input_file;
	if(argc == 1) {
		input_file = openfilename();
	} else if(argc == 2) {
		input_file = argv[1];
	} else {
		cerr << "Zu viele Parameter!";
		return 2;
	}
	ifstream in_file (input_file.c_str(), ios::binary);
	in_file.seekg(0, ios::end);
	size_t length = in_file.tellg(); 
	in_file.seekg( 0, ios::beg );
	if(length != 1024*1024) {
		cerr << "Falsche Dateigr" << oe << ss <<"e! ";
		cerr << "Datei ist " << length << " Bytes gro" << ss;
		cerr << ".\nErwartet wurden 1.048.576 Bytes.";
		return 3;
	}

	//Binärdatei einlesen
	vector<vector<char> > data;
	data.resize(1024);
    if(in_file.is_open())
    {
		char ch;
   		for(int i=0; i<1024; i++) {
   			for(int j=0; j<1024; j++){
   				in_file.get(ch);
   				data[i].push_back(ch);
   			}
		}
    } else {
		cerr << "Kann Datei nicht " << oe <<" ffnen!";
		return 4;
	}
   	in_file.close();

	//csv Datei schreiben
	string csv_out = string(input_file);
	csv_out.append(".csv");
	ofstream out_file (csv_out.c_str(), ios::binary);
  	 for(int i=0; i<1024; i++) {
  		 for(int j=0; j<1023; j++){
  			 out_file << (int)data[i][j] << ";";
  		 }
  		out_file << (int)data[i][1023] << "\n";
  	 }
  	out_file.close();

	//Bitmap erstellen
  	vector<uint8_t> pxvector;
	for(int n=0; n<3; n++) {
  		for(int i=0; i<1024; i++) {
  			for(int j=0; j<1024; j++){
				if(data[i][j]<7) {
					pxvector.push_back(color_table[data[i][j]][n]);
				} else {
					cerr << "Unbekannter Gel" << ae << "ndetyp ";
					cerr << (int)data[i][j];
					cerr << " an Position (" << i << "," << j << ")!";
					return 5;
				}
  			 }
  		 }
	}
	
	//Ausgabe des Bitmaps
	string bmp_out = string(input_file);
	bmp_out.append(".bmp");
    cimg_library::CImg<uint8_t> img(&pxvector[0], 1024, 1024, 1, 3);
	img.save_bmp(bmp_out.c_str());
}
