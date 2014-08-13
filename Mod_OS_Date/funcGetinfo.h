#ifndef _funcGetinfo_H 
#define _funcGetinfo_H
#pragma once

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <windows.h>
#include <winioctl.h>



#pragma warning(disable:4996)
   //  Required to ensure correct PhysicalDrive IOCTL structure setup
#pragma pack(1)

#define  IDENTIFY_BUFFER_SIZE  512


   //  IOCTL commands
#define  DFP_GET_VERSION          0x00074080
#define  DFP_SEND_DRIVE_COMMAND   0x0007c084
#define  DFP_RECEIVE_DRIVE_DATA   0x0007c088

#define  FILE_DEVICE_SCSI              0x0000001b
#define  IOCTL_SCSI_MINIPORT_IDENTIFY  ((FILE_DEVICE_SCSI << 16) + 0x0501)
#define  IOCTL_SCSI_MINIPORT 0x0004D008  //  see NTDDSCSI.H for definition

   //  Valid values for the bCommandReg member of IDEREGS.
#define  IDE_ATAPI_IDENTIFY  0xA1  //  Returns ID sector for ATAPI.
#define  IDE_ATA_IDENTIFY    0xEC  //  Returns ID sector for ATA.

   // The following struct defines the interesting part of the IDENTIFY
   // buffer:
typedef struct _IDSECTOR
{
   USHORT  wGenConfig;
   USHORT  wNumCyls;
   USHORT  wReserved;
   USHORT  wNumHeads;
   USHORT  wBytesPerTrack;
   USHORT  wBytesPerSector;
   USHORT  wSectorsPerTrack;
   USHORT  wVendorUnique[3];
   CHAR    sSerialNumber[20];
   USHORT  wBufferType;
   USHORT  wBufferSize;
   USHORT  wECCSize;
   CHAR    sFirmwareRev[8];
   CHAR    sModelNumber[40];
   USHORT  wMoreVendorUnique;
   USHORT  wDoubleWordIO;
   USHORT  wCapabilities;
   USHORT  wReserved1;
   USHORT  wPIOTiming;
   USHORT  wDMATiming;
   USHORT  wBS;
   USHORT  wNumCurrentCyls;
   USHORT  wNumCurrentHeads;
   USHORT  wNumCurrentSectorsPerTrack;
   ULONG   ulCurrentSectorCapacity;
   USHORT  wMultSectorStuff;
   ULONG   ulTotalAddressableSectors;
   USHORT  wSingleWordDMA;
   USHORT  wMultiWordDMA;
   BYTE    bReserved[128];
} IDSECTOR, *PIDSECTOR;

//
// IDENTIFY data (from ATAPI driver source)
//

#pragma pack(1)

typedef struct _IDENTIFY_DATA {
    USHORT GeneralConfiguration;            // 00 00
    USHORT NumberOfCylinders;               // 02  1
    USHORT Reserved1;                       // 04  2
    USHORT NumberOfHeads;                   // 06  3
    USHORT UnformattedBytesPerTrack;        // 08  4
    USHORT UnformattedBytesPerSector;       // 0A  5
    USHORT SectorsPerTrack;                 // 0C  6
    USHORT VendorUnique1[3];                // 0E  7-9
    USHORT SerialNumber[10];                // 14  10-19
    USHORT BufferType;                      // 28  20
    USHORT BufferSectorSize;                // 2A  21
    USHORT NumberOfEccBytes;                // 2C  22
    USHORT FirmwareRevision[4];             // 2E  23-26
    USHORT ModelNumber[20];                 // 36  27-46
    UCHAR  MaximumBlockTransfer;            // 5E  47
    UCHAR  VendorUnique2;                   // 5F
    USHORT DoubleWordIo;                    // 60  48
    USHORT Capabilities;                    // 62  49
    USHORT Reserved2;                       // 64  50
    UCHAR  VendorUnique3;                   // 66  51
    UCHAR  PioCycleTimingMode;              // 67
    UCHAR  VendorUnique4;                   // 68  52
    UCHAR  DmaCycleTimingMode;              // 69
    USHORT TranslationFieldsValid:1;        // 6A  53
    USHORT Reserved3:15;
    USHORT NumberOfCurrentCylinders;        // 6C  54
    USHORT NumberOfCurrentHeads;            // 6E  55
    USHORT CurrentSectorsPerTrack;          // 70  56
    ULONG  CurrentSectorCapacity;           // 72  57-58
    USHORT CurrentMultiSectorSetting;       //     59
    ULONG  UserAddressableSectors;          //     60-61
    USHORT SingleWordDMASupport : 8;        //     62
    USHORT SingleWordDMAActive : 8;
    USHORT MultiWordDMASupport : 8;         //     63
    USHORT MultiWordDMAActive : 8;
    USHORT AdvancedPIOModes : 8;            //     64
    USHORT Reserved4 : 8;
    USHORT MinimumMWXferCycleTime;          //     65
    USHORT RecommendedMWXferCycleTime;      //     66
    USHORT MinimumPIOCycleTime;             //     67
    USHORT MinimumPIOCycleTimeIORDY;        //     68
    USHORT Reserved5[2];                    //     69-70
    USHORT ReleaseTimeOverlapped;           //     71
    USHORT ReleaseTimeServiceCommand;       //     72
    USHORT MajorRevision;                   //     73
    USHORT MinorRevision;                   //     74
    USHORT Reserved6[50];                   //     75-126
    USHORT SpecialFunctionsEnabled;         //     127
    USHORT Reserved7[128];                  //     128-255
} IDENTIFY_DATA, *PIDENTIFY_DATA;

