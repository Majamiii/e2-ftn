library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Door_lock is port ( 
	iRST  	: in  std_logic;
	iCLK  	: in  std_logic;
	iNEW_REQ	: in  std_logic;
	iCODE		: in  std_logic_vector(3 downto 0);
	oSTATUS	: out std_logic;
	oWARNING	: out std_logic
	);
end entity;

architecture Behavioral of Door_lock is
	
	type tSTATES is(IDLE, CHECK_REQUEST, FIRST, SECOND, THIRD, FOURTH, UNLOCK, PAUSE, WARNING);
	signal sSTATE,sNEXT_STATE : tSTATES;
	signal sIDLE_EN 			: 	std_logic;
	signal sIDLE_CNT  		:	std_logic_vector(2 downto 0);
	signal sIDLE_TC 			:	std_logic;
	signal sCLEAR 				:	std_logic;
	signal sNEW_REQ			: 	std_logic;
	signal sCODE_EN			:	std_logic;
	signal sCODE_CNT			: 	std_logic_vector(1 downto 0);
	signal sUNLOCK_EN			: 	std_logic;
	signal sUNLOCK_CNT		: 	std_logic_vector(4 downto 0);
	signal sUNLOCK_TC			: 	std_logic;
	signal sNEXT_EN 			:	std_logic;
	signal sNEXT_CNT 			:	std_logic_vector(3 downto 0);
	signal sNEXT_TC 			:	std_logic;

	
