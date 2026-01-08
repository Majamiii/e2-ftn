library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity design_sign is
	port(
		iA : in std_logic_vector(3 downto 0);
		iB : in std_logic_vector(3 downto 0);
		oA_GT_B : out std_logic;
		oA_EQ_B : out std_logic;
		oB_GT_A : out std_logic;
		oSUM : out std_logic_vector(4 downto 0)
	);
end entity;


architecture Behavioral of design_sign is
	signal A,B: signed (3 downto 0);
	signal SUM: signed (4 downto 0);
begin
    -- neophodne formalne konverzije da bi ulazi i izlazi ostali std_logic_vector
    A <= signed(iA);
	B <= signed(iB);
	oSUM <= std_logic_vector(SUM);
	

    process(A, B) is
    begin
       SUM <= (A(3) & A) + (B(3) & B);
    end process;

    process (A, B) is
    begin
       oA_GT_B <= '0';
       oA_EQ_B <= '0';
       oB_GT_A <= '0';
	
       if A > B then
           oA_GT_B <= '1';
       elsif A = B then
           oA_EQ_B <= '1';
       else
           oB_GT_A <= '1';
       end if;
    end process;

end architecture;