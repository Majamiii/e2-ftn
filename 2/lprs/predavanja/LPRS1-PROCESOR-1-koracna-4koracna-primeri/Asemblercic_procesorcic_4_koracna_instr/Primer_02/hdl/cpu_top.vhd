
----------------------------------------------------------------------------------
-- Logicko projektovanje racunarskih sistema 1
-- 2011/2012
-- Lab 7
--
-- CPU top level
--
-- author: Ivan Kastelan (ivan.kastelan@rt-rk.com)
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity cpu_top is
    Port ( iCLK : in  STD_LOGIC;
           inRST : in  STD_LOGIC;
           iINSTR : in  STD_LOGIC_VECTOR (14 downto 0);
           iDATA : in  STD_LOGIC_VECTOR (15 downto 0);
           oPC : out  STD_LOGIC_VECTOR (15 downto 0);
           oDATA : out  STD_LOGIC_VECTOR (15 downto 0);
           oADDR : out  STD_LOGIC_VECTOR (15 downto 0);
           oMEM_WE : out  STD_LOGIC;
           oLED : out  STD_LOGIC_VECTOR (15 downto 0));
end cpu_top;

architecture Behavioral of cpu_top is

    component alu is
    Port ( iA : in  STD_LOGIC_VECTOR (15 downto 0);
           iB : in  STD_LOGIC_VECTOR (15 downto 0);
           iSEL : in  STD_LOGIC_VECTOR (3 downto 0);
           oC : out  STD_LOGIC_VECTOR (15 downto 0);
           oSIGN : out  STD_LOGIC;
           oCARRY : out  STD_LOGIC;
           oZERO : out  STD_LOGIC);
    end component;
    
    component cnt is
    Port ( iCLK : in  STD_LOGIC;
           inRST : in  STD_LOGIC;
           iD : in  STD_LOGIC_VECTOR (15 downto 0);
           iEN : in  STD_LOGIC;
           iLOAD : in  STD_LOGIC;
           oQ : out  STD_LOGIC_VECTOR (15 downto 0));
    end component;
    
    component control_unit is
    Port ( iCLK : in  STD_LOGIC;
           inRST : in  STD_LOGIC;
           iINSTR : in  STD_LOGIC_VECTOR (14 downto 0);
           iSIGN : in  STD_LOGIC;
           iZERO : in  STD_LOGIC;
           iCARRY : in  STD_LOGIC;
           oREG_WE : out  STD_LOGIC_VECTOR (7 downto 0);
           oA_WE : out  STD_LOGIC;
           oB_WE : out  STD_LOGIC;
           oC_WE : out  STD_LOGIC;
           oIR_WE : out  STD_LOGIC;
           oPC_IN : out  STD_LOGIC_VECTOR (15 downto 0);
           oPC_EN : out  STD_LOGIC;
           oPC_LOAD : out  STD_LOGIC;
           oMUXA_SEL : out  STD_LOGIC_VECTOR (3 downto 0);
           oMUXB_SEL : out  STD_LOGIC_VECTOR (3 downto 0);
           oALU_SEL : out  STD_LOGIC_VECTOR (3 downto 0);
           oMEM_WE : out  STD_LOGIC);
    end component;
    
    component data_ram is
    Port ( iCLK : in  STD_LOGIC;
           inRST : in  STD_LOGIC;
           iA : in  STD_LOGIC_VECTOR (4 downto 0);
           iD : in  STD_LOGIC_VECTOR (15 downto 0);
           iWE : in  STD_LOGIC;
           oQ : out  STD_LOGIC_VECTOR (15 downto 0));
    end component;
    
    component instr_rom is
    Port ( iA : in  STD_LOGIC_VECTOR (4 downto 0);
           oQ : out  STD_LOGIC_VECTOR (15 downto 0));
    end component;
    
    component mux is
    Port ( iD0 : in  STD_LOGIC_VECTOR (15 downto 0);
           iD1 : in  STD_LOGIC_VECTOR (15 downto 0);
           iD2 : in  STD_LOGIC_VECTOR (15 downto 0);
           iD3 : in  STD_LOGIC_VECTOR (15 downto 0);
           iD4 : in  STD_LOGIC_VECTOR (15 downto 0);
           iD5 : in  STD_LOGIC_VECTOR (15 downto 0);
           iD6 : in  STD_LOGIC_VECTOR (15 downto 0);
           iD7 : in  STD_LOGIC_VECTOR (15 downto 0);
           iD8 : in  STD_LOGIC_VECTOR (15 downto 0);
           iSEL : in  STD_LOGIC_VECTOR (3 downto 0);
           oQ : out  STD_LOGIC_VECTOR (15 downto 0));
    end component;
    
    component reg is
    Generic ( WIDTH : integer := 16 );
    Port ( iCLK : in  STD_LOGIC;
           inRST : in  STD_LOGIC;
           iD : in  STD_LOGIC_VECTOR (WIDTH-1 downto 0);
           iWE : in  STD_LOGIC;
           oQ : out  STD_LOGIC_VECTOR (WIDTH-1 downto 0));
    end component;
    
    signal sREG_WE : std_logic_vector(7 downto 0);
    signal sR0, sR1, sR2, sR3, sR4, sR5, sR6, sR7 : std_logic_vector(15 downto 0);
    signal sMUXA, sMUXB : std_logic_vector(15 downto 0);
    signal sMUXA_SEL, sMUXB_SEL : std_logic_vector(3 downto 0);
    signal sA, sB, sC : std_logic_vector(15 downto 0);
    signal sA_WE, sB_WE, sC_WE : std_logic;
    signal sALU_SEL : std_logic_vector(3 downto 0);
    signal sRESULT : std_logic_vector(15 downto 0);
    signal sIR : std_logic_vector(14 downto 0);
    signal sIR_WE : std_logic;
    signal sPC : std_logic_vector(15 downto 0);
    signal sPC_IN : std_logic_vector(15 downto 0);
    signal sPC_EN, sPC_LOAD : std_logic;
    signal sMEM_WE : std_logic;
    signal sPHASE : std_logic_vector (1 downto 0);
    signal sSIGN, sSIGN_R : std_logic;
    signal sZERO, sZERO_R : std_logic;
    signal sCARRY, sCARRY_R : std_logic;

