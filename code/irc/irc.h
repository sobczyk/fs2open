// IRC.h
// IRC Client header
// Derek Meek
// 2-14-2003

// ############## ATTENTION ##########
// Licensed under the Academic Free License version 2.0
// View License at http://www.opensource.org/licenses/afl-2.0.php
// ###################################

/*
 * $Logfile: /Freespace2/code/irc/irc.h $
 * $Revision: 1.1 $
 * $Date: 2004-03-10 19:11:40 $
 * $Author: Kazan $
 * *
 * $Log: not supported by cvs2svn $
 *
 *
 */



#if !defined(_IRC_H_)
#define _IRC_H_

#include "fs2open_pxo/TCP_Socket.h"

#include <string>
#include <vector>
#include <fstream.h>

class irc_user
{
	std::string user;
	std::string pass;
	std::string host;
	std::string ident;

	std::string modes;
};

class irc_channel
{
	public:
		std::string GetName() { return chan_name; }	
	private:
		std::string chan_name;
		std::string topic;
		std::vector<irc_user> channel_users;
		std::vector<std::string> channel_modes;
		std::vector<std::string> messages;

		int max_messages;

		// logging
		bool Log;
		std::vector<std::string> logfile;
		ofstream LogStream;
};




class irc_client
{
	public:
		irc_client() : bisConnected(false), current_channel(0) {}
		irc_client(std::string user, std::string pass, std::string server, int port) : bisConnected(false), current_channel(0)
				{ connect(user, pass, server, port); }
		~irc_client() { Disconnect(); }

		bool connect(std::string user, std::string pass, std::string server, int port);
		void Disconnect(std::string goodbye = "Bye!");
		bool isConnected() { return bisConnected; }

		void ParseForCommand(std::string UserInput);

		// IRC commands
		void Nick(std::string nick);
		void Pass(std::string pass);
		void User(std::string user, int mode, std::string realname);
		void Mode(std::string chan, std::string modes, std::string targets="");
		void Kick(std::string chan, std::string nick, std::string message);
		void Part(std::string chan, std::string message="");
		void Join(std::string chan);
		void PrivateMessage(std::string target, std::string message);
		void Notice(std::string target, std::string message);
		void Quit(std::string message="");
		void Oper(std::string user, std::string pass);

		// Get Commands
		std::vector<std::string> Maybe_GetRawLines();

	private:
		TCP_Socket mySocket;
		irc_user MyUser;
		bool bisConnected;

		std::vector<irc_channel> channels;
		int current_channel;

		void PutRaw(std::string command);
		std::vector<std::string> ExtractParams(std::string UserInput, int params);
		std::vector<std::string> BreakLines(std::string HostInput);
		
};



#endif