library ieee;
use ieee.std_logic_1164.all;

entity FSM_game_tb is
end entity;
 
architecture Test of FSM_game_tb is
  
   signal sCLK	: std_logic := '0';
   signal sRST : std_logic := '0';
   signal sA 	: std_logic_vector(1 downto 0) := "00";
	signal sB 	: std_logic_vector(1 downto 0) := "00";
   signal sOA 	: std_logic;
	signal sOB 	: std_logic;
	
	constant iCLK_period : time := 10 ns; 
   
	component FSM_game is port ( 
		iRST  : in  std_logic;
		iCLK  : in  std_logic;
		iA	   : in  std_logic_vector(1 downto 0);
		iB	   : in  std_logic_vector(1 downto 0);
		oA  	: out std_logic;
		oB  	: out std_logic
		);
	end component;

begin

   uut: FSM_game port map (
          iCLK => sCLK,
          iRST => sRST,
			 iA	=> sA,
			 iB	=> sB,
          oA => sOA,
          oB => sOB
        );

		  
	iCLK_process: process
	begin
		sCLK <= '0';
		wait for iCLK_period / 2; -- iCLK_period je konstanta
		sCLK <= '1';
		wait for iCLK_period / 2;
	end process;

   stim_proc : process
   begin		
	
		sRST <= '1';
		wait for 2.25*iclk_period;
		sRST <= '0';
		
		-- prva partija: A je pobedio, nema specijalnih poteza i svako je osvojio bar 1 poen
		sB <= "01";					-- B_LEAD
		wait for iCLK_period;
		sB <= "00";
		
		sA <= "01";					-- DRAW, A_LEAD, A_WIN
		wait for 3*iCLK_period;
		sA <= "00";
		
		sRST <= '1';
		wait for 20*iclk_period;
		sRST <= '0';
		 
		-- druga partija:
		sB <= "01";					-- B_LEAD
		wait for iCLK_period;
		sB <= "00";
		
		sA <= "10";					-- A_LEAD
		wait for iCLK_period;
		sA <= "00";
		
		sB <= "10";					-- B_LEAD
		wait for iCLK_period;
		sB <= "00";
		
		sB <= "01";					-- B_WIN
		wait for iCLK_period;
		sB <= "00";
		wait;
   end process;
end architecture;
