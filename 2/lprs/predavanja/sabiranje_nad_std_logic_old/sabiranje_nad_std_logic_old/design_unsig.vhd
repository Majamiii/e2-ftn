library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity design_unsign is
	port(
		iA : in std_logic_vector(3 downto 0);
		iB : in std_logic_vector(3 downto 0);
		oA_GT_B : out std_logic;
		oA_EQ_B : out std_logic;
		oB_GT_A : out std_logic;
		oSUM : out std_logic_vector(4 downto 0)
	);
end entity;

architecture Behavioral of design_unsign is
	
begin

    process(iA, iB) is
    begin
       oSUM <= ('0' & iA) + ('0' & iB);
    end process;

    process (iA, iB) is
    begin
       oA_GT_B <= '0';
       oA_EQ_B <= '0';
       oB_GT_A <= '0';
	
       if iA > iB then
           oA_GT_B <= '1';
       elsif iA = iB then
           oA_EQ_B <= '1';
       else
           oB_GT_A <= '1';
       end if;
    end process;

end architecture;