library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity GrupaB is
	port ( 
			iCLK  	:  in std_logic;
			iRST  	:  in std_logic;
			iDATA		:  in std_logic_vector(7 downto 0);
			iEN   	:  in std_logic;
			iLOAD   	:  in std_logic;
			oCODE 	: out std_logic_vector(2 downto 0);
			oCNTG		: out std_logic_vector(3 downto 0);
			oCNTS		: out std_logic_vector(3 downto 0)
	);
end entity;

architecture Behavioral of GrupaB is

	signal sCOMP : std_logic_vector(7 downto 0);
	signal sROR : std_logic_vector(7 downto 0);
	signal sENG, sENS : std_logic;
	signal sGREAT : std_logic;
	signal sCNTG		:  std_logic_vector(3 downto 0);
	signal sCNTS		:  std_logic_vector(3 downto 0);
	

begin

	--Komplementer
	sCOMP <= not(iDATA - 1);
	
	--Rotirajuci registar
	process(iCLK) begin
		if(rising_edge(iCLK)) then
			if(iRST = '1') then
				sROR <= "00000000";
			elsif(iEN='1') then
				if(iLOAD='1') then
					sROR <= sCOMP;
				else
					sROR <= sCOMP(6 downto 0) & sCOMP(7);
				end if;
			end if;
		end if;
	end process;	
			
	--Prioritetni koder
	oCODE <= "111" when sROR(7)='1' else
				"110" when sROR(6)='1' else
				"101" when sROR(5)='1' else
				"100" when sROR(4)='1' else
				"011" when sROR(3)='1' else
				"010" when sROR(2)='1' else
				"001" when sROR(1)='1' else
				"000";
				
	--Komparator
	sGREAT <= '1' when sROR > 5 else
				 '0';
	
	sENG <= 	'1' when sGREAT='1' else
				'0';
	
	sENS <= 	'1' when sGREAT='0' else
				'0';
				
	--Brojac vecih
	process(iCLK) begin
		if(rising_edge(iCLK)) then
			if(iRST='1') then
				sCNTG <= "0000";
			elsif(sENG='1') then
				if(sCNTG = "1111") then
					sCNTG <= "0000";
				else
					sCNTG <= sCNTG +1;
				end if;
			end if;
		end if;
	end process;
	
	oCNTG <= sCNTG;
	
	--Brojac manjih
	process(iCLK) begin
		if(rising_edge(iCLK)) then
			if(iRST='1') then
				sCNTS <= "0000";
			elsif(sENS='1') then
				if(sCNTS = "1111") then
					sCNTS <= "0000";
				else
					sCNTS <= sCNTS +1;
				end if;
			end if;
		end if;
	end process;
	
	oCNTS <= sCNTS;

end Behavioral;
