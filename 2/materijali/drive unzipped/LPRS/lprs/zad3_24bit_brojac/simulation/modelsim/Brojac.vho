-- Copyright (C) 2019  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and any partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel FPGA IP License Agreement, or other applicable license
-- agreement, including, without limitation, that your use is for
-- the sole purpose of programming logic devices manufactured by
-- Intel and sold by Intel or its authorized distributors.  Please
-- refer to the applicable agreement for further details, at
-- https://fpgasoftware.intel.com/eula.

-- VENDOR "Altera"
-- PROGRAM "Quartus Prime"
-- VERSION "Version 19.1.0 Build 670 09/22/2019 SJ Lite Edition"

-- DATE "11/17/2022 11:30:15"

-- 
-- Device: Altera 10M16SAU169C8G Package UFBGA169
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY FIFTYFIVENM;
LIBRARY IEEE;
USE FIFTYFIVENM.FIFTYFIVENM_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	hard_block IS
    PORT (
	devoe : IN std_logic;
	devclrn : IN std_logic;
	devpor : IN std_logic
	);
END hard_block;

-- Design Ports Information
-- ~ALTERA_TMS~	=>  Location: PIN_G1,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_TCK~	=>  Location: PIN_G2,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_TDI~	=>  Location: PIN_F5,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_TDO~	=>  Location: PIN_F6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- ~ALTERA_CONFIG_SEL~	=>  Location: PIN_D7,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- ~ALTERA_nCONFIG~	=>  Location: PIN_E7,	 I/O Standard: 3.3 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_nSTATUS~	=>  Location: PIN_C4,	 I/O Standard: 3.3 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_CONF_DONE~	=>  Location: PIN_C5,	 I/O Standard: 3.3 V Schmitt Trigger,	 Current Strength: Default


ARCHITECTURE structure OF hard_block IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL \~ALTERA_TMS~~padout\ : std_logic;
SIGNAL \~ALTERA_TCK~~padout\ : std_logic;
SIGNAL \~ALTERA_TDI~~padout\ : std_logic;
SIGNAL \~ALTERA_CONFIG_SEL~~padout\ : std_logic;
SIGNAL \~ALTERA_nCONFIG~~padout\ : std_logic;
SIGNAL \~ALTERA_nSTATUS~~padout\ : std_logic;
SIGNAL \~ALTERA_CONF_DONE~~padout\ : std_logic;
SIGNAL \~ALTERA_TMS~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_TCK~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_TDI~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_CONFIG_SEL~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_nCONFIG~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_nSTATUS~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_CONF_DONE~~ibuf_o\ : std_logic;

BEGIN

ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
END structure;


LIBRARY ALTERA;
LIBRARY FIFTYFIVENM;
LIBRARY IEEE;
USE ALTERA.ALTERA_PRIMITIVES_COMPONENTS.ALL;
USE FIFTYFIVENM.FIFTYFIVENM_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	Brojac IS
    PORT (
	iRST : IN std_logic;
	iCLK : IN std_logic;
	iEN : IN std_logic;
	o7SEGM : OUT std_logic_vector(6 DOWNTO 0);
	oCNT : OUT std_logic_vector(23 DOWNTO 0)
	);
END Brojac;

-- Design Ports Information
-- o7SEGM[0]	=>  Location: PIN_L12,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- o7SEGM[1]	=>  Location: PIN_J2,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- o7SEGM[2]	=>  Location: PIN_J1,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- o7SEGM[3]	=>  Location: PIN_H4,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- o7SEGM[4]	=>  Location: PIN_H5,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- o7SEGM[5]	=>  Location: PIN_K10,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- o7SEGM[6]	=>  Location: PIN_H8,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[0]	=>  Location: PIN_N10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[1]	=>  Location: PIN_M7,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[2]	=>  Location: PIN_N12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[3]	=>  Location: PIN_N9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[4]	=>  Location: PIN_K6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[5]	=>  Location: PIN_J7,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[6]	=>  Location: PIN_J8,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[7]	=>  Location: PIN_K7,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[8]	=>  Location: PIN_M11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[9]	=>  Location: PIN_M9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[10]	=>  Location: PIN_J6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[11]	=>  Location: PIN_N11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[12]	=>  Location: PIN_M8,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[13]	=>  Location: PIN_M13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[14]	=>  Location: PIN_M12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[15]	=>  Location: PIN_L11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- oCNT[16]	=>  Location: PIN_A8,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[17]	=>  Location: PIN_A9,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[18]	=>  Location: PIN_A11,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[19]	=>  Location: PIN_A10,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[20]	=>  Location: PIN_B10,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[21]	=>  Location: PIN_C9,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[22]	=>  Location: PIN_C10,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- oCNT[23]	=>  Location: PIN_D8,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 8mA
-- iCLK	=>  Location: PIN_H6,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- iRST	=>  Location: PIN_F1,	 I/O Standard: 3.3 V Schmitt Trigger,	 Current Strength: Default
-- iEN	=>  Location: PIN_M3,	 I/O Standard: 3.3 V Schmitt Trigger,	 Current Strength: Default


