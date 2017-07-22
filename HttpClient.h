#pragma once

#include <string>
#include "curl/curl.h"

using namespace std;

class HttpClient
{
public:
	HttpClient();
	virtual ~HttpClient();
	bool doGet(string& url, string& response);
protected:
private:
	CURL* _curl;
};
