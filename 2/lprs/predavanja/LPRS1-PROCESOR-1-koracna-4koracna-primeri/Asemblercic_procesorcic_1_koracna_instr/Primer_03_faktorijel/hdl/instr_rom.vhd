
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
    oQ <= "000010000000000"  when iA = 0 else
          "100000001000000"  when iA = 1 else
          "000110000000000"  when iA = 2 else
          "100000010000000"  when iA = 3 else
          "000111000000000"  when iA = 4 else
          "000001000000001"  when iA = 5 else
          "000111010010000"  when iA = 6 else
          "010101000000101"  when iA = 7 else
          "010000000001000"  when iA = 8 else
          "000000000000000";
end Behavioral;
------------------------------------------------------------------

