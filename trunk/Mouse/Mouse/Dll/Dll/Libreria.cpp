//in questa dll ci sono le funzioni per comunicare con il mouse

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#define LIBRERIA extern "C" __declspec(dllexport)
#include "Libreria.h"
extern "C"
{
#include "C:\\WinDDK\\7600.16385.1\\inc\\api\\hidsdi.h"
#include "C:\\WinDDK\\7600.16385.1\\inc\\api\\setupapi.h"
}
#pragma comment(lib, "C:\\WinDDK\\7600.16385.1\\lib\\win7\\i386\\hid.lib") 
#pragma comment(lib, "setupapi.lib") 

//costanti
#define VID 0x04D8
#define PID 0x000D
#define SIZE 6

BYTE featureReport[SIZE]; //feature report
//variabili globali
HANDLE HidDevHandle;
bool found;

//prototipi
void enumerate();

bool check()
{
	found = false;
	enumerate();
	return found;
}

void ApplicaOnMouse(bool check, int value, int s1, int s2, int s3){
	//predispone il feature report
	featureReport[0]=0;
	if(check)
		featureReport[1]=1;
	else
		featureReport[1]=0;
	featureReport[2]=value;
	featureReport[3]=s1;
	featureReport[4]=s2;
	featureReport[5]=s3;
	//invia il feature report
	if(!HidD_SetFeature(HidDevHandle,featureReport,sizeof(featureReport))){
		MessageBox(NULL,L"Impossibile contattare il dispositivo.\r\nControllare se è collegato correttamente",L"ATTENZIONE",MB_OK);
		return;
	}
}

//Chiede al mouse quali sono i suoi parametri
void AskMouse(bool &check, int &value, int &s1, int &s2, int &s3){
	
	//predispone il feature report
	memset(featureReport,0,6);
	//invia il feature report
	
	if(!HidD_GetFeature(HidDevHandle,featureReport,SIZE)){
		MessageBox(NULL,L"Impossibile contattare il dispositivo.\r\nControllare se è collegato correttamente",L"ATTENZIONE",MB_OK);
		return;
	}
	if(featureReport[1]==1)
		//flag settato
		check=true;
	value=featureReport[2];
	s1=featureReport[3];
	s2=featureReport[4];
	s3=featureReport[5];
}

//Fa l'enumerazione dei dispositivi per cercare il mouse
//Restituisce la HANDLE se lo trova. Altrimenti l'applicazione termina
void enumerate(){
	//variabili locali
	GUID HidGuid;	//HID Globally Unique ID: windows supplies us with this value
	HDEVINFO HidDevInfo;	//handle to structure containing all attached HID Device information
	SP_DEVICE_INTERFACE_DATA devInfoData;	//Information structure for HID devices
	BOOLEAN Result;		//result of getting next device information structure
	PSP_DEVICE_INTERFACE_DETAIL_DATA detailData = 0;	//device info data
	BOOLEAN GotRequiredSize=FALSE;	//1-shot got device info data structure size flag
	BOOLEAN DIDResult;	//get device info data result
	DWORD DataSize;		//size of the DeviceInterfaceDetail structure
	DWORD RequiredSize;		//size of device info data structure
	HIDD_ATTRIBUTES HIDAttrib;	//HID device attribute

	//1) Get the HID Globally Unique ID from the OS
	HidD_GetHidGuid(&HidGuid);

	//2) Get an array of structures containing information about
	//all attached and enumerated HIDs
	HidDevInfo = SetupDiGetClassDevs(	&HidGuid, 
										NULL, 
										NULL, 
										DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);

	//3) Step through the attached device list 1 by 1 and examine
	//each of the attached devices.  When there are no more entries in
	//the array of structures, the function will return FALSE. 
				
	int Index = 0;	//init to first index of array 
	devInfoData.cbSize = sizeof(devInfoData);	// set to the size of the structure
												//that will contain the device info data

	
	do {
		// Get informatiD don about the HIevice with the 'Index' array entry
		Result = SetupDiEnumDeviceInterfaces(	HidDevInfo, 
												0, 
												&HidGuid, 
												Index, 
												&devInfoData);

		//If we run into this condition, then there are no more entries
		//to examine, we might as well return FALSE at point
		if(Result == FALSE)
		{
			//free the memory allocated for DetailData
			if(detailData != NULL)
				free(detailData);
						
			//free HID device info list resources
			SetupDiDestroyDeviceInfoList(HidDevInfo);
						
			MessageBox(NULL,L"Dispositivo non trovato!",L"ATTENZIONE!",MB_OK);
			return;
		}


		if(GotRequiredSize == FALSE)
		{
			//3) Get the size of the DEVICE_INTERFACE_DETAIL_DATA
			//structure.  The first call will return an error condition, 
			//but we'll get the size of the strucure 
			DIDResult = SetupDiGetDeviceInterfaceDetail(	HidDevInfo,
															&devInfoData,
															NULL,
															0,
															&DataSize,
															NULL);
			GotRequiredSize = TRUE;

			//allocate memory for the HidDevInfo structure
			detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA) malloc(DataSize);
			
			//set the size parameter of the structure
			detailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		}
							
						
		//4) Now call the function with the correct size parameter.  This 
		//function will return data from one of the array members that 
		//Step #2 pointed to.  This way we can start to identify the
		//attributes of particular HID devices.
		DIDResult = SetupDiGetDeviceInterfaceDetail(	HidDevInfo,
														&devInfoData,
														detailData,
														DataSize,
														&RequiredSize,
														NULL);
		
		//5) Open a file handle to the device.  Make sure the
		//attibutes specify overlapped transactions or the IN
		//transaction may block the input thread.
		HidDevHandle = CreateFile( detailData->DevicePath,
									GENERIC_WRITE,
									FILE_SHARE_READ | FILE_SHARE_WRITE ,
									NULL,
									OPEN_EXISTING,
									FILE_FLAG_OVERLAPPED,
									NULL);
		
		//6) Get the Device VID & PID to see if it's the device we want
		if(HidDevHandle != INVALID_HANDLE_VALUE)
		{
			HIDAttrib.Size = sizeof(HIDAttrib);
			HidD_GetAttributes(HidDevHandle, &HIDAttrib);

			if((HIDAttrib.VendorID == VID) && (HIDAttrib.ProductID == PID))
			{		
				//free the memory allocated for DetailData
				if(detailData != NULL)
					free(detailData);
						
				//free HID device info list resources
				SetupDiDestroyDeviceInfoList(HidDevInfo);
				found = true;
				return;	//found HID device
			}
						
			//7) Close the Device Handle because we didn't find the device
			//with the correct VID and PID
			CloseHandle(HidDevHandle);
		}
		Index++;	/* increment the array index to search the next entry */
	} while(Result == TRUE);
}