library IEEE;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Zadatak is
    Port ( iCLK    : in  std_logic;
           iRST    : in  std_logic;
           iEN     : in  std_logic;
           iSEL    : in  std_logic_vector(1 downto 0);
           iDATA   : in	 std_logic_vector(4 downto 0);
			  oRESULT : out std_logic_vector(4 downto 0));
end Zadatak;

architecture Behavioral of Zadatak is

	signal sCNT 	: std_logic_vector(4 downto 0);
	signal sSHR		: std_logic_vector(4 downto 0);
	signal sEN		: std_logic;
	signal sCOMPL	: std_logic_vector(4 downto 0);
	signal sFx		: std_logic_vector(4 downto 0);
	signal sMUX		: std_logic_vector(4 downto 0);
begin

	-- Brojač po modulu 32 sa dozvolom brojanja
	process(iCLK, iRST) begin
		if(iRST = '1') then
			sCNT <= (others => '0');
		elsif(rising_edge(iCLK)) then
			if(iEN = '1') then
				if(sCNT = 31) then
					sCNT <= (others => '0');
				else
					sCNT <= sCNT + 1;
				end if;
			end if;
		end if;
	end process;
	
	sEN <= '1' when sCNT(0) = '0' else '0';
	
	-- Pomerački registar rotira svoju vrednost udesno kada je vrednost brojača parna.
	-- Bit koji bi „ispao“ pomeranjem udesno dolazi na mesto najznačajnijeg bita.
	-- Početna vrednost pomeračkog registra je 10.
	process(iCLK, iRST) begin
		if(iRST = '1') then
			sSHR <= "01010";
		elsif(rising_edge(iCLK)) then
			if(sEN = '1') then
				sSHR <= sSHR(0) & sSHR(4 downto 1);
			end if;
		end if;
	end process;
	
	-- Komplementer ulaza iDATA (posmatrati da je iDATA označen).
	sCOMPL <= not(iDATA) + 1;
	
	-- F(x) je blok čija je funkcionalnost opisana jednačinom F(x) = x+3.
	-- Vrednost brojača je ulaz za blok F(x).
	sFx <= sCNT + 3;
	
	-- Multiplekser prosleđuje F(x), iz pomeračkog registra, komplementera ili konstantu 17
	sMUX <= 	sFx when iSEL = 0 else
				sSHR when iSEL = 1 else
				sCOMPL when iSEL = 2 else
				"10001";

	oRESULT <= sMUX;
	
end Behavioral;