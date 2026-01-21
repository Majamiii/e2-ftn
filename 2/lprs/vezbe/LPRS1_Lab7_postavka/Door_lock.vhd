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
	signal sIDLE_EN 		: 	std_logic;
	signal sIDLE_CNT  		:	std_logic_vector(2 downto 0);
	signal sIDLE_TC 		:	std_logic;
	signal sCLEAR 			:	std_logic;
	signal sNEW_REQ			: 	std_logic;
	signal sCODE_EN			:	std_logic;
	signal sCODE_CNT		: 	std_logic_vector(1 downto 0);
	signal sCODE_NUM		: 	std_logic_vector(1 downto 0);
	signal sUNLOCK_EN		: 	std_logic;
	signal sUNLOCK_CNT		: 	std_logic_vector(4 downto 0);
	signal sUNLOCK_TC		: 	std_logic;
	signal sNEXT_EN 		:	std_logic;
	signal sNEXT_CNT 		:	std_logic_vector(3 downto 0);
	signal sNEXT_TC 		:	std_logic;
	
begin



end Behavioral;
