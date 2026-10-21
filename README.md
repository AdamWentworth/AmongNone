# AmongNone

One Unreal Engine **5.8** C++ project for macOS and Windows. Use this repository
on both platforms; each checkout generates its own build outputs and IDE files.
Do not make platform-specific project copies or convert the project to fix an
engine registration prompt.

## Prerequisites

- Install Unreal Engine **5.8.x** on each machine. The shared
  `AmongNone.uproject` engine association (`5.8`) is the version requirement.
  The scripts accept patch releases in that series and print the exact version
  selected. Prefer the same patch on both machines, especially when saving assets;
  accepting an engine version does not guarantee assets saved by a newer patch
  can be opened by an older one. Coordinate upgrades on both machines.
- macOS: install full Xcode, complete its first-launch setup, and select its
  developer directory with `xcode-select`. Use the Xcode version supported by
  your installed engine.
- Windows: install Visual Studio's **Game development with C++** workload, its
  supported MSVC toolchain, and Windows SDK. Rider can be your IDE, but Windows
  still needs the Visual Studio C++ build tools. UnrealBuildTool checks the
  compiler and SDK during the build; the engine's requirements are in
  `Engine/Config/Windows/Windows_SDK.json` and the
  [UE 5.8 release notes](https://dev.epicgames.com/documentation/unreal-engine/unreal-engine-5-8-release-notes?lang=en-US).

## Build and open the existing checkout

Run from the repository root in Terminal on macOS:

```sh
bash Scripts/Unreal.sh open
```

Run from the repository root in PowerShell on Windows:

```powershell
powershell -ExecutionPolicy Bypass -File .\Scripts\Unreal.ps1 open
```

Both commands read the shared engine association, check the selected engine's
`Build.version`, build `AmongNoneEditor` in Development for the host platform,
and launch that engine with the existing `AmongNone.uproject`. They support
paths containing spaces and resolve the project independently of the current
working directory. A failed build stops launch. Close the editor before
rebuilding C++ with these commands.

Use `build` instead of `open` to compile without launching. Use `doctor` to
print the resolved project, engine path, and exact version and check the engine
entry points without building or changing registration. A successful native
`build` is still required to validate the compiler and SDK.

The scripts first use `UE_ENGINE_ROOT` if set. Otherwise they look for the
shared engine ID in Epic's Launcher installation manifest; Windows also checks
Epic's engine registry entry. Finally they check the usual Epic Games directory
for `UE_5.8`, `UE_5.8.0`, or `UE_5.8.0_SI`.
For another location, set `UE_ENGINE_ROOT` in your shell:

```sh
export UE_ENGINE_ROOT="/Users/Shared/Epic Games/UE_5.8.0_SI"
```

```powershell
$env:UE_ENGINE_ROOT = 'D:\Epic Games\UE_5.8'
```

These paths belong to each machine. An explicit override is checked strictly;
a wrong engine never silently falls back to another installation.
The `open`, `build`, `generate`, and `doctor` commands do not change engine
registration or the shared project file.

## One-time Windows setup for a project-browser association prompt

Some Windows engine installs are discoverable by the repository scripts but are
registered only under a machine-specific GUID. Unreal's project browser then
cannot resolve the shared 5.8 association and may offer to create a copy.
From the repository root, run this in PowerShell:

    powershell -ExecutionPolicy Bypass -File .\Scripts\Unreal.ps1 setup

The command validates the selected engine and adds the shared 5.8 ID to the
current user's Unreal engine registry. It preserves existing GUID registrations,
does not edit AmongNone.uproject or engine files, and refuses to replace a
5.8 registration that points to another installed engine. Repeating setup
with the same engine is safe. If the engine is in a nonstandard location, set
UE_ENGINE_ROOT first as described above.

**Quit all Unreal Editor instances and reopen AmongNone from the project
browser after setup.** Windows installations already registered under the
shared 5.8 ID do not need this step.

## One-time macOS setup for managed engine installations

An engine installed outside Epic's Launcher may be registered under a local
GUID. Unreal's project browser then shows **Convert Project** even when its
version matches the shared `5.8` ID. Building alone does not fix registration.

For such installations, run this once from the repository root:

```sh
bash Scripts/Unreal.sh setup
```

This validates the engine against `AmongNone.uproject` and registers it as
`UE_5.8` in
`~/Library/Application Support/Epic/UnrealEngineLauncher/LauncherInstalled.dat`.
Other installations and metadata are preserved; the original file is backed up
beside it as `LauncherInstalled.dat.amongnone-backup`. Repeating setup with
the same installation is safe. It does not edit the project or engine files.
It refuses to replace another existing installation for that shared ID; select
that engine instead or resolve its registration deliberately.

**Quit all Unreal Editor instances and reopen the editor after setup.** The
editor caches its engine ID for the lifetime of the process. Open AmongNone
from this engine without copying or converting it. Re-run setup if the engine
moves or a management tool replaces its registration.

A Windows installation made through Epic's Launcher already has the `5.8`
association; it does not need this Mac registration step.

## IDE setup

In Rider, open `AmongNone.uproject` directly and select the local UE 5.8
installation if prompted. Build `AmongNoneEditor` / Development for Mac or
Win64. If you need generated Xcode or Visual Studio project files, run the
platform's script with `generate` instead of `open`. Regenerate them after
moving the checkout or changing the engine installation path.

Keep `"EngineAssociation": "5.8"` in `AmongNone.uproject`. Avoid committing
a machine-specific GUID or using **Convert in-place** for a registration
mismatch. Epic documents
[engine associations and locally generated project files](https://dev.epicgames.com/documentation/en-us/unreal-engine/managing-game-code-in-unreal-engine).

## What belongs in Git

Commit the `.uproject`, `Source/`, `Config/`, `Content/`, project plugin source
and assets, and these scripts. Generated `.sln`/`.slnx`, Xcode projects,
`Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`, and local Rider
settings are ignored. Each platform rebuilds its own binaries from the shared
source. Unreal `.uasset` and `.umap` files are treated as binary in Git.

After pulling changes on either machine, use `doctor` and then `build` before
`open`. On a fresh checkout these commands rebuild locally; no copied binaries
or generated projects are needed. Do not delete `Content/`, `Config/`, or
`Source/` to troubleshoot a build.

## Script regression checks

With Python 3 installed, run on macOS:

```sh
python3 -B -m unittest discover -s Tests -v
```

On Windows:

```powershell
python -B -m unittest discover -s Tests -v
```

These checks exercise registration against temporary manifests and the host
platform's script against a temporary mock engine. They do not modify engine
registration or launch an editor. Run them on both Windows and macOS; they
check script behavior, while a real native `build` verifies Unreal compilation.
