#pragma once

#include <cstdint>

// Vid = Vendor Id, Pid = ProductId
#define AIR_VID 0x3318
#define AIR_PID 0x0424
#define AIR_2_PID 0x0428
#define AIR_2_PRO_PID 0x0432

uint16_t getConnectedProductId();