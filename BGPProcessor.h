 /***********************************************
 *
 *  DESCRIPTION: Atomic Model Base station 1
 *
 *  AUTHOR: Baha Uddin Kazi
 *
 *  DATE: 15/08/2014
 *
 ***********************************************/

 #ifndef __BGPProcessor_H
 #define __BGPProcessor_H

 #include "atomic.h"   // class Atomic
 #include "string.h"	  // class String

 class BGPProcessor : public Atomic
 {
   public:
	 BGPProcessor ( const std::string &name = "BGPProcessor" );  //Default constructor
	       virtual std::string className() const {  return "BGPProcessor" ;}
	       ~BGPProcessor();

   protected:
	          Model &initFunction();
	          Model &externalFunction( const ExternalMessage & );
	          Model &internalFunction( const InternalMessage & );
	          Model &outputFunction( const InternalMessage & );

   private:
	        typedef list<Value> ElementList ;
	          	        	ElementList BGPelements;
	        int InputRoute;
	        int Qlen;
	        bool AlreadyExists,addToList,firstReq;
	        const Port &ProcessorIn1;
	        Port &ProcessorOut1, &ProcessorOut2;
	        Time ProcessTime;
	        Time GenerateTime;
         	enum State{
			            Idle,       //initial state
			            SendPack,   //Sending Packet
			            RecPack,    //Receiving Traffic Packet
		              };
		    State state;
 };

#endif
