library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity top_tb is
end entity;

architecture behavior of top_tb is
    signal iA, iB : std_logic_vector(3 downto 0);
    signal oSUM_unsign, oSUM_sign : std_logic_vector(4 downto 0);
    signal oA_GT_B_unsign, oA_EQ_B_unsign, oB_GT_A_unsign : std_logic;
    signal oA_GT_B_sign, oA_EQ_B_sign, oB_GT_A_sign : std_logic;

    component top
        port(
            iA : in std_logic_vector(3 downto 0);
            iB : in std_logic_vector(3 downto 0);
            oSUM_unsign : out std_logic_vector(4 downto 0);
            oA_GT_B_unsign, oA_EQ_B_unsign, oB_GT_A_unsign : out std_logic;
            oSUM_sign : out std_logic_vector(4 downto 0);
            oA_GT_B_sign, oA_EQ_B_sign, oB_GT_A_sign : out std_logic
        );
    end component;

begin
    uut: top
    port map(
        iA => iA,
        iB => iB,
        oSUM_unsign => oSUM_unsign,
        oA_GT_B_unsign => oA_GT_B_unsign,
        oA_EQ_B_unsign => oA_EQ_B_unsign,
        oB_GT_A_unsign => oB_GT_A_unsign,
        oSUM_sign => oSUM_sign,
        oA_GT_B_sign => oA_GT_B_sign,
        oA_EQ_B_sign => oA_EQ_B_sign,
        oB_GT_A_sign => oB_GT_A_sign
    );

    stimulus_process: process
    begin
        iA <= "0100";  
        iB <= "0011";  
        wait for 10 ns;
        iA <= "0011";  
        iB <= "0100";  
        wait for 10 ns;
        iA <= "0100";  
        iB <= "0100";  
        wait for 10 ns;
        iA <= "1001";  
        iB <= "0111";  
        wait for 10 ns;
        iA <= "0111";  
        iB <= "1001";  
        wait for 10 ns;	
        iA <= "0111";  
        iB <= "1111";  
        wait for 10 ns;			
        wait;
    end process stimulus_process;
end architecture;
