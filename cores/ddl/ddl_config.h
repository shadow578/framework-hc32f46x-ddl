//
// builder configured ddl_config
// ddl options are enabled by adding a define to the compiler options (eg. -D DDL_ADC_ENABLE)
//

#ifndef __DDL_CONFIG_H__
#define __DDL_CONFIG_H__

//
// Driver Libraries (configured by board manifest)
//
#define DDL_ON 1u
#define DDL_OFF 0u

// ICG and UTILITY are always on
// they are required by some of the other drivers
// and it would be a pain to check if they are needed
#define DDL_ICG_ENABLE DDL_ON
#define DDL_UTILITY_ENABLE DDL_ON

// other drivers are configured in the build script
// see tools/platformio/ddl_options.py for details

//
// BSP board select
// required because the selection logic freaks out without it
//
#define BSP_NONE (0u)
#define BSP_EV_HC32F460_LQFP100_V1 (1u)
#define BSP_EV_HC32F460_LQFP100_V2 (2u)

#define BSP_EV_HC32F460 BSP_NONE
#endif // __DDL_CONFIG_H__
