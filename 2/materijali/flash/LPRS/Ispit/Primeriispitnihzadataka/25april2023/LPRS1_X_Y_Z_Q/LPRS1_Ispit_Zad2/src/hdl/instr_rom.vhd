
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
    oQ <= "000010111111111"  when iA = 0 else
          "000010010010010"  when iA = 1 else
          "000010110010000"  when iA = 2 else
          "010010000000111"  when iA = 3 else
          "000110010010000"  when iA = 4 else
          "000001111111011"  when iA = 5 else
          "010000000000010"  when iA = 6 else
          "000010110110110"  when iA = 7 else
          "000010101101101"  when iA = 8 else
          "000110101101000"  when iA = 9 else
          "000010110111101"  when iA = 10 else
          "010010000001110"  when iA = 11 else
          "000000100111000"  when iA = 12 else
          "010000000000010"  when iA = 13 else
          "000010110110110"  when iA = 14 else
          "001000110100000"  when iA = 15 else
          "000000100110000"  when iA = 16 else
          "010000000000010"  when iA = 17 else
          "010000000010010"  when iA = 18 else
          "000000000000000";
end Behavioral;
------------------------------------------------------------------
