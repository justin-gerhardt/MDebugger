/*
 * CmdInterface.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: mojtababagherzadeh
 */

#include "CmdInterface.h"
#include <string>
#include <iostream>
#include <algorithm>

namespace mdebugger {
/// these following three helper trim functions copied form
//stackoverflow http://stackoverflow.com/questions/25829143/c-trim-whitespace-from-a-string

std::string & ltrim(std::string & str)
{
  auto it2 =  std::find_if( str.begin() , str.end() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
  str.erase(str.begin() , it2);
  return str;
}

std::string & rtrim(std::string & str)
{
  auto it1 =  std::find_if( str.rbegin() , str.rend() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
  str.erase( it1.base() , str.end() );
  return str;
}
std::string & trim(std::string & str)
{
   return ltrim(rtrim(str));
}
////////
const std::vector<CMDDesc> CmdInterface::cmdDescList =
	{
			{"help","h",{},"Show the commands and their options"},
			{"breakpoint","b",{{"-c","capsule","M"},{"-t","Transition","M"},
					{"-b|-e","","M"},{"-r","","O"}},"Set/remove breakpoint at beginning/end of a transition"},
			//{"breakpoint","b",{{"-c","capsuleName","M"},{"-t","Transition's name","M"},{"-e","","O"},{"-i","traceNo","O"}},"Set breakpoint at end of a transition"},
			{"breakpoint","b",{{"-c","capsule","M"},{"-s","State","M"},
					{"-b|-e","","M"},{"-en|-ex","","M"},{"-r","","O"}},"Set/remove breakpoint at beginning/end of state entry/exit"},
			//{"breakpoint","b",{{"-c","capsuleName","M"},{"-s","State's name","M"},{"-e","","O"},{"-entry","","O"},{"-exit","","O"},{"-i","traceNo","O"}},"Set breakpoint at end of  state entry/exit"},
			//{"breakpoint","b",{{"-c","capsuleName","M"},{"-t","Transition's name","M"},{"-b","","O"},{"-r","","O"},{"-i","traceNo","O"}},"Remove breakpoint at beginning of a transition"},
			//{"breakpoint","b",{{"-c","capsuleName","M"},{"-t","Transition's name","M"},{"-e","","O"},{"-r","","O"},{"-i","traceNo","O"}},"Remove breakpoint at end of a transition"},
			//{"breakpoint","b",{{"-c","capsuleName","M"},{"-s","State's name","M"},{"-b","","O"},{"-r","","O"},{"-entry","","O"},{"-exit","","O"},{"-i","traceNo","O"}},"Remove breakpoint at beginning of a entry/exit"},
			//{"breakpoint","b",{{"-c","capsuleName","M"},{"-s","State's name","M"},{"-e","","O"},{"-r","","O"},{"-entry","","O"},{"-exit","","O"},{"-i","traceNo","O"}},"Remove breakpoint at end of a state entry/exit"},
			{"next","n",{{"-c","capsule","M"}},"Execute until next step"},
			{"continue","c",{{"-c","capsule","M"}},"Continue execution until next breakpoint"},
			{"run","r",{{"-c","capsule","M"}},"Run the capsule without interrupt"},
			{"modify","m",{{"-c","capsule","M"},{"-n","variable","M"},{"-v","value","M"}},"Modify a attribute of capsule"},
			{"watch","w",{{"-c","capsule","M"},{"-n","variable","O"}},"View the capsule's attributes"},
			{"backtrace","bt",{{"-c","capsule","M"},{"-n","count","M"},{"-e","","O"}},"View  last n events of capsule's execution"},
			{"list","l",{{"-c","capsule","O"},{"-b","","O"}},"List running capsules and their current state"},
			//{"list","l",{},"List capsule's configuration including breakpoints and etc"},
			//{"list","l",{{"-c","capsule","M"},{"-b","","O"}},"List exiting breakpoint"},
			{"seq","sq",{{"-c","capsule","M"},{"-n","count","O"}},"generate sequence diagram for last n events."},
			{"save","s",{{"-c","capsule","M"},{"-f","filePath","M"}},"Save existing events to a file specified by filePath"},
			{"connect","con",{{"-h","host","M"},{"-p","port","M"}},"Connect to eclipse debugger"},
			{"exit","q",{},"Exit the MDebugger"},
			{"restart","r",{},"Restart the Debugging session"},

	};
////////
const std::vector<CMDDesc> CmdInterface::extCmdDescList =
	{
			{"help","h",{},"Show the commands and their options"},
			{"breakpoint","b",{{"-c","capsuleName","M"},{"-t","Transition's name","M"},{"-b","","O"},{"-i","traceNo","O"}},"Set breakpoint at beginning of a transition"},
			{"breakpoint","b",{{"-c","capsuleName","M"},{"-t","Transition's name","M"},{"-e","","O"},{"-i","traceNo","O"}},"Set breakpoint at end of a transition"},
			{"breakpoint","b",{{"-c","capsuleName","M"},{"-s","State's name","M"},{"-b","","O"},{"-entry","","O"},{"-exit","","O"},{"-i","traceNo","O"}},"Set breakpoint at beginning of state entry/exit"},
			{"breakpoint","b",{{"-c","capsuleName","M"},{"-s","State's name","M"},{"-e","","O"},{"-entry","","O"},{"-exit","","O"},{"-i","traceNo","O"}},"Set breakpoint at end of  state entry/exit"},
			{"breakpoint","b",{{"-c","capsuleName","M"},{"-t","Transition's name","M"},{"-b","","O"},{"-r","","O"},{"-i","traceNo","O"}},"Remove breakpoint at beginning of a transition"},
			{"breakpoint","b",{{"-c","capsuleName","M"},{"-t","Transition's name","M"},{"-e","","O"},{"-r","","O"},{"-i","traceNo","O"}},"Remove breakpoint at end of a transition"},
			{"breakpoint","b",{{"-c","capsuleName","M"},{"-s","State's name","M"},{"-b","","O"},{"-r","","O"},{"-entry","","O"},{"-exit","","O"},{"-i","traceNo","O"}},"Remove breakpoint at beginning of a entry/exit"},
			{"breakpoint","b",{{"-c","capsuleName","M"},{"-s","State's name","M"},{"-e","","O"},{"-r","","O"},{"-entry","","O"},{"-exit","","O"},{"-i","traceNo","O"}},"Remove breakpoint at end of a state entry/exit"},
			{"next","n",{{"-c","capsuleName","M"},{"-i","traceNo","O"}},"Execute until next step"},
			{"continue","c",{{"-c","capsuleName","M"},{"-i","traceNo","O"}},"Continue execution until next breakpoint"},
			{"run","r",{{"-c","capsuleName","M"},{"-i","traceNo","O"}},"Run capsule without interrupt"},
			{"modify","m",{{"-c","capsuleName","M"},{"-n","name","M"},{"-v","value","M"},{"-i","traceNo","O"}},"Modify a attribute of capsule"},
			{"view","v",{{"-c","capsuleName","M"},{"-v","","O"},{"-i","traceNo","O"}},"View the capsule's attributes"},
			{"view","v",{{"-c","capsuleName","M"},{"-n","count","M"},{"-e","","O"},{"-i","traceNo","O"}},"View n last action of capsule's action chain"},
			{"list","l",{{"-i","traceNo","O"}},"List running capsules and their current state"},
			{"list","l",{{"-c","capsuleName","M"},{"-i","traceNo","O"}},"List capsule's configuration including breakpoints and etc"},
			{"list","l",{{"-c","capsuleName","M"},{"-b","","O"},{"-i","traceNo","O"}},"List exiting breakpoint"},
			{"seq","sq",{{"-c","capsuleName","M"},{"-n","count","O"}},"generate sequence diagram for last n events."},
			{"save","s",{{"-c","capsuleName","M"},{"-f","filePath","O"}},"Save existing events to a file specified by filePath"},
			{"connect","con",{{"-h","host","M"},{"-p","port","M"},{"-i","traceNo","O"}},"Connect to eclipse debugger"},
			{"exit","q",{},"Exit the MDebugger"},
			{"restart","r",{},"Restart the Debugging session"},

	};
/*const CMDDesc CmdInterface::commandDesc=
	{
			{{"help","h"},{"Show the commands and their options"}},
			{{"breakpoint","b"},{"-c","capsuleName","-t","name","Set breakpoint at start of a transition"}},
			{{"breakpoint","b"},{"-c","capsuleName","-t","-e","name","Set breakpoint at end of a transition"}},
			{{"next","n"},{"-c","capsuleName","Move execution one step"}},
			{{"continue","c"},{"-c","capsuleName","Continue execution until next breakpoint"}},
			{{"modify","m"},{"-c","capsuleName","-n","name","-v","value","Modify a capsule's attribute"}},
			{{"view","v"},{"-c","capsuleName","-v","View the capsule's attributes "}},
			{{"view","v"},{"-c","capsuleName","-e","-n","count","View last  n items of action chains"}},
			{{"list","l"},{"List running capsules and their current state"}},
			{{"list","l"},{"-c","capsuleName","List capsule's configuration including breakpoints and etc"}},
			{{"list","l"},{"-c","capsuleName","-b","List exiting breakpoint"}},
			{{"save","s"},{"-c","capsuleName","Save all capsule's actions chain in a file"}}
	};
const CMDDesc CmdInterface::commandDesc=
	{
			{{"cmdName","help"},{"cmdLetter","h"},{"help","Show the commands and their options"}},
			{{"cmdName","breakpoint"},{"cmdLetter","b"},{"-c","CapsuleName"},{"-t","name"},{"-s",""},{"help","Set breakpoint at start of a transition"}}
	};*/

CmdInterface::CmdInterface() {
	// TODO Auto-generated constructor stub

}

CmdInterface::~CmdInterface() {
	// TODO Auto-generated destructor stub
}

void CmdInterface::showHelp() {
	std::cout<<"Available Commands\n";
	for (int i=0;i<this->cmdDescList.size();i++){
		std::cout<<std::setw(14)<<std::left<<cmdDescList[i].commandName+"|"+cmdDescList[i].commandL;
		std::string options;
		if (cmdDescList[i].commandOptions.size()>=1)
			for (int j=0;j<cmdDescList[i].commandOptions.size();j++)
				if (cmdDescList[i].commandOptions[j][2]=="M")
					options.append(" "+cmdDescList[i].commandOptions[j][0]+" "+ cmdDescList[i].commandOptions[j][1]);
				else
					options.append(" ["+cmdDescList[i].commandOptions[j][0]+" "+ cmdDescList[i].commandOptions[j][1]+"]");
		std::cout<<std::setw(33)<<std::left<<options;
		std::cout<<std::endl;
		//std::cout<<"("<<cmdDescList[i].commandHelp<<std::endl;
	}
}

void CmdInterface::getCommand() {
	showPrompt();
	std::getline(std::cin, this->commandStr);

}

void CmdInterface::tokenizeCommand() {
	this->cmdTokens.clear();
	if (this->commandStr.length()>0){
		std::string tempS="";
		bool newVar=false;
		for (int i=0;i< this->commandStr.length();i++){
			if ((this->commandStr[i]==' ' || this->commandStr[i]=='\n') && newVar){
				newVar=false;
				cmdTokens.push_back(trim(tempS));
				tempS="";
			}
			else if (this->commandStr[i]!=' '){
				tempS=tempS+(commandStr[i]);
				newVar=true;
			}
		}
		if (newVar)
			cmdTokens.push_back(trim(tempS));
	}
	//std::cout<<cmdTokens.size()<<"\n";
	//for (int i=0;i<cmdTokens.size();i++)
	//	std::cout<<cmdTokens[i]<<"\n";
}

const std::string& CmdInterface::getCommandStr() const {
	return commandStr;
}

void CmdInterface::setCommandStr(const std::string& commandStr) {
	this->commandStr = commandStr;
}

mdebugger::mdebuggerCommand CmdInterface::stringToUserCommad(std::string commandName) {
	std::vector<std::string> commands={"breakpoint","continue","help","list","modify","next","save","view","run","seq","connect","exit","restart","backtrace","watch"};
	std::vector<std::string> commandsL={"b","c","h","l","m","n","s","v","r","sq","con","s","r","bt","w"};
	for (int i=0;i<commands.size();i++)
		if (commands[i]==commandName || commandsL[i]==commandName )
			return (mdebugger::mdebuggerCommand)i;

	return UNKOWNCOMMAND;
}

void CmdInterface::showPrompt() {
	std::cout<<"\n"<<"mdebugger#";
}


bool CmdInterface::parseCommand() {
	if (cmdTokens.size()<=0)
		return false;
	mdebugger::mdebuggerCommand cmdID;
	parsedCMD.cmdID=UNKOWNCOMMAND;
	parsedCMD.commandOptions.clear();
	cmdID=this->stringToUserCommad(cmdTokens[0]);
	int cmdIndex=-1;
	for (int i=0;i<cmdDescList.size();i++)
		if (cmdDescList[i].commandL==cmdTokens[0] || cmdDescList[i].commandName==cmdTokens[0]){
			cmdIndex=i;
			break;
	}
	if (cmdIndex==-1)
		return false;
	this->parsedCMD.cmdID=cmdID;
	bool parsError=false;
	for (int i=1;i<cmdTokens.size();i++)
		if (cmdTokens[i][0]=='-'){
			parsError=true;
			for (int z=0;z<cmdDescList.size();z++){
				if (cmdDescList[z].commandL==cmdTokens[0] || cmdDescList[z].commandName==cmdTokens[0])
					for (int j=0;j<cmdDescList[z].commandOptions.size();j++)
						if (cmdDescList[z].commandOptions[j][0]==cmdTokens[i] ||
								cmdDescList[z].commandOptions[j][0].find(cmdTokens[i]+"|")!=std::string::npos||
								cmdDescList[z].commandOptions[j][0].find("|"+cmdTokens[i])!=std::string::npos){ /// check multiple command options here too
							parsError=false;
							if (cmdDescList[z].commandOptions[j][1].length()>=1 && i+1<cmdTokens.size())
								this->parsedCMD.commandOptions[cmdTokens[i]]=cmdTokens[i+1];
							else
								this->parsedCMD.commandOptions[cmdTokens[i]]="SET";
							break;

						}
				if (parsError==false)
					break;
			}
			if (parsError)
				return false;
	}

	return true;
}


bool CmdInterface::parseExtCommand() {
	if (cmdTokens.size()<=0)
		return false;
	mdebugger::mdebuggerCommand cmdID;
	parsedCMD.cmdID=UNKOWNCOMMAND;
	parsedCMD.commandOptions.clear();
	cmdID=this->stringToUserCommad(cmdTokens[0]);
	int cmdIndex=-1;
	for (int i=0;i<extCmdDescList.size();i++)
		if (extCmdDescList[i].commandL==cmdTokens[0] || extCmdDescList[i].commandName==cmdTokens[0]){
			cmdIndex=i;
			break;
	}
	if (cmdIndex==-1)
		return false;
	this->parsedCMD.cmdID=cmdID;
	bool parsError=false;
	for (int i=1;i<cmdTokens.size();i++)
		if (cmdTokens[i][0]=='-'){
			parsError=true;
			for (int z=0;z<extCmdDescList.size();z++){
				if (extCmdDescList[z].commandL==cmdTokens[0] || extCmdDescList[z].commandName==cmdTokens[0])
					for (int j=0;j<extCmdDescList[z].commandOptions.size();j++)
						if (extCmdDescList[z].commandOptions[j][0]==cmdTokens[i] ||
								extCmdDescList[z].commandOptions[j][0].find(cmdTokens[i]+"|")!=std::string::npos||
								extCmdDescList[z].commandOptions[j][0].find("|"+cmdTokens[i])!=std::string::npos){ /// check multiple command options here too
							parsError=false;
							if (extCmdDescList[z].commandOptions[j][1].length()>=1 && i+1<cmdTokens.size())
								this->parsedCMD.commandOptions[cmdTokens[i]]=cmdTokens[i+1];
							else
								this->parsedCMD.commandOptions[cmdTokens[i]]="SET";
							break;

						}
				if (parsError==false)
					break;
			}
			if (parsError)
				return false;
	}

	return true;
}



void CmdInterface::prettyPrint(std::string text, int length, char fillChar) {
	std::cout<<std::left<<std::setw(length)<<std::setfill(fillChar);
	std::cout<<text<<" ";


}

std::vector<std::string> CmdInterface::tokenizeString(std::string str, char seperator) {
	std::vector<std::string> tokens;
	if (str.length()>0){
		std::string tempS="";
		bool newVar=false;
		for (int i=0;i< str.length();i++){
			if ((str[i]==seperator) && newVar){
				newVar=false;
				tokens.push_back(trim(tempS));
				tempS="";
			}
			else {
				tempS=tempS+(str[i]);
				newVar=true;
			}
		}
		if (newVar)
			tokens.push_back((tempS));
	}
	return tokens;
}

void CmdInterface::prettyPrintVariable(std::string varData) {
	std::vector<std::string> tokens=this->tokenizeString(varData, ',');
	if (tokens.size()==3){
		this->prettyPrint(tokens.at(0), 30, ' ');
		this->prettyPrint(tokens.at(1), 10, ' ');
		this->prettyPrint(tokens.at(2), 30, ' ');
	}
	else
		this->prettyPrint("Error: Variable Data is not valid", 30, ' ');
	std::cout<<std::endl;

}

void CmdInterface::prettyPrintTime(long seconds, long nanosecond) {
	char t[23];
	strftime(t, 23, "%H:%M:%S.",localtime(&seconds));
	std::string output(t);
	std::string nano = std::to_string(nanosecond);
	output.append(nano.substr(0,6));
	this->prettyPrint(output, 17, ' ');
}

} /* namespace mdebugger */

const mdebugger::ParsedCMD& mdebugger::CmdInterface::getParsedCmd() const {
	return parsedCMD;
}

void mdebugger::CmdInterface::setParsedCmd(const ParsedCMD& parsedCmd) {
	parsedCMD = parsedCmd;
}
