#ifndef __PLUGIN_PERFORMANCE_FUNC
#define __PLUGIN_PERFORMANCE_FUNC
#pragma pack(push,1)

//函数(数据个数,输出,输入a,输入b,输入c)
typedef void(*pPluginPerformanceFunc)(int, float*, float*, float*, float*);

typedef struct tagPluginPerformanceFuncInfo
{
	unsigned short nFuncMark;//函数编号
	pPluginPerformanceFunc pCallFunc;//函数地址
}PluginPerformanceFuncInfo;

typedef BOOL(*pRegisterPluginFUNC)(PluginPerformanceFuncInfo**);

#pragma pack(pop)
#endif