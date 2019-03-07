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



#if defined(_WIN32) && defined(__MINGW32__)
  /* This is a workaround for MinGW32, see libxml/xmlexports.h */
  #define IN_LIBXML
#endif

#include "thymio_interface.h"

using namespace std;
//using namespace Dashel;
using namespace Aseba;

// code of the shell

ThymioInterface::ThymioInterface(const std::string& target):
    targetStream(connect(target))
{
        Dashel::initPlugins();
        values = new Values();
        map = new MessageMap();
        if(targetStream->failed())
        {
            std::cout << targetStream->getFailReason();
        }
        this->pingNetwork();
        this->wait();
        this->listNodes();
        this->wait();
}

bool ThymioInterface::wait(int timeout)
{
    UnifiedTime startTime;
    while (timeout > 0)
    {
        if (!step(timeout))
            return false;
        const UnifiedTime now;
        timeout -= (now - startTime).value;
        startTime = now;
    }
    return true;
}

void ThymioInterface::sendMessage(const Message& message)
{
	message.serialize(targetStream);
	targetStream->flush();
}

void ThymioInterface::nodeDescriptionReceived(unsigned nodeId)
{
    std::cout << '\r';
    std::cout << "Received description for node " << WStringToUTF8(getNodeName(nodeId))  << "\n";
    std::cout << endl;
}

void ThymioInterface::incomingData(Dashel::Stream *stream)
{
    // receive message
    Message *message = 0;
    try
    {
        // deserialize message using Aseba::Message::receive() static function
        message = Message::receive(stream);
    }
    catch (Dashel::DashelException e)
    {
        // if this stream has a problem, ignore it for now,
        // and let Hub call connectionClosed later.
        std::cout << "error while receiving message: " << e.what() << endl;
        return;
    }

    // pass message to description manager, which builds
    // the node descriptions in background
    NodesManager::processMessage(message);

    // if variables, print
    const Variables *variables(dynamic_cast<Variables *>(message));
    if (variables)
    {
        // as this is a shell, we just print the result of the variable
        // message as we assumes that it was linked to the last
        // GetVariables request, but in case a third-party is requesting
        // variables there might be many response before the one corresponding
        // to the query. In that case, the variables->start value
        // must be checked against the variable map

        for (size_t i = 0; i < variables->variables.size(); ++i)
        {
            values->push_back(variables->variables[i]);
//            std::cout << j << ")" <<variables->variables[i] << " ";
        }
        map->insert( std::pair<uint16_t,Values>(message->source,(*values) ) );
        //clean values for next message
        values = new Values();
    }

    // if user event, print
    const UserMessage *userMessage(dynamic_cast<UserMessage *>(message));
    if (userMessage)
    {
        std::cout << '\r';
        if (userMessage->type < commonDefinitions.events.size())
            std::cout << WStringToUTF8( commonDefinitions.events[userMessage->type].name );
        else
            std::cout << "unknown event " << userMessage->type;
        std::cout << ": ";
        for (size_t i = 0; i < userMessage->data.size(); ++i)
            std::cout << userMessage->data[i] << " ";
        std::cout << endl;
    }

    delete message;
}

