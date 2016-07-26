#pragma once

#include "Runtime/Online/HTTP/Public/Http.h"
#include "SnowHTTP.generated.h"

DECLARE_DELEGATE_TwoParams(HttpDelegate, FString, FString)

UCLASS()
class SNOW_API USnowHTTP : public UObject {

	GENERATED_BODY()

public:
	
	static USnowHTTP* Instance();
	/* The actuall HTTP call */
	void HttpCall(FString url, FString verb);

	/*Assign this function to call when the GET request processes sucessfully*/
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

private:
	USnowHTTP();

	static USnowHTTP* m_pInstance;

	FHttpModule* Http;
};