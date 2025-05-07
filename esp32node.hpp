#ifndef _ESP32_NODE_HPP
#define _ESP32_NODE_HPP

#include "node.hpp"

class Esp32Node: public INode {
	public:
		Esp32Node();
		bool connectWifi(const char* ssid, const char*  pw) override;
		bool isConnectedToWifi() override;
		bool connectMesh() override;
		String httpGetRequest(const char* url) override;
    
};

#endif

