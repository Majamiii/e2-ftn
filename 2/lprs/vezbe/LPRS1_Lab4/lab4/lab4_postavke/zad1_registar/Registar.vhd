library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Registar is
	port (
				iCLK 	: in  std_logic;
				iRST 	: in  std_logic;
				iD 	: in  std_logic_vector (7 downto 0);
				iWE 	: in  std_logic;
				oQ 	: out std_logic_vector (7 downto 0)
		);
end entity;


architecture Behavioral of Registar is
	signal sREG : std_logic_vector(7 downto 0);
begin
	-- registar sa sinhronim resetom
	
	process(iCLK) begin
		if (rising_edge(iCLK)) then
			if(iRST='1') then
				sREG <= "00000000";
			elsif(iRST='0') then
				if(iWE = '1') then
					sREG <= iD;
				end if;
			end if;
		end if;
	end process;
	
	oQ <= sREG;

end Behavioral;
