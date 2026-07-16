// Blueprint-exposed shader-compile status. Lets the startup widget show a
// real "Compiling Shaders: N left" + 0-100% progress instead of a black void.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "R3ALShaderStatics.generated.h"

UCLASS()
class R3ALN3T_UE5_API UR3ALShaderStatics : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // Pipeline cache: shaders still queued to compile this session.
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Shaders")
    static int32 NumPrecompilesRemaining();

    // True while the engine is still compiling/streaming shaders at startup.
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Shaders")
    static bool IsCompilingShaders();

    // 0..1 progress across the current shader-compile batch.
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Shaders")
    static float GetShaderCompileProgress();
};
