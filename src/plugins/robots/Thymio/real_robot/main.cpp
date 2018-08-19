#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/core/utility/configuration/command_line_arg_parser.h>
#include <argos3/core/utility/logging/argos_log.h>
#include "real_Thymio.h"

using namespace argos;

int main(int argc, char* argv[]) {

    /*
     * Parse the command line
     */
   std::string strARGoSFName;
   std::string strControllerId;
   std::string strAsebaFile;
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

   std::cout<< "executed the code";
   try {
      cCLAP.Parse(argc, argv);
   }
   catch(CARGoSException& ex) {
      /* A fatal error occurred: dispose of data, print error and exit */
       LOGERR << "Couldn't Parse Args!" << std::endl;
      return 1;
   }

       // * Initialize the robot
   try {
       CRealThymio* pcRobot = new CRealThymio();
       pcRobot->Init(strARGoSFName, strControllerId);
       /*
        * Perform the main loop
        */
       pcRobot->Execute();
   } catch (CARGoSException& ex) {
       LOGERR << "Couln't Init Robot!" << std::endl;
       return 1;
   }

   /* All done (should never get here) */
   return 0;
}
