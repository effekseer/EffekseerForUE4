
#pragma once

#include "Components/PrimitiveComponent.h"

#include "EffekseerEffect.h"

#include "EffekseerSystemComponent.generated.h"

class EffekseerUpdateData
{
public:
	TArray<void*>				PlayingEffects;
	TArray<FVector>				PlayingEffectPositions;

	TMap<UTexture2D*, UMaterialInstanceDynamic*> OpaqueDynamicMaterials;
	TMap<UTexture2D*, UMaterialInstanceDynamic*> TranslucentDynamicMaterials;
	TMap<UTexture2D*, UMaterialInstanceDynamic*> AdditiveDynamicMaterials;
	TMap<UTexture2D*, UMaterialInstanceDynamic*> SubtractiveDynamicMaterials;
	TMap<UTexture2D*, UMaterialInstanceDynamic*> ModulateDynamicMaterials;

	float	DeltaTime = 0;

	EffekseerUpdateData();
	virtual ~EffekseerUpdateData();
};

UCLASS(ClassGroup = (Effekseer), meta = (BlueprintSpawnableComponent))
class EFFEKSEER_API UEffekseerSystemComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

private:
	FPrimitiveSceneProxy*	sceneProxy = nullptr;
	EffekseerUpdateData*	currentUpdateData = nullptr;

public:
	UEffekseerSystemComponent();
	virtual ~UEffekseerSystemComponent();

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

	virtual UMaterialInterface* GetMaterial(int32 ElementIndex) const override;
	virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials) const override;
	virtual int32 GetNumMaterials() const override;
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	UMaterialInstanceConstant* OpaqueMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	UMaterialInstanceConstant* TranslucentMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	UMaterialInstanceConstant* AdditiveMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	UMaterialInstanceConstant* SubtractiveMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	UMaterialInstanceConstant* ModulateMaterial = nullptr;

	UPROPERTY(Transient)
	TMap<UTexture2D*, UMaterialInstanceDynamic*> OpaqueDynamicMaterials;

	UPROPERTY(Transient)
	TMap<UTexture2D*, UMaterialInstanceDynamic*> TranslucentDynamicMaterials;

	UPROPERTY(Transient)
	TMap<UTexture2D*, UMaterialInstanceDynamic*> AdditiveDynamicMaterials;

	UPROPERTY(Transient)
	TMap<UTexture2D*, UMaterialInstanceDynamic*> SubtractiveDynamicMaterials;

	UPROPERTY(Transient)
	TMap<UTexture2D*, UMaterialInstanceDynamic*> ModulateDynamicMaterials;

	UFUNCTION(BlueprintCallable, Category = "Control")
	void Play(UEffekseerEffect* effect, FVector position);
};
