library ieee;
use ieee.std_logic_1164.all;

entity Registar_tb is
end entity;
 
architecture Test of Registar_tb is
  
   signal sCLK : std_logic := '0';
   signal sRST : std_logic := '0';
	signal sD : std_logic_vector(7 downto 0);
   signal sWE : std_logic  := '0';
   signal sQ : std_logic_vector(7 downto 0);
	
	constant iCLK_PERIOD : time := 10 ns;
	
   component Registar is  
			port (
				iCLK 	: in  std_logic;
				iRST 	: in  std_logic;
				iD 	: in  std_logic_vector (7 downto 0);
				iWE 	: in  std_logic;
				oQ 	: out std_logic_vector (7 downto 0)
		);
   end component;

begin

   uut: Registar port map (
          iCLK => sCLK,
          iRST => sRST,
          iD	=> sD,
			 iWE	=> sWE,
          oQ	=> sQ
        );
	
	--takt process
	clk_proc : process
	begin
		sCLK <= '1';
		wait for iCLK_PERIOD / 2;
		sCLK <= '0';
		wait for iCLK_PERIOD / 2;
	end process;
	
   stimulus : process
   begin
		-- resetovanje sistema pre početka rada
		sRST <= '1';
		wait for 2.25* iCLK_PERIOD;
		sRST <= '0';
		
		sD <= "00000101";
		wait for 10 ns;
		
		-- dozvola upisa vrednosti D
		sWE <= '1';
		wait for 10 ns;
		
		sD <= "11111111";
		sWE <= '0';
		wait for 5 ns;
		
		sWE <= '1';
		wait for 10 ns;
		sWE <= '0';
		wait for 5 ns;
		
		sD <= "00001111";
		wait for 10 ns;
		
		sRST <= '1';
		wait for 2* iCLK_PERIOD;
		sRST <= '0';
		
		sWE <= '1';
		wait for 10 ns;
		sWE <= '0';
		wait;
   end process;
end architecture;
