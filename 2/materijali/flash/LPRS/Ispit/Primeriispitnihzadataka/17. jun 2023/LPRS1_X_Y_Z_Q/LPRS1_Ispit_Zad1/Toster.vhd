library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Toster is port ( 
	iCLK  	: in  std_logic;
	iRST  	: in  std_logic;
	iTOAST  	: in  std_logic;
	oDONE   	: out std_logic;
	oTEMP		: out std_logic_vector(7 downto 0);
	oTIME		: out std_logic_vector(5 downto 0)
	);
end entity;

architecture Behavioral of Toster is

	type tSTATES is (IDLE, WARMUP, TOAST, COOLDOWN);
	signal sSTATE, sNEXT_STATE : tSTATES;
	
	signal sTC1 : std_logic;
	signal sHEAT : std_logic;
	signal sEN : std_logic;
	signal sTC2 : std_logic;
	
	signal sTEMP : std_logic_vector(7 downto 0);
	signal sCNT : std_logic_vector(2 downto 0);
	signal sTIME : std_logic_vector(5 downto 0);
	
begin

	--Brojac
	process(iCLK) begin
		if(rising_edge(iCLK)) then
			if(iRST='1') then
				sCNT <= "000";
			elsif(sCNT=4) then
				sCNT <= "000";
			else
				sCNT <= sCNT + 1;
			end if;
		end if;
	end process;
	
	sTC1 <= '1' when sCNT=4 else '0';
	
	--Senzor za temp
	process(iCLK) begin
		if(rising_edge(iCLK)) then
			if(iRST='1') then
				sTEMP <= "00010100";
			elsif(sTC1='1' and sHEAT='1') then
				if(sTEMP<250) then
					sTEMP <= sTEMP + 10;
				else
					sTEMP <= sTEMP;
				end if;
			elsif(sTC1='0' and sHEAT='0') then
				if(sTEMP>20) then
					sTEMP <= sTEMP - 10;
				else
					sTEMP <= sTEMP;
				end if;
			end if;
		end if;
	end process;
	
	oTEMP <= sTEMP;
	
	--Tajmer za tostiranje
	process(iCLK) begin
		if(rising_edge(iCLK)) then
			if(iRST='1') then
				sTIME <= "111100";
			elsif(sEN='1') then
				if(sTIME=0) then
					sTIME <= "111100";
				else
					sTIME <= sTIME - 1;
				end if;
			end if;
		end if;	
	end process;
	
	oTIME <= sTIME;
	sTC2 <= '1' when sTIME=0 else '0';
	
	--Registar stanja
	process(iCLK) begin
		if(rising_edge(iCLK)) then
			if(iRST='1') then
				sSTATE <= IDLE;
			elsif(iTOAST='1') then
				sSTATE <= sNEXT_STATE;
			end if;
		end if;
	end process;
	
	process(sSTATE, iTOAST, sTEMP, sTC2) begin
	
		case sSTATE is 
			when IDLE =>
				if(iTOAST='1') then
					sNEXT_STATE <= WARMUP;
				else
					sNEXT_STATE <= IDLE;
				end if;
				
			when WARMUP =>
				if(sTEMP>100) then
					sNEXT_STATE <= TOAST;
				else 
					sNEXT_STATe <= WARMUP;
				end if;
				
			when TOAST =>
				if(sTC2='1') then
					sNEXT_STATE <= COOLDOWN;
				else
					sNEXT_STATE <= TOAST;
				end if;
				
			when COOLDOWN =>
				if(iTOAST='0' and sTEMP=20) then
					sNEXT_STATE <= IDLE;
				elsif(iTOAST='1' and sTEMP<100 and sTEMP>20) then
					sNEXT_STATE <= WARMUP;
				elsif(iTOAST='1' and sTEMP<200 and sTEMP>100) then
					sNEXT_STATE <= TOAST;
				else
					sNEXT_STATE <= COOLDOWN;
				end if;
					
			when others => sNEXT_STATE <= IDLE;
			
		end case;
	end process;
	
	--Funkcija izlaza
	oDONE <= '1' when sSTATE=COOLDOWN else '0';
	sHEAT <= '1' when (sSTATE=WARMUP or sSTATE=TOAST) else '0';
	sEN <= '1' when sSTATE=TOAST;
  

end Behavioral;
