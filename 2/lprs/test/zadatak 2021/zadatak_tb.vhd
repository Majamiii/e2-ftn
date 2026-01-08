library ieee;
use ieee.std_logic_1164.all;

entity zadatak_tb is
end zadatak_tb;

architecture Test_tb of zadatak_tb is
	signal sCLK 	: std_logic;
	signal sRST 	: std_logic := '0';
	signal sEN 		: std_logic := '0';
	signal sA	   : std_logic_vector(7 downto 0); -- ulazi u pomerac, comp2
	signal sB	   : std_logic_vector(4 downto 0); -- ulazi u blok F(x), comp2
	signal sC	   : std_logic_vector(6 downto 0); -- prvi sabirak, c2
	signal sD	   : std_logic_vector(6 downto 0); -- drugi sabirak, c2
	signal sRESULT : std_logic_vector(7 downto 0); -- izlaz iz MUX, c2
	signal sCOMP   : std_logic;	-- izlaz iz komparatora
	
	constant iCLK_period : time := 10 ns;

component zadatak is
    Port ( iCLK    : in  std_logic;
           iRST    : in  std_logic;
           iEN     : in  std_logic;
			  iA		 : in std_logic_vector(7 downto 0); -- ulazi u pomerac, comp2
			  iB		 : in std_logic_vector(4 downto 0); -- ulazi u blok F(x), comp2
			  iC		 : in std_logic_vector(6 downto 0); -- prvi sabirak, c2
			  iD		 : in std_logic_vector(6 downto 0); -- drugi sabirak, c2
			  oRESULT : out std_logic_vector(7 downto 0); -- izlaz iz MUX, c2
			  oCOMP   : out std_logic	-- izlaz iz komparatora
			  );
end component;

begin

	uut : zadatak port map (
		iCLK 		=> sCLK,
		iRST 		=> sRST,
		iEN		=> sEN,
		iA 		=> sA,
		iB 		=> sB,
		iC 		=> sC,
		iD 		=> sD,
		oCOMP 	=> sCOMP,
		oRESULT	=> sRESULT
	);

	iCLK_process: process
		begin
			sCLK <= '0';
			wait for iCLK_period / 2; 
			sCLK <= '1';
			wait for iCLK_period / 2;
	end process; 

	
	stimulus : process
	begin		
		
		sA <= "00000000";
		sB <= "00000";
		sC <= "0100000";
		sD <= "0011000";
		
		sRST<='1';
		wait for 5.25*iCLK_period;
		
		sRST<='0';
		sEN <='1';
		wait for 25*iCLK_period;
		
		sEN <= '0';
		-- napravio pun krug, sad ce se zaglaviti na 00
		sA <= "10011111"; -- bitno da je 1 na prvom mestu
		wait for 5*iCLK_period;
		sA <= "01010101";
		wait for 5*iCLK_period;
		
		sB <= "01000";
		sEN<='1';
		wait for 1*iCLK_period;
		sEN<='0';
		wait for 4*iCLK_period;
		sB <= "00111";
		wait for 5*iCLK_period;
		sB <= "11101";
		wait for 5*iCLK_period;
		
		
		sEN<='1';
		wait for 1*iCLK_period;
		sEN<='0';
		wait for 3*iCLK_period;
		-- 32+24=56
		sC <= "0000011";
		sD <= "0000100";
		-- 7
		wait for 4*iCLK_period;
		
		sEN <= '1';
		wait for 1*iCLK_period;
		sEN<='0';
		wait for 4*iCLK_period;
		
		
		--	Podesiti barem jedan slučaj da izlaz iz komparatora bude ‘1’ i barem jedan da izlaz iz komparatora bude 
		--	‘0’ 
		
		-- slucaj da je 1 : iC i iD su negativni brojevi, sabiramo ih
		sEN <= '1';
		wait for 3*iCLK_period;
		sEN <= '0';
		
		sD <= "1000010";
		sC <= "1000001";
		wait for 10*iCLK_period;
		
		-- slucaj da je 0 : konstanta;
		sEN <= '1';
		wait for 1*iCLK_period;
		sEN<='0';
		wait for 10*iCLK_period;

		
		
		wait;
	end process stimulus;

end architecture;