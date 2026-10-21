param(
    [ValidateSet('open', 'build', 'generate')]
    [string]$Action = 'open'
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
if ($env:OS -ne 'Windows_NT') {
    throw 'This script requires Windows. On macOS, use Scripts/Unreal.sh.'
}

$projectDir = Split-Path -Parent $PSScriptRoot
$project = Join-Path $projectDir 'AmongNone.uproject'
$engineRoot = $env:UE_ENGINE_ROOT
if ([string]::IsNullOrWhiteSpace($engineRoot)) {
    foreach ($folder in @('UE_5.8', 'UE_5.8.0', 'UE_5.8.0_SI')) {
        $candidate = Join-Path $env:ProgramFiles "Epic Games\$folder"
        if (Test-Path -LiteralPath (Join-Path $candidate 'Engine\Build\Build.version') -PathType Leaf) {
            $engineRoot = $candidate
            break
        }
    }
}
if ([string]::IsNullOrWhiteSpace($engineRoot) -or
    !(Test-Path -LiteralPath (Join-Path $engineRoot 'Engine\Build\Build.version') -PathType Leaf)) {
    throw 'UE 5.8.0 not found. Set UE_ENGINE_ROOT to the installation folder containing Engine\.'
}
$engineRoot = (Resolve-Path -LiteralPath $engineRoot).Path
$versionFile = Join-Path $engineRoot 'Engine\Build\Build.version'
$version = Get-Content -LiteralPath $versionFile -Raw | ConvertFrom-Json
$versionNumber = "$($version.MajorVersion).$($version.MinorVersion).$($version.PatchVersion)"
if ($versionNumber -ne '5.8.0') {
    throw "UE 5.8.0 is required; found $versionNumber at $engineRoot."
}

Write-Host "Using Unreal Engine 5.8.0: $engineRoot"
$buildTool = Join-Path $engineRoot 'Engine\Build\BatchFiles\Build.bat'
if ($Action -eq 'generate') {
    & $buildTool -projectfiles "-Project=$project" -game -engine
    exit $LASTEXITCODE
}

# Build the native editor module before opening this checkout directly.
& $buildTool AmongNoneEditor Win64 Development "-Project=$project" -WaitMutex -NoHotReloadFromIDE
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}
if ($Action -eq 'open') {
    $editor = Join-Path $engineRoot 'Engine\Binaries\Win64\UnrealEditor.exe'
    Start-Process -FilePath $editor -ArgumentList ('"{0}"' -f $project)
}
