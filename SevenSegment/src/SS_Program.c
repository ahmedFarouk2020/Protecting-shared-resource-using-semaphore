/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : August 19 2020                              */
/*********************************************************/

#include "../inc/STD_TYPES.h"
#include "../inc/BIT_MATH.h"

#include "../inc/SS_interface.h"

#include "../inc/DIO_interface.h"


void SS_Init(uint8_t PortId)
{
	// DIO_SetPortDirection(PortId,OUTPUT);
	DIO_setPinDirection(PortId , PIN0 , OUTPUT );
	DIO_setPinDirection(PortId , PIN1 , OUTPUT );
	DIO_setPinDirection(PortId , PIN2 , OUTPUT );
	DIO_setPinDirection(PortId , PIN3 , OUTPUT );
	DIO_setPinDirection(PortId , PIN4 , OUTPUT );
	DIO_setPinDirection(PortId , PIN5 , OUTPUT );
	DIO_setPinDirection(PortId , PIN6 , OUTPUT );
}



void SS_voidDisplayNum(uint8_t portId, uint8_t Num, uint8_t mode)
{
	switch(mode)
	{
		case COMMON_CATHODE : 
			DIO_SetPortValue(portId,Num);
			break;
		case COMMON_ANODE : 
			DIO_SetPortValue(portId,Num);
			break;
	}
}