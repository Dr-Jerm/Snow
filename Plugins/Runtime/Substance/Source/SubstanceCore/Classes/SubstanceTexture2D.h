// Copyright 2016 Allegorithmic Inc. All rights reserved.
// File: SubstanceTexture2D.h

#pragma once
#include "SubstanceGraphInstance.h"
#include "SubstanceTexture2D.generated.h"

/** Forward Declare */
class USubstanceTexture2D;

namespace SubstanceAir
{
	class OutputInstance;
	class GraphInstance;
}

struct OutputInstanceData
{
	MS_ALIGN(16) TWeakObjectPtr<USubstanceTexture2D> Texture;
	MS_ALIGN(16) TWeakObjectPtr<USubstanceGraphInstance> ParentInstance;

	FGuid CacheGuid;
};

//Note:: These are the current set of channels that we support in UE4 and not all
//substance channel output types are listed here.
UENUM(BlueprintType)
enum ESubChannelType
{
	Diffuse,
	Ambient,
	BaseColor,
	Metallic,
	Roughness,
	Emissive,
	Normal,
	Mask,
	Opacity,
	Refraction,
	AmbientOcclusion,
	Glossiness,
	Height,
	Displacement,
	Reflection,
	Invalid
};

UCLASS(hideCategories = Object)
class SUBSTANCECORE_API USubstanceTexture2D : public UTexture2DDynamic
{
public:
	GENERATED_UCLASS_BODY()

	/** Id of OutpuInstance */
	uint32 mUid;

	/** Reference to the Output Instance */
	SubstanceAir::OutputInstance* OutputCopy;

	/** The custom data used for the OutputInstance */
	OutputInstanceData mUserData;

#if PLATFORM_PS4 || (SUBSTANCE_HAS_PS4_SDK && WITH_EDITOR)
	/** used for PS4 cooking */
	TIndirectArray<struct FTexture2DMipMap> PlatformMips;
#endif

	/** Graph that will update this texture */
	UPROPERTY(VisibleAnywhere, Category = "Substance")
	USubstanceGraphInstance* ParentInstance;

	/** The addressing mode to use for the X axis. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Texture, meta = (DisplayName = "X-axis Tiling Method"), AssetRegistrySearchable, AdvancedDisplay)
	TEnumAsByte<enum TextureAddress> AddressX;

	/** The addressing mode to use for the Y axis. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Texture, meta = (DisplayName = "Y-axis Tiling Method"), AssetRegistrySearchable, AdvancedDisplay)
	TEnumAsByte<enum TextureAddress> AddressY;

	/** Returns a list of all of the input identifiers */
	UFUNCTION(BlueprintCallable, Category = "Substance")
	ESubChannelType GetChannel();

	/** Whether or not this is a cook asset */
	UPROPERTY()
	bool bCooked;

	/** The texture data. */
	TIndirectArray<struct FTexture2DMipMap> Mips;

	/** Flag to determine which method we will use to link output instance*/
	bool bLinkLegacy;

	/** Sets the properties of the texture to expose to the end user */
	bool CanEditChange(const UProperty* InProperty) const;

	/** Used to link to the output instance */
	void LinkOutputInstance();

	/** Used to link to legacy format output instance */
	void LinkLegacyOutputInstance();

	/** Serializes the assets that were created and saved post framework refactor */
	void SerializeCurrent(FArchive& Ar);

	/** Serializes assets that were created before the framework refactor */
	void SerializeLegacy(FArchive& Ar);

	/** Cooks the textures tiled from the editor specifically for PS4 */
	void CookTextureForPS4(FArchive& Ar, int32 FirstMip);

	/** Cooks the texture normally */
	void CookTexture2D(FArchive& Ar, int32 FirstMip);

	// Begin UObject interface.
	virtual void Serialize(FArchive& Ar) override;
	virtual void BeginDestroy() override;
	virtual void PostLoad() override;
	virtual void PostDuplicate(bool bDuplicateForPIE) override;
	virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;
	// End UObject interface.

	// Begin UTexture interface.
	virtual FString GetDesc() override;
	virtual void UpdateResource() override;
	virtual FTextureResource* CreateResource() override;
	// End UTexture interface.
};
