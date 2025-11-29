
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
    oQ <= "010000000000000"  when iA = 0 else
          "000000000000000";
end Behavioral;
------------------------------------------------------------------