ARCHITECTURE structure OF Brojac IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_iRST : std_logic;
SIGNAL ww_iCLK : std_logic;
SIGNAL ww_iEN : std_logic;
SIGNAL ww_o7SEGM : std_logic_vector(6 DOWNTO 0);
SIGNAL ww_oCNT : std_logic_vector(23 DOWNTO 0);
SIGNAL \~QUARTUS_CREATED_ADC1~_CHSEL_bus\ : std_logic_vector(4 DOWNTO 0);
SIGNAL \iCLK~inputclkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \~QUARTUS_CREATED_GND~I_combout\ : std_logic;
SIGNAL \~QUARTUS_CREATED_UNVM~~busy\ : std_logic;
SIGNAL \~QUARTUS_CREATED_ADC1~~eoc\ : std_logic;
SIGNAL \o7SEGM[0]~output_o\ : std_logic;
SIGNAL \o7SEGM[1]~output_o\ : std_logic;
SIGNAL \o7SEGM[2]~output_o\ : std_logic;
SIGNAL \o7SEGM[3]~output_o\ : std_logic;
SIGNAL \o7SEGM[4]~output_o\ : std_logic;
SIGNAL \o7SEGM[5]~output_o\ : std_logic;
SIGNAL \o7SEGM[6]~output_o\ : std_logic;
SIGNAL \oCNT[0]~output_o\ : std_logic;
SIGNAL \oCNT[1]~output_o\ : std_logic;
SIGNAL \oCNT[2]~output_o\ : std_logic;
SIGNAL \oCNT[3]~output_o\ : std_logic;
SIGNAL \oCNT[4]~output_o\ : std_logic;
SIGNAL \oCNT[5]~output_o\ : std_logic;
SIGNAL \oCNT[6]~output_o\ : std_logic;
SIGNAL \oCNT[7]~output_o\ : std_logic;
SIGNAL \oCNT[8]~output_o\ : std_logic;
SIGNAL \oCNT[9]~output_o\ : std_logic;
SIGNAL \oCNT[10]~output_o\ : std_logic;
SIGNAL \oCNT[11]~output_o\ : std_logic;
SIGNAL \oCNT[12]~output_o\ : std_logic;
SIGNAL \oCNT[13]~output_o\ : std_logic;
SIGNAL \oCNT[14]~output_o\ : std_logic;
SIGNAL \oCNT[15]~output_o\ : std_logic;
SIGNAL \oCNT[16]~output_o\ : std_logic;
SIGNAL \oCNT[17]~output_o\ : std_logic;
SIGNAL \oCNT[18]~output_o\ : std_logic;
SIGNAL \oCNT[19]~output_o\ : std_logic;
SIGNAL \oCNT[20]~output_o\ : std_logic;
SIGNAL \oCNT[21]~output_o\ : std_logic;
SIGNAL \oCNT[22]~output_o\ : std_logic;
SIGNAL \oCNT[23]~output_o\ : std_logic;
SIGNAL \iCLK~input_o\ : std_logic;
SIGNAL \iCLK~inputclkctrl_outclk\ : std_logic;
SIGNAL \Add0~0_combout\ : std_logic;
SIGNAL \Add0~11\ : std_logic;
SIGNAL \Add0~12_combout\ : std_logic;
SIGNAL \iRST~input_o\ : std_logic;
SIGNAL \iEN~input_o\ : std_logic;
SIGNAL \Add0~13\ : std_logic;
SIGNAL \Add0~14_combout\ : std_logic;
SIGNAL \Add0~15\ : std_logic;
SIGNAL \Add0~16_combout\ : std_logic;
SIGNAL \Add0~17\ : std_logic;
SIGNAL \Add0~18_combout\ : std_logic;
SIGNAL \Add0~19\ : std_logic;
SIGNAL \Add0~20_combout\ : std_logic;
SIGNAL \Add0~21\ : std_logic;
SIGNAL \Add0~22_combout\ : std_logic;
SIGNAL \Add0~23\ : std_logic;
SIGNAL \Add0~24_combout\ : std_logic;
SIGNAL \Equal0~3_combout\ : std_logic;
SIGNAL \Add0~25\ : std_logic;
SIGNAL \Add0~26_combout\ : std_logic;
SIGNAL \Add0~27\ : std_logic;
SIGNAL \Add0~28_combout\ : std_logic;
SIGNAL \Add0~29\ : std_logic;
SIGNAL \Add0~30_combout\ : std_logic;
SIGNAL \Add0~31\ : std_logic;
SIGNAL \Add0~32_combout\ : std_logic;
SIGNAL \Add0~33\ : std_logic;
SIGNAL \Add0~34_combout\ : std_logic;
SIGNAL \Add0~35\ : std_logic;
SIGNAL \Add0~36_combout\ : std_logic;
SIGNAL \Add0~37\ : std_logic;
SIGNAL \Add0~38_combout\ : std_logic;
SIGNAL \Add0~39\ : std_logic;
SIGNAL \Add0~40_combout\ : std_logic;
SIGNAL \Equal0~1_combout\ : std_logic;
SIGNAL \Equal0~2_combout\ : std_logic;
SIGNAL \Add0~41\ : std_logic;
SIGNAL \Add0~42_combout\ : std_logic;
SIGNAL \Add0~43\ : std_logic;
SIGNAL \Add0~44_combout\ : std_logic;
SIGNAL \Add0~45\ : std_logic;
SIGNAL \Add0~46_combout\ : std_logic;
SIGNAL \Equal0~0_combout\ : std_logic;
SIGNAL \Equal0~4_combout\ : std_logic;
SIGNAL \Add0~1\ : std_logic;
SIGNAL \Add0~2_combout\ : std_logic;
SIGNAL \sCNT~1_combout\ : std_logic;
SIGNAL \Add0~3\ : std_logic;
SIGNAL \Add0~4_combout\ : std_logic;
SIGNAL \Add0~5\ : std_logic;
SIGNAL \Add0~6_combout\ : std_logic;
SIGNAL \Equal0~6_combout\ : std_logic;
SIGNAL \Add0~7\ : std_logic;
SIGNAL \Add0~8_combout\ : std_logic;
SIGNAL \sCNT~2_combout\ : std_logic;
SIGNAL \Add0~9\ : std_logic;
SIGNAL \Add0~10_combout\ : std_logic;
SIGNAL \Equal0~5_combout\ : std_logic;
SIGNAL \sCNT~0_combout\ : std_logic;
SIGNAL sCNT : std_logic_vector(23 DOWNTO 0);
SIGNAL \ALT_INV_iRST~input_o\ : std_logic;

