#ifndef WEBFILESERVER_H_
#define WEBFILESERVER_H_

#include <WiFi.h>             
//#include <ESP32WebServer.h>   
#include <WebServer.h> 
//#include <ESPmDNS.h>
//#include <SD.h> 
//#include <SPI.h>

//ESP32WebServer server(80);
WebServer server(80);

bool SD_present = false; //Controls if the SD card is present or not
bool server_on = false;
String webpage = ""; //String to save the html code

void FileServerSetup(void);
void SD_dir();
void File_Upload();
void printDirectory(const char * dirname, uint8_t levels);
void SD_file_download(String filename);
void handleFileUpload();
void SD_file_delete(String filename);
void SendHTML_Header();
void SendHTML_Content();
void SendHTML_Stop();
void ReportSDNotPresent();
void ReportFileNotPresent(String target);
void ReportCouldNotCreateFile(String target);
void append_page_header();
void append_page_footer();
String file_size(int bytes);

#endif