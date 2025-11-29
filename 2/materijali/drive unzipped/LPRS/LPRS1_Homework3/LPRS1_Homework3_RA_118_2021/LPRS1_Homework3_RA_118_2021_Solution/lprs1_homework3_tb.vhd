library ieee;
use ieee.std_logic_1164.all;

entity lprs1_homework3_tb is
end entity;
 
architecture Test of lprs1_homework3_tb is
  
   signal sCLK		: std_logic := '0';
   signal sRST 	: std_logic := '0';
   signal sLEFT  : std_logic := '0';
	signal sRIGHT : std_logic := '0';
	signal soLEFT	: std_logic_vector(2 downto 0);
	signal soRIGHT	: std_logic_vector(2 downto 0);
	
	constant iCLK_period : time := 10 ns; 
   
	component lprs1_homework3 is port ( 
	iCLK  	: in  std_logic;
	iRST  	: in  std_logic;
	iLEFT  	: in  std_logic;
	iRIGHT  	: in  std_logic;
	oLEFT		: out std_logic_vector(2 downto 0);
	oRIGHT	: out std_logic_vector(2 downto 0)
	);
	end component;

begin

   uut: lprs1_homework3  port map (
          iCLK 	=> sCLK,
          iRST 	=> sRST,
			 iLEFT	=> sLEFT,
			 iRIGHT	=> sRIGHT,
          oLEFT 	=> soLEFT,
          oRIGHT 	=> soRIGHT
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
		wait for 3.25 * iCLK_period;
		sRST <= '0';
		
		sLEFT <= '1';
		wait for 21 * iCLK_period;
		sLEFT <= '0';
		
		wait for iCLK_period;
		
		-------------------------------------------------
		
		wait for 3.25 * iCLK_period;
		sRST <= '0';
		
		sRIGHT <= '1';
		wait for 21 * iCLK_period;
		sRIGHT <= '0';
		
		wait for iCLK_period;
		
		-------------------------------------------------
		
		sRST <= '1';
		wait for 5 * iCLK_period;
		
		sRST <= '0';
		
		sRIGHT <= '1';
		wait for 11 * iCLK_period;
		sRIGHT <= '0';

		wait for iCLK_period;
		sLEFT <= '1';
		wait for 25 * iCLK_period;
		
		sRST <= '1';
		wait;
		
   end process;
end architecture;
