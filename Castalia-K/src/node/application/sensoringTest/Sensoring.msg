//****************************************************************************
//*  Copyright: National ICT Australia,  2007 - 2011                         *
//*  Developed at the ATP lab, Networked Systems research theme              *
//*  Author(s): Yuriy Tselishchev, Athanassios Boulis                        *
//*  This file is distributed under the terms in the attached LICENSE file.  *
//*  If you do not find this file, copies can be found by writing to:        *
//*                                                                          *
//*      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia             *
//*      Attention:  License Inquiry.                                        *
//*                                                                          *  
//****************************************************************************/

cplusplus {{
#include "ApplicationPacket_m.h"
#include <string>
using namespace std;
}}

class ApplicationPacket;

struct Info{
	unsigned short nodeID;
	double locX;
	double locY;
	string payload;
	double sensData;
}

packet Sensoring extends ApplicationPacket {
	Info extraData;
}