COMPONENT hard_block
    PORT (
	devoe : IN std_logic;
	devclrn : IN std_logic;
	devpor : IN std_logic);
END COMPONENT;

BEGIN

ww_iRST <= iRST;
ww_iCLK <= iCLK;
ww_iEN <= iEN;
o7SEGM <= ww_o7SEGM;
oCNT <= ww_oCNT;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\~QUARTUS_CREATED_ADC1~_CHSEL_bus\ <= (\~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\);

\iCLK~inputclkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \iCLK~input_o\);
\ALT_INV_iRST~input_o\ <= NOT \iRST~input_o\;
auto_generated_inst : hard_block
PORT MAP (
	devoe => ww_devoe,
	devclrn => ww_devclrn,
	devpor => ww_devpor);

-- Location: LCCOMB_X26_Y27_N28
\~QUARTUS_CREATED_GND~I\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \~QUARTUS_CREATED_GND~I_combout\ = GND

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	combout => \~QUARTUS_CREATED_GND~I_combout\);

-- Location: IOOBUF_X50_Y2_N2
\o7SEGM[0]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \o7SEGM[0]~output_o\);

-- Location: IOOBUF_X0_Y9_N9
\o7SEGM[1]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \o7SEGM[1]~output_o\);

-- Location: IOOBUF_X0_Y9_N2
\o7SEGM[2]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \o7SEGM[2]~output_o\);

-- Location: IOOBUF_X0_Y8_N23
\o7SEGM[3]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \o7SEGM[3]~output_o\);

-- Location: IOOBUF_X0_Y8_N16
\o7SEGM[4]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \o7SEGM[4]~output_o\);

-- Location: IOOBUF_X50_Y2_N23
\o7SEGM[5]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \o7SEGM[5]~output_o\);

-- Location: IOOBUF_X50_Y11_N16
\o7SEGM[6]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => VCC,
	devoe => ww_devoe,
	o => \o7SEGM[6]~output_o\);

-- Location: IOOBUF_X16_Y0_N2
\oCNT[0]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(0),
	devoe => ww_devoe,
	o => \oCNT[0]~output_o\);

-- Location: IOOBUF_X8_Y0_N9
\oCNT[1]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(1),
	devoe => ww_devoe,
	o => \oCNT[1]~output_o\);

-- Location: IOOBUF_X16_Y0_N23
\oCNT[2]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(2),
	devoe => ww_devoe,
	o => \oCNT[2]~output_o\);

-- Location: IOOBUF_X19_Y0_N30
\oCNT[3]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(3),
	devoe => ww_devoe,
	o => \oCNT[3]~output_o\);

-- Location: IOOBUF_X14_Y0_N2
\oCNT[4]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(4),
	devoe => ww_devoe,
	o => \oCNT[4]~output_o\);

