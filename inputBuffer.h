 #ifndef __INPUTBUFFER_H
 #define __INPUTBUFFER_H

 #include "atomic.h"     // class Atomic
 #include "string.h"	 // class String
 #include "list.h"

 class inputBuffer : public Atomic
 {
   public:
	 	 inputBuffer( const std::string &name = "inputBuffer" );	//Default constructor
	       virtual std::string className() const { return "inputBuffer"; }
	       ~inputBuffer();

   protected:
	          Model &initFunction();
	          Model &externalFunction( const ExternalMessage & );
	          Model &internalFunction( const InternalMessage & );
	          Model &outputFunction( const InternalMessage & );

   private:
	        const Port &In1,&reqIn;
	        Port &Out1;
	        Time ProcessTime;
	        typedef list<Value> ElementList ;
	        			ElementList elements;
	        int Request;
	        int Request2;
	        int Request3;
	        int Qlen;
	        int Qlen12;
	        int Qlen13;
	        bool FirstTime;
         	enum State{
			            Idle,       //initial state
			            Push,
			            Pop,
		              };
		    State state;
 };

 #endif
