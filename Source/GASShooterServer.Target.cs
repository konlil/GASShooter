// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class GASShooterServerTarget : TargetRules
{
	public GASShooterServerTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		bUsesSteam = true;

        if (Target.Configuration != UnrealTargetConfiguration.Shipping &&
            Target.Configuration != UnrealTargetConfiguration.Test)
        {
			//For flame graph sampling
			//AdditionalCompilerArguments += "-fno-omit-frame-pointer";
			bOmitFramePointers = false;
		}

        DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "GASShooter" } );
	}
}
