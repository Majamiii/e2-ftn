
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_SIGNED.ALL;

entity instr_rom is
    Port ( iA : in  STD_LOGIC_VECTOR (7 downto 0);
           oQ : out  STD_LOGIC_VECTOR (14 downto 0));
end instr_rom;

-- ubaciti sadrzaj *.txt datoteke generisane pomocu lprsasm ------
architecture Behavioral of instr_rom is
begin
    oQ <= "100000000000110"  when iA = 0 else
          "000110110110000"  when iA = 1 else
          "100000001000110"  when iA = 2 else
          "000110110110000"  when iA = 3 else
          "100000010000110"  when iA = 4 else
          "000110110110000"  when iA = 5 else
          "000110101101000"  when iA = 6 else
          "000110101101000"  when iA = 7 else
          "000110101101000"  when iA = 8 else
          "100000011000101"  when iA = 9 else
          "000010111101110"  when iA = 10 else
          "000010111000111"  when iA = 11 else
          "010001000011000"  when iA = 12 else
          "000100011011011"  when iA = 13 else
          "010110000010110"  when iA = 14 else
          "000010111111111"  when iA = 15 else
          "000110111111000"  when iA = 16 else
          "000011111111011"  when iA = 17 else
          "010001000010110"  when iA = 18 else
          "100000100000101"  when iA = 19 else
          "110000000011001"  when iA = 20 else
          "000110001001000"  when iA = 21 else
          "000110101101000"  when iA = 22 else
          "010000000001001"  when iA = 23 else
          "000010111111111"  when iA = 24 else
          "000110111111000"  when iA = 25 else
          "110000000111010"  when iA = 26 else
          "010000000011011"  when iA = 27 else
          "000000000000000";
end Behavioral;
------------------------------------------------------------------
