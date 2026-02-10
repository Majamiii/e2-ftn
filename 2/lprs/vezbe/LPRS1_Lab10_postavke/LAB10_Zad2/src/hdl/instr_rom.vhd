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
		"000010000000000"  when iA = 0 else
		"000010001001001"  when iA = 1 else
		"000110110110000"  when iA = 2 else
		"000110110110000"  when iA = 3 else
		"100000010000110"  when iA = 4 else
		"000110001001000"  when iA = 5 else
		"000111010010000"  when iA = 6 else
		"010010000001010"  when iA = 7 else
		"001000001001000"  when iA = 8 else
		"010000000000110"  when iA = 9 else
		"100000010000110"  when iA = 10 else
		"000110110110000"  when iA = 11 else
		"000010111010110"  when iA = 12 else
		"000110111111000"  when iA = 13 else
		"000110111111000"  when iA = 14 else
		"000110111111000"  when iA = 15 else
		"010001000010101"  when iA = 16 else
		"100000011000110"  when iA = 17 else
		"000001000000011"  when iA = 18 else
		"000110110110000"  when iA = 19 else
		"010000000001100"  when iA = 20 else
		"000001000000001"  when iA = 21 else
		"001011000000000"  when iA = 22 else
		"001011000000000"  when iA = 23 else
		"000010111111111"  when iA = 24 else
		"100000100000111"  when iA = 25 else
		"000110111111000"  when iA = 26 else
		"100000101000111"  when iA = 27 else
		"110000000000100"  when iA = 28 else
		"000010111111111"  when iA = 29 else
		"000110111111000"  when iA = 30 else
		"110000000111101"  when iA = 31 else
		"010000000100000"  when iA = 32 else
------------------------------------------------------------------
        "000000000000000";
end architecture;
