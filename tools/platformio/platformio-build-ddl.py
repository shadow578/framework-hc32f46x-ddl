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


# get a list from the board manifest
def get_manifest_list(key: str) -> list[str]:
    # get raw list
    l =  board.get(key, "").split("\n")

    # strip lines & remove empty lines
    l = [x.strip() for x in l if x.strip() != ""]
    return l

# get extra build flags from the board manifest
# pio only allows adding flags to all languages, not just c/c++/asm
# so we have to do it manually...
extra_common_gcc_flags = get_manifest_list("build.flags.common")
extra_c_flags = get_manifest_list("build.flags.c")
extra_cxx_flags = get_manifest_list("build.flags.cpp")
extra_asm_flags = get_manifest_list("build.flags.asm")
extra_link_flags = get_manifest_list("build.flags.link")

# prepare basic compile environment
# as far as i understood, the flags in 'CCFLAGS' should be added to all the other flags, but it doesn't seem to work that way...
# as such, i'm adding them to all the other flags manually, which is kinda hacky, but seems to work just fine
common_gcc_flags = extra_common_gcc_flags + [
    f"-mcpu={board.get('build.cpu')}",
	"-mthumb",
	"-mthumb-interwork",
	"-Os",
	"-fmessage-length=0",
	"-fsigned-char",
	"-ffunction-sections",
	"-fdata-sections",
	"-Wall",
	"-g3"
]

# build flags for all languages
env.Append(
    # common gcc (?)
    CCFLAGS=common_gcc_flags + [],

    # c
    CFLAGS=common_gcc_flags + extra_c_flags + [
        "-std=gnu17"
    ],
    
    # c++
    CXXFLAGS=common_gcc_flags + extra_cxx_flags + [
        "-std=gnu++17"
    ],

    # asm
    ASFLAGS=common_gcc_flags + extra_asm_flags + [
        "-x", "assembler-with-cpp"
    ],

    # linker
    LINKFLAGS=common_gcc_flags + extra_link_flags + [
        ("-Wl,--default-script", board.get("build.ldscript", join(FRAMEWORK_DIR, "ld", "hc32f46x_param.ld"))),
        #"-Wl,--print-memory-usage",
        "--specs=nano.specs",
        "--specs=nosys.specs",
        "-Wl,--gc-sections,--relax",
        "-Wl,--check-sections",
        "-Wl,--entry=Reset_Handler",
        "-Wl,--unresolved-symbols=report-all",
        "-Wl,--warn-common",
        f"-Wl,-Map,{join('$BUILD_DIR', '${PROGNAME}.map')}"
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
	    "ARM_MATH_ROUNDING",
        ('__SOURCE_FILE_NAME__', '\\"${SOURCE.file}\\"') # add the source file name to the defines, so it can be used in the code
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


# size regexps, depend on the linker script and thus defined here
env.Replace(
    # note: .data is included in both, as it's copied from flash to ram
    # this yields different sizes between ld and pio, but flash size matches the final binary size (which is what we want)
    SIZEPROGREGEXP=r"^(?:\.vectors|\.icg_sec|\.rodata|\.text|\.ARM.extab|\.ARM.exidx|\.preinit_array|\.init_array|\.fini_array|\.data)\s+(\d+).*",
    SIZEDATAREGEXP=r"^(?:\.data|\.bss)\s+(\d+).*",
)


# resolve and append linker script parameters to ld command line
# parameters are passed into the linker script via the --defsym flag, as symbols
# this allows the linker script to be generic, and the parameters to be passed in using the board manifest
# however, this could cause issues as it's not *exactly* what this flag is for, but it should work for a while...
def setup_ld_params():
    # get the parameters from the board manifest
    flash_start = board.get("build.ld_args.flash_start", "0x0")
    flash_size = board.get("build.ld_args.flash_size", "256K")

    # parse flash start (hex, convert to int)
    flash_start = int(flash_start, 16)

    # parse flash size (K or M suffix, convert to bytes)
    if flash_size[-1] == "K":
        flash_size = int(flash_size[:-1]) * 1024
    elif flash_size[-1] == "M":
        flash_size = int(flash_size[:-1]) * 1024 * 1024
    else:
        flash_size = int(flash_size)

    # calculate and check usable flash size
    flash_size_usable = flash_size - flash_start
    if flash_size_usable <= 0:
        raise ValueError("usable flash size is less than or equal to 0. check flash_start and flash_size in the board manifest")

    # add compile flags to the build environment
    print(f"linker parameters: FLASH_START={flash_start}, FLASH_SIZE={flash_size}; usable flash size: {flash_size_usable}")
    env.Append(
        # linker script parameters
        LINKFLAGS=[
            f"-Wl,--defsym=FLASH_START={flash_start}",
            f"-Wl,--defsym=FLASH_SIZE={flash_size}",
        ],

        # c/c++ defines
        CPPDEFINES=[
            f"LD_FLASH_START={flash_start}",
            f"LD_FLASH_SIZE={flash_size}",
        ]
    )

    # correct maximum_size parameter used by platformio
    # to equal FLASH_SIZE - FLASH_START
    board._manifest["upload"]["maximum_size"] = flash_size_usable
setup_ld_params()

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
