// Copyright 2016 Gamemakin LLC. All Rights Reserved.

#include "LinterPrivatePCH.h"
#include "LinterSettings.h" 
#include "LevelSequence.h" // @PlasticWax #PlasticWax - Uncommented this line and added a Public Module to Plugin Build Rules
#include "LevelSequenceObject.h"
#include "AIController.h"
#include "MediaTexture.h"
#include "MediaPlayer.h"
#include "MediaSoundWave.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BTService.h"
#include "WidgetBlueprint.h"
#include "UnrealEd.h"
#include "Animation/AimOffsetBlendSpace.h"
#include "Animation/AimOffsetBlendSpace1D.h"
#include "Animation/AnimComposite.h"
#include "Animation/Rig.h"
#include "VectorField/VectorField.h"
#include "VectorField/VectorFieldAnimated.h"
#include "VectorField/VectorFieldStatic.h"
#include "Slate/SlateBrushAsset.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "Engine/DestructibleMesh.h"
#include "GameFramework/GameMode.h" // @PlasticWax #PlasticWax - Added this header
#include "Runtime/Engine/Classes/Engine/GameInstance.h" // @PlasticWax #PlasticWax - Added this header
#include "Paper2DModule.h" // @PlasticWax #PlasticWax - Added this header
#include "PaperSprite.h" // @PlasticWax #PlasticWax - Added this header
#include "PaperFlipBook.h" // @PlasticWax #PlasticWax - Added this header
#include "PaperTileMap.h" // @PlasticWax #PlasticWax - Added this header
#include "PaperTileSet.h" // @PlasticWax #PlasticWax- Added this header

