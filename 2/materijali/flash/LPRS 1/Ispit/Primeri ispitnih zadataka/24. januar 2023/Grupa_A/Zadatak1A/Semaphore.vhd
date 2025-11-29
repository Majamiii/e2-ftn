library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Semaphore is port ( 
	iCLK  	: in  std_logic;
	iRST  	: in  std_logic;
	iSTART  	: in  std_logic;
	oRED   	: out std_logic;
	oGREEN	: out std_logic;
	oCNT		: out std_logic_vector(5 downto 0)
	);
end entity;

architecture Behavioral of Semaphore is

	type tSTATE is (IDLE, RED, GREEN, YELLOW);
	signal sSTATE, sNEXT_STATE : tSTATE;

	signal sRED_CNT : std_logic_vector(5 downto 0);
	signal sYELLOW_CNT : std_logic_vector(5 downto 0);
	signal sGREEN_CNT : std_logic_vector(5 downto 0);
	
	signal sR_EN : std_logic;
	signal sG_EN : std_logic;
	signal sY_EN : std_logic;
	
	signal sR_TC : std_logic;
	signal sG_TC : std_logic;
	signal sY_TC : std_logic;
	
begin
	
	--Brojac crvenog svetla mod 60
	process(iCLK) begin
		if(rising_edge(iCLK)) then
			if(iRST='1') then
				sRED_CNT <= "000000";
			elsif(sR_EN='1') then
				if(sRED_CNT=59) then
					sRED_CNT <= "000000";
				else
					sRED_CNT <= sRED_CNT + 1;
				end if;
			end if;
		end if;
	end process;
	
	sR_TC <= '1' when sRED_CNT=59 else '0';
	
	--Brojac zelenog svetla mod 20
	process(iCLK) begin
		if(rising_edge(iCLK)) then
			if(iRST='1') then
				sGREEN_CNT <= "000000";
			elsif(sG_EN='1') then
				if(sGREEN_CNT=29) then
					sGREEN_CNT <= "000000";
				else
					sGREEN_CNT <= sGREEN_CNT + 1;
				end if;
			end if;
		end if;
	end process;
	
	sG_TC <= '1' when sGREEN_CNT=29 else '0';
	
	--Brojac zutog svetla mod 10
	process(iCLK) begin
		if(rising_edge(iCLK)) then
			if(iRST='1') then
				sYELLOW_CNT <= "000000";
			elsif(sY_EN='1') then
				if(sYELLOW_CNT=9) then
					sYELLOW_CNT <= "000000";
				else
					sYELLOW_CNT <= sYELLOW_CNT + 1;
				end if;
			end if;
		end if;
	end process;
	
	sY_TC <= '1' when sYELLOW_CNT=9 else '0';
	
	--Registar stanja
	process(iCLK) begin
		if(rising_edge(iCLK)) then
			if(iRST='1') then
				sSTATE <= IDLE;
			else
				sSTATE <= sNEXT_STATE;
			end if;
		end if;
	end process;
	
	--Funkcija prelaza
	process(sSTATE, iSTART, sR_TC, sG_TC, sY_TC) begin
		case sSTATE is
			when IDLE =>
				if(iSTART='1') then
					sNEXT_STATE <= RED;
				else
					sNEXT_STATE <= IDLE;
				end if;
			
			when RED =>
				if(sR_TC='1') then
					sNEXT_STATE <= GREEN;
				else
					sNEXT_STATE <= RED;
				end if;
				
			when GREEN =>
				if(sG_TC='1') then
					sNEXT_STATE <= YELLOW;
				else
					sNEXT_STATE <= GREEN;
				end if;
			
			when YELLOW =>
				if(sY_TC='1') then
					sNEXT_STATE <= RED;
				else
					sNEXT_STATE <= YELLOW;
				end if;
				
			when others =>
				sNEXT_STATE <= IDLE;
				
		end case;
	end process;
	
	--Funkcija izlaza
	oRED <= '1' when (sSTATE=RED or sSTATE=YELLOW) else '0';
	oGREEN <= '1' when sSTATE=GREEN else '0';
	sR_EN <= '1' when sSTATE=RED else '0';
	sG_EN <= '1' when sSTATE=GREEN else '0';
	sY_EN <= '1' when sSTATE=YELLOW else '0';
	
	--Multiplekser
	process(sSTATE, sRED_CNT, sGREEN_CNT, sYELLOW_CNT) begin
		case sSTATE is 
			when RED => oCNT <= sRED_CNT;
			when GREEN => oCNT <= sGREEN_CNT;
			when others => oCNT <= sYELLOW_CNT;
		end case;
	end process;
	
end Behavioral;
