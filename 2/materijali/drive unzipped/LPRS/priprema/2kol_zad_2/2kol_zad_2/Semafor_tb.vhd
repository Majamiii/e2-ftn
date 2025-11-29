library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all; 
 
entity Semafor_tb is
end Semafor_tb;
 
architecture Test of Semafor_tb is 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    component Semafor
    port(	iCLK    : in  std_logic;
				inRST    : in  std_logic;
				
				o_R   : out std_logic;
				o_Y : out std_logic;
				o_G : out std_logic);
    end component;
    
   --Inputs
   signal sCLK : std_logic ;
   signal sRST : std_logic ;
  
 	--Outputs
   signal s_R    : std_logic;
   signal s_Y : std_logic;
	signal s_G  : std_logic;
	
   -- Clock period definitions
   constant iCLK_period : time := 10 ns;
 
begin
 
	-- Instantiate the Unit Under Test (UUT)
   uut: Semafor port map (
          iCLK => sCLK,
          inRST => sRST,
			 
          o_R => s_R,
			 o_Y => s_Y,
			 o_G => s_G);

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
   
	sRST<='0';
	wait for 2.25*iclK_period;
	srst<='1';
	
	wait;
	end process;
END;