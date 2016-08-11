#include "Snow.h"
#include "SnowLogger.h"

//#include "Runtime/Sockets/Public/SocketSubsystem.h"
//#include "Runtime/Networking/Public/Interfaces/IPv4/IPv4Address.h"


USnowLogger* USnowLogger::m_pInstance = NULL;


USnowLogger* USnowLogger::Instance()
{
	if (!m_pInstance) {   // Only allow one instance of class to be generated.
		m_pInstance = NewObject<USnowLogger>();
	}
	return m_pInstance;
}


void USnowLogger::SendLog(FString message) {
	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	//Request->OnProcessRequestComplete().BindUObject(this, &SnowHTTP::OnResponseReceived);
	Request->OnProcessRequestComplete().BindUObject(this, &USnowLogger::OnResponseReceived);
	//This is the url on which to process the request
	/*Request->SetURL("http://192.168.1.112/");*/
	Request->SetURL("http://192.168.1.112:5000");
	Request->SetVerb("POST");
	Request->SetContentAsString(message);
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}



USnowLogger::USnowLogger()
{
	//FSocket* Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	//FString address = TEXT("192.168.1.112");
	//int32 port = 5000;
	//FIPv4Address ip;
	//FIPv4Address::Parse(address, ip);


	//TSharedRef addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	//addr->SetIp(ip.GetValue());
	//addr->SetPort(port);

	//bool connected = Socket->Connect(*addr);


}

/*Assigned function on successfull http call*/
void USnowLogger::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

}


//USnowLogger::~USnowLogger()
//{
//}
