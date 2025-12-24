library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Brojac is port ( 
	iRST  : in  std_logic;
	iCLK  : in  std_logic;
	iEN   : in  std_logic;
	oCNT  : out std_logic_vector(7 downto 0)
	);
end entity;

architecture Behavioral of Brojac is
	-- za čuvanje stanja sekvencijalne mreže uvek koristiti interni signal
	signal sCNT : std_logic_vector(7 downto 0);
	signal sTC	: std_logic;
	
begin
	process (iRST, iCLK) begin -- uvek samo iRST i iCLK u listi osetljivosti
		if(iRST = '1') then  	    -- asinhroni reset
			sCNT <= "00000000";  	-- početna vrednost	
		elsif (iCLK'event and iCLK = '1') then -- na svaku promenu takta
			if(iEN = '1') then     		   -- i kada je iEN aktivan
				sCNT <= sCNT + '1';  	   -- povećava se vrednost brojača
			end if;
		end if;					 
	end process;
	
	sTC <= '1' when sCNT = 255 else '0';
	
	oCNT <=sCNT;  -- izvan procesa dodeliti vrednost internog signala izlaznom signalu

end Behavioral;