void ThymioInterface::listNodes()
{

    for (NodesMap::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
        std::cout << WStringToUTF8( (it->second).name )<< endl;
}

void ThymioInterface::listVariables(const string target){
    bool ok;
    const unsigned nodeId(getNodeId(UTF8ToWString(target), 0, &ok));
    if (!ok)
    {
        wcerr << "invalid node name " << UTF8ToWString(target) << endl;
        return;
    }
    const TargetDescription* desc(getDescription(nodeId));
    if (!desc)
        return;

    // dump target description
    wcerr << "Target name " << desc->name << endl;
    wcerr << "protocol version " << desc->protocolVersion << endl;
    wcerr << "bytecode size " << desc->bytecodeSize << endl;
    wcerr << "variables size " << desc->variablesSize << endl;
    wcerr << "stack size " << desc->stackSize << endl;
    wcerr << "variables:" << endl;

    // if we have a result from the compiler for this node...
    const NodeNameToVariablesMap::const_iterator allVarMapIt(allVariables.find(target));
    if (allVarMapIt != allVariables.end())
    {
        // ... use it
        const VariablesMap& varMap(allVarMapIt->second);
        VariablesMap::const_iterator it(varMap.begin());
        for (;it != varMap.end(); ++it)
            wcerr << "  " << it->first << " " << it->second.second << endl;
    }
    else
    {
        // ... otherwise shows variables from the target description
        for (size_t i=0; i<desc->namedVariables.size(); ++i)
        {
            const TargetDescription::NamedVariable& var(desc->namedVariables[i]);
            wcerr << "  " << var.name << " " << var.size << endl;
        }
    }
    wcerr << "local events: " << endl;
    for (size_t i=0; i<desc->localEvents.size(); ++i)
    {
        const TargetDescription::LocalEvent &event(desc->localEvents[i]);
        wcerr << "  " << event.name << " - " << event.description << endl;
    }
    wcerr << "native functions:" << endl;
    for (size_t i=0; i<desc->nativeFunctions.size(); ++i)
    {
        const TargetDescription::NativeFunction& func(desc->nativeFunctions[i]);
        wcerr << "  " << func.name << "(";
        for (size_t j=0; j<func.parameters.size(); ++j)
        {
            const TargetDescription::NativeFunctionParameter& param(func.parameters[j]);
            wcerr << param.name << "[";
            if (param.size > 0)
                wcerr << param.size;
            else
                wcerr << "T<" << -param.size << ">";
            wcerr << "]";
            if (j+1 != func.parameters.size())
                wcerr << ", ";
        }
        wcerr << ") - ";
        wcerr << func.description << endl;
    }
}

ThymioInterface::Values ThymioInterface::getVariable(const std::string& nodeName, const std::string& varName)
{
	// get node id, variable position and length
	unsigned nodeId, pos;
    const bool exists(getNodeAndVarPos(nodeName, varName, nodeId, pos));
	if (!exists)
        std::cout<< "error: there is no node : "<< nodeName;
	bool ok;
    const unsigned length(getVariableSize(nodeId, UTF8ToWString(varName), &ok));
	if (!ok)
        std::cout<< "error: there is no variable : "<< varName;

	// send the message
    GetVariables* g = new GetVariables(nodeId, pos, length);
    g->serialize(targetStream);
    targetStream->flush();
    this->wait();
    ThymioInterface::Values v;
    uint16_t m = g->dest;
    try{
        std::map<uint16_t,Values>::iterator it = map->find(m);
          if (it != map->end())
            {
              v = it->second;
              map->erase(it);
            }

    }catch(std::exception e)
    {
        std::cout<< e.what();
        v = *values;
    }
    delete g;
    return v;
}

void ThymioInterface::setVariable(const string& nodeName, const string& varName, const VariablesDataVector data)
{
    // get node id, variable position and length
    unsigned nodeId, pos;
    const bool exists(getNodeAndVarPos(nodeName, varName, nodeId, pos));
    if (!exists)
        return;

    // send the message
    SetVariables setVariables(nodeId, pos, data);
    setVariables.serialize(targetStream);
    targetStream->flush();
    this->wait();
}

void ThymioInterface::sendEventName(const string& eventName, const VariablesDataVector data)
{

	size_t pos;
    if (!commonDefinitions.events.contains(UTF8ToWString(eventName), &pos))
	{
        wcerr << "event " << UTF8ToWString(eventName) << " is unknown" << endl;
		return;
	}

	// build event and emit
//    VariablesDataVector sdata;
//    for (size_t i=0; i<data.size(); ++i)
//        sdata.push_back(atoi(data[i].c_str()));
    UserMessage userMessage(pos, data);
	userMessage.serialize(targetStream);
	targetStream->flush();
}

void ThymioInterface::load(const string& filePath)
{
	// open document
    const string& fileName(filePath);
	xmlDoc *doc(xmlReadFile(fileName.c_str(), nullptr, 0));
	if (!doc)
	{
		wcerr << "cannot read XML from file " << UTF8ToWString(fileName) << endl;
		return;
	}
    xmlNode *domRoot(xmlDocGetRootElement(doc));

	// clear existing data
	commonDefinitions.events.clear();
	commonDefinitions.constants.clear();
	allVariables.clear();


	// load new data
	int noNodeCount(0);
	bool wasError(false);
	if (!xmlStrEqual(domRoot->name, BAD_CAST("network")))
	{
		wcerr << "root node is not \"network\", XML considered invalid" << endl;
		wasError = true;
	}
	else for (xmlNode *domNode(xmlFirstElementChild(domRoot)); domNode; domNode = domNode->next)
	{
		if (domNode->type == XML_ELEMENT_NODE)
		{
			// an Aseba node, which contains a virtual machine
			if (xmlStrEqual(domNode->name, BAD_CAST("node")))
			{
				// get attributes, child and content
				xmlChar *name(xmlGetProp(domNode, BAD_CAST("name")));
				if (!name)
				{
					wcerr << "missing \"name\" attribute in \"node\" entry" << endl;
				}
				else
				{
					const string _name((const char *)name);
					xmlChar * text(xmlNodeGetContent(domNode));
					if (!text)
					{
						wcerr << "missing text in \"node\" entry" << endl;
					}
					else
					{
						// got the identifier of the node and compile the code
						unsigned preferedId(0);
						xmlChar *storedId = xmlGetProp(domNode, BAD_CAST("nodeId"));
						if (storedId)
							preferedId = unsigned(atoi((char*)storedId));
						bool ok;
						unsigned nodeId(getNodeId(UTF8ToWString(_name), preferedId, &ok));
						if (ok)
						{
							if (!compileAndSendCode(UTF8ToWString((const char *)text), nodeId, _name))
								wasError = true;
						}
						else
							noNodeCount++;

						// free attribute and content
						xmlFree(text);
					}
					xmlFree(name);
				}
			}
			// a global event
			else if (xmlStrEqual(domNode->name, BAD_CAST("event")))
			{
				// get attributes
				xmlChar *name(xmlGetProp(domNode, BAD_CAST("name")));
				if (!name)
					wcerr << "missing \"name\" attribute in \"event\" entry" << endl;
				xmlChar *size(xmlGetProp(domNode, BAD_CAST("size"))); 
				if (!size)
					wcerr << "missing \"size\" attribute in \"event\" entry" << endl;
				// add event
				if (name && size)
				{
					int eventSize(atoi((const char *)size));
					if (eventSize > ASEBA_MAX_EVENT_ARG_SIZE)
					{
						wcerr << "Event " << name << " has a length " << eventSize << "larger than maximum" <<  ASEBA_MAX_EVENT_ARG_SIZE << endl;
						wasError = true;
						break;
					}
					else
					{
						commonDefinitions.events.push_back(NamedValue(UTF8ToWString((const char *)name), eventSize));
					}
				}
				// free attributes
				if (name)
					xmlFree(name);
				if (size)
					xmlFree(size);
			}
			// a global constant
			else if (xmlStrEqual(domNode->name, BAD_CAST("constant")))
			{
				// get attributes
				xmlChar *name(xmlGetProp(domNode, BAD_CAST("name")));
				if (!name)
					wcerr << "missing \"name\" attribute in \"constant\" entry" << endl;
				xmlChar *value(xmlGetProp(domNode, BAD_CAST("value"))); 
				if (!value)
					wcerr << "missing \"value\" attribute in \"constant\" entry" << endl;
				// add constant if attributes are valid
				if (name && value)
				{
					commonDefinitions.constants.push_back(NamedValue(UTF8ToWString((const char *)name), atoi((const char *)value)));
				}
				// free attributes
				if (name)
					xmlFree(name);
				if (value)
					xmlFree(value);
			}
			else
				wcerr << "Unknown XML node seen in .aesl file: " << domNode->name << endl;
		}
	}

	// release memory
	xmlFreeDoc(doc);

	// check if there was an error
	if (wasError)
	{
		wcerr << "There was an error while loading script " << UTF8ToWString(fileName) << endl;
		commonDefinitions.events.clear();
		commonDefinitions.constants.clear();
		allVariables.clear();
	}

	// check if there was some matching problem
	if (noNodeCount)
	{
		wcerr << noNodeCount << " scripts have no corresponding nodes in the current network and have not been loaded." << endl;
	}
}

bool ThymioInterface::compileAndSendCode(const wstring& source, unsigned nodeId, const string& nodeName)
{
	// compile code
	std::wistringstream is(source);
	Error error;
	BytecodeVector bytecode;
	unsigned allocatedVariablesCount;

	Compiler compiler;
	compiler.setTargetDescription(getDescription(nodeId));
	compiler.setCommonDefinitions(&commonDefinitions);
	bool result = compiler.compile(is, bytecode, allocatedVariablesCount, error);

	if (result)
	{
		// send bytecode
		sendBytecode(targetStream, nodeId, std::vector<uint16_t>(bytecode.begin(), bytecode.end()));
		// run node
		Run msg(nodeId);
		msg.serialize(targetStream);
		targetStream->flush();
		// retrieve user-defined variables for use in get/set
		allVariables[nodeName] = *compiler.getVariablesMap();
		return true;
	}
	else
	{
		wcerr << "compilation for node " << UTF8ToWString(nodeName) << " failed: " << error.toWString() << endl;
		return false;
	}
}

void ThymioInterface::stop(const std::string& nodeName)
{
	bool ok;
    const unsigned nodeId(getNodeId(UTF8ToWString(nodeName), 0, &ok));
	if (!ok)
	{
        wcerr << "invalid node name " << UTF8ToWString(nodeName) << endl;
		return;
	}

	// build stop message and send
	Stop stopMsg(nodeId);
	stopMsg.serialize(targetStream);
	targetStream->flush();
}

void ThymioInterface::run(const string& nodeName)
{
    bool ok;
    const unsigned nodeId(getNodeId(UTF8ToWString(nodeName), 0, &ok));
    if (!ok)
    {
        wcerr << "invalid node name " << UTF8ToWString(nodeName) << endl;
        return;
    }

    // build run message and send
    Run runMsg(nodeId);
    runMsg.serialize(targetStream);
    targetStream->flush();
}

bool ThymioInterface::getNodeAndVarPos(const string& nodeName, const string& variableName, unsigned& nodeId, unsigned& pos) const
{
	// make sure the node exists
	bool ok;
    wstring s = UTF8ToWString(nodeName);
	nodeId = getNodeId(UTF8ToWString(nodeName), 0, &ok);
    if (!ok)
	{
		wcerr << "invalid node name " << UTF8ToWString(nodeName) << endl;
		return false;
	}
	pos = unsigned(-1);

	// check whether variable is knwon from a compilation, if so, get position
	const NodeNameToVariablesMap::const_iterator allVarMapIt(allVariables.find(nodeName));
	if (allVarMapIt != allVariables.end())
	{
		const VariablesMap& varMap(allVarMapIt->second);
		const VariablesMap::const_iterator varIt(varMap.find(UTF8ToWString(variableName)));
		if (varIt != varMap.end())
			pos = varIt->second.first;
	}

	// if variable is not user-defined, check whether it is provided by this node
	if (pos == unsigned(-1))
	{
		bool ok;
		pos = getVariablePos(nodeId, UTF8ToWString(variableName), &ok);
        if (!ok)
		{
			wcerr << "variable " << UTF8ToWString(variableName) << " does not exists in node " << UTF8ToWString(nodeName);
			return false;
		}
	}
	return true;
}

bool ThymioInterface::setup(const string& nodeName){
    // clear existing data
    commonDefinitions.events.clear();
    commonDefinitions.constants.clear();
    allVariables.clear();

    commonDefinitions.events.push_back(NamedValue(UTF8ToWString("thymioevents"), 2));
    std::wstring code;
    bool ok;
    unsigned nodeId(getNodeId(Aseba::UTF8ToWString(nodeName), 0, &ok));
    if (ok){

        commonDefinitions.events.push_back(NamedValue(UTF8ToWString("ProxVLeds"), 2));
        //The whole code for both events should be compiled together
        commonDefinitions.events.push_back(NamedValue(UTF8ToWString("ProxHLeds"), 8));
        code = Aseba::UTF8ToWString("onevent ProxVLeds call leds.prox.v(event.args[0],event.args[1])\n onevent ProxHLeds call leds.prox.h(event.args[0],event.args[1],event.args[2],event.args[3],event.args[4],event.args[5],event.args[6],event.args[7])");
        if (compileAndSendCode(code, nodeId, nodeName))
            std::cout<<"Couln't send this command!";



    }
    return false;

}
int main()
{
    // initialize Dashel plugins

    const char* target = "ser:name=Thymio-II";

    // create the interface
    ThymioInterface* interface = new ThymioInterface(target);


    interface->listNodes();
    interface->wait();

//    interface->load("/home/sina/Desktop/aseba/examples/clients/cpp-api/ScriptDBusThymio.aesl");
    interface->setup("thymio-II");
    interface->wait();


    int j = 0;
    int k = 0;
    ThymioInterface::Values proximity_h;
    ThymioInterface::Values proximity_v;
    do{
        proximity_h = interface->getVariable("thymio-II","prox.horizontal");
        proximity_v = interface->getVariable("thymio-II","prox.ground.delta");

        std::printf("%i ) ",k);
        for (std::vector<short>::size_type i = 0; i!=proximity_h.size(); i++)
        {
            //std::cout << shell->j << ")" << shell->values[i] << " ";
            std::printf(" %f ",(double)proximity_h[i]);
        }
        std::printf("\n");

        std::printf("%i ) ",k++);
        for (std::vector<short>::size_type i = 0; i!=proximity_v.size(); i++)
        {
            //std::cout << shell->j << ")" << shell->values[i] << " ";
            std::printf("%f ",(double)proximity_v[i]);
        }
        std::printf("\n");

//        if(proximity_h[2]>2000)
//            interface->setVariable("thymio-II","motor.left.target",{25});
//        else
//            interface->setVariable("thymio-II","motor.left.target",{0});

        j++;
    }
    while(j<=10);

    interface->sendEventName("ProxHLeds",{32,32,32,32,32,32,32,32});
    interface->sendEventName("ProxVLeds",{32,32});

    interface->wait(1000);

    interface->sendEventName("ProxHLeds",{0,0,0,0,0,0,0,0});
    interface->sendEventName("ProxVLeds",{0,0});



    interface->setVariable("thymio-II","motor.left.target",{0});
    interface->setVariable("thymio-II","motor.right.target",{0});
    ThymioInterface::Values accelerometer;

    j = 0;
    k = 0;
    do{
        accelerometer = interface->getVariable("thymio-II","acc");
//        interface->setVariable("thymio-II","motor.left.target",{to_string(k++)});
//        interface->setVariable("thymio-II","motor.right.target",{to_string(k++)});

        std::cout<<j<< ") -x:" << (short)accelerometer[0] << " -y:" << (short)accelerometer[1] << " z:" << (short)accelerometer[2] <<endl;

        j++;
    }
    while(j<=100);

    interface->setVariable("thymio-II","motor.left.target",{0});
    interface->setVariable("thymio-II","motor.right.target",{0});

	return 0;
}
