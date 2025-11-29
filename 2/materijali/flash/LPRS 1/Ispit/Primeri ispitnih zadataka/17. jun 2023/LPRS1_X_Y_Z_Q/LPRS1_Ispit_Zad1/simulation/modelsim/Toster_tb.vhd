library ieee;
use ieee.std_logic_1164.all;

entity Toster_tb is
end entity;
 
architecture Test of Toster_tb is
  
   signal sCLK		: std_logic := '0';
   signal sRST 	: std_logic := '0';
   signal sTOAST  : std_logic := '0';
	signal sDONE   : std_logic;
	signal sTEMP	: std_logic_vector(7 downto 0);
	signal sTIME	: std_logic_vector(5 downto 0);
	
	constant iCLK_period : time := 10 ns; 
   
	component Toster is port ( 
		iCLK  	: in  std_logic;
		iRST  	: in  std_logic;
		iTOAST  	: in  std_logic;
		oDONE   	: out std_logic;
		oTEMP		: out std_logic_vector(7 downto 0);
		oTIME		: out std_logic_vector(5 downto 0)
	);
	end component;

begin

   uut: Toster port map (
          iCLK 	=> sCLK,
          iRST 	=> sRST,
			 iTOAST	=> sTOAST,
			 oDONE	=> sDONE,
          oTEMP 	=> sTEMP,
          oTIME 	=> sTIME
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
	
		
		
		
		wait;
   end process;
end architecture;