-- Location: IOOBUF_X16_Y0_N16
\oCNT[5]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(5),
	devoe => ww_devoe,
	o => \oCNT[5]~output_o\);

-- Location: IOOBUF_X21_Y0_N2
\oCNT[6]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(6),
	devoe => ww_devoe,
	o => \oCNT[6]~output_o\);

-- Location: IOOBUF_X16_Y0_N9
\oCNT[7]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(7),
	devoe => ww_devoe,
	o => \oCNT[7]~output_o\);

-- Location: IOOBUF_X21_Y0_N30
\oCNT[8]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(8),
	devoe => ww_devoe,
	o => \oCNT[8]~output_o\);

-- Location: IOOBUF_X14_Y0_N16
\oCNT[9]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(9),
	devoe => ww_devoe,
	o => \oCNT[9]~output_o\);

-- Location: IOOBUF_X14_Y0_N9
\oCNT[10]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(10),
	devoe => ww_devoe,
	o => \oCNT[10]~output_o\);

-- Location: IOOBUF_X16_Y0_N30
\oCNT[11]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(11),
	devoe => ww_devoe,
	o => \oCNT[11]~output_o\);

-- Location: IOOBUF_X14_Y0_N23
\oCNT[12]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(12),
	devoe => ww_devoe,
	o => \oCNT[12]~output_o\);

-- Location: IOOBUF_X19_Y0_N23
\oCNT[13]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(13),
	devoe => ww_devoe,
	o => \oCNT[13]~output_o\);

-- Location: IOOBUF_X19_Y0_N16
\oCNT[14]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(14),
	devoe => ww_devoe,
	o => \oCNT[14]~output_o\);

-- Location: IOOBUF_X21_Y0_N23
\oCNT[15]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(15),
	devoe => ww_devoe,
	o => \oCNT[15]~output_o\);

-- Location: IOOBUF_X19_Y17_N9
\oCNT[16]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(16),
	devoe => ww_devoe,
	o => \oCNT[16]~output_o\);

-- Location: IOOBUF_X19_Y17_N16
\oCNT[17]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(17),
	devoe => ww_devoe,
	o => \oCNT[17]~output_o\);

-- Location: IOOBUF_X16_Y17_N9
\oCNT[18]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(18),
	devoe => ww_devoe,
	o => \oCNT[18]~output_o\);

-- Location: IOOBUF_X16_Y17_N2
\oCNT[19]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(19),
	devoe => ww_devoe,
	o => \oCNT[19]~output_o\);

-- Location: IOOBUF_X19_Y17_N23
\oCNT[20]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(20),
	devoe => ww_devoe,
	o => \oCNT[20]~output_o\);

-- Location: IOOBUF_X19_Y17_N2
\oCNT[21]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(21),
	devoe => ww_devoe,
	o => \oCNT[21]~output_o\);

-- Location: IOOBUF_X21_Y17_N30
\oCNT[22]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(22),
	devoe => ww_devoe,
	o => \oCNT[22]~output_o\);

-- Location: IOOBUF_X16_Y17_N16
\oCNT[23]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => sCNT(23),
	devoe => ww_devoe,
	o => \oCNT[23]~output_o\);

-- Location: IOIBUF_X0_Y9_N22
\iCLK~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_iCLK,
	o => \iCLK~input_o\);

-- Location: CLKCTRL_G4
\iCLK~inputclkctrl\ : fiftyfivenm_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \iCLK~inputclkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \iCLK~inputclkctrl_outclk\);

-- Location: LCCOMB_X16_Y4_N8
\Add0~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~0_combout\ = sCNT(0) $ (VCC)
-- \Add0~1\ = CARRY(sCNT(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001111001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => sCNT(0),
	datad => VCC,
	combout => \Add0~0_combout\,
	cout => \Add0~1\);

-- Location: LCCOMB_X16_Y4_N18
\Add0~10\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~10_combout\ = (sCNT(5) & (!\Add0~9\)) # (!sCNT(5) & ((\Add0~9\) # (GND)))
-- \Add0~11\ = CARRY((!\Add0~9\) # (!sCNT(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(5),
	datad => VCC,
	cin => \Add0~9\,
	combout => \Add0~10_combout\,
	cout => \Add0~11\);

-- Location: LCCOMB_X16_Y4_N20
\Add0~12\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~12_combout\ = (sCNT(6) & (\Add0~11\ $ (GND))) # (!sCNT(6) & (!\Add0~11\ & VCC))
-- \Add0~13\ = CARRY((sCNT(6) & !\Add0~11\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(6),
	datad => VCC,
	cin => \Add0~11\,
	combout => \Add0~12_combout\,
	cout => \Add0~13\);

-- Location: IOIBUF_X25_Y22_N15
\iRST~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_iRST,
	o => \iRST~input_o\);

-- Location: IOIBUF_X0_Y3_N15
\iEN~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_iEN,
	o => \iEN~input_o\);

