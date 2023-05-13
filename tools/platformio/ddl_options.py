# defines for all available ddl drivers
# can be extracted from the (stock) ddl_config.h using 
# the following regex: "#define\s+(DDL_[A-Z0-9_]+_ENABLE)" (remove IGC and UTILITY)
DDL_DEFINES = [
 "DDL_PRINT_ENABLE",
 "DDL_ADC_ENABLE",
 "DDL_AES_ENABLE",
 "DDL_CAN_ENABLE",
 "DDL_CLK_ENABLE",
 "DDL_CMP_ENABLE",
 "DDL_CRC_ENABLE",
 "DDL_DCU_ENABLE",
 "DDL_DMAC_ENABLE",
 "DDL_EFM_ENABLE",
 "DDL_EMB_ENABLE",
 "DDL_EVENT_PORT_ENABLE",
 "DDL_EXINT_NMI_SWI_ENABLE",
 "DDL_GPIO_ENABLE",
 "DDL_HASH_ENABLE",
 "DDL_I2C_ENABLE",
 "DDL_I2S_ENABLE",
 "DDL_INTERRUPTS_ENABLE",
 "DDL_INTERRUPTS_SHARE_ENABLE",
 "DDL_KEYSCAN_ENABLE",
 "DDL_MPU_ENABLE",
 "DDL_OTS_ENABLE",
 "DDL_PWC_ENABLE",
 "DDL_QSPI_ENABLE",
 "DDL_RMU_ENABLE",
 "DDL_RTC_ENABLE",
 "DDL_SDIOC_ENABLE",
 "DDL_SPI_ENABLE",
 "DDL_SRAM_ENABLE",
 "DDL_SWDT_ENABLE",
 "DDL_TIMER0_ENABLE",
 "DDL_TIMER4_CNT_ENABLE",
 "DDL_TIMER4_EMB_ENABLE",
 "DDL_TIMER4_OCO_ENABLE",
 "DDL_TIMER4_PWM_ENABLE",
 "DDL_TIMER4_SEVT_ENABLE",
 "DDL_TIMER6_ENABLE",
 "DDL_TIMERA_ENABLE",
 "DDL_TRNG_ENABLE",
 "DDL_USART_ENABLE",
 "DDL_USBFS_ENABLE",
 "DDL_WDT_ENABLE",
]

# special cases for DDL to board option conversion
# because a) pio really does not like these otherwise,
# or b) the option name is not the same as the define
DDL_DEFINES_SPECIAL = [
    ("DDL_INTERRUPTS_SHARE_ENABLE", "build.ddl.interrupts_share"),
    ("DDL_EVENT_PORT_ENABLE", "build.ddl.event_port"),
    ("DDL_EXINT_NMI_SWI_ENABLE", "build.ddl.exint"),
]

# ddl enable/disable definitions
# must be defined in ddl_config.h
DDL_ON = "DDL_ON"
DDL_OFF = "DDL_OFF"

def define_to_board_option(define_str: str) -> str:
    """
    Converts a DDL define to a option in the board manifest.
    e.g. "DDL_ADC_ENABLE" -> "build.ddl.adc"
    or "DDL_TIMER4_CNT_ENABLE" -> "build.ddl.timer4.cnt"

    :param define_str: The DDL define to convert, e.g. "DDL_ADC_ENABLE"
    :return: The converted option, e.g. "build.ddl.adc"
    """
   
    # handle special cases
    for special_case in DDL_DEFINES_SPECIAL:
        if special_case[0] == define_str:
            return special_case[1]

    # normal case
    define_str = define_str.lower().split("_enable")[0]
    define_str = define_str.replace("_", ".")
    return "build." + define_str


def get_ddl_configuration_defines(board) -> list:
    """
    Resolves the defines needed for the selected DDL configuration from the board manifest.
    It does this by checking if the board manifest has the option "build.ddl.<driver>" set to "true".

    :param board: The board manifest object
    :return: a list of defines that should be added to the 'CPPDEFINES' variable
    """

    cpp_defines = []

    # get all the keys from the board manifest, append to config defines list
    for ddl_define in DDL_DEFINES:
        option_name = define_to_board_option(ddl_define)
        if board.get(option_name, "false") == "true":
            print(f"Driver Library '{ddl_define}' enabled")
            cpp_defines.append((ddl_define, DDL_ON))
        else:
            cpp_defines.append((ddl_define, DDL_OFF))
    
    return cpp_defines
