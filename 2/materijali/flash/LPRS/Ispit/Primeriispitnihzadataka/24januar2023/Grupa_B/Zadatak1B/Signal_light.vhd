library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Signal_light is port ( 
	iCLK  	: in  std_logic;
	iRST  	: in  std_logic;
	iLEFT  	: in  std_logic;
	iRIGHT  	: in  std_logic;
	oLEFT		: out std_logic_vector(2 downto 0);
	oRIGHT	: out std_logic_vector(2 downto 0)
	);
end entity;

architecture Behavioral of Signal_light is
	
	type tSTATE is (IDLE, L1,L2,L3,R1,R2,R3);
	signal sSTATE, sNEXT_STATE: tSTATE;
	signal sL_TC, sR_TC : std_logic;
	signal sL_RST, sR_RST : std_logic;
	signal sL_EN, sR_EN : std_logic;
	signal sL_CNT, sR_CNT : std_logic_vector(5 downto 0);
	
begin
	 -- levi brojac modula 10
	 process (iCLK,iRST)begin
		if (iRST = '1') then
			sL_CNT <= (others=>'0');
		elsif(rising_edge(iCLK)) then
			if (sL_RST = '1') then
				sL_CNT <= (others=>'0');
			elsif (iLEFT = '1') then
				if (sL_CNT=9) then
					sL_CNT <= (others =>'0');
				else
					sL_CNT <= sL_CNT +1;
				end if;			
			end if;
		end if;
	 end process;
	 
	 -- desni brojac modula 10
	 process (iCLK,iRST)begin
		if (iRST = '1') then
			sR_CNT <= (others=>'0');
		elsif(rising_edge(iCLK)) then
			if (sR_RST = '1') then
				sR_CNT <= (others=>'0');
			elsif (iRIGHT = '1') then
				if (sR_CNT=9) then
					sR_CNT <= (others =>'0');
				else
					sR_CNT <= sR_CNT +1;
				end if;			
			end if;
		end if;
	 end process;
	 
	 sL_TC <= '1' when sL_CNT=9 else '0';
	 sR_TC <= '1' when sR_CNT=9 else '0';
	 
	 -- registar stanja
	 process (iCLK,iRST)begin
		if(iRST='1') then
			sSTATE <= IDLE;
		elsif(rising_edge(iCLK))then
			sSTATE <= sNEXT_STATE;
		end if;
	 end process;
	 
	 -- funkcija prelaza
	 process(iCLK,iRST,iLEFT,iRIGHT,sL_EN,sR_EN)begin
			case (sSTATE) is
			
				when IDLE =>
					if (iLEFT='1') then
						sNEXT_STATE <= L1;
					elsif (iRIGHT = '1') then
						sNEXT_STATE <= R1;
					else
						sNEXT_STATE<=sSTATE;
					end if;
					
				when L1 =>
					if (iLEFT = '1' and sL_TC='1')then
						sNEXT_STATE <= L2;
					elsif (iLEFT = '0') then
						sNEXT_STATE <= IDLE;
					else
						sNEXT_STATE <= L1;
					end if;
					
				when L2 =>
					if (iLEFT = '1' and sL_TC='1')then
						sNEXT_STATE <= L3;
					elsif (iLEFT = '0') then
						sNEXT_STATE <= IDLE;
					else
						sNEXT_STATE <= L2;
					end if;
					
				when L3 =>
					if (iLEFT = '0' or sL_TC='1')then
						sNEXT_STATE <= IDLE;
					else
						sNEXT_STATE <= L3;
					end if;
					
				when R1 =>
					if (iRIGHT = '1' and sR_TC='1')then
						sNEXT_STATE <= R2;
					elsif (iRIGHT = '0') then
						sNEXT_STATE <= IDLE;
					else
						sNEXT_STATE <= R1;
					end if;
					
				when R2 =>
					if (iRIGHT = '1' and sR_TC='1')then
						sNEXT_STATE <= R3;
					elsif (iRIGHT = '0') then
						sNEXT_STATE <= IDLE;
					else
						sNEXT_STATE <= R2;
					end if;
				
				when R3 =>
					if (iRIGHT = '0' or sL_TC='1')then
						sNEXT_STATE <= IDLE;
					else
						sNEXT_STATE <= R3;
					end if;
				
				when others =>
					sNEXT_STATE <= IDLE;					
					
			end case;
	 end process;
	 
	 -- izlazi
	 oLEFT <= "001" when sSTATE=L1 else
				 "011" when sSTATE=L2 else
				 "111" when sSTATE=L3 else
				 "000";
	 oRIGHT <= "100" when sSTATE=R1 else
				  "110" when sSTATE=R2 else
				  "111" when sSTATE=R3 else
				  "000";
				  
	
	 sL_EN <= '1' when sSTATE = L1 or sSTATE=L2 or sSTATE=L3 else '0';
	 sR_EN <= '1' when sSTATE = R1 or sSTATE=R2 or sSTATE=R3 else '0';
	 
	 
	 sL_RST <= '1' when sSTATE = IDLE or sSTATE = R1 or sSTATE=R2 or sSTATE=R3 else '0';
	 sR_RST <= '1' when sSTATE = IDLE or sSTATE = L1 or sSTATE=L2 or sSTATE=L3 else '0';


end Behavioral;





