ULinterSettings::ULinterSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bDoAssetNamingConventionChecks(true)
	, bDoFolderNameChecks(true)
	, bDoFolderNamePascalCaseCheck(true)
	, bDoFolderNameSpaceCheck(true)
	, bDoFolderNameUnicodeCheck(true)
	, bUseTopLevelFolderForAssets(true)
	, bMapsInMapsFolder(true)
	, bDoFolderNameAssetsRedundantCheck(true)
	, bDoFolderNameAssetTypeRedundantCheck(true)
	, bBPCompiles(true)
	, bBPVariableChecks(true)
	, bBPVarPascalCase(true)
	, bBPVarBoolPrefix(true)
	, bBPVarBoolIsQuestion(true)
	, bBPVarAtomicInclusion(true)
	, bBPVarArrayPlurals(true)
	, bBPVarExposeOnSpawnEditable(true)
	, bBPVarEditableCategories(true)
	, bBPVarSaveGameInSaveGame(true)
	, bBPVarSaveNoConfig(true)
{
#define ADD_SETTING(TYPE, PREFIX, SUFFIX) AssetNameSettings.Add(TYPE, FAssetTypeNameSetting(TEXT(PREFIX), TEXT(SUFFIX)));

	/*  DEVELOPER NOTES
		This is the location where you setup the rules mapping 
		a prefix to a particular asset type. Warning! If you are using 
		objects created by thirdparty plugins and wish to set 
		a prefix for those dont! Even though you can include headers
		here for the type things get nasty in terms of plugin interdependence.
		If you remove a plugin from the engine and forget to compile you will
		get what are called linker errors. Plugins should NOT depend on the existance
		of other plugins because you can always turn a dependecy off or remove it
		from your project or from the engine */

	// Animations
	ADD_SETTING(UAimOffsetBlendSpace::StaticClass(), "AO_", "_BlendSpace");
	ADD_SETTING(UAimOffsetBlendSpace1D::StaticClass(), "AO_", "_BlendSpace1D");
	ADD_SETTING(UAnimBlueprint::StaticClass(), "ABP_", "");
	ADD_SETTING(UAnimComposite::StaticClass(), "AC_", "");
	ADD_SETTING(UAnimMontage::StaticClass(), "AM_", "");
	ADD_SETTING(UAnimSequence::StaticClass(), "AS_", "");
	ADD_SETTING(UBlendSpace::StaticClass(), "BS_", "_BlendSpace");
	ADD_SETTING(UBlendSpace1D::StaticClass(), "BS_", "_BlendSpace1D");
	ADD_SETTING(ULevelSequence::StaticClass(), "LS_", "");
	ADD_SETTING(UMorphTarget::StaticClass(), "SK_", "_MT");
	ADD_SETTING(URig::StaticClass(), "Rig_", "");
	ADD_SETTING(USkeletalMesh::StaticClass(), "SK_", "");
	ADD_SETTING(USkeleton::StaticClass(), "SK_", "_SKEL");

	// Artificial Intelligence
	ADD_SETTING(AAIController::StaticClass(), "AIC_", "");
	ADD_SETTING(UBehaviorTree::StaticClass(), "BT_", "");
	ADD_SETTING(UBlackboardData::StaticClass(), "BB_", "");
	ADD_SETTING(UBTDecorator::StaticClass(), "BTDecorator_", "");
	ADD_SETTING(UBTService::StaticClass(), "BTService_", "");
	ADD_SETTING(UBTTaskNode::StaticClass(), "BTTask_", "");

	// Blueprints
	ADD_SETTING(AGameMode::StaticClass(), "GM_", "");
	ADD_SETTING(UGameInstance::StaticClass(), "GI_", "");
	ADD_SETTING(UBlueprint::StaticClass(), "BP_", "");
	ADD_SETTING(UInterface::StaticClass(), "BPI_", "");
	ADD_SETTING(UBlueprintFunctionLibrary::StaticClass(), "BPFL_", "");
	// No class found for Macro Library
	ADD_SETTING(UUserDefinedEnum::StaticClass(), "EN_", "");
	ADD_SETTING(UUserDefinedStruct::StaticClass(), "ST_", "");

	// Materials
	ADD_SETTING(UMaterial::StaticClass(), "M_", "");
	ADD_SETTING(UMaterialInstance::StaticClass(), "MI_", "");
	ADD_SETTING(UMaterialFunction::StaticClass(), "MF_", "");
	ADD_SETTING(UMaterialParameterCollection::StaticClass(), "MPC_", "");
	ADD_SETTING(UMaterialInstanceConstant::StaticClass(), "MIC_", "");
	ADD_SETTING(USubsurfaceProfile::StaticClass(), "SSP_", "");

	// Textures
	ADD_SETTING(UTexture2D::StaticClass(), "T_", "");
	ADD_SETTING(UTextureCube::StaticClass(), "TC_", "");
	ADD_SETTING(UMediaTexture::StaticClass(), "MT_", "");
	ADD_SETTING(UTextureRenderTarget2D::StaticClass(), "RT_", "");
	ADD_SETTING(UTextureRenderTargetCube::StaticClass(), "RTC_", "");
	ADD_SETTING(UTextureLightProfile::StaticClass(), "TLP_", "");

	// Miscellaneous
	ADD_SETTING(UVectorFieldAnimated::StaticClass(), "VFA_", "");
	ADD_SETTING(UCameraAnim::StaticClass(), "CA_", "");
	ADD_SETTING(UCurveLinearColor::StaticClass(), "CurveL_", "");
	ADD_SETTING(UCurveTable::StaticClass(), "CurveT_", "");
	ADD_SETTING(UDataTable::StaticClass(), "DT_", "");
	ADD_SETTING(UCurveFloat::StaticClass(), "CurveF_", "");
	//ADD_SETTING(UFoliageType::StaticClass(), "FT_", "");
	ADD_SETTING(UForceFeedbackEffect::StaticClass(), "FFE_", "");
	//ADD_SETTING(ULandscapeGrassType::StaticClass(), "LG_", "");
	//ADD_SETTING(ULandscapeLayerInfoObject::StaticClass(), "LL_", "");
	ADD_SETTING(UMatineeAnimInterface::StaticClass(), "Matinee_", "");
	ADD_SETTING(UMediaPlayer::StaticClass(), "MP_", "");
	ADD_SETTING(UObjectLibrary::StaticClass(), "OL_", "");
	ADD_SETTING(UVectorFieldStatic::StaticClass(), "VF_", "");
	ADD_SETTING(UTouchInterface::StaticClass(), "TI_", "");
	ADD_SETTING(UCurveVector::StaticClass(), "CurveV_", "");

	// Paper 2D
	ADD_SETTING(UPaperSprite::StaticClass(), "PSS_", ""); 
	ADD_SETTING(UPaperFlipbook::StaticClass(), "PFB_", "");
	ADD_SETTING(UPaperTileMap::StaticClass(), "PTM_", "");
	ADD_SETTING(UPaperTileSet::StaticClass(), "PTS_", "");

	// Physics
	ADD_SETTING(UPhysicalMaterial::StaticClass(), "PM_", "");
	ADD_SETTING(UPhysicsAsset::StaticClass(), "PHYS_", "");
	ADD_SETTING(UDestructibleMesh::StaticClass(), "DM_", "");

	// Sounds
	ADD_SETTING(UDialogueVoice::StaticClass(), "DV_", "");
	ADD_SETTING(UDialogueWave::StaticClass(), "DW_", "");
	ADD_SETTING(UMediaSoundWave::StaticClass(), "MSW_", "");
	ADD_SETTING(UReverbEffect::StaticClass(), "Reverb_", "");
	ADD_SETTING(USoundAttenuation::StaticClass(), "ATT_", "");
	ADD_SETTING(USoundClass::StaticClass(), "SCS_", "");
	ADD_SETTING(USoundConcurrency::StaticClass(), "", "_SCN");
	ADD_SETTING(USoundCue::StaticClass(), "A_", "_Cue");
	ADD_SETTING(USoundMix::StaticClass(), "Mix_", "");
	ADD_SETTING(USoundWave::StaticClass(), "A_", "");

	// User Interface
	ADD_SETTING(UFont::StaticClass(), "Font_", "");
	ADD_SETTING(USlateBrushAsset::StaticClass(), "Brush_", "");
	ADD_SETTING(USlateWidgetStyleAsset::StaticClass(), "Style_", "");
	ADD_SETTING(UWidgetBlueprint::StaticClass(), "WBP_", "");

	// Effects
	ADD_SETTING(UParticleSystem::StaticClass(), "PS_", "");

	// Meshes
	ADD_SETTING(UStaticMesh::StaticClass(), "SM_", "");
	ADD_SETTING(UDestructibleMesh::StaticClass(), "DM_", "");

#undef ADD_SETTING

	// Macro Library Setting (Special Case Unfortunately)
	MacroLibrarySetting.Prefix = TEXT("BPML_");
	
}