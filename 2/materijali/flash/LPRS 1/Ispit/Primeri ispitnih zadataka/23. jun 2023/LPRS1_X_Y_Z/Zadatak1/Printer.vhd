---------------------------------------------
-- Ime i prezime: 
-- Broj indeksa: 
---------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Printer is port ( 
	iCLK  		: in  std_logic;
	iRST  		: in  std_logic;
	iPRINT  	: in  std_logic;
	iADD_PAPER  : in  std_logic;
	iAMOUNT		: in  std_logic_vector(7 downto 0);
	oPRINT		: out std_logic;
	oERROR		: out std_logic
	);
end entity;

architecture Behavioral of Printer is
  signal sEMPTY : std_logic; 
  signal sPAPER_EN : std_logic;
  signal sSLEEP_EN: std_logic;
  signal sSLEEP_TC: std_logic;
  signal sPRINT_EN: std_logic;
  signal sPRINT_TC: std_logic;
  signal sSLEEP_CNT : std_logic_vector(5 downto 0); -- modul 60
  signal sPRINT_CNT : std_logic_vector(3 downto 0); --modul 15
  signal sPAPER_CNT : std_logic_vector(7 downto 0);
  
  type state_type is (IDLE, SLEEP, CHECK_PAPER, PRINT, ERROR); 
  signal state, state_next : state_type;
  ---
	
begin
	--registar stanja (asinhroni reset)
	process(iCLK,iRST) begin
	
		if(iRST ='1') then
			state <= IDLE;
		elsif(rising_edge(iCLK)) then
			state <= state_next;
		end if;
	end process;

	--automat
	process(state,state_next,iPRINT,sSLEEP_TC,sEMPTY,sPRINT_TC) begin
	
	case (state) is
	
	when IDLE =>
		if (iPRINT = '1') then
			state_next <= CHECK_PAPER;
		elsif(sSLEEP_TC = '1') then
			state_next <= SLEEP;
		else
			state_next <= IDLE;
		end if;
		
	when SLEEP =>
		if(iPRINT = '1') then
			state_next <= IDLE;
		else
			state_next <= SLEEP;
		end if;
		
	when CHECK_PAPER =>
		if(sEMPTY = '0') then
			state_next <= PRINT;
		elsif(sEMPTY = '1') then
			state_next <= ERROR;
		else
			state_next <= CHECK_PAPER;
		end if;
		
	when ERROR =>
		state_next <= IDLE;
		
	when PRINT =>
		if(sPRINT_TC = '1') then
			state_next <= IDLE;
		else
			state_next <= PRINT;
		end if;
		
	when others =>
		state_next <= IDLE;
	
	end case;
	
	end process;
	
	--funkcija izlaza automata
	
	oPRINT <= '1' when state = PRINT else '0';
	oERROR <= '1' when state = ERROR else '0';
	sSLEEP_EN <= '1' when state = IDLE else '0';
	sPRINT_EN <= '1' when state = PRINT else '0';
	sPAPER_EN <= '1' when state = CHECK_PAPER else '0';
	
	--brojac 1 (brojac za neaktivno stanje)
	process(iCLK,iRST) begin
	
		if(iRST = '1') then
			sSLEEP_CNT <= (others=>('0'));
			sSLEEP_TC <= '0';
		elsif(rising_edge(iCLK)) then
			if(sSLEEP_EN = '1') then
				if(sSLEEP_CNT = "111011") then -- 59 binarno
					sSLEEP_CNT <= (others=>('0'));
					sSLEEP_TC <= '1';
				else
					sSLEEP_CNT <= sSLEEP_CNT +1;
					sSLEEP_TC <= '0';
				end if;
			else
				sSLEEP_CNT <= (others=>('0'));
				sSLEEP_TC <= '0';
			end if;
		end if;
	end process;
	
	--brojac 2 (brojac za stampanje)
	process(iCLK,iRST) begin
		
		if(iRST = '1') then
			sPRINT_CNT <= (others=>('0'));
			sPRINT_TC <= '0';
		elsif(rising_edge(iCLK)) then
			if(sPRINT_EN = '1') then
				if(sPRINT_CNT = "1110") then -- 14 binarno
					sPRINT_CNT <= "0000";
					sPRINT_TC <= '1';
				else
					sPRINT_CNT <= sPRINT_CNT +1;
					sPRINT_TC <= '0';
				end if;
			else
				sPRINT_CNT <= "0000";
				sPRINT_TC <= '0';
			end if;
		end if;
	end process;
	
	
	--brojac 3(brojac za papir)
	process(iCLK,iRST) begin
	
		if(iRST = '1') then
			sPAPER_CNT <= (others=>('0')); --nisam siguran za ovo
			sEMPTY <= '1';
		elsif(rising_edge(iCLK)) then
			if(sPAPER_EN = '1') then
				if(iADD_PAPER = '1') then
					sPAPER_CNT <= sPAPER_CNT + iAMOUNT;
				end if;
				
				if(sPAPER_CNT = "00000000") then
					sEMPTY <= '1';
				else
					sEMPTY <= '0';
					sPAPER_CNT <= sPAPER_CNT - 1;
				end if;
			end if;	
		end if;
	end process;
	
end Behavioral;
