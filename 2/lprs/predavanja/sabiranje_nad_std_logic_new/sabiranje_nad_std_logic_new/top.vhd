library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity top is
   port(
         iA : in std_logic_vector(3 downto 0);
         iB : in std_logic_vector(3 downto 0);    
         oSUM_unsign : out std_logic_vector(4 downto 0);
         oA_GT_B_unsign, oA_EQ_B_unsign, oB_GT_A_unsign: out std_logic;
		 oSUM_sign : out std_logic_vector(4 downto 0);
		 oA_GT_B_sign, oA_EQ_B_sign, oB_GT_A_sign : out std_logic
       );
end entity;

architecture behavior of top is

    component design_unsign
        port(
            iA : in std_logic_vector(3 downto 0);
            iB : in std_logic_vector(3 downto 0);
            oA_GT_B : out std_logic;
            oA_EQ_B : out std_logic;
            oB_GT_A : out std_logic;
            oSUM : out std_logic_vector(4 downto 0)
        );
    end component;

    component design_sign
        port(
            iA : in std_logic_vector(3 downto 0);
            iB : in std_logic_vector(3 downto 0);
            oA_GT_B : out std_logic;
            oA_EQ_B : out std_logic;
            oB_GT_A : out std_logic;
            oSUM : out std_logic_vector(4 downto 0)
        );
    end component;

begin
    u_unsign: design_unsign
    port map(
        iA => iA,
        iB => iB,
        oA_GT_B => oA_GT_B_unsign,
        oA_EQ_B => oA_EQ_B_unsign,
        oB_GT_A => oB_GT_A_unsign,
        oSUM => oSUM_unsign
    );

    u_sign: design_sign
    port map(
        iA => iA,
        iB => iB,
        oA_GT_B => oA_GT_B_sign,
        oA_EQ_B => oA_EQ_B_sign,
        oB_GT_A => oB_GT_A_sign,
        oSUM => oSUM_sign
    );
	
end architecture;