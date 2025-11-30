#ifndef JONESRETICLE_H
#define JONESRETICLE_H

// Lock-On Aim Reticle
// Inspired by N64 port and based on Zelda OOT's target reticle system
// Renders 4 triangular arrows pointing inward at the target

#include <j3dcore/j3d.h>

#include <rdroid/types.h>
#include <sith/types.h>

J3D_EXTERN_C_START

void JonesReticle_Open(void);
void JonesReticle_Close(void);

/**
 * Enables or disables reticle system.
 * When reticle system is disabled the target tracing won't update and nothing will be rendered.
 *
 * @param bEnable - true / false
 */
void J3DAPI JonesReticle_Enable(bool bEnable);
bool JonesReticle_IsEnabled(void);

/**
 * Updates reticle state:
 * - Locks/Unlocks reticle target based on player's current target
 * - Calculates new reticle position
 * - Updates reticle animation according to `deltaTime`
 *
 * @param deltaTime
 */
void J3DAPI JonesReticle_Update(float deltaTime);

//!< Renders reticle to screen
void JonesReticle_Render(void);

/**
 * Checks if reticle animation is paused
 * @return true if paused, otherwise false
 */
bool JonesReticle_IsPaused(void);

//!< Pauses reticle animation
void JonesReticle_Pause(void);

//!< Resumes reticle animation
void JonesReticle_Resume(void);

J3D_EXTERN_C_END

#endif // JONESRETICLE_H
