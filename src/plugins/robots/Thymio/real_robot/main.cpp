#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/core/utility/configuration/command_line_arg_parser.h>
#include <argos3/core/utility/logging/argos_log.h>
#include "real_Thymio.h"
#include "dbusinterface.h"

using namespace argos;

int main(int argc, char* argv[]) {

    QCoreApplication a(argc,argv);

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
//   cCLAP.AddArgument<std::string>(
//      'f',
//      "--asebascript-file",
//      "the path of aseba script",
//      strAsebaFile);
   std::cout<< "executed the code";
   try {
      cCLAP.Parse(argc, argv);
   }
   catch(CARGoSException& ex) {
      /* A fatal error occurred: dispose of data, print error and exit */
       LOGERR << "Couldn't Parse Args!" << std::endl;
      return 1;
   }

   /*get connection to Thymio */
   Aseba::DBusInterface* ThymioInterface;
   try {
       ThymioInterface = new Aseba::DBusInterface();
   } catch (std::exception ex) {
       std::cout<<ex.what();
   }

   /* Open and pass the events file*/
   try {
       ThymioInterface->loadScript("../../../ScriptDBusThymio.aesl");
   } catch (std::exception ex) {
       //std::cout<<ex.what()<<"couldn't open file";
       THROW_ARGOSEXCEPTION("Unknown actuator \"");
   }


       // * Initialize the robot
   try {
       CRealThymio* pcRobot = new CRealThymio();
       pcRobot->Init(strARGoSFName, strControllerId, ThymioInterface);
       /*
        * Perform the main loop
        */
       pcRobot->Execute();
   } catch (CARGoSException& ex) {
       LOGERR << "Couln't Init Robot!" << std::endl;
       return 1;
   }

   /* All done (should never get here) */
   return a.exec();
}
