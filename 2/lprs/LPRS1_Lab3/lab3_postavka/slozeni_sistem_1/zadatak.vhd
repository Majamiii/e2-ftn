library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity zadatak is
	port(
		iA : in std_logic_vector(7 downto 0);
		iB : in std_logic_vector(2 downto 0);
		iSEL : in std_logic_vector(1 downto 0);
		iGATE : in std_logic_vector(3 downto 0); -- sama nesto vezbam
		oY : out std_logic_vector(3 downto 0);
		oSEGM : out std_logic_vector(6 downto 0);
		oZERO : out std_logic;
		oGATE : out std_logic
	);
end entity;

architecture Behavioral of zadatak is
	signal sENC : std_logic_vector(2 downto 0);
	signal sADD : std_logic_vector(3 downto 0);
	signal sCOMPL: std_logic_vector(3 downto 0);
	signal sSHR : std_logic_vector(3 downto 0);
	signal sDEC : std_logic_vector(7 downto 0);
	signal sMUX : std_logic_vector(3 downto 0);
	signal sMAJA : std_logic_vector(1 downto 0);
	
begin

	sENC <= "111" when iA(7)='1' else
			"110" when iA(6)='1' else
			"101" when iA(5)='1' else
			"100" when iA(4)='1' else
			"011" when iA(3)='1' else
			"010" when iA(2)='1' else
			"001" when iA(1)='1' else
			"000";
			
	sADD <= ('0'&iB)+('0'&sENC);
	sCOMPL <= not(sADD)+1;
	
	sSHR <= sADD(3)&sADD(3)&sADD(3 downto 2);
	
	sDEC <= "10000000" when iB="111" else
			"01000000" when iB="110" else
			"00100000" when iB="101" else
			"00010000" when iB="100" else
			"00001000" when iB="011" else
			"00000100" when iB="010" else
			"00000010" when iB="001" else
			"00000001";
			
	process (iSEL, sCOMPL, sSHR, sDEC) begin
		case(iSEL) is
			when "00" => sMUX <= sCOMPL;
			when "01" => sMUX <= sSHR;
			when "10" => sMUX <= sDEC(7 downto 4);
			when others => sMUX <= sDEC(3 downto 0);
		end case;
	end process;
	
	-- smux ide na osegm
	oSEGM <= "0000001" when sMUX="0000" else
				"1001111" when sMUX="0001" else
				"0010010" when sMUX="0010" else
				"0000110" when sMUX="0011" else
				"1001100" when sMUX="0100" else
				"0100100" when sMUX="0101" else
				"0100000" when sMUX="0110" else
				"0001111" when sMUX="0111" else
				"0000000" when sMUX="1000" else
				"0000100" when sMUX="1001" else
				"1111111";
				
	oY <= sMUX;
	oZERO <= '1' when sMUX="0000" else '0';
	
	
	-- sMAJA -- zezam se sad malo sa komparatorima
	sMAJA <= "11" when (iA>iB) else
				"00" when (iA=iB) else
				"10";
				
	-- majority gate
	-- izlaz je aktivan ako su makar 3 od 4 jedinice
	oGATE <= '1' when iGATE="1111" else
				'1' when iGATE = "1110" else
				'1' when iGATE="1101" else
				'1' when iGATE="1011" else
				'1' when iGATE="0111" else
				'0';
	

end architecture;