library ieee;
use ieee.std_logic_1164.all;

entity Semaphore_tb is
end entity;
 
architecture Test of Semaphore_tb is
  
   signal sCLK		: std_logic := '0';
   signal sRST 	: std_logic := '0';
   signal sSTART  : std_logic := '0';
	signal sRED    : std_logic;
	signal sGREEN	: std_logic;
	signal sCNT		: std_logic_vector(5 downto 0);
	
	constant iCLK_period : time := 10 ns; 
   
	component Semaphore is port ( 
	iCLK  	: in  std_logic;
	iRST  	: in  std_logic;
	iSTART  	: in  std_logic;
	oRED   	: out std_logic;
	oGREEN	: out std_logic;
	oCNT		: out std_logic_vector(5 downto 0)
	);
	end component;

begin

   uut: Semaphore port map (
          iCLK 	=> sCLK,
          iRST 	=> sRST,
			 iSTART	=> sSTART,
			 oRED		=> sRED,
          oGREEN 	=> sGREEN,
          oCNT 	=> sCNT
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
		wait for 5.25*iCLK_period;
		sRST <= '0';
		
		sSTART <= '1';
		wait for 270*iCLK_period;
		sSTART <= '0';
		
		sRST <= '1';
		wait for 5*iCLK_period;
		sRST <= '0';
		
		sSTART <= '1';
		wait for 180*iCLK_period;
		sSTART <= '0';
		
		sRST <= '1';
		
		wait;
   end process;
end architecture;
