library ieee;
use ieee.std_logic_1164.all;

entity Door_lock_tb is
end entity;
 
architecture Test of Door_lock_tb is
  
   signal sCLK			: std_logic := '0';
   signal sRST 		: std_logic := '0';
   signal sNEW_REQ 	: std_logic := '0';
	signal sCODE		: std_logic_vector(3 downto 0) := "0000";
   signal sSTATUS 	: std_logic;
	signal sWARNING	: std_logic;
	
	constant iCLK_period : time := 10 ns; 
   
	component Door_lock is port ( 
	iRST  	: in  std_logic;
	iCLK  	: in  std_logic;
	iNEW_REQ	: in  std_logic;
	iCODE		: in  std_logic_vector(3 downto 0);
	oSTATUS	: out std_logic;
	oWARNING	: out std_logic
	);
	end component;

begin

   uut: Door_lock port map (
      iRST  	=>	sRST,
		iCLK  	=> sCLK,
		iNEW_REQ	=> sNEW_REQ,
		iCODE  	=> sCODE,
		oSTATUS 	=> sSTATUS,
		oWARNING	=> sWARNING
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
