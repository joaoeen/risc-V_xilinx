--!
--! Copyright 2018 Sergey Khabarov, sergeykhbr@gmail.com
--!
--! Licensed under the Apache License, Version 2.0 (the "License");
--! you may not use this file except in compliance with the License.
--! You may obtain a copy of the License at
--!
--!     http://www.apache.org/licenses/LICENSE-2.0
--!
--! Unless required by applicable law or agreed to in writing, software
--! distributed under the License is distributed on an "AS IS" BASIS,
--! WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
--! See the License for the specific language governing permissions and
--! limitations under the License.
--!

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library techmap;
use techmap.gencomp.all;

package config_target is
-- Technology and synthesis options
  constant CFG_FABTECH : integer := zynq7000;
  constant CFG_MEMTECH : integer := zynq7000;
  constant CFG_PADTECH : integer := zynq7000;
  constant CFG_JTAGTECH : integer := zynq7000;

  constant CFG_TOPDIR : string := "../../../";
  
  --! @brief   Disable/Enable River CPU instance.
  --! @details When enabled platform will instantiate processor named as
  --!          "RIVER" entirely written on VHDL. 
  --!          Otherwise "Rocket" will be used (developed by Berkley
  --!          team).
  --! @warning DSU available only for \e "RIVER" processor.
  constant CFG_COMMON_RIVER_CPU_ENABLE : boolean := true;

  --! @brief   Dual-core configuration enabling
  --! @details This config parameter used only with CPU River
  constant CFG_COMMON_DUAL_CORE_ENABLE : boolean := false;

  --! @brief   HEX-image for the initialization of the Boot ROM.
  --! @details This file is used by \e inferred ROM implementation.
  constant CFG_SIM_BOOTROM_HEX : string := 
              CFG_TOPDIR & "examples/boot/linuxbuild/bin/bootimage.hex";

  --! @brief   HEX-image for the initialization of the FwImage ROM.
  --! @details This file is used by \e inferred ROM implementation.
  constant CFG_SIM_FWIMAGE_HEX : string := 
                CFG_TOPDIR & "examples/zephyr/gcc711/zephyr.hex";
                

  --! @brief Hardware SoC Identificator.
  --!
  --! @details Read Only unique platform identificator that could be
  --!          read by firmware from the Plug'n'Play support module.
  constant CFG_HW_ID : std_logic_vector(31 downto 0) := X"20190524";

  --! @brief Enabling Ethernet MAC interface.
  --! @details By default MAC module enables support of the debug feature EDCL.
  constant CFG_ETHERNET_ENABLE : boolean := false;

  --! @brief Enable/Disable Debug Unit 
  constant CFG_DSU_ENABLE : boolean := true;

end;