#pragma pack()

typedef struct _SRB_IO_CONTROL
{
   ULONG HeaderLength;
   UCHAR Signature[8];
   ULONG Timeout;
   ULONG ControlCode;
   ULONG ReturnCode;
   ULONG Length;
} SRB_IO_CONTROL, *PSRB_IO_CONTROL;

   // Structure returned by PhysicalDrive IOCTL for several commands
typedef struct _SENDCMDOUTPARAMS
{
   DWORD         cBufferSize;   //  Size of bBuffer in bytes
   DRIVERSTATUS  DriverStatus;  //  Driver status structure.
   BYTE          bBuffer[1];    //  Buffer of arbitrary length in which to store the data read from the                                                       // drive.
} SENDCMDOUTPARAMS, *PSENDCMDOUTPARAMS, *LPSENDCMDOUTPARAMS;

   //  GETVERSIONOUTPARAMS contains the data returned from the 
   //  Get Driver Version function.
typedef struct _GETVERSIONOUTPARAMS
{
   BYTE bVersion;      // Binary driver version.
   BYTE bRevision;     // Binary driver revision.
   BYTE bReserved;     // Not used.
   BYTE bIDEDeviceMap; // Bit map of IDE devices.
   DWORD fCapabilities; // Bit mask of driver capabilities.
   DWORD dwReserved[4]; // For future use.
} GETVERSIONOUTPARAMS, *PGETVERSIONOUTPARAMS, *LPGETVERSIONOUTPARAMS;


#define  MAX_IDE_DRIVES  16

#include <vector>
using namespace std;
vector<WORD*> m_DriveSerialList ;


BOOL AddIfNew(USHORT *pIdSector)
{
	BOOL bAdd = TRUE;
	for(UINT i =0; i< m_DriveSerialList.size();i++)
	   {
		   if(memcmp(pIdSector,m_DriveSerialList[i],256 * sizeof(WORD)) == 0)
		   {
			   bAdd = false;
			   break;
		   }
	   }
	   if(bAdd)
	   {
		    WORD* diskdata = new WORD[256];
			 ::memcpy(diskdata,pIdSector,256*sizeof(WORD));
			 m_DriveSerialList.push_back(diskdata);
	   }
	   return bAdd;
}
   // DoIDENTIFY
   // FUNCTION: Send an IDENTIFY command to the drive
   // bDriveNum = 0-3
   // bIDCmd = IDE_ATA_IDENTIFY or IDE_ATAPI_IDENTIFY
