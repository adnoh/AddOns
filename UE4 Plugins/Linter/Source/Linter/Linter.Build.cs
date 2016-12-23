// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Linter : ModuleRules
{
	public Linter(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"Linter/Public",
                /* @PlasticWax #PlasticWax - Added Search Paths here so that Linter
                 *  can find relevent engine headers */                
                "Developer/AssetTools/Public/",
                "Developer/AssetTools/Private/",
                "Developer/AssetTools/Classes/",
                "Editor/ContentBrowser/Public/",
                "Editor/ContentBrowser/Private/",
                "Editor/ContentBrowser/Classes/",
                "Runtime/AssetRegistry/Public/",
                "Runtime/AssetRegistry/Private/",
                "Runtime/AssetRegistry/Classes/",
                "Runtime/Engine/Private",
                "Runtime/Engine/Classes",
                "Runtime/Engine/Public",
                "Runtime/Media/Public/",
                "Runtime/Media/Private/",
                "Runtime/Media/Classes/",
                "Runtime/LevelSequence/Public",
                "Runtime/LevelSequence/Private",
                "Runtime/LevelSequence/Classes",
            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"Linter/Private",
                /* @PlasticWax #PlasticWax - Added Search Paths here so that Linter
                 *  can find relevent engine headers */                
                "Developer/AssetTools/Public/",
                "Developer/AssetTools/Private/",
                "Developer/AssetTools/Classes/",
                "Editor/ContentBrowser/Public/",
                "Editor/ContentBrowser/Private/",
                "Editor/ContentBrowser/Classes/",
                "Runtime/AssetRegistry/Public/",
                "Runtime/AssetRegistry/Private/",
                "Runtime/AssetRegistry/Classes/",
                "Runtime/Engine/Private",
                "Runtime/Engine/Classes",
                "Runtime/Engine/Public",
                "Runtime/Media/Public/",
                "Runtime/Media/Private/",
                "Runtime/Media/Classes/",
                "Runtime/LevelSequence/Public",
                "Runtime/LevelSequence/Private",
                "Runtime/LevelSequence/Classes",
            }
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "LevelSequence", // @PlasticWax #PlasticWax - Have to add the LevelSequence Module so that we can use the LevelSequence Header
                "Paper2D", // @PlasticWax #PlasticWax - Added this so we can use the Paper2DModule
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UnrealEd",
                "UMG",
                "UMGEditor",
                "ContentBrowser",
                "AssetTools",
                "EditorStyle",
                "Projects",
                "MediaAssets",
                "Landscape",
                "AIModule",
                "NetworkReplayStreaming",
                "BlueprintGraph"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
                //"LevelSequence",
            }
			);
	}
}