begin

    i_ALU : alu port map (
        iA => sA,
        iB => sB,
        iSEL => sALU_SEL,
        oC => sRESULT,
        oSIGN => sSIGN,
        oCARRY => sCARRY,
        oZERO => sZERO
    );
    
    process (iCLK, inRST) begin
        if (inRST = '0') then
            sSIGN_R <= '0';
            sCARRY_R <= '0';
            sZERO_R <= '0';
        elsif (iCLK'event and iCLK = '1') then
            if (sC_WE = '1') then
                sSIGN_R <= sSIGN;
                sCARRY_R <= sCARRY;
                sZERO_R <= sZERO;
            end if;
        end if;
    end process;
    
    i_PC : cnt port map (
        iCLK => iCLK,
        inRST => inRST,
        iD => sPC_IN,
        iEN => sPC_EN,
        iLOAD => sPC_LOAD,
        oQ => sPC
    );
    
    cu_i : control_unit port map (
        iCLK => iCLK,
        inRST => inRST,
        iINSTR => sIR,
        oREG_WE => sREG_WE,
        oA_WE => sA_WE,
        oB_WE => sB_WE,
        oC_WE => sC_WE,
        oIR_WE => sIR_WE,
        oPC_IN => sPC_IN,
        oPC_EN => sPC_EN,
        oPC_LOAD => sPC_LOAD,
        oMUXA_SEL => sMUXA_SEL,
        oMUXB_SEL => sMUXB_SEL,
        oALU_SEL => sALU_SEL,
        oMEM_WE => sMEM_WE,
        iSIGN => sSIGN_R,
        iCARRY => sCARRY_R,
        iZERO => sZERO_R
    );
    
    i_MUXA : mux port map (
        iD0 => sR0,
        iD1 => sR1,
        iD2 => sR2,
        iD3 => sR3,
        iD4 => sR4,
        iD5 => sR5,
        iD6 => sR6,
        iD7 => sR7,
        iD8 => iDATA,
        iSEL => sMUXA_SEL,
        oQ => sMUXA
    );
    
    i_MUXB : mux port map (
        iD0 => sR0,
        iD1 => sR1,
        iD2 => sR2,
        iD3 => sR3,
        iD4 => sR4,
        iD5 => sR5,
        iD6 => sR6,
        iD7 => sR7,
        iD8 => iDATA,
        iSEL => sMUXB_SEL,
        oQ => sMUXB
    );
    
    i_IR : reg generic map (
        WIDTH => 15
    ) port map (
        iCLK => iCLK,
        inRST => inRST,
        iD => iINSTR,
        iWE => sIR_WE,
        oQ => sIR
    );
    
    i_R0 : reg port map (
        iCLK => iCLK,
        inRST => inRST,
        iD => sC,
        iWE => sREG_WE(0),
        oQ => sR0
    );
    
    i_R1 : reg port map (
        iCLK => iCLK,
        inRST => inRST,
        iD => sC,
        iWE => sREG_WE(1),
        oQ => sR1
    );
    
    i_R2 : reg port map (
        iCLK => iCLK,
        inRST => inRST,
        iD => sC,
        iWE => sREG_WE(2),
        oQ => sR2
    );
    
    i_R3 : reg port map (
        iCLK => iCLK,
        inRST => inRST,
        iD => sC,
        iWE => sREG_WE(3),
        oQ => sR3
    );
    
    i_R4 : reg port map (
        iCLK => iCLK,
        inRST => inRST,
        iD => sC,
        iWE => sREG_WE(4),
        oQ => sR4
    );
    
    i_R5 : reg port map (
        iCLK => iCLK,
        inRST => inRST,
        iD => sC,
        iWE => sREG_WE(5),
        oQ => sR5
    );
    
    i_R6 : reg port map (
        iCLK => iCLK,
        inRST => inRST,
        iD => sC,
        iWE => sREG_WE(6),
        oQ => sR6
    );
    
    i_R7 : reg port map (
        iCLK => iCLK,
        inRST => inRST,
        iD => sC,
        iWE => sREG_WE(7),
        oQ => sR7
    );
    
    i_RA : reg port map (
        iCLK => iCLK,
        inRST => inRST,
        iD => sMUXA,
        iWE => sA_WE,
        oQ => sA
    );
    
    i_RB : reg port map (
        iCLK => iCLK,
        inRST => inRST,
        iD => sMUXB,
        iWE => sB_WE,
        oQ => sB
    );
    
    i_RC : reg port map (
        iCLK => iCLK,
        inRST => inRST,
        iD => sRESULT,
        iWE => sC_WE,
        oQ => sC
    );
    
    oPC <= sPC;
    oDATA <= sC;
    oADDR <= sMUXB;
    oMEM_WE <= sMEM_WE;
    
    oLED <= sC;

end Behavioral;
