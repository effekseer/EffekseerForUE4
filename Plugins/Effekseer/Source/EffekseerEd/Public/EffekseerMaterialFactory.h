
#pragma once

#include <memory>
#include "CoreMinimal.h"
#include "Factories/Factory.h"

#if WITH_EDITOR
#include "Editor/UnrealEd/Public/EditorReimportHandler.h"
#endif

#include "EffekseerMaterial.h"
#include "EffekseerMaterialFactory.generated.h"


struct NativeEffekseerMaterialContext;

UCLASS()
class UEffekseerMaterialFactory : public UFactory, public FReimportHandler
{
	GENERATED_UCLASS_BODY()

	void LoadData(UMaterial* targetMaterial, std::shared_ptr<NativeEffekseerMaterialContext> native);

	virtual bool DoesSupportClass(UClass* Class) override;
	virtual UClass* ResolveSupportedClass() override;

	virtual UObject* FactoryCreateBinary(
		UClass* InClass,
		UObject* InParent,
		FName InName,
		EObjectFlags Flags,
		UObject* Context,
		const TCHAR* Type,
		const uint8*& Buffer,
		const uint8* BufferEnd,
		FFeedbackContext* Warn) override;

	virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;
	virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;
	virtual EReimportResult::Type Reimport(UObject* Obj) override;

};
