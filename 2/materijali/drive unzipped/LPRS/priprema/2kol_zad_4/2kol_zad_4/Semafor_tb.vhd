library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all; 
 
entity Semafor_tb is
end Semafor_tb;
 
architecture Test of Semafor_tb is 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    component Semafor
    port(	iclk   : in std_logic;
				inRst  : in std_logic;
				istart : in std_logic;
				
				iA0    : in std_logic;
				iA1    : in std_logic;
				iA2    : in std_logic;
				iA3    : in std_logic;
				iA4    : in std_logic;
				iA5    : in std_logic;
				iA6    : in std_logic;
				iA7    : in std_logic;
				
				iB0    : in std_logic;
				iB1    : in std_logic;
				iB2    : in std_logic;
				iB3    : in std_logic;
				iB4    : in std_logic;
				iB5    : in std_logic;
				iB6    : in std_logic;
				iB7    : in std_logic;

				oDONE    : out std_logic;
				oE : out std_logic;
				oOUT : out std_logic_vector(2 DOWnto 0));
    end component;
    
   --Inputs
   signal sCLK : std_logic ;
   signal sRST : std_logic ;
   signal sStart : std_logic ;
	
	signal sA0    : std_logic;
	signal sA1    :  std_logic;
	signal sA2    : std_logic;
	signal sA3    :  std_logic;
	signal sA4    : std_logic;
	signal sA5    : std_logic;
	signal sA6    : std_logic;
	signal sA7    : std_logic;
	
	signal sB0    :  std_logic;
	signal sB1    :  std_logic;
	signal sB2    :  std_logic;
	signal sB3    :  std_logic;
	signal sB4    :  std_logic;
	signal sB5    :  std_logic;
	signal sB6    :  std_logic;
	signal sB7    : std_logic;
	

 	--Outputs
   signal sdone    : std_logic;
   signal sE : std_logic;
	signal sOUT  : std_logic_vector(2 downto 0);
	
	
   -- Clock period definitions
   constant iCLK_period : time := 10 ns;
 
begin
 
	-- Instantiate the Unit Under Test (UUT)
   uut: Semafor port map (
          iCLK => sCLK,
          inRST => sRST,
          istart => sstart,
			 
			 
			iA0=> sA0,
			iA1=> sA1,
			iA2=> sA2,
			iA3=> sA3,
			iA4=> sA4,
			iA5=> sA5,
			iA6=> sA6,
			iA7=> sA7,
			 
			iB0=> sB0,
			iB1=> sB1,
			iB2=> sB2,
			iB3=> sB3,
			iB4=> sB4,
			iB5=> sB5,
			iB6=> sB6,
			iB7=> sB7,
			oDONE=>sDone,
			oE=>sE,
			oOuT=>sOut
			 );

   -- Clock process definitions
   iCLK_process :process
   begin
		sCLK <= '0';
		wait for iCLK_period/2;
		sCLK <= '1';
		wait for iCLK_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
   sA0<= '0';
	sA1<= '1';
	sA2<= '0';
	sA3<= '1';
	sA4<= '0';
	sA5<= '1';
	sA6<= '0';
	sA7<= '1';
	sB0<= '0';
	sB1<= '1';
	sB2<= '0';
	sB3<= '1';
	sB4<= '0';
	sB5<= '1';
	sB6<= '0';
	sB7<= '1';

	srst<='1';
	wait for 2.25*iclK_period;
	srsT<='0';
	wait for iclK_period;
	sstart<='1';
	wait for iclK_period;
	sstart<='0';
	wait for 10*iclK_period;
	
	srsT<='1';
	wait for 2* iclK_period;
	srst<='0';
	sA0<= '0';
	sA1<= '1';
	sA2<= '0';
	sA3<= '1';
	sA4<= '0';
	sA5<= '0';
	sA6<= '0';
	sA7<= '1';
	sB0<= '0';
	sB1<= '1';
	sB2<= '0';
	sB3<= '1';
	sB4<= '0';
	sB5<= '1';
	sB6<= '0';
	sB7<= '1';
	wait for iclK_period;
	sstart<='1';
	wait for iclK_period;
	sstart<='0';
	wait for 10*iclK_period;
	wait;
   end process;

END;