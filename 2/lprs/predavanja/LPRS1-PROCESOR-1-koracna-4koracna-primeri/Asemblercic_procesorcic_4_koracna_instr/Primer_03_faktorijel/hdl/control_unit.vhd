
----------------------------------------------------------------------------------
-- Logicko projektovanje racunarskih sistema 1
-- 2011/2012,2020
--
-- Control unit
--
-- authors:
-- Ivan Kastelan (ivan.kastelan@rt-rk.com)
-- Milos Subotic (milos.subotic@uns.ac.rs)
----------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity control_unit is
	port(
		iCLK      : in  std_logic;
		inRST     : in  std_logic;
		iINSTR    : in  std_logic_vector(14 downto 0);
		iSIGN     : in  std_logic;
		iZERO     : in  std_logic;
		iCARRY    : in  std_logic;
		oREG_WE   : out std_logic_vector(7 downto 0);
		oA_WE     : out std_logic;
		oB_WE     : out std_logic;
		oC_WE     : out std_logic;
		oIR_WE    : out std_logic;
		oPC_IN    : out std_logic_vector(15 downto 0);
		oPC_EN    : out std_logic;
		oPC_LOAD  : out std_logic;
		oMUXA_SEL : out std_logic_vector(3 downto 0);
		oMUXB_SEL : out std_logic_vector(3 downto 0);
		oALU_SEL  : out std_logic_vector(3 downto 0);
		oMEM_WE   : out std_logic
	);
end entity control_unit;

architecture Behavioral of control_unit is

	signal sY : std_logic_vector(2 downto 0);
	signal sX : std_logic_vector(2 downto 0);
	signal sZ : std_logic_vector(2 downto 0);
	signal sA : std_logic_vector(8 downto 0);
	signal sI : std_logic_vector(5 downto 0);
	signal sO : std_logic_vector(3 downto 0);
	signal sT : std_logic_vector(1 downto 0);
	
	signal sZ_DEC : std_logic_vector(7 downto 0);
	signal sDO_JMP : std_logic;
	
	type tSTATES is (FETCH, DECODE, EXECUTE, WRITE_BACK);
	signal sSTATE : tSTATES;
	
begin

	sY <= iINSTR(2 downto 0);
	sX <= iINSTR(5 downto 3);
	sZ <= iINSTR(8 downto 6);
	sA <= iINSTR(8 downto 0);
	sI <= iINSTR(14 downto 9);
	sO <= sI(3 downto 0);
	sT <= sI(5 downto 4);
	
	sZ_DEC <=
		"00000001" when sZ = "000" else
		"00000010" when sZ = "001" else
		"00000100" when sZ = "010" else
		"00001000" when sZ = "011" else
		"00010000" when sZ = "100" else
		"00100000" when sZ = "101" else
		"01000000" when sZ = "110" else
		"10000000";
	
	sDO_JMP <= 
		'1' when
			sT = "01" and                         -- Jump instructions.
			(
				(sO = "0000") or                  -- jmp
				(sO = "0001" and iZERO  = '1') or -- jmpz
				(sO = "0010" and iSIGN  = '1') or -- jmps
				(sO = "0011" and iCARRY = '1') or -- jmpc
				(sO = "0101" and iZERO  = '0') or -- jmpnz
				(sO = "0110" and iSIGN  = '0') or -- jmpns
				(sO = "0111" and iCARRY = '0')    -- jmpnc
			)
		else '0';
	
	-- FSM reg and transition function.
	process(iCLK, inRST)
	begin
		if inRST = '0' then
			sSTATE <= FETCH;
		elsif iCLK'event and iCLK = '1' then
			case sSTATE is
				when FETCH =>
					sSTATE <= DECODE;
				when DECODE =>
					sSTATE <= EXECUTE;
				when EXECUTE =>
					sSTATE <= WRITE_BACK;
				when WRITE_BACK =>
					sSTATE <= FETCH;
			end case;
		end if;
	end process;
	
	-- Output function.
	process(
		sSTATE,
		sY,
		sX,
		sA,
		sO,
		sT,
		sZ_DEC,
		sDO_JMP
	)
	begin
		-- Neutral values by default.
		oREG_WE <= "00000000";
		oA_WE <= '0';
		oB_WE <= '0';
		oC_WE <= '0';
		oIR_WE <= '0';
		oPC_IN <= "0000000000000000";
		oPC_EN <= '0';
		oPC_LOAD <= '0';
		oMUXA_SEL <= "0000";
		oMUXB_SEL <= "0000";
		oALU_SEL <= "0000";
		oMEM_WE <= '0';
		
		-- Assigning values to control signals.
		case sSTATE is
			when FETCH =>
				-- Instruction is written in IR.
				oIR_WE <= '1';
				
			when DECODE =>
				-- Operands are written in A and B, MUX's select operands.
				if sT = "10" then
					-- Load instruction.
					oMUXA_SEL <= "1000";
				else
					-- Other instructions.
					oMUXA_SEL <= '0' & sX;
				end if;
				oMUXB_SEL <= '0' & sY;
				oA_WE <= '1';
				oB_WE <= '1';
				
			when EXECUTE =>
				-- ALU performs operation and result is written in C.
				oALU_SEL <= sO;
				if sT /= "01" then
					-- Write to flag reg if not jump instructions.
					oC_WE <= '1';
				end if;
				
			when WRITE_BACK =>
				-- Result is written in register or memory and jump is done.
				if sT = "00" or sT = "10" then
					-- ALU or load instructions.
					oREG_WE <= sZ_DEC;
				end if;
				oPC_EN <= '1'; -- Enable PC: increment or load.
				if sDO_JMP = '1' then
					-- Load new PC.
					oPC_IN <= "0000000" & sA;
					oPC_LOAD <= '1';
				end if;
				oMUXB_SEL <= '0' & sY; -- Kept for store intruction.
				if sT = "11" then
					-- Store instructions.
					oMEM_WE <= '1';
				end if;
				
		end case;
	end process;


end architecture;
