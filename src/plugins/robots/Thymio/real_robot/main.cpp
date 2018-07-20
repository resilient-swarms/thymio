#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/core/utility/configuration/command_line_arg_parser.h>
#include <argos3/core/utility/logging/argos_log.h>
#include "real_Thymio.h"

using namespace argos;

int main(int argc, char* argv[]) {
   /*
    * Parse the command line
    */
    QCoreApplication a(argc,argv);
   std::cout<< "executed the code";
   std::string strARGoSFName;
   std::string strControllerId;
   CCommandLineArgParser cCLAP;
   cCLAP.AddArgument<std::string>(
      'c',
      "--config-file",
      "the experiment XML configuration file",
      strARGoSFName);
   cCLAP.AddArgument<std::string>(
      'i',
      "--controller-id",
      "the id of the controller to run",
      strControllerId);
   try {
      cCLAP.Parse(argc, argv);
      
       // * Initialize the robot
       
      CRealThymio* pcRobot = new CRealThymio();
      pcRobot->Init(strARGoSFName, strControllerId);
      /*
       * Perform the main loop
       */
      pcRobot->Execute();
   }
   catch(CARGoSException& ex) {
      /* A fatal error occurred: dispose of data, print error and exit */
      // LOGERR << ex.what() << std::endl;
      return 1;
   }
   /* All done (should never get here) */
   return a.exec();
}
