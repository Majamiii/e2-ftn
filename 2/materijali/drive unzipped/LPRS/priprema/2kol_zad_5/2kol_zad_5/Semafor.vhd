library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Semafor is
    port ( 	iCLK    : in  std_logic;
				inRST    : in  std_logic;
				icar    : in  std_logic_vector (1 downto 0);
				
				oTOTAL    : out std_logic_vector(7 downto 0);
				oOPEN : out std_logic;
				oWARNING : out std_logic
				);
end Semafor;

architecture Behavioral of Semafor is
	
	signal sRESET : std_logic;
	signal sCNT : std_logic_vector (3 downto 0);
	signal sENABLE: std_logic;
	type stanje is (IDLE, WARNING, OPEN_MEMBER, FREE_ENTRY, OPEN_GUEST);
	signal sstate,snext_state : stanje;
	signal sTOTAL : std_logic_vector(7 downto 0);
	

begin

	-------------------------AUTOMAT-----------------------------------------

	process (iCLK, inRST) begin
		if(inRST = '1') then
			sSTATE <= IDLE;
		elsif(rising_edge(iCLK)) then
			sSTATE <= sNEXT_STATE;
		end if;
	end process;
 
 
	process(iCAR, iCLK, inRST, sCNT) begin 
		case (SSTATE) is
			when IDLE => 
				if(iCAR = "10") then
					sNEXT_STATE <= WARNING;
				elsif(iCAR  = "01") then
					sNEXT_STATE <= OPEN_MEMBER;
				else 
					sNEXT_STATE <= sSTATE;
				end if;
				
			when WARNING =>
				sNEXT_STATE <= IDLE;
			
			when OPEN_MEMBER =>
				sNEXT_STATE <= FREE_ENTRY;
			
			when FREE_ENTRY => 
				if (iCAR = "10") then
					sNEXT_STATE <= OPEN_GUEST;
				elsif(sCNT = 14) then
					sNEXT_STATE <= IDLE;
				else 
					sNEXT_STATE <= sSTATE;
				end if;
			when OPEN_GUEST =>
				sNEXT_STATE <= IDLE;
			
			when others =>
				sNEXT_STATE <= IDLE;
		end case;
	end process;
	
	
			
			--izlazni signali automata-
			
	oOPEN <= sENABLE;

	sENABLE <=   '1' when sSTATE = OPEN_MEMBER or sSTATE = OPEN_GUEST else
				    '0'; 
	
	oWARNING <=  '1' when sSTATE = WARNING else
				    '0'; 
	
	sRESET <=    '0' when sSTATE = FREE_ENTRY else 
					 '1';
			-----------------------------
			
			
			
	------------------------------------------------------------------
						--==counter 1===--
	
	process(iCLK, sRESET) begin
		if (sRESET = '1') then
			sCNT <= "0000";
		elsif(rising_edge(iCLK)) then
			if(sCNT < 14) then	
				sCNT <= sCNT + 1;
			elsif(sCNT = 14) then
				sCNT <= "0000";
			end if;
		end if;
	end process;	
	------------------------------------------------------------------
	
	process(iCLK, inRST, sENABLE) begin
		if(sRESET = '1') then
			sTOTAL <= "00000000";
		elsif(sENABLE = '1') then
				if (rising_edge(iCLK)) then
					sTOTAL <= sTOTAL + 1;
				end if;
		end if;
	end process;
	
	
	oTOTAL <= sTOTAL;
	
	
	
end Behavioral;