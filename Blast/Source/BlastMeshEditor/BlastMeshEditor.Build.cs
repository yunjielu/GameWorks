// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
using System;
using System.IO;

namespace UnrealBuildTool.Rules
{
    public class BlastMeshEditor : ModuleRules
    {
        public BlastMeshEditor(ReadOnlyTargetRules Target) : base(Target)
        {
			PrivateIncludePaths.AddRange(
                new string[] {
                    Path.GetFullPath(Path.Combine(ModuleDirectory, "../BlastRuntime/Public/extensions/assetutils/include/")),
                    Path.GetFullPath(Path.Combine(ModuleDirectory, "../BlastRuntime/Public/extensions/authoringCommon/include/")),
                    Path.GetFullPath(Path.Combine(ModuleDirectory, "../BlastRuntime/Public/extensions/authoring/include/")),
                    Path.GetFullPath(Path.Combine(ModuleDirectory, "../BlastRuntime/Public/extensions/serialization/include/")),
                    Path.GetFullPath(Path.Combine(ModuleDirectory, "../BlastRuntime/Public/extensions/shaders/include/")),
                    Path.GetFullPath(Path.Combine(ModuleDirectory, "../BlastRuntime/Public/extensions/stress/include/")),
                    Path.GetFullPath(Path.Combine(ModuleDirectory, "../BlastRuntime/Public/globals/include/")),
                    Path.GetFullPath(Path.Combine(ModuleDirectory, "../BlastRuntime/Public/lowlevel/include/")),
                }
            );
			
            PublicDependencyModuleNames.AddRange(
                new string[] {
                "Engine",
                "PhysX"
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                "BlastRuntime",
                "BlastEditor",
                "Core",
                "CoreUObject",
                "InputCore",
                "RenderCore",
                "PhysicsCore",
                "Slate",
                "SlateCore",
                "EditorStyle",
                "UnrealEd",
                "Projects",
                "DesktopPlatform",
                "AdvancedPreviewScene",
                "AssetTools",
                "LevelEditor",
                "MeshMergeUtilities",
                "RawMesh",
                "MeshUtilities",
                "MeshUtilitiesCommon",
                "MeshDescription",
                "MeshDescriptionOperations",
                "RHI",
                }
            );

            DynamicallyLoadedModuleNames.Add("PropertyEditor");

            string[] BlastLibs =
            {
                 "NvBlastExtAuthoring",
            };

            BlastRuntime.SetupModuleBlastSupport(this, BlastLibs);

            AddEngineThirdPartyPrivateStaticDependencies(Target, "FBX");

            //SetupModulePhysXAPEXSupport(Target);
        }
    }
}