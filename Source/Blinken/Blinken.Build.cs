// Some copyright should be here...

using UnrealBuildTool;
using System.IO;

public class Blinken : ModuleRules
{
	public Blinken(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"Blinken/Public"
				
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"Blinken/Private",
				
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				
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

				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		PublicIncludePaths.Add( Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/ChromaSDK/inc") ) );
	}
}
