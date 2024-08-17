#include "jonesInventory.h"
#include <j3dcore/j3dhook.h>
#include <Jones3D/RTI/symbols.h>

#define jonesInventory_pGameStatistics J3D_DECL_FAR_VAR(jonesInventory_pGameStatistics, SithGameStatistics*)
#define jonesInventory_msecStatisticsGameTime J3D_DECL_FAR_VAR(jonesInventory_msecStatisticsGameTime, unsigned int)

void jonesInventory_InstallHooks(void)
{
    // Uncomment only lines for functions that have full definition and doesn't call original function (non-thunk functions)

    // J3D_HOOKFUNC(jonesInventory_Open);
    // J3D_HOOKFUNC(jonesInventory_Load);
    // J3D_HOOKFUNC(jonesInventory_Close);
    // J3D_HOOKFUNC(jonesInventory_ActivateItem);
    // J3D_HOOKFUNC(jonesInventory_UseItem);
    // J3D_HOOKFUNC(jonesInventory_ResetGameStatistics);
    // J3D_HOOKFUNC(jonesInventory_GetMaxDifficultyLevel);
    // J3D_HOOKFUNC(jonesInventory_UpdateSolvedHintsStatistics);
    // J3D_HOOKFUNC(jonesInventory_UpdateIQPoints);
    // J3D_HOOKFUNC(jonesInventory_GetTotalIQPoints);
    // J3D_HOOKFUNC(jonesInventory_AdvanceStatistics);
    // J3D_HOOKFUNC(jonesInventory_AdvanceFoundTreasuresStatistics);
    // J3D_HOOKFUNC(jonesInventory_UpdateGameTimeStatistics);
    // J3D_HOOKFUNC(jonesInventory_UpdateLevelStatisticTime);
    // J3D_HOOKFUNC(jonesInventory_ResetStatisticsGameTime);
}

void jonesInventory_ResetGlobals(void)
{
    memset(&jonesInventory_pGameStatistics, 0, sizeof(jonesInventory_pGameStatistics));
    memset(&jonesInventory_msecStatisticsGameTime, 0, sizeof(jonesInventory_msecStatisticsGameTime));
}

int jonesInventory_Open(void)
{
    return J3D_TRAMPOLINE_CALL(jonesInventory_Open);
}

int J3DAPI jonesInventory_Load(const char* pFilename)
{
    return J3D_TRAMPOLINE_CALL(jonesInventory_Load, pFilename);
}

void J3DAPI jonesInventory_Close()
{
    J3D_TRAMPOLINE_CALL(jonesInventory_Close);
}

int J3DAPI jonesInventory_ActivateItem(SithThing* pThing, int typeId)
{
    return J3D_TRAMPOLINE_CALL(jonesInventory_ActivateItem, pThing, typeId);
}

int J3DAPI jonesInventory_UseItem(SithThing* pPlayer, unsigned int typeId)
{
    return J3D_TRAMPOLINE_CALL(jonesInventory_UseItem, pPlayer, typeId);
}

int J3DAPI jonesInventory_ResetGameStatistics()
{
    return J3D_TRAMPOLINE_CALL(jonesInventory_ResetGameStatistics);
}

int J3DAPI jonesInventory_GetMaxDifficultyLevel()
{
    return J3D_TRAMPOLINE_CALL(jonesInventory_GetMaxDifficultyLevel);
}

void jonesInventory_UpdateSolvedHintsStatistics(void)
{
    J3D_TRAMPOLINE_CALL(jonesInventory_UpdateSolvedHintsStatistics);
}

// Maybe this function updates IQ points
void J3DAPI jonesInventory_UpdateIQPoints(size_t difficulty)
{
    J3D_TRAMPOLINE_CALL(jonesInventory_UpdateIQPoints, difficulty);
}

int jonesInventory_GetTotalIQPoints(void)
{
    return J3D_TRAMPOLINE_CALL(jonesInventory_GetTotalIQPoints);
}

void J3DAPI jonesInventory_AdvanceStatistics()
{
    J3D_TRAMPOLINE_CALL(jonesInventory_AdvanceStatistics);
}

void jonesInventory_AdvanceFoundTreasuresStatistics()
{
    J3D_TRAMPOLINE_CALL(jonesInventory_AdvanceFoundTreasuresStatistics);
}

void J3DAPI jonesInventory_UpdateGameTimeStatistics(unsigned int msecTime)
{
    J3D_TRAMPOLINE_CALL(jonesInventory_UpdateGameTimeStatistics, msecTime);
}

void J3DAPI jonesInventory_UpdateLevelStatisticTime(int elapsedSec, SithLevelStatistic* pLevelStats, unsigned int msecNewTime, int msecPreviousTime)
{
    J3D_TRAMPOLINE_CALL(jonesInventory_UpdateLevelStatisticTime, elapsedSec, pLevelStats, msecNewTime, msecPreviousTime);
}

void jonesInventory_ResetStatisticsGameTime()
{
    J3D_TRAMPOLINE_CALL(jonesInventory_ResetStatisticsGameTime);
}
