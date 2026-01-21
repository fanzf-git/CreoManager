#include "pch.h"
#include "OdaInitilize.h"

OdaInitilize::McOdaSystemServices()
{
    static const char* ActInfo[] = {
  #include "OdActivationInfo"
    };
    odActivate(ActInfo[0], ActInfo[1]);
}

OdaInitilize::~McOdaSystemServices()
{
    odCleanUpStaticData();
}
