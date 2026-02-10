
----------------------------------------------------------------------------------
-- Logicko projektovanje racunarskih sistema 1
-- 2011/2012
-- Lab 7
--
-- Computer system top level
--
-- author: Ivan Kastelan (ivan.kastelan@rt-rk.com)
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity top is
    Port ( iCLK : in  STD_LOGIC;
           inRST : in  STD_LOGIC;
           oLED : out  STD_LOGIC_VECTOR (15 downto 0));
end top;

architecture Behavioral of top is

    component cpu_top is
    Port ( iCLK : in  STD_LOGIC;
           inRST : in  STD_LOGIC;
           iINSTR : in  STD_LOGIC_VECTOR (14 downto 0);
           iDATA : in  STD_LOGIC_VECTOR (15 downto 0);
           oPC : out  STD_LOGIC_VECTOR (15 downto 0);
           oDATA : out  STD_LOGIC_VECTOR (15 downto 0);
           oADDR : out  STD_LOGIC_VECTOR (15 downto 0);
           oMEM_WE : out  STD_LOGIC;
           oLED : out  STD_LOGIC_VECTOR (15 downto 0));
    end component;
    
    component instr_rom is
    Port ( iA : in  STD_LOGIC_VECTOR (4 downto 0);
           oQ : out  STD_LOGIC_VECTOR (14 downto 0));
    end component;
    
    component data_ram is
    Port ( iCLK : in  STD_LOGIC;
           inRST : in  STD_LOGIC;
           iA : in  STD_LOGIC_VECTOR (4 downto 0);
           iD : in  STD_LOGIC_VECTOR (15 downto 0);
           iWE : in  STD_LOGIC;
           oQ : out  STD_LOGIC_VECTOR (15 downto 0));
    end component;
    
    signal sINSTR : std_logic_vector(14 downto 0);
    signal sDATA_LD : std_logic_vector(15 downto 0);
    signal sPC : std_logic_vector(15 downto 0);
    signal sDATA_ST : std_logic_vector(15 downto 0);
    signal sADDR : std_logic_vector(15 downto 0);
    signal sMEM_WE : std_logic;

begin

    cpu_top_i : cpu_top port map (
        iCLK => iCLK,
        inRST => inRST,
        iINSTR => sINSTR,
        iDATA => sDATA_LD,
        oPC => sPC,
        oDATA => sDATA_ST,
        oADDR => sADDR,
        oMEM_WE => sMEM_WE,
        oLED => oLED
    );
    
    i_instr_rom : instr_rom port map (
        iA => sPC(4 downto 0),
        oQ => sINSTR
    );
    
    i_data_ram : data_ram port map (
        iCLK => iCLK,
        inRST => inRST,
        iA => sADDR(4 downto 0),
        iD => sDATA_ST,
        iWE => sMEM_WE,
        oQ => sDATA_LD
    );

end Behavioral;
