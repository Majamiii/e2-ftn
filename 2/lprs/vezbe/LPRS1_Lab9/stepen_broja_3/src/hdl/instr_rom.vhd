-------------------------------------------------------
-- Logicko projektovanje racunarskih sistema 1
-- 2011/2012, 2023
--
-- Instruction ROM
--
-- authors:
-- Ivan Kastelan (ivan.kastelan@rt-rk.com)
-- Milos Subotic (milos.subotic@uns.ac.rs)
-------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity instr_rom is
	port(
		iA : in  std_logic_vector(7 downto 0);
		oQ : out std_logic_vector(14 downto 0)
	);
end instr_rom;

architecture arch of instr_rom is
begin
	oQ <=
------------------------------------------------------------------
		"100000000000000"  when iA = 0 else
		"000110001001000"  when iA = 1 else
		"010000000000011"  when iA = 2 else
		"000010110000010"  when iA = 3 else
		"010001000001001"  when iA = 4 else
		"001000110001000"  when iA = 5 else
		"000001001110001"  when iA = 6 else
		"000110010010000"  when iA = 7 else
		"010000000000011"  when iA = 8 else
		"010000000001001"  when iA = 9 else
------------------------------------------------------------------
        "000000000000000";
end architecture;
