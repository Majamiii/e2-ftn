
-------------------------------------------------------
-- Logicko projektovanje racunarskih sistema 1
-- 2020
--
-- DNA sequence ROM.
--
-- author:
-- Milos Subotic (milos.subotic@uns.ac.rs)
-------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity sequence_rom is
	port(
		iA : in  std_logic_vector(7 downto 0);
		oQ : out std_logic_vector(1 downto 0)
	);
end entity sequence_rom;

architecture Behavioral of sequence_rom is
	
	type tROM is array(0 to 255) of std_logic_vector(1 downto 0);
	signal sROM : tROM := (
		-- DNA sequence --
		others => "00"
	);
begin
	oQ <= sROM(conv_integer(iA));
end architecture;
