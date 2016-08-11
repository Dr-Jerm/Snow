#pragma once

#include "Runtime/Online/HTTP/Public/Http.h"
#include "SnowLogger.generated.h"

UCLASS()
class SNOW_API USnowLogger : public UObject
{
	GENERATED_BODY()

public:

	static USnowLogger* Instance();

	void SendLog(FString message);


private:

	USnowLogger();
	//~USnowLogger();

	static USnowLogger* m_pInstance;

	/*Assign this function to call when the GET request processes sucessfully*/
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};

