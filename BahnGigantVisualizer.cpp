//============================================================================
// Name         : BahnGigantVisualizer.cpp
// Author       : simugamer
// Version      : 0.2
// Copyright    : GNU 3 Public Licence
// Beschreibung : Nimmt ein Memory-Dump der Texturinformationen und ein 1024x1024 Bitmap.
//                An Stellen, an denen das Bitmap schwarz ist, werden die Daten in dem Dump
//                so verändert, dass beim zurückladen an dieser Stelle in Bahngigant die Textur
//                dunkel wird. Zum rückgängigmachen eine BMP Datei laden, die kein schwarz enthält
//                Der Memorydump kann z.B mit UsaMimi Hurricane erstellt werden. 
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
#include <sstream>
using namespace std;

const unsigned char AE = static_cast<unsigned char>(142); 
const unsigned char ae = static_cast<unsigned char>(132); 
const unsigned char OE = static_cast<unsigned char>(153); 
const unsigned char oe = static_cast<unsigned char>(148); 
const unsigned char UE = static_cast<unsigned char>(154); 
const unsigned char ue = static_cast<unsigned char>(129); 
const unsigned char ss = static_cast<unsigned char>(225);

bool commandline_mode;

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
	string bin_filename;
	string bmp_filename;
	if(argc == 1) {
		bin_filename = openfilename("Texurinfo-Dump (*.*)\0*.*\0");
		bmp_filename = openfilename("24-Bit-Bitmap (*.bmp)\0*.bmp\0");
		commandline_mode = false;
		if(bin_filename.size()==0) {
			MessageBox(NULL, "Kein Texurinfo-Dump ausgewählt!" , NULL, MB_ICONERROR);
			return 2;
		}
		if(bin_filename.size()==0) {
			MessageBox(NULL, "Kein Windows Bitmap ausgewählt!" , NULL, MB_ICONERROR);
			return 2;
		}
	} else if(argc == 3) {
		bin_filename = argv[1];
		bmp_filename = argv[1];
		commandline_mode = true;
	} else {
		cerr << "Falsche Anzahl an Parametern!";
		return 2;
	}
	ifstream in_file (bin_filename.c_str(), ios::binary);
	in_file.seekg(0, ios::end);
	size_t length = in_file.tellg(); 
	in_file.seekg( 0, ios::beg );
	if(length != 1024*1024*4) {
		if(commandline_mode) {
			cerr << "Falsche Dateigr" << oe << ss <<"e des Texurinfo-Dumps! ";
			cerr << "Datei ist " << length << " Bytes gro" << ss;
			cerr << ".\nErwartet wurden 4.194.304 Bytes.";
		}
		else {
			std::stringstream error_string;
			error_string << "Falsche Dateigröße des Texurinfo-Dumps! ";
			error_string << "Datei ist " << length << " Bytes groß";
			error_string << ".\nErwartet wurden 4.194.304 Bytes.";
			MessageBox(NULL, error_string.str().c_str() , NULL, MB_ICONERROR);
		}
		return 3;
	}

	//Binärdatei einlesen
	vector<vector<vector<unsigned char> > > bin_data;
	bin_data.resize(1024);
    if(in_file.is_open())
    {
		char ch;
   		for(int i=0; i<1024; i++) {
			bin_data[i].resize(1024);
   			for(int j=0; j<1024; j++){
				for(int k=0; k<4; k++){
   					in_file.get(ch);
   					bin_data[i][j].push_back(ch);
				}
   			}
		}
    } else {
		if(commandline_mode) {
			cerr << "Kann Texurinfo-Dump nicht " << oe <<" ffnen!";
		} else {
			std::stringstream error_string;
			error_string << "Kann Texurinfo-Dump nicht öffnen!";
			MessageBox(NULL, error_string.str().c_str() , NULL, MB_ICONERROR);
		}
		return 4;
	}
   	in_file.close();

	//Bitmap einlesen
	cimg_library::CImg<unsigned char> image(bmp_filename.c_str());
	if(image.height()!=1024 || image.width()!= 1024) {
		if(commandline_mode) {
			cerr << "Falsche Dimensionen des BMP.\n";
			cerr << "BMP muss 1024x1024 gro" << ss << " sein!";
		} else {
			std::stringstream error_string;
			error_string << "Falsche Dimensionen des BMP.\n";
			error_string << "BMP muss 1024x1024 groß sein!";
			MessageBox(NULL, error_string.str().c_str() , NULL, MB_ICONERROR);
		}
		return 5;
	}
	vector<vector<vector<unsigned char> > > bmp_data;
	bmp_data.reserve(1024);
	bmp_data.resize(1024);
	for(int i=0; i<1024; i++) {
		bmp_data[i].reserve(1024);
		bmp_data[i].resize(1024);
  		for(int j=0; j<1024; j++){
			bmp_data[i][j].reserve(3);
			bmp_data[i][j].resize(3);
  		 }
	}
	unsigned char *pixel = image.data();
	for(int n=0; n<3; n++) {
  		for(int i=0; i<1024; i++) {
  			for(int j=0; j<1024; j++){
				bmp_data[i][j][n] = *pixel;
				pixel++;
  			 }
  		 }
	}

	//Binärdaten ändern
	for(int i=0; i<1024; i++) {
  		for(int j=0; j<1024; j++){
			if(bmp_data[i][j][0]==0 && bmp_data[i][j][1]==0 && bmp_data[i][j][2]==0) {//schwarze Pixel
				if(bin_data[i][j][0] == 0xFF || bin_data[i][j][0] == 0x0F) {
					bin_data[i][j][0] = 0x0F;
				} else if(bin_data[i][j][0] == 0xC8 || bin_data[i][j][0] == 0x08) {
					bin_data[i][j][0] = 0x08;
				} else {
					if(commandline_mode) {
						cerr << "Unbekannte Helligkeitsstufe " << (int)bin_data[i][j][0] << ".";
					} else {
						std::stringstream error_string;
						error_string << "Unbekannte Helligkeitsstufe " << (int)bin_data[i][j][0] << ".";
						MessageBox(NULL, error_string.str().c_str() , NULL, MB_ICONERROR);
					}
					return 6;
				}
			} else {
				if(bin_data[i][j][0] == 0xFF || bin_data[i][j][0] == 0x0F) {
					bin_data[i][j][0] = 0xFF;
				} else if(bin_data[i][j][0] == 0xC8 || bin_data[i][j][0] == 0x08) {
					bin_data[i][j][0] = 0xC8;
				} else {
					if(commandline_mode) {
						cerr << "Unbekannte Helligkeitsstufe " << (int)bin_data[i][j][0] << ".";
					} else {
						std::stringstream error_string;
						error_string << "Unbekannte Helligkeitsstufe " << (int)bin_data[i][j][0] << ".";
						MessageBox(NULL, error_string.str().c_str() , NULL, MB_ICONERROR);
					}
					return 7;
				}
			}
  		}
  	}

	//Binärdatei schreiben
	string bin_out_filename = bin_filename;
	bin_out_filename.append(".out");
	ofstream bin_out(bin_out_filename, ios::binary);
	for(int i=0; i<1024; i++) {
  		for(int j=0; j<1024; j++){
			for(int n=0; n<4; n++){
				bin_out << bin_data[i][j][n];
			}
		}
	}
}
