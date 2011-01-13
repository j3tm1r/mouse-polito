/********************************************************************
 FileName:      HardwareProfile.h
 Dependencies:  See INCLUDES section
 Processor:     PIC18, PIC24, or PIC32 USB Microcontrollers
 Hardware:      The code is natively intended to be used on the 
                  following hardware platforms: 
                    PICDEM� FS USB Demo Board
                    PIC18F46J50 FS USB Plug-In Module
                    PIC18F87J50 FS USB Plug-In Module
                    Explorer 16 + PIC24 or PIC32 USB PIMs
                    PIC24F Starter Kit
                    Low Pin Count USB Development Kit
                  The firmware may be modified for use on other USB 
                    platforms by editing this file (HardwareProfile.h)
 Compiler:  	Microchip C18 (for PIC18), C30 (for PIC24), 
                  or C32 (for PIC32)
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the �Company�) for its PIC� Microcontroller is intended and
 supplied to you, the Company�s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
  2.3   09/15/2008   Broke out each hardware platform into its own
                     "HardwareProfile - xxx.h" file
********************************************************************/

#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

/*******************************************************************/
    /******** USB stack hardware selection options *********************/
    /*******************************************************************/
    //This section is the set of definitions required by the MCHPFSUSB
    //  framework.  These definitions tell the firmware what mode it is
    //  running in, and where it can find the results to some information
    //  that the stack needs.
    //These definitions are required by every application developed with
    //  this revision of the MCHPFSUSB framework.  Please review each
    //  option carefully and determine which options are desired/required
    //  for your application.
	
	//#define USE_USB_BUS_SENSE_IO
    #define tris_usb_bus_sense  TRISAbits.TRISA1    // Input
    
    #if defined(USE_USB_BUS_SENSE_IO)
    	#define USB_BUS_SENSE       PORTAbits.RA1
    #else
    	#define USB_BUS_SENSE       1
    #endif
    
    //#define USE_SELF_POWER_SENSE_IO	
    #define tris_self_power     TRISAbits.TRISA2    // Input
    
    #if defined(USE_SELF_POWER_SENSE_IO)
    	#define self_power          PORTAbits.RA2
    #else
    	#define self_power          1
    #endif

	/* // External Transceiver Interface
	#define tris_usb_vpo        TRISBbits.TRISB3    // Output
	#define tris_usb_vmo        TRISBbits.TRISB2    // Output
	#define tris_usb_rcv        TRISAbits.TRISA4    // Input
	#define tris_usb_vp         TRISCbits.TRISC5    // Input
	#define tris_usb_vm         TRISCbits.TRISC4    // Input
	#define tris_usb_oe         TRISCbits.TRISC1    // Output
	
	#define tris_usb_suspnd     TRISAbits.TRISA3    // Output
	*/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/

    //Uncomment the following line to make the output HEX of this 
    //  project work with the HID Bootloader
    #define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER	

    /** Board definition ***********************************************/
    //These defintions will tell the main() function which board is
    //  currently selected.  This will allow the application to add
    //  the correct configuration bits as wells use the correct
    //  initialization functions for the board.  These defitions are only
    //  required in the stack provided demos.  They are not required in
    //  final application design.
    
    #define DEMO_BOARD LOW_PIN_COUNT_USB_DEVELOPMENT_KIT
    #define LOW_PIN_COUNT_USB_DEVELOPMENT_KIT
		
    #define CLOCK_FREQ 48000000
    #define MEMSIC_ADD 0b00010000
    
    /** L E D ***********************************************************/
	#define mInitLed_1()		TRISCbits.TRISC4 = OUTPUT_PIN
	#define mLED_1              LATCbits.LATC4
	#define mLED_1_On()         mLED_1 = 1
	#define mLED_1_Off()        mLED_1 = 0
	#define mLED_1_Toggle()     mLED_1 = !mLED_1
	
	/** S W I T C H *****************************************************/
	#define mInitSwitch()     	TRISCbits.TRISC5 = INPUT_PIN
	#define action_sw      		PORTCbits.RC5

	/** Pippo TASTI ****************************************************/
	typedef enum AnalogPins
	{
		UP = 9, DOWN = 6, LEFT = 4, RIGHT = 5, 
		TASTO_SX = 7, TASTO_DX = 8, 
		WHEELUP = 10, WHEELDOWN = 11
	}
	AnalogPins;
	
    /** I/O pin definitions ********************************************/
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0
	/** MACROS ++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	

	/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++**/
#endif  //HARDWARE_PROFILE_H
