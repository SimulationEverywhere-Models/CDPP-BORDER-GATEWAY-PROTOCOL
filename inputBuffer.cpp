
 #include "inputBuffer.h"      // class BSQueue
 #include "message.h"    // class ExternalMessage, InternalMessage
 #include <iostream>
 #include <fstream>
 // ofstream BQI1 ("BS1QIn.txt");
 // ofstream BQO1 ("BS1QOut.txt");

 inputBuffer::inputBuffer( const string &name ) : Atomic( name )
 , In1( addInputPort( "In1" ) )
 , reqIn( addInputPort( "reqIn" ) )
 , Out1( addInputPort( "Out1" ) )
 , ProcessTime (00,00,00,00)
 {
 }

 Model &inputBuffer::initFunction()
 {
   FirstTime = false;
   Request = 0;
   Qlen = 0;
   state = Idle;
   elements.erase( elements.begin(), elements.end() ) ;
   passivate();
   return *this ;
 }

 Model &inputBuffer::externalFunction( const ExternalMessage &msg )
 {
   if( msg.port() == In1 ) // Input from In1
	 {
	   elements.push_back( msg.value() ) ; //Store Input value in Queue
	   state = Push;
	   Qlen++;
	   holdIn( Atomic::active, ProcessTime);
	 }
     else if (elements.size() > 0)  //So
          	 {
    	       Request = 1;
    	       state = Pop;
    	       holdIn( Atomic::active, ProcessTime);
      	     }
             else if (elements.size() == 0)
            	     {      // Here this two condition are True :(msg.port() == Req) & (elements.size() == 0)
            	       Request = 1;   // Although Queue is empty but remember that server is waiting for input.
            	       passivate();   // If the queue is empty then passivate.
            	     }

   return *this;
 }

 Model &inputBuffer::outputFunction( const InternalMessage &msg )
 {

    if (FirstTime || ((state == Pop) && (Request == 1)))
     {
	 sendOutput( msg.time(), Out1, elements.front());  // Send out data from Queue
	 FirstTime = false;
     }
   return *this ;
 }

 Model &inputBuffer::internalFunction( const InternalMessage & )
 {
   switch (state){
   				    case Idle:
   				    	       if (Request == 1)
   				    	    		   {
   				    	    	   	   	   state = Pop;
   				    	    		   }
   				    	    	else passivate();
   					           break;

   				    case Push:
 			    	            state = Idle;
   					            break;

   				    case Pop:
   				    	       if (Request == 1)
   				    	       {
   				    	    	   elements.pop_front();
   				    	    	   Qlen--;
   				    	       }

   				    	       Request = 0;
   				    	       state = Idle;
   					           break;
           		 }
   return *this;
 }

 inputBuffer::~inputBuffer()
 {
 }
