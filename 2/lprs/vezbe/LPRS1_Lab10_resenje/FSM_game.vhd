library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity FSM_game is port ( 
	iRST  : in  std_logic;
	iCLK  : in  std_logic;
	iA	   : in  std_logic_vector(1 downto 0);
	iB	   : in  std_logic_vector(1 downto 0);
	oA  	: out std_logic;
	oB  	: out std_logic
	);
end entity;

architecture Behavioral of FSM_game is

	signal sWIN	: std_logic_vector(1 downto 0);	-- 0 - igra traje, 1 - A pobedio, 2 - B pobedio
	
	type tSTATE	is (DRAW, A_LEAD, B_LEAD, A_WIN, B_WIN);
	signal sSTATE, sNEXT_STATE	: tSTATE;
	
begin


	-- registar pamćenja stanja automata
	process(iCLK, iRST) begin
		if(iRST = '1') then
			sSTATE <= DRAW;
		elsif(rising_edge(iCLK)) then
			sSTATE <= sNEXT_STATE;
		end if;
	end process;
	
	-- funkcija prelaza stanja
	process(sSTATE, iA, iB) begin
		case(sSTATE) is
			when DRAW => 
							if iA = 1 then
								sNEXT_STATE <= A_LEAD;
							elsif iB = 1 then
								sNEXT_STATE <= B_LEAD;
							else
								sNEXT_STATE <= sSTATE;
							end if;
			when A_LEAD	=>
							if iA = 1 then
								sNEXT_STATE <= A_WIN;
							elsif iB = 1 then
								sNEXT_STATE <= DRAW;
							elsif iB = 2 then
								sNEXT_STATE <= B_LEAD;
							else
								sNEXT_STATE <= sSTATE;
							end if;
			when B_LEAD	=>
							if iA = 1 then
								sNEXT_STATE <= DRAW;
							elsif iB = 1 then
								sNEXT_STATE <= B_WIN;
							elsif iA = 2 then
								sNEXT_STATE <= A_LEAD;
							else
								sNEXT_STATE <= sSTATE;
							end if;
			when others =>
							sNEXT_STATE <= sSTATE;
		end case;
	end process;

	-- signal sWIN
	sWIN <= 	"01" when sSTATE = A_WIN else
				"10" when sSTATE = B_WIN else
				"00";
				
	-- dekoder
	oA <= '1' when sWIN = "01" else '0';
	oB <= '1' when sWIN = "10" else '0';
end Behavioral;
