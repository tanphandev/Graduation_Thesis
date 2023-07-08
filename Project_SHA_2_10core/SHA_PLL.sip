set_global_assignment -entity "SHA_PLL" -library "lib_SHA_PLL" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "SHA_PLL" -library "lib_SHA_PLL" -name IP_TOOL_VERSION "18.1"
set_global_assignment -entity "SHA_PLL" -library "lib_SHA_PLL" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_SHA_PLL" -name SPD_FILE [file join $::quartus(sip_path) "SHA_PLL.spd"]

set_global_assignment -library "lib_SHA_PLL" -name MISC_FILE [file join $::quartus(sip_path) "SHA_PLL_sim/SHA_PLL.vo"]
