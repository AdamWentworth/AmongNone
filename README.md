# AmongNone

Unreal Engine **5.8.0** C++ starter for macOS and Windows. Use the same repository
on both platforms; build outputs and IDE files are generated locally.

## Prerequisites

- Install Unreal Engine **5.8.0** on each machine.
- macOS: install full Xcode, complete its first-launch setup, and select its
  developer directory with `xcode-select`. This Mac was verified with Xcode 27.1.
- Windows: install Visual Studio's **Game development with C++** workload with
  Visual Studio 2022 17.14+ or Visual Studio 2026, MSVC 14.38+, and Windows SDK
  10.0.22621.0+ (see [UE 5.8 SDK requirements](https://dev.epicgames.com/documentation/unreal-engine/unreal-engine-5-8-release-notes?lang=en-US)).
  Rider can be your IDE, but Windows still needs the Visual Studio C++ build tools.

## One-time macOS setup for managed engine installations

This Mac's `UE_5.8.0_SI` engine was installed outside Epic's Launcher and is
registered under a local GUID. Unreal's project browser compares that GUID
with the project's shared `5.8` ID and shows **Convert Project** even though
both are UE 5.8.0. Building successfully does not resolve that registration.

Run this once from the repository root on each Mac with a managed installation:

```sh
bash Scripts/Unreal.sh setup
```

This validates version **5.8.0** and registers the installation as `UE_5.8` in
`~/Library/Application Support/Epic/UnrealEngineLauncher/LauncherInstalled.dat`.
Other installations and metadata are preserved; the original file is backed up
beside it as `LauncherInstalled.dat.amongnone-backup`. Repeating setup is safe.
It does not edit `AmongNone.uproject` or the engine installation.

**Quit all Unreal Editor instances and reopen the editor after setup.** The
editor caches its own engine ID for the lifetime of the process. You can then
open AmongNone normally from the project browser or `.uproject` file using
this 5.8.0 editor, without copying or converting the project. Re-run setup if
the engine moves or a management tool replaces its local registration.

A Windows installation made through Epic's Launcher already has the `5.8`
association; it does not need this Mac registration step.

## Build and open the existing checkout

Run from the repository root in Terminal on macOS:

```sh
bash Scripts/Unreal.sh open
```

Run from the repository root in PowerShell on Windows:

```powershell
powershell -ExecutionPolicy Bypass -File .\Scripts\Unreal.ps1 open
```

Both commands check the engine's `Build.version` for **5.8.0**, build
`AmongNoneEditor` in Development for the host platform, and launch that engine
with the existing `AmongNone.uproject`. The scripts work with paths containing
spaces. Use `build` instead of `open` to compile without launching the editor.
Close the editor before rebuilding C++ with these commands.

The scripts look in the usual Epic Games installation directory for `UE_5.8`,
`UE_5.8.0`, or `UE_5.8.0_SI`. For another location, set `UE_ENGINE_ROOT` in your
shell before running a command:

```sh
export UE_ENGINE_ROOT="/Users/Shared/Epic Games/UE_5.8.0_SI"
```

```powershell
$env:UE_ENGINE_ROOT = 'D:\Epic Games\UE_5.8'
```

These paths belong to each machine. The `open`, `build`, and `generate` commands
do not change engine registration or the shared project file. Only the explicit
Mac `setup` command updates local registration.

## IDE setup

In Rider, open `AmongNone.uproject` directly and select the local UE 5.8.0
installation if prompted. Build `AmongNoneEditor` / Development for Mac or
Win64. If you need generated Xcode or Visual Studio project files, run the
platform's script with `generate` instead of `open`. Regenerate them after
moving the checkout or changing the engine installation path.

## Engine association and version prompts

Keep `"EngineAssociation": "5.8"` in `AmongNone.uproject`; Epic's Launcher uses
the major/minor identifier even for patch release 5.8.0. The Mac setup step
registers the local installation under that same ID. Avoid changing the shared
project to a machine-specific GUID or using **Convert in-place** to resolve a
registration mismatch. After setup and an editor restart, ordinary project
opening should use the existing checkout directly.

Epic documents [engine associations and locally generated project files](https://dev.epicgames.com/documentation/en-us/unreal-engine/managing-game-code-in-unreal-engine).

## What belongs in Git

Commit the `.uproject`, `Source/`, `Config/`, `Content/`, project plugin source
and assets, and these scripts. Generated `.sln`/`.slnx`, Xcode projects,
`Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`, and local Rider
settings are ignored. Each platform rebuilds its own binaries from the shared
source. Unreal `.uasset` and `.umap` files are treated as binary in Git.