-- Location: FF_X16_Y4_N21
\sCNT[6]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~12_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(6));

-- Location: LCCOMB_X16_Y4_N22
\Add0~14\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~14_combout\ = (sCNT(7) & (!\Add0~13\)) # (!sCNT(7) & ((\Add0~13\) # (GND)))
-- \Add0~15\ = CARRY((!\Add0~13\) # (!sCNT(7)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(7),
	datad => VCC,
	cin => \Add0~13\,
	combout => \Add0~14_combout\,
	cout => \Add0~15\);

-- Location: FF_X16_Y4_N23
\sCNT[7]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~14_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(7));

-- Location: LCCOMB_X16_Y4_N24
\Add0~16\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~16_combout\ = (sCNT(8) & (\Add0~15\ $ (GND))) # (!sCNT(8) & (!\Add0~15\ & VCC))
-- \Add0~17\ = CARRY((sCNT(8) & !\Add0~15\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(8),
	datad => VCC,
	cin => \Add0~15\,
	combout => \Add0~16_combout\,
	cout => \Add0~17\);

-- Location: FF_X16_Y4_N25
\sCNT[8]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~16_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(8));

-- Location: LCCOMB_X16_Y4_N26
\Add0~18\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~18_combout\ = (sCNT(9) & (!\Add0~17\)) # (!sCNT(9) & ((\Add0~17\) # (GND)))
-- \Add0~19\ = CARRY((!\Add0~17\) # (!sCNT(9)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(9),
	datad => VCC,
	cin => \Add0~17\,
	combout => \Add0~18_combout\,
	cout => \Add0~19\);

-- Location: FF_X16_Y4_N27
\sCNT[9]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~18_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(9));

-- Location: LCCOMB_X16_Y4_N28
\Add0~20\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~20_combout\ = (sCNT(10) & (\Add0~19\ $ (GND))) # (!sCNT(10) & (!\Add0~19\ & VCC))
-- \Add0~21\ = CARRY((sCNT(10) & !\Add0~19\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(10),
	datad => VCC,
	cin => \Add0~19\,
	combout => \Add0~20_combout\,
	cout => \Add0~21\);

-- Location: FF_X16_Y4_N29
\sCNT[10]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~20_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(10));

-- Location: LCCOMB_X16_Y4_N30
\Add0~22\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~22_combout\ = (sCNT(11) & (!\Add0~21\)) # (!sCNT(11) & ((\Add0~21\) # (GND)))
-- \Add0~23\ = CARRY((!\Add0~21\) # (!sCNT(11)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(11),
	datad => VCC,
	cin => \Add0~21\,
	combout => \Add0~22_combout\,
	cout => \Add0~23\);

-- Location: FF_X16_Y4_N31
\sCNT[11]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~22_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(11));

-- Location: LCCOMB_X16_Y3_N0
\Add0~24\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~24_combout\ = (sCNT(12) & (\Add0~23\ $ (GND))) # (!sCNT(12) & (!\Add0~23\ & VCC))
-- \Add0~25\ = CARRY((sCNT(12) & !\Add0~23\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(12),
	datad => VCC,
	cin => \Add0~23\,
	combout => \Add0~24_combout\,
	cout => \Add0~25\);

-- Location: FF_X16_Y3_N1
\sCNT[12]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~24_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(12));

-- Location: LCCOMB_X15_Y4_N16
\Equal0~3\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Equal0~3_combout\ = (!sCNT(12) & (!sCNT(9) & (!sCNT(11) & !sCNT(10))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(12),
	datab => sCNT(9),
	datac => sCNT(11),
	datad => sCNT(10),
	combout => \Equal0~3_combout\);

-- Location: LCCOMB_X16_Y3_N2
\Add0~26\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~26_combout\ = (sCNT(13) & (!\Add0~25\)) # (!sCNT(13) & ((\Add0~25\) # (GND)))
-- \Add0~27\ = CARRY((!\Add0~25\) # (!sCNT(13)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(13),
	datad => VCC,
	cin => \Add0~25\,
	combout => \Add0~26_combout\,
	cout => \Add0~27\);

-- Location: FF_X16_Y3_N3
\sCNT[13]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~26_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(13));

-- Location: LCCOMB_X16_Y3_N4
\Add0~28\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~28_combout\ = (sCNT(14) & (\Add0~27\ $ (GND))) # (!sCNT(14) & (!\Add0~27\ & VCC))
-- \Add0~29\ = CARRY((sCNT(14) & !\Add0~27\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(14),
	datad => VCC,
	cin => \Add0~27\,
	combout => \Add0~28_combout\,
	cout => \Add0~29\);

-- Location: FF_X16_Y3_N5
\sCNT[14]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~28_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(14));

