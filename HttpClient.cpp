
#include "HttpClient.h"
#include <vector>
#include <stdio.h>
#include "ConvertUtils.h"

typedef size_t(*write_callback)(char *data, size_t size, size_t nmemb, std::string *writeData);

// Callback function used by libcurl for collect response data
static size_t WriteData(char *data, size_t size, size_t nmemb, std::string *writeData)
{
	if (writeData == nullptr)
		return 0;
	writeData->append(data, size*nmemb);
	return size*nmemb;
}

HttpClient::HttpClient() {
	curl_global_init(CURL_GLOBAL_ALL);
	_curl = curl_easy_init();
}

HttpClient::~HttpClient() {
	if (_curl)
		curl_easy_cleanup(_curl);
	curl_global_cleanup();
}

bool HttpClient::doGet(string& url, string& response) {

	CURLcode res;
	if (_curl == nullptr)
		return false;
	res = curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
	if (CURLE_OK != res)
		return false;
	res = curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, true);
	if (CURLE_OK != res)
		return false;
	//struct curl_slist * list = nullptr;
	//list = curl_slist_append(list, "Content-Type:application/json");
	//list = curl_slist_append(list, "");
	//res = curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, list);
	//if (CURLE_OK != res)
	//	return false;
#ifdef _DEBUG
	res = curl_easy_setopt(_curl, CURLOPT_VERBOSE, 1);
	if (CURLE_OK != res)
		return false;
#endif
	//res = curl_easy_setopt(_curl, CURLOPT_HEADER, 1);
	//if (CURLE_OK != res)
	//	return false;
	curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteData);
	if (CURLE_OK != res)
		return false;
	curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &response);
	if (CURLE_OK != res)
		return false;
	res = curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1);
	if (CURLE_OK != res)
		return false;
	//res = curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, 5);
	//if (CURLE_OK != res)
	//	return false;
	res = curl_easy_perform(_curl);
	if (CURLE_OK != res)
		return false;

	return true;
}