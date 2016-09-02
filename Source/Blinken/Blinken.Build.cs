// Copyright (C) 2016 Descendent Studios, Inc.

using UnrealBuildTool;
using System.IO;

public class Blinken : ModuleRules
{
	public Blinken(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange( new string[] { "Engine", "Core", "InputCore", "CoreUObject" } ); 

		if(Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Razer Chroma SDK
			PublicIncludePaths.Add( Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/ChromaSDK/inc") ) );

			// LogitechG SDK
			PublicLibraryPaths.Add( Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/LogitechG/lib", Target.Platform.ToString()) ) );
			PublicAdditionalLibraries.Add("LogitechLEDLib.lib");
			PublicIncludePaths.Add( Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/LogitechG/inc") ) );
			
			// AlienFX SDK
			PublicIncludePaths.Add( Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/AlienFXSDK/includes") ) );
			RuntimeDependencies.Add(
				new RuntimeDependency(Path.Combine(ModuleDirectory, "../../ThirdParty/AlienFXSDK/dll", Target.Platform.ToString(), "LightFX.dll"))
				);
		}
	}
}
