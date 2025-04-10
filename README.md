# RestoreWaspDestroyDialog

This is a hack built for [Lucas' Simpsons Hit & Run Mod Launcher](https://modbakery.donutteam.com/releases/view/6) that restores the dialog event that plays when destroying a wasp in-game.

## How to install

- Download a release from https://github.com/Hampo/RestoreWaspDestroyDialog/releases
- If it doesn't already exist, create a `Hacks` directory at `Documents\My Games\Lucas' Simpsons Hit & Run Mod Launcher\Hacks`
- Extract the `RestoreWaspDestroyDialog.lmlh` from the release archive into that `Hacks` directory

## How to use

If you're an end user, you can find the hack in the `Settings` tab of your mod launcher. Just tick the hack to enable it and it will work.

If you're a mod developer, you can add this as a hack in your `Meta.ini`, under the `[Miscellaneous]` header.
It is recommended to use `OptionalHack`, rather than `RequiredHack`, as this is not an official Lucas hack.

## Proof of Concept

This was made a proof of concept that it's possible to restore the event. Ideally this will be included in a future mod launcher update and this version will become redundant.