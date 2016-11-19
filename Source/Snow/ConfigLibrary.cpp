// Fill out your copyright notice in the Description page of Project Settings.

#include "Snow.h"
#include "ConfigLibrary.h"

UConfigLibrary::UConfigLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UConfigLibrary::ReadConfigStringValue(const FString FileNameWithPath, const FString VariableName, FString &value) {
	value = "";
	if (!GConfig) return;

	const TCHAR* path = *FileNameWithPath;
	const TCHAR* name = *VariableName;

	FString ValueReceived;
	GConfig->GetString(
		path,
		name,
		ValueReceived,
		GEngineIni
		);

	value = ValueReceived;
	return;
}

void UConfigLibrary::ReadConfigBoolValue(const FString FileNameWithPath, const FString VariableName, bool &value) {
	value = false;
	if (!GConfig) return;

	const TCHAR* path = *FileNameWithPath;
	const TCHAR* name = *VariableName;

	bool ValueReceived = false;
	GConfig->GetBool(
		path,
		name,
		ValueReceived,
		GEngineIni
		);

	value = ValueReceived;
	return;
}
void UConfigLibrary::WriteConfigBoolValue(const FString FileNameWithPath, const FString VariableName, bool value) {
	if (!GConfig) return;

	const TCHAR* path = *FileNameWithPath;
	const TCHAR* name = *VariableName;

	bool ValueReceived = false;
	GConfig->SetBool(
		path,
		name,
		value,
		GEngineIni
		);

	GConfig->Flush(false, GGameIni);
	return;
}

void UConfigLibrary::ReadConfigIntValue(const FString FileNameWithPath, const FString VariableName, int32 &value) {
	value = false;
	if (!GConfig) return;

	const TCHAR* path = *FileNameWithPath;
	const TCHAR* name = *VariableName;

	int32 ValueReceived = 0;
	GConfig->GetInt(
		path,
		name,
		ValueReceived,
		GEngineIni
		);

	value = ValueReceived;
	return;
}

void UConfigLibrary::ReadConfigFloatValue(const FString FileNameWithPath, const FString VariableName, float &value) {
	value = false;
	if (!GConfig) return;

	const TCHAR* path = *FileNameWithPath;
	const TCHAR* name = *VariableName;

	float ValueReceived = 0.0f;
	GConfig->GetFloat(
		path,
		name,
		ValueReceived,
		GEngineIni
		);

	value = ValueReceived;
	return;
}

