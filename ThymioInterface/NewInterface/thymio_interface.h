/*
	Aseba - an event-based framework for distributed robot control
	Created by Stéphane Magnenat <stephane at magnenat dot net> (http://stephane.magnenat.net)
	with contributions from the community.
	Copyright (C) 2007--2018 the authors, see authors.txt for details.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published
	by the Free Software Foundation, version 3 of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SHELL_H
#define SHELL_H


#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#include <iostream>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <vector>
#include <string>
#include <dashel/dashel-posix.h>
#include <aseba/common/msg/NodesManager.h>
#include <aseba/compiler/compiler.h>
#include <aseba/common/utils/utils.h>
#include <aseba/transport/dashel_plugins/dashel-plugins.h>


/*
	This is the main class of the Aseba client, called Shell
	because this example provides a simple command-line shell
	to interact with an Aseba network. Start this program
	and type "help" to see the list of commands.

	This class inherits from Dashel::Hub and Aseba::NodesManager.
	The first provides the synchronisation between the command-line
	inputs and the Aseba messages from an Aseba target, through the
	streams shellStream and targetStream.
	The second reconstruct target descriptions by filtering
	Aseba messages through NodesManager::processMessage().
*/
namespace Aseba{
class ThymioInterface: public Dashel::Hub, public Aseba::NodesManager
{
public:
	typedef std::vector<std::string> strings;
	typedef std::map<std::string, Aseba::VariablesMap> NodeNameToVariablesMap;
    typedef std::vector<std::uint16_t> Values;
    typedef std::map<uint16_t, Values> MessageMap;
    Values* values;
    MessageMap* map;

private:
	// streams
    Dashel::Stream* targetStream;

	// result of last compilation and load used to interprete messages
	Aseba::CommonDefinitions commonDefinitions;
	NodeNameToVariablesMap allVariables;

public:
    int j = 0;
	// interface with main()
    ThymioInterface(const std::string& target);
    ~ThymioInterface(){
        this->wait();
        this->closeStream(targetStream);
    }

public:
	// reimplemented from parent classes
	virtual void sendMessage(const Aseba::Message& message);
	virtual void nodeDescriptionReceived(unsigned nodeId);
    virtual void incomingData(Dashel::Stream *targetStream);

    // wait function
    bool wait(int timeout = 20);


	// implementation of all commands
	void listNodes();
    void listVariables(const std::string target);
    Values getVariable(const std::string& nodeName, const std::string& varName);
    void setVariable(const std::string& nodeName, const std::string& varName, VariablesDataVector data);
    void sendEventName(const std::string& eventName, const VariablesDataVector data);
    void load(const std::string& filePath);
    void stop(const std::string& nodeName);
    void run(const std::string& nodeName);
    bool setup(const std::string& nodeName);

	// helper functions
	bool getNodeAndVarPos(const std::string& nodeName, const std::string& variableName, unsigned& nodeId, unsigned& pos) const;
	bool compileAndSendCode(const std::wstring& source, unsigned nodeId, const std::string& nodeName);
};
}
#endif // SHELL_H