BOOL DoIDENTIFY (HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP,
                 PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum,
                 PDWORD lpcbBytesReturned)
{
      // Set up data structures for IDENTIFY command.
   pSCIP -> cBufferSize = IDENTIFY_BUFFER_SIZE;
   pSCIP -> irDriveRegs.bFeaturesReg = 0;
   pSCIP -> irDriveRegs.bSectorCountReg = 1;
   pSCIP -> irDriveRegs.bSectorNumberReg = 1;
   pSCIP -> irDriveRegs.bCylLowReg = 0;
   pSCIP -> irDriveRegs.bCylHighReg = 0;

      // Compute the drive number.
   pSCIP -> irDriveRegs.bDriveHeadReg = 0xA0 | ((bDriveNum & 1) << 4);

      // The command can either be IDE identify or ATAPI identify.
   pSCIP -> irDriveRegs.bCommandReg = bIDCmd;
   pSCIP -> bDriveNumber = bDriveNum;
   pSCIP -> cBufferSize = IDENTIFY_BUFFER_SIZE;

   return ( DeviceIoControl (hPhysicalDriveIOCTL, DFP_RECEIVE_DRIVE_DATA,
               (LPVOID) pSCIP,
               sizeof(SENDCMDINPARAMS) - 1,
               (LPVOID) pSCOP,
               sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1,
               lpcbBytesReturned, NULL) );
}


