"""
HC32F46x DDL
Device Driver Libraries for the HC32F46x series of microcontrollers
"""
import os
import re
from os.path import isdir, join

from SCons.Script import DefaultEnvironment

from ddl_options import get_ddl_configuration_defines


# get the environment
env = DefaultEnvironment()
platform = env.PioPlatform()
board = env.BoardConfig()
build_core = board.get("build.core", "")


# ensure framework is installed
FRAMEWORK_DIR = platform.get_package_dir("framework-hc32f46x-ddl")
DDL_DIR = join(FRAMEWORK_DIR, "cores", "ddl")
assert isdir(FRAMEWORK_DIR)
assert isdir(DDL_DIR)


# find and print ddl version from version.txt
def get_ddl_version(version_file: str) -> str:
    with open(version_file, "r") as f:
        for line in f.readlines():
            if re.match(r"\d+\.\d+\.\d+", line):
                return line.split()[0]
    
    return "unknown"
ddl_version = get_ddl_version(join(DDL_DIR, "version.txt"))
print(f"Using DDL version {ddl_version}")


# prepare basic compile environment
# as far as i understood, the flags in 'CCFLAGS' should be added to all the other flags, but it doesn't seem to work that way...
# as such, i'm adding them to all the other flags manually, which is kinda hacky, but seems to work just fine
common_gcc_flags = [
    "-mcpu=cortex-m4",
	"-mthumb",
	"-mthumb-interwork",
	"-Os",
	"-fmessage-length=0",
	"-fsigned-char",
	"-ffunction-sections",
	"-fdata-sections",
	"-Wall",
	"-g"
]
env.Append(
    # common gcc (?)
    CCFLAGS=common_gcc_flags + [],

    # c
    CFLAGS=common_gcc_flags + [
        "-std=gnu17"
    ],
    
    # c++
    CXXFLAGS=common_gcc_flags + [
        "-std=gnu++17",
        "-fabi-version=0"
    ],

    # asm
    ASFLAGS=common_gcc_flags + [
        "-x", "assembler-with-cpp"
    ],

    # linker
    LINKFLAGS=common_gcc_flags + [
        "-Xlinker",
        "--gc-sections",
        ("-Wl,--default-script", board.get("build.ldscript", join(FRAMEWORK_DIR, "ld", "hc32f46x_param.ld"))),
        #"-Wl,--no-warn-rwx-segment", # introduced in gcc 12, and thus not supported by the version platformio uses
        "-Wl,--print-memory-usage",
        "--specs=nano.specs",
        "--specs=nosys.specs",
    ],

    # c/c++ defines
    CPPDEFINES=[
        "HC32F460",
        "USE_DEVICE_DRIVER_LIB",
        "__TARGET_FPU_VFP",
	    "__FPU_PRESENT=1",
	    "_MPU_PRESENT=1",
	    "ARM_MATH_CM4",
	    "ARM_MATH_MATRIX_CHECK",
	    "ARM_MATH_ROUNDING"
    ],

    # c/c++ include paths
    # all directories in core/ddl are added to the include path
    CPPPATH=[
        DDL_DIR,
        join(DDL_DIR, "addon"),
        join(DDL_DIR, "cmsis"),
        join(DDL_DIR, "common"),
        join(DDL_DIR, "compat"),
        join(DDL_DIR, "library", "inc"),
        join(DDL_DIR, "startup"),
    ]
)


# resolve and append linker script parameters to ld command line
# parameters are passed into the linker script via the --defsym flag, as symbols
# this allows the linker script to be generic, and the parameters to be passed in using the board manifest
# however, this could cause issues as it's not *exactly* what this flag is for, but it should work for a while...
def get_ld_params():
    # define keys to symbol def names
    ld_args = []
    ld_arg_keys_to_def_mapping = {
        "build.ld_args.flash_start": "FLASH_START",
        "build.ld_args.flash_size": "FLASH_SIZE",
    }

    # get all the keys from the board manifest, append to arguments list
    for key, def_name in ld_arg_keys_to_def_mapping.items():
        if key in board:
            param_value = board.get(key)
            print(f"linker script param {def_name} = {param_value}")
            ld_args.append(f"-Wl,--defsym={def_name}={param_value}")
        
    return ld_args
env.Append(LINKFLAGS=get_ld_params())


# resolve and add ddl configuration to defines
env.Append(CPPDEFINES=get_ddl_configuration_defines(board))


# resolve middleware configuration and build
# middleware configuration is defined in the board manifest, just like ddl configuration
# however, middleware is not just a list of defines, but instead a change in the include paths and source files
MW_DIR = join(FRAMEWORK_DIR, "middleware")
if isdir(MW_DIR):
    # find all available middleware, by folder name
    for mw in [f.name for f in os.scandir(MW_DIR) if f.is_dir()]: # [sd_card, w25q]
        # check if middleware is enabled in the board manifest
        if board.get("build.mw." + mw, "false") == "true":
            print(f"Middleware '{mw}' enabled")

            # add middleware include paths to the build
            env.Append(CPPPATH=[join(MW_DIR, mw, "inc")])

            # build middleware
            env.BuildSources(join("$BUILD_DIR", "FrameworkDDL_" + mw), join(MW_DIR, mw, "src"))

# build ddl core
env.BuildSources(join("$BUILD_DIR", "FrameworkDDL"), DDL_DIR)
