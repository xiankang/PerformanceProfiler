#include "stdafx.h"
#include "PerformanceFuncSets.h"
#include <string>
#include "HttpClient.h"
#include <iostream>
#include "json/json.h"
#include "ConvertUtils.h"

using namespace std;

static string performHttp = "http://m.data.eastmoney.com/Nbjb/GetReport_yjyg?page=1&pagesize=10&order=jzrq&desc=-1&code=%06d&type=yjyg";

string getUrl(int code) {
	string url;
	char buffer[1000];
	sprintf(buffer, performHttp.c_str(), code);
	url = buffer;
	return url;
}

void IsInPerformanceForecast(int dataLen, float* pfOut, float* pfInA, float* pfInB, float* pfInC)
{
	//query
	string key = "业务变动幅度简介";
	int code = *pfInA;
	string url = getUrl(code);
	string response;
	HttpClient httpClient;
	httpClient.doGet(url, response);
	string decodedRes = UTF8_To_string(response);
	Json::Reader reader;
	Json::Value root;
	std::string performance;

	if (reader.parse(decodedRes, root)) {
		Json::Value result = root["result"];
		Json::Value RepotrList = result["RepotrList"];
		int i = 0;
		Json::Value newData = RepotrList[i];

		performance = newData[key].asString();
	}

	//从performance里面取最小值
	int firstIndex = performance.find_first_of("%");
	int lastIndex = performance.find_last_of("%");
	int secondNumIndex = firstIndex + 3;

	float minPerformance = atof(performance.substr(0, firstIndex).c_str());
	float maxPerformance = atof(performance.substr(secondNumIndex, lastIndex).c_str());
	for (int i = 0; i < dataLen; i++)
	{
		pfOut[i] = *pfInB <1 ? minPerformance : maxPerformance;
	}
}

void testPerformance(int dataLen, float* pfOut, float* pfInA, float* pfInB, float* pfInC) {
	for (int i = 0; i < dataLen; i++)
	{
		pfOut[i] = 30;
	}
}
//加载的函数
PluginPerformanceFuncInfo g_PerformanceFuncSets[] =
{
	{ 1, (pPluginPerformanceFunc)&IsInPerformanceForecast },
	{ 2, (pPluginPerformanceFunc)&testPerformance },
	{ 0, NULL },
};

//导出给PluginPerformanceFunc的注册函数
BOOL RegisterTdxFunc(PluginPerformanceFuncInfo** pFun)
{
	if (*pFun == NULL)
	{
		(*pFun) = g_PerformanceFuncSets;
		return TRUE;
	}
	return FALSE;
}