BOOL ReadPhysicalDriveInNTWithAdminRights (void)
{
   int done = FALSE;
   int drive = 0;
   BYTE IdOutCmd [sizeof (SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];
   for (drive = 0; drive < MAX_IDE_DRIVES; drive++)
   {
      HANDLE hPhysicalDriveIOCTL = 0;

         //  Try to get a handle to PhysicalDrive IOCTL, report failure
         //  and exit if can't.
      TCHAR driveName [256];

      sprintf (driveName, "\\\\.\\PhysicalDrive%d", drive);

         //  Windows NT, Windows 2000, must have admin rights
      hPhysicalDriveIOCTL = CreateFile (driveName,
                               GENERIC_READ | GENERIC_WRITE, 
                               FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                               OPEN_EXISTING, 0, NULL);

      if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
      {
         GETVERSIONOUTPARAMS VersionParams;
         DWORD               cbBytesReturned = 0;

            // Get the version, etc of PhysicalDrive IOCTL
         memset ((void*) &VersionParams, 0, sizeof(VersionParams));

         if (  DeviceIoControl (hPhysicalDriveIOCTL, DFP_GET_VERSION,
                   NULL, 
                   0,
                   &VersionParams,
                   sizeof(VersionParams),
                   &cbBytesReturned, NULL) )
         {         


				// If there is a IDE device at number "i" issue commands
				// to the device
			 if (VersionParams.bIDEDeviceMap > 0)
			 {
				BYTE             bIDCmd = 0;   // IDE or ATAPI IDENTIFY cmd
				SENDCMDINPARAMS  scip;

				// Now, get the ID sector for all IDE devices in the system.
				   // If the device is ATAPI use the IDE_ATAPI_IDENTIFY command,
				   // otherwise use the IDE_ATA_IDENTIFY command
				bIDCmd = (VersionParams.bIDEDeviceMap >> drive & 0x10) ? \
						  IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;

				memset (&scip, 0, sizeof(scip));
				memset (IdOutCmd, 0, sizeof(IdOutCmd));

				if ( DoIDENTIFY (hPhysicalDriveIOCTL, 
						   &scip, 
						   (PSENDCMDOUTPARAMS)&IdOutCmd, 
						   (BYTE) bIDCmd,
						   (BYTE) drive,
						   &cbBytesReturned))
				{
	              
		
				   USHORT *pIdSector = (USHORT *)
								 ((PSENDCMDOUTPARAMS) IdOutCmd) -> bBuffer;
				   AddIfNew(pIdSector);	  
				   done = TRUE;
				}
			}
	    }

         CloseHandle (hPhysicalDriveIOCTL);
      }
   }

   return done;
}

BOOL ReadPhysicalDriveInNTUsingSmart (void)
{
   int done = FALSE;
   int drive = 0;

   for (drive = 0; drive < MAX_IDE_DRIVES; drive++)
   {
      HANDLE hPhysicalDriveIOCTL = 0;

         //  Try to get a handle to PhysicalDrive IOCTL, report failure
         //  and exit if can't.

	  TCHAR driveName [256];
      sprintf  (driveName, "\\\\.\\PhysicalDrive%d", drive);

         //  Windows NT, Windows 2000, Windows Server 2003, Vista
      hPhysicalDriveIOCTL = CreateFile (driveName,
                               GENERIC_READ | GENERIC_WRITE, 
                               FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 
							   NULL, OPEN_EXISTING, 0, NULL);

      if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
      {

      }
      else
      {
         GETVERSIONINPARAMS GetVersionParams;
         DWORD cbBytesReturned = 0;

            // Get the version, etc of PhysicalDrive IOCTL
         memset ((void*) & GetVersionParams, 0, sizeof(GetVersionParams));

         if (  DeviceIoControl (hPhysicalDriveIOCTL, SMART_GET_VERSION,
                   NULL, 
                   0,
     			   &GetVersionParams, sizeof (GETVERSIONINPARAMS),
				   &cbBytesReturned, NULL) )
         {         
	           // Allocate the command buffer
			ULONG CommandSize = sizeof(SENDCMDINPARAMS) + IDENTIFY_BUFFER_SIZE;
        	PSENDCMDINPARAMS Command = (PSENDCMDINPARAMS) malloc (CommandSize);
	           // Retrieve the IDENTIFY data
	           // Prepare the command
#define ID_CMD          0xEC            // Returns ID sector for ATA
			Command -> irDriveRegs.bCommandReg = ID_CMD;
			DWORD BytesReturned = 0;
	        if ( DeviceIoControl (hPhysicalDriveIOCTL, 
				                    SMART_RCV_DRIVE_DATA, Command, sizeof(SENDCMDINPARAMS),
									Command, CommandSize,
									&BytesReturned, NULL) )

			{
        	    //   // Print the IDENTIFY data
                //DWORD diskdata [256];
                USHORT *pIdSector = (USHORT *)
                             (PIDENTIFY_DATA) ((PSENDCMDOUTPARAMS) Command) -> bBuffer;


				AddIfNew(pIdSector);
  
                done = TRUE;
			}
	           // Done
            CloseHandle (hPhysicalDriveIOCTL);
			free (Command);
		 }
      }
   }

   return done;
}

char * ConvertToString (WORD diskdata [256], int firstIndex, int lastIndex)
{
   static char string [1024];
   int index = 0;
   int position = 0;

      //  each integer has two characters stored in it backwards
   for (index = firstIndex; index <= lastIndex; index++)
   {
         //  get high byte for 1st character
      string [position] = (char) (diskdata [index] / 256);
      position++;

         //  get low byte for 2nd character
      string [position] = (char) (diskdata [index] % 256);
      position++;
   }

      //  end the string 
   string [position] = '\0';

      //  cut off the trailing blanks
   for (index = position - 1; index > 0 && ' ' == string [index]; index--)
      string [index] = '\0';

   return string;
}


char* ModelNumber (UINT drive)
{
	return ConvertToString(m_DriveSerialList[drive], 27, 46);
}

char* SerialNumber (UINT drive)
{
	return ConvertToString(m_DriveSerialList[drive], 10, 19);
}


char* RevisionNumber (UINT drive)
{
	return ConvertToString(m_DriveSerialList[drive], 23, 26);
}

char* DriveType (UINT drive)
{
   if (m_DriveSerialList[drive][0] & 0x0080)
      return "移动硬盘";
   else if (m_DriveSerialList[drive][0] & 0x0040)
      return "固定硬盘";
   else return "未知硬盘";
}

//提升进程权限
BOOL UpdateProcessPrivilege( HANDLE hProcess, LPCTSTR lpPrivilegeName = SE_DEBUG_NAME )
// hProcess [in] : 要提升的进程，目标进程
// lpPrivilegeName [in] : 要提升到的特权，目标特权
// 返回值 : TRUE : 成功; FALSE : 失败
{
	HANDLE hToken;
	if ( ::OpenProcessToken( hProcess, TOKEN_ALL_ACCESS, &hToken ) ) {
		
		LUID destLuid;
		if ( ::LookupPrivilegeValue( NULL, lpPrivilegeName, &destLuid ) ) {
			
			TOKEN_PRIVILEGES TokenPrivileges;
			TokenPrivileges.PrivilegeCount = 1;
			TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			TokenPrivileges.Privileges[0].Luid = destLuid;
			int iResult;
			if ( iResult = ::AdjustTokenPrivileges( hToken, FALSE, &TokenPrivileges, 
									0, NULL, NULL ) ) {
				
				return TRUE;				
			}
		}
	}

	return FALSE;
}

#endif 