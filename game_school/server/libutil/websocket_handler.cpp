#ifdef WIN32
	#ifndef _UNISTD_H  
	#define _UNISTD_H  
	#include <io.h>  
	#include <process.h>  
	#endif /* _UNISTD_H */  
#else
#include <unistd.h>
#endif

#include "websocket_handler.h"
#include "pw_types.h"

#ifdef _MSC_VER
    #include <windows.h>
    #pragma comment(lib, "wsock32.lib")
#else
	#include <arpa/inet.h>
#endif

Websocket_Handler::Websocket_Handler(int fd):
		buff_(),
		status_(WEBSOCKET_UNCONNECT),
		header_map_(),
		fd_(fd),
		request_(new Websocket_Request)
{
}

Websocket_Handler::Websocket_Handler(int fd, const char* data) :
		buff_(),
		status_(WEBSOCKET_UNCONNECT),
		header_map_(),
		fd_(fd),
		request_(new Websocket_Request)
{
	memcpy(buff_, data, strlen(data));
}

Websocket_Handler::~Websocket_Handler(){
}

int Websocket_Handler::process(){
	if(status_ == WEBSOCKET_UNCONNECT){
		return handshark();
	}
	request_->fetch_websocket_info(buff_);
	request_->print();
	memset(buff_, 0, sizeof(buff_));
	return 0;
}

int Websocket_Handler::handshark(){
	char request[1024] = {};
	status_ = WEBSOCKET_HANDSHARKED;
	fetch_http_info();
	parse_str(request);
	memset(buff_, 0, sizeof(buff_));
	return send_data(request);
}


void Websocket_Handler::InitMessage(const char* data)
{
	memcpy(buff_, data, strlen(data));
}

int Websocket_Handler::wsDecodeFrame(std::string inFrame, std::string &outMessage)
{
	int ret = WS_OPENING_FRAME;
	const char *frameData = inFrame.c_str();
	const int frameLength = inFrame.size();
	if (frameLength < 2)
	{
		ret = WS_ERROR_FRAME;
	}

	// 检查扩展位并忽略
	if ((frameData[0] & 0x70) != 0x0)
	{
		ret = WS_ERROR_FRAME;
	}

	// fin位: 为1表示已接收完整报文, 为0表示继续监听后续报文
	ret = (frameData[0] & 0x80);
	if ((frameData[0] & 0x80) != 0x80)
	{
		ret = WS_ERROR_FRAME;
	}

	// mask位, 为1表示数据被加密
	if ((frameData[1] & 0x80) != 0x80)
	{
		ret = WS_ERROR_FRAME;
	}

	// 操作码
	uint16_t payloadLength = 0;
	uint8_t payloadFieldExtraBytes = 0;
	uint8_t opcode = static_cast<uint8_t>(frameData[0] & 0x0f);
	if (opcode == WS_TEXT_FRAME)
	{
		// 处理utf-8编码的文本帧
		payloadLength = static_cast<uint16_t>(frameData[1] & 0x7f);
		if (payloadLength == 0x7e)
		{
			uint16_t payloadLength16b = 0;
			payloadFieldExtraBytes = 2;
			memcpy(&payloadLength16b, &frameData[2], payloadFieldExtraBytes);
			payloadLength = ntohs(payloadLength16b);
		}
		else if (payloadLength == 0x7f)
		{
			// 数据过长,暂不支持
			ret = WS_ERROR_FRAME;
		}
	}
	else if (opcode == WS_BINARY_FRAME)
	{
		uint32 headerLen = 2;
		payloadLength = static_cast<uint16_t>(frameData[1] & 0x7f);
		byte* pos = (byte*)frameData[0];
		if (payloadLength < 126)
		{
			// 用7位bit表示长度
			// 无操作
		}
		else if (payloadLength == 126)
		{
			// 用16位bit表示长度
			if (frameLength < 4) return WS_ERROR_FRAME; // 数据不足
			

			payloadLength = *(uint16*)pos;
			pos += 2;
			payloadLength += 2;
			payloadLength = (uint16)payloadLength;
		}
		else if (payloadLength == 127)
		{
			// 用64位bit表示长度
			if (frameLength < 10) return WS_ERROR_FRAME; // 数据不足
			payloadLength = (uint32)*(uint64*)pos; // 最大值不会超过4字节
			pos += 8;
			headerLen += 8;
			payloadLength = (uint32)(uint64)payloadLength;
		}
	}
	else if (opcode == WS_PING_FRAME || opcode == WS_PONG_FRAME)
	{
		// 二进制/ping/pong帧暂不处理
		
	}
	else if (opcode == WS_CLOSING_FRAME)
	{
		ret = WS_CLOSING_FRAME;
	}
	else
	{
		ret = WS_ERROR_FRAME;
	}

	// 数据解码
	if ((ret != WS_ERROR_FRAME) && (payloadLength > 0))
	{
		// header: 2字节, masking key: 4字节
		const char *maskingKey = &frameData[2 + payloadFieldExtraBytes];
		char *payloadData = new char[payloadLength + 1];
		memset(payloadData, 0, payloadLength + 1);
		memcpy(payloadData, &frameData[2 + payloadFieldExtraBytes + 4], payloadLength);
		for (int i = 0; i < payloadLength; i++)
		{
			payloadData[i] = payloadData[i] ^ maskingKey[i % 4];
		}

		outMessage = payloadData;
		delete[] payloadData;
	}

	return ret;

}

void Websocket_Handler::parse_str(char *request){
	strcat(request, "HTTP/1.1 101 Switching Protocols\r\n");
	strcat(request, "Connection: upgrade\r\n");
	strcat(request, "Sec-WebSocket-Accept: ");
	std::string server_key = header_map_["Sec-WebSocket-Key"];
	server_key += MAGIC_KEY;

	SHA1 sha;
	unsigned int message_digest[5];
	sha.Reset();
	sha << server_key.c_str();

	sha.Result(message_digest);
	for (int i = 0; i < 5; i++) {
		message_digest[i] = htonl(message_digest[i]);
	}
	server_key = base64_encode(reinterpret_cast<const unsigned char*>(message_digest),20);
	server_key += "\r\n";
	strcat(request, server_key.c_str());
	strcat(request, "Upgrade: websocket\r\n\r\n");
}

int Websocket_Handler::fetch_http_info(){
	std::istringstream s(buff_);
	std::string request;

	std::getline(s, request);
	if (request[request.size()-1] == '\r') {
		request.erase(request.end()-1);
	} else {
		return -1;
	}

	std::string header;
	std::string::size_type end;

	while (std::getline(s, header) && header != "\r") {
		if (header[header.size()-1] != '\r') {
			continue; //end
		} else {
			header.erase(header.end()-1);	//remove last char
		}

		end = header.find(": ",0);
		if (end != std::string::npos) {
			std::string key = header.substr(0,end);
			std::string value = header.substr(end+2);
			header_map_[key] = value;
		}
	}

	return 0;
}

int Websocket_Handler::send_data(char *buff){
	//return write(fd_, buff, strlen(buff));
	 send(fd_, buff, strlen(buff), 0);
	 int err = WSAGetLastError();
	 return 0;
}
