 /***********************************************
 *
 *  DESCRIPTION: Atomic Model Base Station 1 (BS1)
 *
 *  AUTHOR: Baha Uddin Kazi
 *
 *  DATE: 15/08/2014
 *
 ***********************************************/

 #include "BGPProcessor.h"
 #include "message.h"       // InternalMessage ....
#include <iostream>

 BGPProcessor::BGPProcessor( const std::string &name ) : Atomic( name )
 , ProcessorIn1( addInputPort( "ProcessorIn1" ) )
 , ProcessorOut1( addInputPort( "ProcessorOut1" ) )
 , ProcessorOut2( addInputPort( "ProcessorOut2" ) )
 , ProcessTime (00,00,00,10)
 , GenerateTime(00,00,00,50)
 //, CCSTh(0)
 //, BS1Th(0)
 //, BS2Th(0)
 //, BS3Th(0)
 {
 }

 Model &BGPProcessor::initFunction()
  {
	 Qlen = 0;
	 firstReq = true;
	 AlreadyExists = false;
    state = Idle;	// idle
    addToList = false;
    holdIn(Atomic::active, 0);  //Programmed to have an instantaneous internal transition.
    BGPelements.erase( BGPelements.begin(), BGPelements.end() ) ;
	return *this ;
  }

 Model &BGPProcessor::externalFunction( const ExternalMessage &msg )
  {
	 list<Value>::iterator iter1;
	if (msg.port()==ProcessorIn1)
	{
		 InputRoute = msg.value();
	 	 holdIn(Atomic::active, ProcessTime);
	 	 state = RecPack;
	 	 addToList = true;

	}
	if (BGPelements.size() > 0){
		iter1 = BGPelements.begin();
		while(iter1 != BGPelements.end()){
			if (*iter1 == InputRoute){

				AlreadyExists = true;
				break;
			}
			iter1++;
		}
	}
	return *this;
  }

 Model &BGPProcessor::outputFunction( const InternalMessage &msg )
 {

	if (state == RecPack && addToList == true && AlreadyExists == false){
		sendOutput(msg.time(), ProcessorOut1, InputRoute);
		sendOutput(msg.time(), ProcessorOut2, 1);
		BGPelements.push_back(InputRoute);
		addToList = false;
	}
	if (firstReq == true || AlreadyExists == true){
		sendOutput(msg.time(), ProcessorOut2, 1);
		firstReq = false;
		AlreadyExists = false;
	}
	return *this ;
 }

 Model &BGPProcessor::internalFunction( const InternalMessage & )
 {

	 switch (state){
	 		case Idle:
	 			passivate();
	 			break;
	 		case RecPack:
	 			state = Idle;
	 			break;
	 	}
	 return *this;
 }

 BGPProcessor::~BGPProcessor()
{
}
