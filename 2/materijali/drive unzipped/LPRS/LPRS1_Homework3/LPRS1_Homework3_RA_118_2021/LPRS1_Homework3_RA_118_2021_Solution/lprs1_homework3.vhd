library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

-- Libraries.

entity lprs1_homework3 is
	port(
		iCLK  	: in  std_logic;
		iRST  	: in  std_logic;
		iLEFT  	: in  std_logic;
		iRIGHT  	: in  std_logic;
		oLEFT		: out std_logic_vector(2 downto 0);
		oRIGHT	: out std_logic_vector(2 downto 0)
	);
end entity;


architecture arch of lprs1_homework3 is
	type tSTATE is (IDLE, R1, R2, R3, L1, L2, L3);
	signal sSTATE, sNEXT_STATE: tSTATE;
	
	signal sR_EN, sL_EN, sRST_R, sRST_L : std_logic;
	signal sTC_L, sTC_R : std_logic_vector(3 downto 0);

begin
	
	process(iCLK, iRST) begin 
		if (iRST = '1') then
			sSTATE <= IDLE;
		elsif (rising_edge(iCLK)) then
			sSTATE <= sNEXT_STATE;
		end if;
	end process;
	
	process(sSTATE, sTC_L, sTC_R, iLEFT, iRIGHT, iCLK, iRST) begin
		
		case (sSTATE) is
			when IDLE =>
				if(iLEFT = '1') then 
					sNEXT_STATE <= L1;
				elsif(iRIGHT = '1') then
					sNEXT_STATE <= R1;
				else
					sNEXT_STATE <= sSTATE;
				end if;
				
			when L1 => 
				if(sTC_L = "1001" and iLEFT = '1') then
					sNEXT_STATE <= L2;
				elsif(iLEFT = '0') then
					sNEXT_STATE <= IDLE;
				else
					sNEXT_STATE <= sSTATE;
				end if;
			
			when L2 => 
				if(sTC_L = "1001" and iLEFT = '1') then
					sNEXT_STATE <= L3;
				elsif(iLEFT = '0') then
					sNEXT_STATE <= IDLE;
				else
					sNEXT_STATE <= sSTATE;
				end if;
			
			when L3 => 
				if(sTC_L = "1001" or iLEFT = '0') then
					sNEXT_STATE <= IDLE;
				else
					sNEXT_STATE <= sSTATE;
				end if;
			
			when R1 => 
				if(sTC_R = "1001" and iRIGHT = '1') then
					sNEXT_STATE <= R2;
				elsif(iRIGHT = '0') then
					sNEXT_STATE <= IDLE;
				else
					sNEXT_STATE <= sSTATE;
				end if;
				
			when R2 => 
				if(sTC_R = "1001" and iRIGHT = '1') then
					sNEXT_STATE <= R3;
				elsif(iRIGHT = '0') then
					sNEXT_STATE <= IDLE;
				else
					sNEXT_STATE <= sSTATE;
				end if;
				
			when R3 => 
				if(sTC_R = "1001" or iRIGHT = '0') then
					sNEXT_STATE <= IDLE;
				else
					sNEXT_STATE <= sSTATE;
				end if;
				
			when others => 
				sNEXT_STATE <= IDLE;
		end case;
	end process;
	
	
	sR_EN <=  '1' when sSTATE = R1 or sSTATE = R2 or sSTATE = R3 else
			    '0';
				
	sL_EN <=  '1' when sSTATE = L1 or sSTATE = L2 or sSTATE = L3 else
			    '0';
				
	sRST_r <= '1' when sSTATE = IDLE or sSTATE = L1 or sSTATE = L2 
									or sSTATE = L3 else
			    '0';
				
	sRST_l <= '1' when sSTATE = IDLE or sSTATE = R1 or sSTATE = R2 
									or sSTATE = R3 else
			    '0';
	
	oLEFT <=  "001" when sSTATE = L1 else
				 "011" when sSTATE = L2 else
				 "111" when sSTATE = L3 else
				 "000";
				 
				 
	oRIGHT <= "100" when sSTATE = R1 else
				 "110" when sSTATE = R2 else
				 "111" when sSTATE = R3 else
				 "000";
	
	-- levi brojac
	
	process (iCLK, IRST) begin 
		if(iRST = '1') then
			sTC_L <= "0000";
		elsif(rising_edge(iCLK)) then
			if (sL_EN = '1') then
				if(sTC_L < 9) then
					sTC_L <= sTC_L + 1;
				elsif(sTC_L >= 9) then
					sTC_L <= "0000";
				end if;
			end if;
		end if;
	end process;
	

	--desni brojac
	
	process (iCLK, IRST) begin 
		if(iRST = '1') then
			sTC_R <= "0000";
		elsif(rising_edge(iCLK)) then
			if (sR_EN = '1') then
				if(sTC_R < 9) then
					sTC_R <= sTC_R + 1;
				elsif(sTC_R >= 9) then
					sTC_R <= "0000";
				end if;
			end if;
		end if;
	end process;


	
end architecture;