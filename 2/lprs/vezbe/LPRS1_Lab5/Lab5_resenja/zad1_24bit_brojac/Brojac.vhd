library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;

entity Brojac is port ( 
	iRST  : in  std_logic;
	iCLK  : in  std_logic;
	iEN   : in  std_logic;
	o7SEGM : out std_logic_vector(6 downto 0);
	oCNT  : out std_logic_vector(23 downto 0)
	);
end entity;

architecture Behavioral of Brojac is
	-- za čuvanje stanja sekvencijalne mreže uvek koristiti interni signal
	signal sCNT 		: std_logic_vector(23 downto 0);
	signal sCNT_segm  : std_logic_vector(3 downto 0); -- brojač sekundi za 7-segmentni
	signal sTC	: std_logic;
	--constant cCNT_MAX	: std_logic_vector(23 downto 0) := "101101110001101100000000"; -- moze i X"B71B00" za hex zapis
	constant cCNT_MAX		: std_logic_vector(23 downto 0) := "000000000000000000001100"; -- 12, za simulaciju

begin
	-- brojač po modulu cCNT_MAX
	process (iRST, iCLK) begin -- uvek samo iRST i iCLK u listi osetljivosti
		if(iRST = '1') then  	    	-- asinhroni reset
			sCNT <= (others=>'0');  	-- početna vrednost	
		elsif (iCLK'event and iCLK = '1') then -- na svaku promenu takta
			if(iEN = '1') then     		   -- i kada je iEN aktivan
				if(sCNT = cCNT_MAX) then	-- brojač po modulu
					sCNT <= (others=>'0');
				else
					sCNT <= sCNT + '1';  	   -- povećava se vrednost brojača
				end if;
			end if;
		end if;					 
	end process;
	
	sTC <= '1' when sCNT = cCNT_MAX else '0'; -- prošla je 1 sekunda
	
	oCNT <=sCNT;  -- izvan procesa dodeliti vrednost internog signala izlaznom signalu

	-- brojač sekundi
	process (iRST, iCLK) begin -- uvek samo iRST i iCLK u listi osetljivosti
		if(iRST = '1') then  	    	-- asinhroni reset
			sCNT_segm <= (others=>'0');  	-- početna vrednost	
		elsif (iCLK'event and iCLK = '1') then -- na svaku promenu takta
			if(iEN = '1' and sTC = '1') then     		   -- i kada je sTC aktivan
				if(sCNT_segm = 9) then
					sCNT_segm <= (others => '0');
				else
					sCNT_segm <= sCNT_segm + '1';  	   -- povećava se vrednost brojača
				end if;
			end if;
		end if;					 
	end process;
	-- dodatak za ispis na 7-segmentni displej
	process(sCNT_segm) begin
		case sCNT_segm is
			when "0000" => o7SEGM <= "0000001"; -- 0
			when "0001" => o7SEGM <= "1001111"; -- 1
			when "0010" => o7SEGM <= "0010010"; -- 2
			when "0011" => o7SEGM <= "0000110"; -- 3
			when "0100" => o7SEGM <= "1001100"; -- 4
			when "0101" => o7SEGM <= "0100100"; -- 5
			when "0110" => o7SEGM <= "0100000"; -- 6
			when "0111" => o7SEGM <= "0001111"; -- 7
			when "1000" => o7SEGM <= "0000000"; -- 8
			when "1001" => o7SEGM <= "0000100"; -- 9
			when "1010" => o7SEGM <= "0000010"; -- A
			when "1011" => o7SEGM <= "1100000"; -- B
			when "1100" => o7SEGM <= "0110001"; -- C
			when "1101" => o7SEGM <= "1000010"; -- D
			when "1110" => o7SEGM <= "0110000"; -- E
			when "1111" => o7SEGM <= "0111000"; -- F
			when others => o7SEGM <= "1111111"; -- null
		end case;
	end process;
	
end Behavioral;
