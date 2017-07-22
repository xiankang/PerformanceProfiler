#ifndef __PERFORMANCE_FUNC_SETS
#define __PERFORMANCE_FUNC_SETS
#include "PluginPerformanceFunc.h"

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus
	__declspec(dllexport) BOOL RegisterTdxFunc(PluginPerformanceFuncInfo** pFun);
#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__PERFORMANCE_FUNC_SETS