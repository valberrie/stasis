# Overview
Stasis allows mods to bypass Steam and run solely locally.

If you try to load a typical Source 2013 mod without Steam open, you may run into two major roadblocks.
1. The launcher will not be able to locate the Source SDK.
2. You will get an error dialogue from `public/filesystem_init.cpp` with the message "No SteamApps connection" (This message has been amended in Stasis). This is because your mod uses search paths in its `gameinfo.txt` that refer to Steam AppIDs.

In most cases, the second issue is all that needs to be addressed, which means that `gameinfo.txt` must be amended to mount game assets without referring to AppIDs, most commonly by replacing `|appid_XXXXXX|` with `|all_source_engine_paths|` or `|gameinfo_path|`.

However, if this doesn't work on its own, you can supply the command line argument `-nosteam`, and `-path`, followed by the full path to the root directory of your installation of Source SDK Base 2013 Multiplayer. Most commonly, `"C:\Program Files (x86)\Steam\steamapps\common\Source SDK Base 2013 Multiplayer"`, WITH the double quotes.