#ifndef __WEBSOCKET_HANDLER__
#define __WEBSOCKET_HANDLER__

//#include <arpa/inet.h>
#include <iostream>
#include <map>
#include <sstream>
#include "base64.h"
#include "sha1.h"
//#include "debug_log.h"
#include "websocket_request.h"

#define MAGIC_KEY "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"

enum WEBSOCKET_STATUS {
	WEBSOCKET_UNCONNECT = 0,
	WEBSOCKET_HANDSHARKED = 1,
};

enum WS_Status
{
	WS_STATUS_CONNECT = 0,
	WS_STATUS_UNCONNECT = 1,
};

enum WS_FrameType
{
	WS_EMPTY_FRAME = 0xF0,
	WS_ERROR_FRAME = 0xF1,
	WS_TEXT_FRAME = 0x01,
	WS_BINARY_FRAME = 0x02,
	WS_PING_FRAME = 0x09,
	WS_PONG_FRAME = 0x0A,
	WS_OPENING_FRAME = 0xF3,
	WS_CLOSING_FRAME = 0x08
};


typedef std::map<std::string, std::string> HEADER_MAP;

class Websocket_Handler{
public:
	Websocket_Handler(int fd);
	Websocket_Handler(int fd, const char* data);
	~Websocket_Handler();
	int process();
	inline char *getbuff();
	const HEADER_MAP GetMessage() { return header_map_; }
	int fetch_http_info();
	int handshark();
	void InitMessage(const char* data);
	int wsDecodeFrame(std::string inFrame, std::string &outMessage);
private:
	
	void parse_str(char *request);
	
	int send_data(char *buff);
	void process_shake_hand(int sock, char* http_str);
private:
	char buff_[2048000];
	WEBSOCKET_STATUS status_;
	HEADER_MAP header_map_;
	int fd_;
	Websocket_Request *request_;
};

inline char *Websocket_Handler::getbuff(){
	return buff_;
}

#endif
