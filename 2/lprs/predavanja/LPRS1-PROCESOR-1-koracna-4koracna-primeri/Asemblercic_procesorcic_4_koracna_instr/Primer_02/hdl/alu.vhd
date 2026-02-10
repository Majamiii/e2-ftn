
----------------------------------------------------------------------------------
-- Logicko projektovanje racunarskih sistema 1
-- 2011/2012
-- Lab 5-7
--
-- ALU
--
-- author: Ivan Kastelan (ivan.kastelan@rt-rk.com)
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_SIGNED.ALL;

entity alu is
    Port ( iA : in  STD_LOGIC_VECTOR (15 downto 0);
           iB : in  STD_LOGIC_VECTOR (15 downto 0);
           iSEL : in  STD_LOGIC_VECTOR (3 downto 0);
           oC : out  STD_LOGIC_VECTOR (15 downto 0);
           oSIGN : out  STD_LOGIC;
           oCARRY : out  STD_LOGIC;
           oZERO : out  STD_LOGIC);
end alu;

architecture Behavioral of alu is

    signal sA : std_logic_vector(16 downto 0);
    signal sB : std_logic_vector(16 downto 0);
    signal sC : std_logic_vector(16 downto 0);

begin
    -- Sign extensions.
    sA <= iA(15) & iA;
    sB <= iB(15) & iB;

    -- Mux with arithmetic-logical operations.
    sC <= sA                                when iSEL = "0000" else
          sA + sB                           when iSEL = "0001" else
          sA - sB                           when iSEL = "0010" else
          sA and sB                         when iSEL = "0011" else
          sA or sB                          when iSEL = "0100" else
          not(sA)                           when iSEL = "0101" else
          sA + 1                            when iSEL = "0110" else
          sA - 1                            when iSEL = "0111" else
          '0' & sA(14 downto 0) & '0'       when iSEL = "1000" else
          "00" & sA(15 downto 1)            when iSEL = "1001" else
          sA(16) & sA(14 downto 0) & '0'    when iSEL = "1010" else
          sA(16) & sA(15) & sA(15 downto 1) when iSEL = "1011" else
          (others => '0');
    
	 -- Flags.
    oC <= sC(15 downto 0);
    oZERO <= '1' when sC(15 downto 0) = "0000000000000000" else '0';
    oCARRY <= sC(16);
    oSIGN <= sC(15);

end Behavioral;
