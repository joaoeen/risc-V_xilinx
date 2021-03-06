/*
 *  Copyright 2019 Sergey Khabarov, sergeykhbr@gmail.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <inttypes.h>
#include <string.h>
#include <axi_maps.h>
#include "fw_api.h"

static const uint64_t UNMAPPED_ADDRESS = 0x70000040;

void test_missaccess(void) {
    pnp_map *pnp = (pnp_map *)ADDR_NASTI_SLAVE_PNP;
    // clear register. it should be modified from exception handler
    pnp->fwdbg1 = 0;

    // Read unmapped address to some register (to avoid optimization)
    pnp->idt = *((uint64_t *)UNMAPPED_ADDRESS);

    if (pnp->fwdbg1 != UNMAPPED_ADDRESS) {
        printf_uart("rd_missaccess. .FAIL: %08x != %08x\r\n",
                    pnp->fwdbg1, UNMAPPED_ADDRESS);
    } else {
        printf_uart("%s", "rd_missaccess. .PASS\r\n");
    }

    // Test write miss access
    pnp->fwdbg1 = 0;
    *((uint64_t *)(UNMAPPED_ADDRESS + 8)) = 0x33445566;

    if (pnp->fwdbg1 != (UNMAPPED_ADDRESS+8)) {
        printf_uart("wr_missaccess. .FAIL: %08x != %08x\r\n",
                    pnp->fwdbg1, (UNMAPPED_ADDRESS+8));
    } else {
        printf_uart("%s", "wr_missaccess. .PASS\r\n");
    }
}
