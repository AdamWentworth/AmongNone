"""Register a managed macOS UE 5.8.0 install under the shared 5.8 engine ID."""

import json
import os
from pathlib import Path
import shutil
import sys
import tempfile


def register(engine_root, manifest):
    engine_root = engine_root.resolve(strict=True)
    version = json.loads((engine_root / "Engine/Build/Build.version").read_text())
    if tuple(version.get(key) for key in ("MajorVersion", "MinorVersion", "PatchVersion")) != (5, 8, 0):
        raise ValueError("Only Unreal Engine 5.8.0 can be registered as 5.8.")
    if not (engine_root / "Engine/Binaries/Mac/UnrealEditor.app").is_dir():
        raise ValueError("The selected installation has no macOS UnrealEditor.app.")

    # DesktopPlatform reads this file before consulting the Mac's GUID registry.
    # A plain '5.8' alias in Install.ini is insufficient: its Mac reader parses
    # those keys as GUIDs. Keep the project's portable Launcher ID instead.
    data = json.loads(manifest.read_text()) if manifest.exists() else {"InstallationList": []}
    installations = data["InstallationList"]
    if not isinstance(installations, list) or any(not isinstance(item, dict) for item in installations):
        raise ValueError("Invalid InstallationList; the registration file was left unchanged.")
    matching = [item for item in installations if item.get("AppName") == "UE_5.8"]
    registration = dict(matching[0]) if matching else {"AppName": "UE_5.8"}
    registration["InstallLocation"] = str(engine_root)
    # Prefer the shared ID when the same directory also has another local ID.
    updated = [registration] + [item for item in installations if item.get("AppName") != "UE_5.8"]
    if installations == updated:
        return False

    manifest.parent.mkdir(parents=True, exist_ok=True)
    backup = manifest.with_name(manifest.name + ".amongnone-backup")
    if manifest.exists() and not backup.exists():
        shutil.copy2(manifest, backup)
    data["InstallationList"] = updated
    temporary_path = None
    try:
        with tempfile.NamedTemporaryFile(mode="w", encoding="utf-8", dir=manifest.parent, delete=False) as stream:
            temporary_path = Path(stream.name)
            if manifest.exists():
                os.fchmod(stream.fileno(), manifest.stat().st_mode & 0o777)
            json.dump(data, stream, indent=2)
            stream.write("\n")
        os.replace(temporary_path, manifest)
    finally:
        if temporary_path is not None and temporary_path.exists():
            temporary_path.unlink()
    return True


def main():
    if sys.platform != "darwin" or len(sys.argv) != 2:
        raise ValueError("Run bash Scripts/Unreal.sh setup on macOS.")
    manifest = Path.home() / "Library/Application Support/Epic/UnrealEngineLauncher/LauncherInstalled.dat"
    changed = register(Path(sys.argv[1]), manifest)
    print("Registered Unreal Engine 5.8.0 as 5.8." if changed else "Unreal Engine 5.8.0 is already registered as 5.8.")
    print("Registration: " + str(manifest))
    print("Restart all Unreal Editor instances, then open AmongNone normally. No conversion is needed.")


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError, KeyError) as error:
        sys.exit(str(error))
