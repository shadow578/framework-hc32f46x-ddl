"""
HC32F460 DDL
Device Driver Libraries for the HC32F460 series of microcontrollers
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
is_debug_build = "debug" in env.GetBuildType()

# ensure framework is installed correctly
FRAMEWORK_DIR = platform.get_package_dir("framework-hc32f46x-ddl")
DDL_DIR = join(FRAMEWORK_DIR, "cores", "ddl")
assert isdir(FRAMEWORK_DIR)
assert isdir(DDL_DIR)

def get_ld_args() -> dict:
    """
    Get linker script parameters from the board manifest

    :return: dict with flash_start, flash_size and boot_mode
    """

    # get parameters from board manifest
    flash_start = board.get("build.ld_args.flash_start", "0x0")
    flash_size = board.get("build.ld_args.flash_size", "256K")
    boot_mode = board.get("build.ld_args.boot_mode", "1")

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

    # correct maximum_size parameter used by platformio
    # to equal FLASH_SIZE - FLASH_START
    board._manifest["upload"]["maximum_size"] = flash_size_usable

    # parse boot mode
    # 0 / 1 / "primary" = primary boot mode
    # 2 / "secondary" = secondary boot mode
    if boot_mode in ["0", "1", "primary"]:
        boot_mode = 1
    elif boot_mode in ["2", "secondary"]:
        boot_mode = 2
    else:
        raise ValueError("boot_mode must be 0/1/'primary' or 2/'secondary'!")

    # boot_mode must be primary if flash_start is 0
    if flash_start == 0 and boot_mode != 1:
        raise ValueError("flash_start is 0, but boot_mode is not 1 (primary)! This is not allowed, as a bootloader is required to use primary boot mode!")

    # print linker parameters
    print(f"linker parameters: FLASH_START={flash_start}, FLASH_SIZE={flash_size}; BOOT_MODE={boot_mode}; usable flash size: {flash_size_usable}")
    return {
        flash_start: flash_start,
        flash_size: flash_size,
        boot_mode: boot_mode,
    }

def preprocess_ld_script():
    """
    Preprocess the linker script to allow c-style preprocessor directives. 
    also parses & adds linker script parameters from the board manifest
    
    :see: https://stackoverflow.com/a/35824964/13942493
    """

    # get linker script source
    # either from the board manifest, or the default one
    ld_script_source = board.get("build.ldscript", join(FRAMEWORK_DIR, "ld", "hc32f46x_param.ld"))

    # allow disabling preprocessing using board_build.ld_args.preprocess
    if board.get("build.ld_args.preprocess", "true") == "true":
        # preprocess the linker script
        # output will be written to $BUILD_DIR/PROGNAME.ld
        ld_script_target = join("$BUILD_DIR", "${PROGNAME}.ld")

        # prepare CPP defines
        flash_start, flash_size, boot_mode = get_ld_args()
        ld_args_defines = [
            f"LD_FLASH_START={flash_start}",
            f"LD_FLASH_SIZE={flash_size}",
            f"LD_BOOT_MODE={boot_mode}",
        ]

        # setup the preprocessing command
        ld_preprocess_args = [
            *[f"-D {d}" for d in ld_args_defines],
        ]
        ld_preprocess = env.Command(
            ld_script_target,
            ld_script_source,
            env.VerboseAction(
                f"$CC -C -P -x c -E $SOURCE -o $TARGET {' '.join(ld_preprocess_args)}",
                "Generating LD script $TARGET",
            )
        )

        # ensure the linker script is built before the program is linked
        # by adding it as a dependency to firmware.elf
        env.Depends("$BUILD_DIR/$PROGNAME$PROGSUFFIX", ld_preprocess)
        env.Replace(LDSCRIPT_PATH=ld_script_target)

        # add defines to the build environment so they can be used in c/c++ code as well
        env.Append(CPPDEFINES=ld_args_defines)
    else:
        # no preprocessing, just use the source file directly
        env.Replace(LDSCRIPT_PATH=ld_script_source)

# preprocess the linker script before starting the build
preprocess_ld_script()


def get_manifest_list(key: str) -> list[str]:
    """
    get a list of strings from the board manifest

    :param key: key in the board manifest
    :return: list of strings under that key
    """
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
common_gcc_flags = [
    f"-mcpu={board.get('build.cpu')}",
	"-mthumb",
	"-mthumb-interwork",
	"-Os",
	"-fmessage-length=0",
	"-fsigned-char",
	"-ffunction-sections",
	"-fdata-sections",
	"-Wall",

    # compile with full debug symbols if debug build
    "-g3" if is_debug_build else "",
] + extra_common_gcc_flags

# build flags for all languages
env.Append(
    # common gcc (?)
    CCFLAGS=common_gcc_flags,

    # c
    CFLAGS=common_gcc_flags + [
        "-std=gnu17"
    ] + extra_c_flags,
    
    # c++
    CXXFLAGS=common_gcc_flags + [
        "-std=gnu++17"
    ] + extra_cxx_flags,

    # asm
    ASFLAGS=common_gcc_flags + [
        "-x", "assembler-with-cpp"
    ] + extra_asm_flags,

    # linker
    LINKFLAGS=common_gcc_flags + [
        #"-Wl,--print-memory-usage",
        "--specs=nano.specs",
        "--specs=nosys.specs",
        "-Wl,--gc-sections,--relax",
        "-Wl,--check-sections",
        "-Wl,--unresolved-symbols=report-all",
        "-Wl,--warn-common",
        f"-Wl,-Map,{join('$BUILD_DIR', '${PROGNAME}.map')}"
    ] + extra_link_flags,

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
