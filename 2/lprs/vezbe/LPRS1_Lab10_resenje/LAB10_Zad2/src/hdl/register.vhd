
----------------------------------------------------------------------------------
-- Logicko projektovanje racunarskih sistema 1
-- 2011/2012, 2023
--
-- Register
--
-- authors:
-- Ivan Kastelan (ivan.kastelan@rt-rk.com)
-- Teodora Novkovic (teodora.novkovic@uns.ac.rs)
----------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity reg is
    Generic ( WIDTH : integer := 16 );
    port ( iCLK : in  std_logic;
           iRST : in  std_logic;
           iD   : in  std_logic_vector (WIDTH-1 downto 0);
           iWE  : in  std_logic;
           oQ   : out std_logic_vector (WIDTH-1 downto 0)
         );
end reg;

architecture Behavioral of reg is

    signal sREG : std_logic_vector(WIDTH-1 downto 0);

begin

    process (iCLK, iRST) begin
        if (iRST = '1') then
            sREG <= (others => '0');
        elsif (iCLK'event and iCLK = '1') then
            if (iWE = '1') then
                sREG <= iD;
            end if;
        end if;
    end process;
    
    oQ <= sREG;

end Behavioral;
