#ifndef JONES3D_JONESINVENTORY_H
#define JONES3D_JONESINVENTORY_H
#include <Jones3D/types.h>
#include <Jones3D/RTI/addresses.h>
#include <j3dcore/j3d.h>
#include <rdroid/types.h>
#include <sith/types.h>
#include <std/types.h>

J3D_EXTERN_C_START

int jonesInventory_Open(void);
int J3DAPI jonesInventory_Load(const char* pFilename);
void J3DAPI jonesInventory_Close();
int J3DAPI jonesInventory_ActivateItem(SithThing* pThing, int typeId);
int J3DAPI jonesInventory_UseItem(SithThing* pPlayer, unsigned int typeId);
int jonesInventory_ResetGameStatistics(void);
size_t jonesInventory_GetMaxDifficultyLevel(void);
void jonesInventory_UpdateSolvedHintsStatistics(void);
void J3DAPI jonesInventory_UpdateIQPoints(size_t difficulty);
int jonesInventory_GetTotalIQPoints(void);
void J3DAPI jonesInventory_AdvanceStatistics();
void jonesInventory_AdvanceFoundTreasuresStatistics();
void J3DAPI jonesInventory_UpdateGameTimeStatistics(unsigned int msecTime);
void J3DAPI jonesInventory_UpdateLevelStatisticTime(int elapsedSec, SithLevelStatistic* pLevelStats, unsigned int msecNewTime, int msecPreviousTime);
void jonesInventory_ResetStatisticsGameTime();

// Helper hooking functions
void jonesInventory_InstallHooks(void);
void jonesInventory_ResetGlobals(void);

J3D_EXTERN_C_END
#endif // JONES3D_JONESINVENTORY_H