begin

	-- prvi brojač po modulu 5 za proveru zahteva
	process (iCLK, iRST) begin
		if (iRST = '1') then
			sIDLE_CNT <= "000";
		elsif (iCLK'event and iCLK = '1') then
			if(sIDLE_EN = '1') then
				if(sIDLE_CNT = 4) then
					sIDLE_CNT <= "000";
				else
					sIDLE_CNT <= sIDLE_CNT + 1;
				end if;
			end if;
		end if;
	end process;
	
	-- Dozvolu brojanja ovom brojaču daje automat kada se nalazi u stanju IDLE
	sIDLE_EN <= '1' when sSTATE = IDLE else '0';
	
	-- Kada izbroji do kraja, brojač javlja automatu da je istekao traženi vremenski period
	sIDLE_TC <= '1' when sIDLE_CNT = 4 else '0';
	
	-- Drugi brojač je zadužen za kontrolu rada automata kada stanar krene da unosi šifru za vrata
	-- (odbrojava vreme za koje korisnik treba da unese novu cifru).
	-- On je modula 10 i broji na svaku rastuću ivicu ako ima dozvolu brojanja koju mu daje automat
	-- kada se nalazi u stanju PAUSE.
	-- Kada izbroji do kraja, javlja automatu da je istekao traženi vremenski period.
	
	process (iCLK, iRST) begin
		if (iRST = '1') then
			sNEXT_CNT <= "1001";
		elsif (iCLK'event and iCLK = '1') then
			if(sNEXT_EN = '1') then
				if(sNEXT_CNT = 0) then
					sNEXT_CNT <= "1001";
				else
					sNEXT_CNT <= sNEXT_CNT - 1;
				end if;
			end if;
		end if;
	end process;

	sNEXT_EN <= '1' when sSTATE = PAUSE else '0';
	sNEXT_TC <= '1' when sNEXT_CNT = 0 else '0';
	
	-- Treći brojač služi za kontrolu vrata kada se jednom otključaju.
	-- Ovaj brojač određuje koliko dugo će vrata biti otključana.
	-- On je modula 30 i broji na svaku rastuću ivicu ako ima dozvolu brojanja
	-- Dozvolu brojanja mu daje automat kada se nalazi u stanju UNLOCK.
	-- Kada izbroji do kraja, javlja automatu da je istekao traženi vremenski period.
	process (iCLK, iRST) begin
		if (iRST = '1') then
			sUNLOCK_CNT <= "00000";
		elsif (iCLK'event and iCLK = '1') then
			if(sUNLOCK_EN = '1') then
				if(sUNLOCK_CNT = 29) then
					sUNLOCK_CNT <= "00000";
				else
					sUNLOCK_CNT <= sUNLOCK_CNT + 1;
				end if;
			end if;
		end if;
	end process;
	sUNLOCK_EN <= '1' when sSTATE = UNLOCK else '0';
	sUNLOCK_TC <= '1' when sUNLOCK_CNT = 29 else '0';
	
	-- Četvrti brojač ne meri vremenski period već broji koliko je karaktera šifre obrađeno.
	-- Uvećava svoju vrednost na rastuću ivicu ako ima dozvolu brojanja.
	-- Dozvolu brojanja mu daje automat kada se nalazi u stanjima FIRST, SECOND ili THIRD.
	-- Kada je cela sekvenca od 4 karaktera prošla treba resetovati brojač.
	
	process (iCLK, iRST) begin
		if (iRST = '1') then
			sCODE_CNT <= "00";
		elsif (iCLK'event and iCLK = '1') then
			if(sCODE_EN = '1') then
				if(sCODE_CNT = 3) then
					sCODE_CNT <= "00";
				else
					sCODE_CNT <= sCODE_CNT + 1;
				end if;
			end if;
		end if;
	end process;
	
	sCODE_EN <= '1' when (sSTATE = FIRST or sSTATE = SECOND or sSTATE = THIRD) else '0';
	
	-- Registar za obradu zahteva je jednobitan i očitava da li se pojavio novi zahtev iNEW_REQ
	-- Kada se pojavi novi zahtev, on pamti tu vrednost sve dok automat ne obradi taj zahtev i postavi
	-- registar opet na početnu vrednost ‘0’ signalom sCLEAR.
	process (iCLK, iRST) begin
		if (iRST = '1') then
			sNEW_REQ <= '0';
		elsif (iCLK'event and iCLK = '1') then
			if(iNEW_REQ = '1') then
				sNEW_REQ <= iNEW_REQ;
			elsif(sCLEAR = '1') then
				sNEW_REQ <= '0';
			end if;
		end if;
	end process;
	
	sCLEAR <= '1' when (sUNLOCK_TC = '1' or sSTATE = WARNING) else '0';
	
	-- registar za pamćenje stanja automata
	process (iCLK, iRST) begin
		if (iRST = '1') then
			sSTATE <= IDLE;
		elsif (iCLK'event and iCLK = '1') then
			sSTATE <= sNEXT_STATE;
		end if;
	end process;


	-- funkcija prelaza
	process(sSTATE, sIDLE_TC, sNEW_REQ, iCODE, sUNLOCK_TC, sNEXT_CNT, sCODE_CNT, sNEXT_TC) begin
		case (sSTATE) is 
			when IDLE => 				if(sIDLE_TC = '1') then
												sNEXT_STATE <= CHECK_REQUEST;
											else 
												sNEXT_STATE <= IDLE;
											end if;
				
			when CHECK_REQUEST =>	if (sNEW_REQ = '1') then
												sNEXT_STATE <= FIRST ;
											else 
												sNEXT_STATE <= IDLE;
											end if;
			when FIRST => 				if( iCODE = 2) then 
												sNEXT_STATE <= PAUSE;
											else 
												sNEXT_STATE <= WARNING;
											end if;
			when SECOND => 			if( iCODE = 3) then 
												sNEXT_STATE <= PAUSE;
											else 
												sNEXT_STATE <= WARNING;
											end if;
			when THIRD =>				if( iCODE = 4) then 
												sNEXT_STATE <= PAUSE;
											else 
												sNEXT_STATE <= WARNING;
											end if;
			when FOURTH =>				if( iCODE = 7) then 
												sNEXT_STATE <= UNLOCK;
											else 
												sNEXT_STATE <= WARNING;
											end if;
			when UNLOCK =>				if (sUNLOCK_TC = '1') then
												sNEXT_STATE <= IDLE;
											else
												sNEXT_STATE <= UNLOCK;
											end if;
			when PAUSE => 				if (sNEXT_TC ='1')then
												if(sCODE_CNT = 1) then
													sNEXT_STATE <= SECOND;
												elsif(sCODE_CNT = 2) then
													sNEXT_STATE <= THIRD;
												elsif(sCODE_CNT = 3) then
													sNEXT_STATE <= FOURTH;
												else
													sNEXT_STATE <= PAUSE;
												end if;
											else
												sNEXT_STATE <= sSTATE;
											end if;
			when others =>				sNEXT_STATE <= sSTATE;
		end case;
	end process;
		
	oSTATUS <= '1' when sSTATE = UNLOCK else '0';	

	oWARNING <= '1' when sSTATE = WARNING else '0';

end Behavioral;
