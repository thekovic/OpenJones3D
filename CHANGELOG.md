## v0.3.1
### General:
  - Fixed radius of fading plate 3DO models (5d705fb)
  - Codebase update and cleanup (bf2c4f7)
  - Fixed bug calculating time delta when path move thing is blocked (f361b65)
    This fixes the bug where another thing object blocks the path of path moving objects, causing them to continue moving indefinitely as long as the path is blocked.
    e.g.: pressed button moves out of socket if player blocks its path when the button moves to initial position.
  - Fixed incorrect usage of enum flags (918bcee)
  - Added define guard for `STRICT` macro to prevent redefinition warnings (1b0e597)
  - Fixed incorrect enumerator names enum `SithCollisionType` (f2cbab2)

## v0.3
### General:
  - Fixed various bugs
  - Fixed game crash on save game restore when an object is attached to a non-primary mesh face of a 3D model (45c8065) 
  - Fixed hiding console on cutscene start (27ca92b)
  - Fixed light range in `ThingLight` / `SetThingLight` COG functions (e9d4167)  
    This fix ensures that the light range is correctly set when the COG function is called.  
    Fixes light flickering bug when camera is facing and is near the light source.
  - Fixed casting float to int (0ada120)  
    This fix ensures that:
    * The correct integer values are popped from the COG execution stack.
    * AI instinct parameters are correctly parsed when the AI class is parsed.
  - Added developer COG verbs (33f8f9d)
  - Added error log when popping invalid string from COG stack (34c9e20)
  - Rename debug mode flag `SITHDEBUG_AILOOK_FOR_TARGET_DISABLED` to `SITHDEBUG_AINOTARGET` (53b9091)
  - Changed argument order of debug print COG functions (a80ed30)  
    Also changed the log level to debug.
  - Added programs `yacc` & `flex` (d6f5be6 + b669ca8)
  - Fixed yacc initial line number at the start of code parsing. (232f268)  
    This fixes line number in log when error is encountered.
  - Fixed bug in multiple COG thing functions (`sithCogFunctionThing` module) where a return value  
   was not pushed to the execution stack on error. (e9d4167)  
    This fixes corruption of the COG's execution stack when an error occurs.
  - Added new `rdVector` arithmetic functions (c4c8ee5)
  - Fix null pointer dereference && infinitive loop in `sithAnimate_BuildScrollFaceRotate`, `sithAnimate_PushItem`, `sithAnimate_PullItem`, `sithAnimate_UpdatePushItemAnim` and `sithAnimate_UpdatePullItemAnim` (70cf7bf)
  - Fixed handling division by zero in `sithAnimate_StartSpriteSizeAnim` & `sithAnimate_StartThingMoveAnim` (f5dc718)
  - Altered the `AnimateSpriteSize` COG function to return -1 when deltaTime is 0. (039a227)  
    This change prevents unnecessary animation creation, thereby saving animation slots.  
    The function now returns -1 to the script when the sprite size is set instantly but no animation is created,  
    whereas previously, -1 was returned only on animation creation errors.
  - Fixed deterministic restoration of 3D sound handles from savegame file and prevented sound handle collisions (6c3acc4)  
    * Recalculates original handle entropy from saved handle before playing or loading sounds.
    * Ensures restored handle entropy never falls below the highest handle used during restore to prevent handle collision.
    * Prevents handle collisions that could swap playing sounds and cause looping sounds to stick at the player's position.
    * Ensures restored 3D and far playing sounds have exactly the same handles they had when the sound state was saved.  
    This fixes issues with COG scripts that store sound handles in variables.  
    Previously, restored sounds had different handles than when they were saved, which potentially broke script logic.
  - [QOL] Removed the loop flag from sound modes (2a757af)  
    This prevents repeated accumulation of the same sound in sound buffer, ensuring the buffer doesn't fill up and preventing new sounds from playing.  
    *Note, marked as QOL because this issue becomes most relevant when QOL for looping far sound is in place.*
  - [QOL] Increased max number of simultaneous playing sounds to 128 (d8fdedc)
  - Fixed OOB bug in command line level selection (24ab38b)
  - Added level related hardcoded constants (fedb5bf)
  - Fixed resetting IMP fire state, player visibility, and disabling of swimming inventory on system close (645471a)
  - Added new system COG functions:
    * `DebugVector` (eb860f8)
    * `EnablePrint` (32763c2)
    * `IsPrintEnabled` (32763c2)
    * `DebugPrint` (33f8f9d)
    * `DebugFlex` (33f8f9d)
    * `DebugInt` (33f8f9d)
    * `DebugLocalSymbols` (33f8f9d)
    * `DebugWaitForKey` (33f8f9d)
    * `sithSprite` (3f0d87f)
    * `sithParticle` (3f0d87f)
    * `sithPathMove` (8ba32fb)
  - Implemented `Print*` Cog functions (33f8f9d)
  - Implemented sound save & restore functions (4ab0c6f)
  - Implemented modules:
    * `sithConsole` (7879d45)
    * `sithCommand` (4ec4941)
    * `sithCogFunction` (33f8f9d)
    * `sithCogFunctionSector` (e46c2ab)
    * `sithCogFunctionSurface` (40b6d38)
    * `sithCogFunctionSound` (2df2214)
    * `sithAI` (ca79900)
    * `sithAIAwareness` (d7f822f)
    * `sithAIClass` (d7f822f)
    * `sithPuppet` (a68d1a7)
    * `sithTemplate` (a53d895)
    * `SoundDriver` (0530afe)
    * `sithSoundClass` (3d2d82d)
    * `sithCogFunctionAI` (f6c8fb8)
    * `sithSound` (5bbb9eb)
    * `sithExplosion` (d15ac1c)
    * `sithCogParse` (b669ca8)
    * `sithCogYacc` (b669ca8)
    * `sithCogFunctionPlayer` ([PR#19](https://github.com/smlu/OpenJones3D/pull/19))
    * `sithCogFunctionThing` ([PR#19](https://github.com/smlu/OpenJones3D/pull/19))
    * `jonesConfig` ([PR#21](https://github.com/smlu/OpenJones3D/pull/21))
    * `sithWorld` (85a9ebe)
    * `sithOverlayMap` (967e433)
    * `sithAnimate` (ef93c3c)
    * `sithGamesave` (3dc6ee4)
    * `sithDSSCog` (0b8f620)
    * `Sound` (664b8f8)
  - Added `Sound_GetAllInstanceInfo` & `Sound_SoundDump` functions (8654185)
  - Added `stdConffile_GetWriteFileHandle` function (cee02bd)
  - Fixed bug to correctly update key press state in `stdControl_ReadAxisAsKey` function (1ab4c44)
  - Refactored `stdControl` module (fc4060c)
  - Fixed bug to correctly obtain the file handle when opening a savegame file for reading and writing (a90a59d)
  - Added devmode logic to `sithConsole` module (57b685b)  
    This enables commands flagged with `SITHCONSOLE_DEVMODE` flag to be available only
    when console flags have `SITHCONSOLE_DEVMODE` set.
  - Added devmode console commands:
    * `jumplevel` (e59ffab)
    * `radius` (e59ffab)
    * `pvs` (e59ffab)
    * `nextlevel` (e59ffab)
    * `endlevel` (e59ffab)
    * `restart` (e59ffab)
    * `sounds` (e59ffab)
    * `devmode` (e59ffab)
    * `ineditor` (e59ffab)
    * `money` (1e9a47f)
    * `interface` (1e9a47f)
    * `indicator` (1e9a47f)
    * `invul`, `wuss`, `ouch`, `warp`, `jump`, `imp1`, `imp2` (9d399b0)
    * `imp3`, `imp4`, `imp5`, `fly`, `players`, `ping`, `kick` (9d399b0)
    * `tick`, `session`, `electroman`, `trackshots`, `caminfo` (9d399b0)
    * `fov`, `tj`, `weapons`, `help`, `disableai`, `notarget` (9d399b0)
    * `disablepuppet`, `cogtrace`, `coglist`, `cogstatus` (9d399b0)
    * `noaishots`, `aistatus`, `ailist`, `cogpause` (9d399b0)
    * `pauseallcogs`, `matlist`, `activate`, `slowmo` (9d399b0)
    * `stopsound`, `wpdraw` (9d399b0)
    * `noclip` (2d9f47a)
    * `print` (44e28c5)

### Display & Render:
  - Added support for display resolutions higher than 2048-pixel (6f9db7e)
  - Fixed bug rendering ceiling sky (2a200d5)
  - Fixed thumbnail rendering in save game dialog (c7bb134)
  - Fixed thumbnail rendering in exit dialog (b64fb63)
  - Increased size of game save/load dialogs (ce321bb)
  - Changed the native open file dialog for game save dialog (5871f09)
  - Implemented the top layer of the game save dialog, resulting in a dialog style update (f38ff8a)
  - Fixed incorrect scaling & positioning of dialog controls with nested child windows. (50a3f83)  
    This fixes positioning of lists in Indy's trade post and key config dialogs.
  - Increased font size for all GDI dialogs (d1a09a0)
  - Added scaling for embedded dialog icon(s) (d1a09a0)
  - Increased size of exit dialog icon (fc92734)
  - Implemented chapter completed dialog (8ceab2c) 
  - Fixed rendering of IQ points in chapter completed dialog (8ceab2c)
  - Implemented Indy's trading post dialog (a8a32ff)
  - Fixed column padding in trading post dialog (a8a32ff)
  - Increased the size of store item icon to 48 (a8a32ff)
  - Fixed drawing 2D line to 24 BPP & 32 BPP video buffer (81b4bc7)
  - Fixed the alpha value of the health indicator on the first run and when the screen resolution changes (e32a52d)
  - Fixed the hardware-accelerated drawing of 2D lines (5a63bc7)  
    Subsequently, this fix addresses the drawing error of level wireframe geometry on the overlay map

### Game play:
  - [QOL] Fixed removal of loop-playing far sound. (2a25add)  
    This ensures the loop-playing sound continues to play when the listener comes in sound hearing range.
  - Fixed submersion of dead thing in cold-water/lava (18d828d)
  - Fixed mouse sensitivity when in-editor mode (d25081f)
  - Added mouse button actions for fire/activate, jump, weapon toggle, and weapon selection when in-editor mode (d25081f)
  - Restricted developer/debug control keys to in-editor/dev mode only (d25081f)
  - [QOL] Fixed stop looping far sound when volume is below threshold (5a169d7)
  - Fixed playing far sound on sound restore from savegame (b8a82d4)
  - [QOL] Improved AI controlled actor movement at cliff edges (8ed5690)  
    Enhanced the AI actors's behavior when reaching cliff edges. Previously, AI actor would perform a 180-degree turn followed by a random 60-degree movement in new direction. Now, it performs a random 60-degree movement based on its prior direction, resulting in more natural and predictable navigation.
  - [QOL] Fixed AI collision deadlock on predefined paths (49ef284)  
    Two AI actors that collided head-on traversing a predefined waypoint path previously entered a "dancing" loop as they continuously attempted to pass each other. Now, upon detecting a collision, each actor randomly adjusts its direction by 0–45° in its current movement direction, enabling them to maneuver past one another.
  - [QOL] Fixed an issue with falling velocity during jump-rollback movements (c1673ac)  
  Originally, when player performed a jump-rollback, the fall velocity was incorrectly reset to 0, allowing them to drop from dangerous heights without taking damage. Now, the fall speed is properly maintained.

## v0.2
### General:
  - Fixed various bugs
  - Fixed floating point precision bug in `rdVector` & `rdMatrix34` functions (3b800ad)
  - Made OpenJones3D binaries portable by adding absolute resource dir path to JonesFile VFS (fca6ef2)  
    This change allows binaries to be placed in any arbitrary location, eliminating the requirement for a Resource folder.
  - Fixed typo in framerate output text (47537aa)
  - Fixed initializing and clearing resource array on `JonesFile_Close` (47537aa)
  - Fixed the invocation of `jonesString_GetString("JONES_STR_LOADERROR")` on every call to `JonesMain_ProcessGamesaveState` when there is no load error or the game is not being restored (47537aa)
  - Fixed error text when it was cached by `jonesString_GetString` in call to `JonesMain_LogErrorToFile` (485d553)
  - Changed the location of `JonesError.txt` to be always written in current working directory instead of installed path (485d553)  
    This change resolves a potential fatal error that could occur when writing the error log due to the registry system failing to startup.
  - Changed warning log to output to console or file (dcd3015)
  - Made console log output colorized (dcd3015)
  - Added debugger log output (dcd3015)
  - Removed material buffer size constraint when loading material section form NDY level file in `sithMaterial_LoadMaterialsText` (dcd3015) 
  - Fixed potential infinitive loop bug when .uni file is missing line break at the end of file (6b71793)
  - Implemented `sithSurface` module (b448041)

### Display & Render:
  - Fixed scaling of color component when converting pixel data row in `stdColor_ColorConvertOneRow` (9e6ba77)
  - Changed default engine texture format to 32 bit from 16 bit (249a416)
  - Removed support for 16 bpp textures (3152496)
  - Increased `rdCache` vertex buffer size to 32768 * 64 (25ceaba)
  - Increased `rdModel3` (.3DO) mesh constraints based on `rdCache` constraints (a008386)
  - Increased max no. of sectors in camera view to 4096 (b448041)
  - Increased max no. of thing with sectors to 8192 (b448041)

### Game play:
  - Changed to by default play the higher resolution intro movie (800x600) (ffa2e9d)
  - Fixed retrieving model by index number when loading savegame (669904d)  
    This change adds temporary wrapper function `sithModel_GetModelByIndexWrap`.
  - Added support for 24/32 bit textures to CND cnd file format  (91d0a87)
  - Changed how developer dialog discovers level files (30630d1)  
    Now dialog first looks for ndy folder in current working directory, and if found searches for level files in that folder.  
    If ndy folder is not found the dialog checks for level files in `Install Path\Resource\ndy`.
  - Fixed searching for ndy level file when corresponding cnd file is not found (5e64e5b)  
    When game progresses to the next level this enables using ndy file for original levels when the corresponding cnd file is not found
  - Enabled weapon COG functions in devmode (a9cbc0b)

### HUD:
  - Fixed drawing of horizontal wall line (8046835)

## v0.1
### General:
  - Fixed minor bugs
  - Improve game loading times by disabling VSync and blt frame buffers instead of flip.
  - Changed DPI awareness to per monitor aware v2
  - Added check for NAN value of provided angle in `stdMath_SinCos`
  - Fixed issue with float precision in `stdMath_NormalizeAngle` which could result in angles larger than 360 degrees.  
    This fixes array out of bound read in `stdMath_SinCos`, which fixes random crash when opening inventory menu  
    or calling COG function `JonesInvItemChanged` from script.
  - Fixed deleting hdc on pixel data read error in `stdBmp_Load`
  - Fixed reading/writing 24 bpp pixel from bytes in `stdColor_ColorConvertOneRow`.
    This fixes conversion of 24bit RGB image.
  - Fixed exit code (0) when app successfully exits
  - Fixed infinitive loop when call to `wkernel_pfProcess` returned value other than -1, 0 or 1 (`wkernel_Run`)
  - Fixed copying full pixel data row from source mipmap in `std3D_AllocSystemTexture`. Originally was fixed to 16 bpp row.
  - (`JonesFile`) Fixed path buffer size to 128 chars, was 48 chars
  - (`JonesFile`) Fixed writing to file by using correct file write function in `JonesFile_FilePrintf`
  - Added bounds check for number of animating joints when loading keyframe from *.key file
  - Fixed a bug in sound compression where clipping of the audio waveform occurred
  - Fixed infinitive loop bug when voice subtitle contains too long word (`sithVoice_AddSubtitle`)

  - Fixed accessing null pointer in `sithWhip_Reset` when `sithCamera` is already closed.  
    Fixed checking for null `sithWeapon_SendMessageAim` before calling  
    function`sithWeapon_IsLocalPlayerUnableToUseWeapon` in `sithWeapon_SendMessageAim` functions.  
    This 2 fixes solve the game crash when player is aiming with whip and exits the game/program
    at the same time.

  - Fixed game crash when player aims with the whip and exits the game simultaneously by:
    - Addressing a null pointer access in `sithWhip_Reset` when `sithCamera` is already closed.
    - Adding a null check for `sithWeapon_SendMessageAim` before calling `sithWeapon_IsLocalPlayerUnableToUseWeapon`.
    - Added high poly checkbox option to developer dialog (`High poly objects`)
    - Added high poly checkbox option to gameplay options (`High poly objects`)

### Game play:
- Fixed the direction of fired projectiles for 2-hand-held weapons by setting the initial direction.  
  This should resolve the issue of random crashes when firing the weapon, as the projectile will now be correctly aimed at the target.
- Fixed damaging player when game runs at > 40 FPS and Taklit's part, Azerim's part or tool from beyond runs out of energy (`sithPlayer_Update`)
- Fixed rendering file list in load game dialog
- Fixed DPI scaling of dialogs
- Fixed bug where controls could become unresponsive when climbing down a whip and pressing the jump-off key simultaneously.
- Enabled HD 3D models by default

### Display & Render:
  - Added "simulated" VSync in window mode
  - Added resolution cap to HD resolutions since Direct3D3 doesn't support higher resolutions
  - Fixed raster to use correct vertices buffer when in vertex only mode
  - Fixed clearing raster vertex buffer on startup
  - Added option to disable VSync in `stdDisplay_Update`
  - Fixed rendering of sprite when fog is globally disabled
  - Fixed rendering of polyline when fog is globally disabled
  - Fixed projecting Z coordinate when camera aspect ratio != 1.0  
    In addition, this resolves rendering of ceiling sky when aspect ratio != 1.0
  - Fixed screen space projection by correctly applying camera aspect ratio
  - Fixed restoring backbuffer when surface is lost on surface lock
  - Removed hardcoded 16 BPP resolution limitation; the game now defaults to the resolution stored in settings.
  - Removed hardcoded 16 BPP startup resolution limitation when initializing developer dialog allowing for the resolution stored in settings to be selected by default.
  - Set 32 BPP resolution as default
  - Fixed using 32 BPP resolution stored in settings

### HUD:
  - (`JonesDialog`) Fixed rendering game background when system dialog box is open
  - Removed help menu option
  - Fixed inventory menu position for wide screen resolutions
  - Fixed inventory menu scaling when aspect ratio is other than 4:3
  - Fixed inventory changed animation position and scaling when aspect ratio is other than 4:3
  - Fixed scaling of HUD health & endurance indicators for screen resolutions other than 4:3
  - Fixed possible menu close lock and game freeze due to uninitialized icon translation move rate.
  - Fixed start icon transition when closing menu.  
    Properly initialized move rate for the first transitioning icon, preventing its immediate disappearance.
  - Fixed bug in inventory item change render function (`JonesHud_RenderInventoryItemChange`) which used  
    an unbounded yaw value (yaw > 360°) in the calculation of the item's yaw angle. This could lead to  
    an infinite loop and prevent the menu from opening.
  - Fixed rotation bug for selected inventory item (`JonesHud_UpdateItem`).  
    The yaw added to delta yaw was not bounded to 360 degrees, which could lead to incorrect rotation of the item.
  - Fixed rendering end credits on different screen resolutions
  - Fixed fadeout of credits theme music
  - Increased credits fadeout to 2 sec
