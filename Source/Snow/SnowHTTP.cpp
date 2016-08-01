#include "Snow.h"
#include "SnowHTTP.h"

USnowHTTP* USnowHTTP::m_pInstance = NULL;


USnowHTTP* USnowHTTP::Instance()
{
	if (!m_pInstance) {   // Only allow one instance of class to be generated.
		m_pInstance = NewObject<USnowHTTP>();
	}
	return m_pInstance;
}

void USnowHTTP::HttpCall(FString url, FString verb) {
	Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	//Request->OnProcessRequestComplete().BindUObject(this, &SnowHTTP::OnResponseReceived);
	Request->OnProcessRequestComplete().BindUObject(this, &USnowHTTP::OnResponseReceived);
	//This is the url on which to process the request
	/*Request->SetURL("http://192.168.1.112/");*/
	Request->SetURL(url);
	Request->SetVerb(verb);
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

/*Assigned function on successfull http call*/
void USnowHTTP::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		FString recievedMessage = JsonObject->GetStringField("message");

		//Output it to the engine
		UE_LOG(LogTemp, Warning, TEXT("Message: %s"), *recievedMessage);
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, recievedMessage);
	}
}

USnowHTTP::USnowHTTP() {
	Http = &FHttpModule::Get();
}
