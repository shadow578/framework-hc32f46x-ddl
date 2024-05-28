# Files Mapping

the ddl files provided by HDSC (hc32f460_ddl_Revx.y.z.zip) are mapped to the files in this core as follows:

| core file                   | ddl package file                                                                                              |
| --------------------------- | ------------------------------------------------------------------------------------------------------------- |
| `cores/ddl/addon/*`         | -                                                                                                             |
| `cores/ddl/cmsis/*`         | `drivers/cmsis/Include/*`                                                                                     |
| `cores/ddl/common/*`        | `drivers/cmsis/Device/HDSC/hc32f4xx/Include/*`, `drivers/cmsis/Device/HDSC/hc32f4xx/Source/system_hc32f460.c` |
| `cores/ddl/compat/*`        | -                                                                                                             |
| `cores/ddl/library/*`       | `drivers/hc32_II_driver/*`                                                                                    |
| `middleware/sd_card/*`      | `/projects/ev_hc32f460_lqfp100_v2/examples/sdioc/sdioc_sd/source/sd.*`                                        |
| `cores/ddl/hc32f4xx_conf.h` | based on `projects/ev_hc32f460_lqfp100_v2/template/source/hc32f4xx_conf.h`                                    |
| `cores/ddl/version.txt`     | -                                                                                                             |
| `ld/hc32f46x_param.ld`      | parameterized version of `drivers/cmsis/Device/HDSC/hc32f4xx/Source/GCC/linker/HC32F460xC.ld`                 |