-- Location: LCCOMB_X16_Y3_N6
\Add0~30\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~30_combout\ = (sCNT(15) & (!\Add0~29\)) # (!sCNT(15) & ((\Add0~29\) # (GND)))
-- \Add0~31\ = CARRY((!\Add0~29\) # (!sCNT(15)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(15),
	datad => VCC,
	cin => \Add0~29\,
	combout => \Add0~30_combout\,
	cout => \Add0~31\);

-- Location: FF_X16_Y3_N7
\sCNT[15]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~30_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(15));

-- Location: LCCOMB_X16_Y3_N8
\Add0~32\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~32_combout\ = (sCNT(16) & (\Add0~31\ $ (GND))) # (!sCNT(16) & (!\Add0~31\ & VCC))
-- \Add0~33\ = CARRY((sCNT(16) & !\Add0~31\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(16),
	datad => VCC,
	cin => \Add0~31\,
	combout => \Add0~32_combout\,
	cout => \Add0~33\);

-- Location: FF_X16_Y3_N9
\sCNT[16]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~32_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(16));

-- Location: LCCOMB_X16_Y3_N10
\Add0~34\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~34_combout\ = (sCNT(17) & (!\Add0~33\)) # (!sCNT(17) & ((\Add0~33\) # (GND)))
-- \Add0~35\ = CARRY((!\Add0~33\) # (!sCNT(17)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(17),
	datad => VCC,
	cin => \Add0~33\,
	combout => \Add0~34_combout\,
	cout => \Add0~35\);

-- Location: FF_X16_Y3_N11
\sCNT[17]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~34_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(17));

-- Location: LCCOMB_X16_Y3_N12
\Add0~36\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~36_combout\ = (sCNT(18) & (\Add0~35\ $ (GND))) # (!sCNT(18) & (!\Add0~35\ & VCC))
-- \Add0~37\ = CARRY((sCNT(18) & !\Add0~35\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(18),
	datad => VCC,
	cin => \Add0~35\,
	combout => \Add0~36_combout\,
	cout => \Add0~37\);

-- Location: FF_X16_Y3_N13
\sCNT[18]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~36_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(18));

-- Location: LCCOMB_X16_Y3_N14
\Add0~38\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~38_combout\ = (sCNT(19) & (!\Add0~37\)) # (!sCNT(19) & ((\Add0~37\) # (GND)))
-- \Add0~39\ = CARRY((!\Add0~37\) # (!sCNT(19)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(19),
	datad => VCC,
	cin => \Add0~37\,
	combout => \Add0~38_combout\,
	cout => \Add0~39\);

-- Location: FF_X16_Y3_N15
\sCNT[19]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~38_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(19));

-- Location: LCCOMB_X16_Y3_N16
\Add0~40\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~40_combout\ = (sCNT(20) & (\Add0~39\ $ (GND))) # (!sCNT(20) & (!\Add0~39\ & VCC))
-- \Add0~41\ = CARRY((sCNT(20) & !\Add0~39\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(20),
	datad => VCC,
	cin => \Add0~39\,
	combout => \Add0~40_combout\,
	cout => \Add0~41\);

-- Location: FF_X16_Y3_N17
\sCNT[20]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~40_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(20));

-- Location: LCCOMB_X16_Y3_N26
\Equal0~1\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Equal0~1_combout\ = (!sCNT(18) & (!sCNT(20) & (!sCNT(19) & !sCNT(17))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(18),
	datab => sCNT(20),
	datac => sCNT(19),
	datad => sCNT(17),
	combout => \Equal0~1_combout\);

-- Location: LCCOMB_X16_Y3_N28
\Equal0~2\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Equal0~2_combout\ = (!sCNT(15) & (!sCNT(14) & (!sCNT(16) & !sCNT(13))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(15),
	datab => sCNT(14),
	datac => sCNT(16),
	datad => sCNT(13),
	combout => \Equal0~2_combout\);

-- Location: LCCOMB_X16_Y3_N18
\Add0~42\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~42_combout\ = (sCNT(21) & (!\Add0~41\)) # (!sCNT(21) & ((\Add0~41\) # (GND)))
-- \Add0~43\ = CARRY((!\Add0~41\) # (!sCNT(21)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(21),
	datad => VCC,
	cin => \Add0~41\,
	combout => \Add0~42_combout\,
	cout => \Add0~43\);

-- Location: FF_X16_Y3_N19
\sCNT[21]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~42_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(21));

-- Location: LCCOMB_X16_Y3_N20
\Add0~44\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~44_combout\ = (sCNT(22) & (\Add0~43\ $ (GND))) # (!sCNT(22) & (!\Add0~43\ & VCC))
-- \Add0~45\ = CARRY((sCNT(22) & !\Add0~43\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(22),
	datad => VCC,
	cin => \Add0~43\,
	combout => \Add0~44_combout\,
	cout => \Add0~45\);

-- Location: FF_X16_Y3_N21
\sCNT[22]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~44_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(22));

-- Location: LCCOMB_X16_Y3_N22
\Add0~46\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~46_combout\ = sCNT(23) $ (\Add0~45\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(23),
	cin => \Add0~45\,
	combout => \Add0~46_combout\);

-- Location: FF_X16_Y3_N23
\sCNT[23]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~46_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(23));

