#!/bin/bash
set -euo pipefail

action="${1:-open}"
case "$action" in
    setup|build|open|generate) ;;
    *) echo "Usage: bash Scripts/Unreal.sh [setup|open|build|generate]" >&2; exit 1 ;;
esac
if [ "$#" -gt 1 ]; then
    echo "Usage: bash Scripts/Unreal.sh [setup|open|build|generate]" >&2
    exit 1
fi
if [ "$(uname -s)" != Darwin ]; then
    echo "This script requires macOS. On Windows, use Scripts/Unreal.ps1." >&2
    exit 1
fi

project_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
project="$project_dir/AmongNone.uproject"
engine_root="${UE_ENGINE_ROOT:-}"
if [ -z "$engine_root" ]; then
    for candidate in "/Users/Shared/Epic Games/UE_5.8" "/Users/Shared/Epic Games/UE_5.8.0" "/Users/Shared/Epic Games/UE_5.8.0_SI"; do
        if [ -f "$candidate/Engine/Build/Build.version" ]; then
            engine_root="$candidate"
            break
        fi
    done
fi
if [ ! -f "$engine_root/Engine/Build/Build.version" ]; then
    echo "UE 5.8.0 not found. Set UE_ENGINE_ROOT to the installation folder containing Engine/." >&2
    exit 1
fi
engine_root="$(cd "$engine_root" && pwd)"
version_file="$engine_root/Engine/Build/Build.version"
major="$(/usr/bin/plutil -extract MajorVersion raw -o - "$version_file")"
minor="$(/usr/bin/plutil -extract MinorVersion raw -o - "$version_file")"
patch="$(/usr/bin/plutil -extract PatchVersion raw -o - "$version_file")"
if [ "$major.$minor.$patch" != 5.8.0 ]; then
    echo "UE 5.8.0 is required; found $major.$minor.$patch at $engine_root." >&2
    exit 1
fi

echo "Using Unreal Engine 5.8.0: $engine_root"
if [ "$action" = setup ]; then
    exec /usr/bin/python3 "$project_dir/Scripts/RegisterEngineMac.py" "$engine_root"
fi
batch_dir="$engine_root/Engine/Build/BatchFiles/Mac"
if [ "$action" = generate ]; then
    exec /bin/bash "$batch_dir/GenerateProjectFiles.sh" "-project=$project" -game -engine
fi

# Build the native editor module before opening this checkout directly.
/bin/bash "$batch_dir/Build.sh" AmongNoneEditor Mac Development "-Project=$project" -WaitMutex -NoHotReloadFromIDE
if [ "$action" = open ]; then
    /usr/bin/open -n -a "$engine_root/Engine/Binaries/Mac/UnrealEditor.app" --args "$project"
fi
