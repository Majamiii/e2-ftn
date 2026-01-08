library ieee;
use ieee.std_logic_1164.all;

entity Zadatak_tb is
end Zadatak_tb;

architecture Test_tb of Zadatak_tb is
	signal sCLK 	: std_logic;
	signal sRST 	: std_logic := '0';
	signal sEN 		: std_logic := '0';
	signal sSEL 	: std_logic_vector(1 downto 0) := "00";
	signal sDATA 	: std_logic_vector(4 downto 0) := "00000";
	signal sRESULT : std_logic_vector(4 downto 0);
	
	constant iCLK_period : time := 10 ns;

component Zadatak is
    Port ( iCLK    : in  std_logic;
           iRST    : in  std_logic;
           iEN     : in  std_logic;
           iSEL    : in  std_logic_vector(1 downto 0);
           iDATA   : in	 std_logic_vector(4 downto 0);
			  oRESULT : out std_logic_vector(4 downto 0));
end component;

begin

	uut : Zadatak port map (
		iCLK 		=> sCLK,
		iRST 		=> sRST,
		iEN 		=> sEN,
		iSEL 		=> sSEL,
		iDATA 	=> sDATA,
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
		--	Resetovati sistem 2.25 perioda takta
		sRST <= '1';
		wait for 2.25*iCLK_period;
		sRST <= '0';
		
		-- 10 perioda takta prikazivati izlaz iz F(x)
		sEN <= '1';
		sSEL <= "00";
		wait for 10*iCLK_period;
		
		-- 20 perioda takta prikazivati izlaz iz pomeračkog registra
		-- ali tako da barem 5 uzastopnih perioda takta registar ne promeni svoju vrednost
		sSEL <= "01";
		wait for 9*iCLK_period; -- neparna vrednost brojača
		sEN <= '0';
		wait for 5*iCLK_period;
		sEN <= '1';
		wait for 6*iCLK_period;
		
		-- Prikazati kao izlaz iz komplementera vrednost -4 i zadržati na izlazu 2 periode takta
		sDATA <= "00100";
		sSEL <= "10";
		wait for 2*iCLK_period;
		
		-- 5 perioda takta prikazivati na izlazu konstantu 17
		sSEL <= "11";
		wait for 5*iCLK_period;
		wait;
	end process stimulus;

end architecture;