-- Location: LCCOMB_X16_Y3_N24
\Equal0~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Equal0~0_combout\ = (!sCNT(21) & (!sCNT(22) & (!sCNT(23) & !sCNT(0))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(21),
	datab => sCNT(22),
	datac => sCNT(23),
	datad => sCNT(0),
	combout => \Equal0~0_combout\);

-- Location: LCCOMB_X16_Y4_N2
\Equal0~4\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Equal0~4_combout\ = (\Equal0~3_combout\ & (\Equal0~1_combout\ & (\Equal0~2_combout\ & \Equal0~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal0~3_combout\,
	datab => \Equal0~1_combout\,
	datac => \Equal0~2_combout\,
	datad => \Equal0~0_combout\,
	combout => \Equal0~4_combout\);

-- Location: LCCOMB_X16_Y4_N10
\Add0~2\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~2_combout\ = (sCNT(1) & (!\Add0~1\)) # (!sCNT(1) & ((\Add0~1\) # (GND)))
-- \Add0~3\ = CARRY((!\Add0~1\) # (!sCNT(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(1),
	datad => VCC,
	cin => \Add0~1\,
	combout => \Add0~2_combout\,
	cout => \Add0~3\);

-- Location: LCCOMB_X16_Y4_N6
\sCNT~1\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT~1_combout\ = (\Add0~2_combout\ & (((!\Equal0~4_combout\) # (!\Equal0~6_combout\)) # (!\Equal0~5_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010101010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~2_combout\,
	datab => \Equal0~5_combout\,
	datac => \Equal0~6_combout\,
	datad => \Equal0~4_combout\,
	combout => \sCNT~1_combout\);

-- Location: FF_X16_Y4_N7
\sCNT[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT~1_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(1));

-- Location: LCCOMB_X16_Y4_N12
\Add0~4\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~4_combout\ = (sCNT(2) & (\Add0~3\ $ (GND))) # (!sCNT(2) & (!\Add0~3\ & VCC))
-- \Add0~5\ = CARRY((sCNT(2) & !\Add0~3\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(2),
	datad => VCC,
	cin => \Add0~3\,
	combout => \Add0~4_combout\,
	cout => \Add0~5\);

-- Location: FF_X16_Y4_N13
\sCNT[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~4_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(2));

-- Location: LCCOMB_X16_Y4_N14
\Add0~6\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~6_combout\ = (sCNT(3) & (!\Add0~5\)) # (!sCNT(3) & ((\Add0~5\) # (GND)))
-- \Add0~7\ = CARRY((!\Add0~5\) # (!sCNT(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(3),
	datad => VCC,
	cin => \Add0~5\,
	combout => \Add0~6_combout\,
	cout => \Add0~7\);

-- Location: FF_X16_Y4_N15
\sCNT[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~6_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(3));

-- Location: LCCOMB_X15_Y4_N6
\Equal0~6\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Equal0~6_combout\ = (!sCNT(3) & (sCNT(4) & (!sCNT(2) & sCNT(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000010000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(3),
	datab => sCNT(4),
	datac => sCNT(2),
	datad => sCNT(1),
	combout => \Equal0~6_combout\);

-- Location: LCCOMB_X16_Y4_N16
\Add0~8\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Add0~8_combout\ = (sCNT(4) & (\Add0~7\ $ (GND))) # (!sCNT(4) & (!\Add0~7\ & VCC))
-- \Add0~9\ = CARRY((sCNT(4) & !\Add0~7\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => sCNT(4),
	datad => VCC,
	cin => \Add0~7\,
	combout => \Add0~8_combout\,
	cout => \Add0~9\);

-- Location: LCCOMB_X16_Y4_N0
\sCNT~2\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT~2_combout\ = (\Add0~8_combout\ & (((!\Equal0~6_combout\) # (!\Equal0~4_combout\)) # (!\Equal0~5_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Equal0~5_combout\,
	datab => \Equal0~4_combout\,
	datac => \Equal0~6_combout\,
	datad => \Add0~8_combout\,
	combout => \sCNT~2_combout\);

-- Location: FF_X16_Y4_N1
\sCNT[4]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT~2_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(4));

-- Location: FF_X16_Y4_N19
\sCNT[5]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \Add0~10_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(5));

-- Location: LCCOMB_X17_Y4_N24
\Equal0~5\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \Equal0~5_combout\ = (!sCNT(5) & (!sCNT(7) & (!sCNT(6) & !sCNT(8))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => sCNT(5),
	datab => sCNT(7),
	datac => sCNT(6),
	datad => sCNT(8),
	combout => \Equal0~5_combout\);

-- Location: LCCOMB_X16_Y4_N4
\sCNT~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \sCNT~0_combout\ = (\Add0~0_combout\ & (((!\Equal0~4_combout\) # (!\Equal0~6_combout\)) # (!\Equal0~5_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010101010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~0_combout\,
	datab => \Equal0~5_combout\,
	datac => \Equal0~6_combout\,
	datad => \Equal0~4_combout\,
	combout => \sCNT~0_combout\);

-- Location: FF_X16_Y4_N5
\sCNT[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \iCLK~inputclkctrl_outclk\,
	d => \sCNT~0_combout\,
	clrn => \ALT_INV_iRST~input_o\,
	ena => \iEN~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => sCNT(0));

-- Location: UNVM_X0_Y18_N40
\~QUARTUS_CREATED_UNVM~\ : fiftyfivenm_unvm
-- pragma translate_off
GENERIC MAP (
	addr_range1_end_addr => -1,
	addr_range1_offset => -1,
	addr_range2_end_addr => -1,
	addr_range2_offset => -1,
	addr_range3_offset => -1,
	is_compressed_image => "false",
	is_dual_boot => "false",
	is_eram_skip => "false",
	max_ufm_valid_addr => -1,
	max_valid_addr => -1,
	min_ufm_valid_addr => -1,
	min_valid_addr => -1,
	part_name => "quartus_created_unvm",
	reserve_block => "true")
-- pragma translate_on
PORT MAP (
	nosc_ena => \~QUARTUS_CREATED_GND~I_combout\,
	xe_ye => \~QUARTUS_CREATED_GND~I_combout\,
	se => \~QUARTUS_CREATED_GND~I_combout\,
	busy => \~QUARTUS_CREATED_UNVM~~busy\);

-- Location: ADCBLOCK_X25_Y28_N0
\~QUARTUS_CREATED_ADC1~\ : fiftyfivenm_adcblock
-- pragma translate_off
GENERIC MAP (
	analog_input_pin_mask => 0,
	clkdiv => 1,
	device_partname_fivechar_prefix => "none",
	is_this_first_or_second_adc => 1,
	prescalar => 0,
	pwd => 1,
	refsel => 0,
	reserve_block => "true",
	testbits => 66,
	tsclkdiv => 1,
	tsclksel => 0)
-- pragma translate_on
PORT MAP (
	soc => \~QUARTUS_CREATED_GND~I_combout\,
	usr_pwd => VCC,
	tsen => \~QUARTUS_CREATED_GND~I_combout\,
	chsel => \~QUARTUS_CREATED_ADC1~_CHSEL_bus\,
	eoc => \~QUARTUS_CREATED_ADC1~~eoc\);

ww_o7SEGM(0) <= \o7SEGM[0]~output_o\;

ww_o7SEGM(1) <= \o7SEGM[1]~output_o\;

ww_o7SEGM(2) <= \o7SEGM[2]~output_o\;

ww_o7SEGM(3) <= \o7SEGM[3]~output_o\;

ww_o7SEGM(4) <= \o7SEGM[4]~output_o\;

ww_o7SEGM(5) <= \o7SEGM[5]~output_o\;

ww_o7SEGM(6) <= \o7SEGM[6]~output_o\;

ww_oCNT(0) <= \oCNT[0]~output_o\;

ww_oCNT(1) <= \oCNT[1]~output_o\;

ww_oCNT(2) <= \oCNT[2]~output_o\;

ww_oCNT(3) <= \oCNT[3]~output_o\;

ww_oCNT(4) <= \oCNT[4]~output_o\;

ww_oCNT(5) <= \oCNT[5]~output_o\;

ww_oCNT(6) <= \oCNT[6]~output_o\;

ww_oCNT(7) <= \oCNT[7]~output_o\;

ww_oCNT(8) <= \oCNT[8]~output_o\;

ww_oCNT(9) <= \oCNT[9]~output_o\;

ww_oCNT(10) <= \oCNT[10]~output_o\;

ww_oCNT(11) <= \oCNT[11]~output_o\;

ww_oCNT(12) <= \oCNT[12]~output_o\;

ww_oCNT(13) <= \oCNT[13]~output_o\;

ww_oCNT(14) <= \oCNT[14]~output_o\;

ww_oCNT(15) <= \oCNT[15]~output_o\;

ww_oCNT(16) <= \oCNT[16]~output_o\;

ww_oCNT(17) <= \oCNT[17]~output_o\;

ww_oCNT(18) <= \oCNT[18]~output_o\;

ww_oCNT(19) <= \oCNT[19]~output_o\;

ww_oCNT(20) <= \oCNT[20]~output_o\;

ww_oCNT(21) <= \oCNT[21]~output_o\;

ww_oCNT(22) <= \oCNT[22]~output_o\;

ww_oCNT(23) <= \oCNT[23]~output_o\;
END structure;


