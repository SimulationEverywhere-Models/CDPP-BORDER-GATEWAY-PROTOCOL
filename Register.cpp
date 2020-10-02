 /**********************************************
 *
 *  DESCRIPTION: Simulator::registerNewAtomics()
 *
 *  AUTHOR: Misagh Tavanpour
 *
 *  DATE: 10/12/2012
 *
 **********************************************/

 #include <modeladm.h>
 #include <mainsimu.h>

 #include "inputBuffer.h"
 #include "BGPProcessor.h"

 void MainSimulator::registerNewAtomics()
 {
   SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<inputBuffer>() , "inputBuffer" ) ;
   SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<BGPProcessor>() , "BGPProcessor" ) ;

 }
