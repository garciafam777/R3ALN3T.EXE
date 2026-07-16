#include "R3ALShaderStatics.h"
#include "ShaderPipelineCache.h"   // FShaderPipelineCache (Engine)
#include "ShaderCompiler.h"        // GShaderCompilingManager (RenderCore)
#include "Engine/Engine.h"         // GEngine

int32 UR3ALShaderStatics::NumPrecompilesRemaining()
{
    return FShaderPipelineCache::NumPrecompilesRemaining();
}

bool UR3ALShaderStatics::IsCompilingShaders()
{
    if (GShaderCompilingManager && GShaderCompilingManager->IsCompiling())
    {
        return true;
    }
    return FShaderPipelineCache::NumPrecompilesRemaining() > 0;
}

float UR3ALShaderStatics::GetShaderCompileProgress()
{
    // Capture a high-water total ourselves so we don't depend on a specific
    // FShaderCompilingManager accessor that varies across engine versions.
    static int32 CapturedTotal = 0;

    const int32 Remaining = FShaderPipelineCache::NumPrecompilesRemaining();

    if (GShaderCompilingManager && GShaderCompilingManager->IsCompiling())
    {
        const int32 Outstanding = GShaderCompilingManager->GetNumOutstandingJobs();
        if (CapturedTotal < Outstanding)
        {
            CapturedTotal = Outstanding;
        }
        if (CapturedTotal <= 0)
        {
            return Remaining > 0 ? 0.f : 1.f;
        }
        return FMath::Clamp(1.f - (float)Outstanding / (float)CapturedTotal, 0.f, 1.f);
    }

    // Not actively compiling this tick -> reset for the next batch.
    CapturedTotal = 0;
    return Remaining > 0 ? 0.f : 1.f;
}
