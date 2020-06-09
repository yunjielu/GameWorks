using System;
using System.IO;

namespace UnrealBuildTool.Rules
{
    public class BlastEditor : ModuleRules
    {
        public BlastEditor(ReadOnlyTargetRules Target) : base(Target)
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
                    "Blast",
                    "UnrealEd"
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "BlastRuntime",
                    "Core",
                    "CoreUObject",
                    "AssetTools",
                    "Engine",
                    "RenderCore",
                    "Renderer",
                    "PropertyEditor",
                    "XmlParser",
                    "ContentBrowser",
                    "Projects",
                    "Slate",
                    "SlateCore",
                    "MainFrame",
                    "InputCore",
                    "EditorStyle",
                    "LevelEditor",
					"MeshPaint",
                    "JsonUtilities",
                    "Json",
                    "RHI",
                }
            );

            //Don't add to PrivateDependencyModuleNames since we only use IBlastMeshEditorModule and we can't have a circular depdency on Linux
            PrivateIncludePathModuleNames.AddRange(
                new string[] {
                    "BlastMeshEditor",
                }
            );


            string[] BlastLibs =
            {
                 "NvBlastExtAssetUtils",
				 "NvBlastExtAuthoring",
            };

            BlastRuntime.SetupModuleBlastSupport(this, BlastLibs);

            AddEngineThirdPartyPrivateStaticDependencies(Target, "FBX");

        }
    }
}