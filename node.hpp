#ifndef _NODE_HPP
#define _NODE_HPP

#include <Arduino.h>

class INode {
	public:
		virtual bool connectWifi(const char* ssid, const char*  pw) = 0;
		virtual bool connectMesh() = 0;
		virtual bool isConnectedToWifi() = 0;
		virtual String httpGetRequest(const char* url) = 0;
};
#endif