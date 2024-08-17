#ifndef SITH_SITHPLAYER_H
#define SITH_SITHPLAYER_H
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <sith/Main/sithMain.h>
#include <sith/RTI/addresses.h>
#include <std/types.h>

J3D_EXTERN_C_START

#define sithPlayer_g_bPlayerInPor J3D_DECL_FAR_VAR(sithPlayer_g_bPlayerInPor, int)
// extern int sithPlayer_g_bPlayerInPor ;

#define sithPlayer_g_impFireType J3D_DECL_FAR_VAR(sithPlayer_g_impFireType, int)
// extern int sithPlayer_g_impFireType ;

#define sithPlayer_g_playerNum J3D_DECL_FAR_VAR(sithPlayer_g_playerNum, size_t)
// extern size_t sithPlayer_g_playerNum;

#define sithPlayer_g_numPlayers J3D_DECL_FAR_VAR(sithPlayer_g_numPlayers, size_t)
// extern size_t sithPlayer_g_numPlayers;

#define sithPlayer_g_pLocalPlayerThing J3D_DECL_FAR_VAR(sithPlayer_g_pLocalPlayerThing, SithThing*)
// extern SithThing *sithPlayer_g_pLocalPlayerThing;

#define sithPlayer_g_pLocalPlayer J3D_DECL_FAR_VAR(sithPlayer_g_pLocalPlayer, SithPlayer*)
// extern SithPlayer *sithPlayer_g_pLocalPlayer;

#define sithPlayer_g_bPlayerInvulnerable J3D_DECL_FAR_VAR(sithPlayer_g_bPlayerInvulnerable, int)
// extern int sithPlayer_g_bPlayerInvulnerable;

#define sithPlayer_g_bInAetheriumSector J3D_DECL_FAR_VAR(sithPlayer_g_bInAetheriumSector, int)
// extern int sithPlayer_g_bInAetheriumSector;

#define sithPlayer_g_bGuybrush J3D_DECL_FAR_VAR(sithPlayer_g_bGuybrush, int)
// extern int sithPlayer_g_bGuybrush;

#define sithPlayer_g_curLevelNum J3D_DECL_FAR_VAR(sithPlayer_g_curLevelNum, int)
// extern int sithPlayer_g_curLevelNum;

#define sithPlayer_g_bBonusMapBought J3D_DECL_FAR_VAR(sithPlayer_g_bBonusMapBought, int)
// extern int sithPlayer_g_bBonusMapBought;

#define sithPlayer_g_aPlayers J3D_DECL_FAR_ARRAYVAR(sithPlayer_g_aPlayers, SithPlayer(*)[24])
// extern SithPlayer sithPlayer_g_aPlayers[24];

#define sithPlayer_g_impState J3D_DECL_FAR_VAR(sithPlayer_g_impState, float)
// extern float sithPlayer_g_impState;

void J3DAPI sithPlayer_Open(const wchar_t* awName);
void sithPlayer_Close();
const wchar_t* J3DAPI sithPlayer_GetLocalPlayerName();
void J3DAPI sithPlayer_PlacePlayers(SithWorld* pWorld);
void J3DAPI sithPlayer_HidePlayer(unsigned int playerNum);
int J3DAPI sithPlayer_ShowPlayer(size_t playerNum, DPID id);
void J3DAPI sithPlayer_SetLocalPlayer(unsigned int playerNum);
void J3DAPI sithPlayer_Reset(unsigned int playerNum);
void J3DAPI sithPlayer_Update(SithPlayer* pPlayer, float secDetaTime);
void J3DAPI sithPlayer_NewPlayer(SithThing* pPlayer);
int J3DAPI sithPlayer_GetPlayerNum(DPID playerId);
void J3DAPI sithPlayer_PlayerKilledAction(SithThing* pPlayerThing, const SithThing* pSrcThing);
void J3DAPI sithPlayer_KillPlayer(SithThing* pPlayerThing);
int J3DAPI sithPlayer_GetThingPlayerNum(const SithThing* pThing);
int J3DAPI sithPlayer_ToggleGuybrush();
void J3DAPI sithPlayer_IMPStartFiring(int fireType);
void J3DAPI sithPlayer_IMPEndFiring(int fireType);

// Helper hooking functions
void sithPlayer_InstallHooks(void);
void sithPlayer_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // SITH_SITHPLAYER_H
