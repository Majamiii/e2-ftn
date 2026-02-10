
----------------------------------------------------------------------------------
-- Logicko projektovanje racunarskih sistema 1
-- 2011/2012,2020-2022, 2023
--
-- Control unit
--
-- authors:
-- Ivan Kastelan (ivan.kastelan@rt-rk.com)
-- Milos Subotic (milos.subotic@uns.ac.rs)
-- Teodora Novkovic (teodora.novkovic@uns.ac.rs)
----------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity control_unit is
	port(
		iINSTR    : in  std_logic_vector(14 downto 0);
		iSIGN     : in  std_logic;
		iZERO     : in  std_logic;
		iCARRY    : in  std_logic;
		oREG_WE   : out std_logic_vector(7 downto 0);
		oPC_IN    : out std_logic_vector(15 downto 0);
		oPC_LOAD  : out std_logic;
		oMUXA_SEL : out std_logic_vector(3 downto 0);
		oMUXB_SEL : out std_logic_vector(3 downto 0);
		oALU_SEL  : out std_logic_vector(3 downto 0);
		oMEM_WE   : out std_logic;
		oFLAGS_WE : out std_logic
	);
end entity control_unit;

architecture arch of control_unit is

	signal sY : std_logic_vector(2 downto 0);
	signal sX : std_logic_vector(2 downto 0);
	signal sZ : std_logic_vector(2 downto 0);
	signal sA : std_logic_vector(8 downto 0);
	signal sI : std_logic_vector(5 downto 0);
	signal sO : std_logic_vector(3 downto 0);
	signal sT : std_logic_vector(1 downto 0);
	
	signal sZ_DEC : std_logic_vector(7 downto 0);
	signal sFLAGS_ARE_FOR_JMP : std_logic;
	
begin

	-- Instruction parser: sY, sX, sZ, sA, sI, sO, sT
	
	
	-- Selecting source operands for ALU: oMUXA_SEL and oMUXB_SEL.
	-- Load instruction source iDATA.
	
	
	-- Decoder sZ_DEC
	
	
	-- Result is written in registers on ALU or Load instructions: oREG_WE.
	
	
	-- Store instruction WE.
	
	
	-- Write to flag reg if not jump instructions.
	
	
	-- Load sA to PC i.e. jump to address.
	oPC_IN <= "0000000" & sA;
	sFLAGS_ARE_FOR_JMP <=
		'1' when
			(sO = "0000") or                  -- jmp
			(sO = "0001" and iZERO  = '1') or -- jmpz
			(sO = "0010" and iSIGN  = '1') or -- jmps
			(sO = "0011" and iCARRY = '1') or -- jmpc
			(sO = "0101" and iZERO  = '0') or -- jmpnz
			(sO = "0110" and iSIGN  = '0') or -- jmpns
			(sO = "0111" and iCARRY = '0')    -- jmpnc
		else '0';

	oPC_LOAD <= '1' when sT = "01" and sFLAGS_ARE_FOR_JMP = '1' else '0';

end architecture;
