library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all; 
 
entity Semafor_tb is
end Semafor_tb;
 
architecture Test of Semafor_tb is 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    component Semafor
    port(		iCLK    : in  std_logic;
				iRST    : in  std_logic;
				iSel     : in  std_logic_vector (1 downto 0);
				iduration  : in  std_logic_vector(7 downto 0);
				istart  : in  std_logic;
				o150w    : out std_logic;
				o300w : out std_logic;
				o650w : out std_logic;
				o800w : out std_logic;
				oWARN  : out std_logic);
    end component;
    
   --Inputs
   signal sCLK : std_logic ;
   signal sRST : std_logic ;
   signal sSEL  : std_logic_vector(1 downto 0) ;
   signal sStart : std_logic ;
	signal sDuration: std_logic_vector(7 downto 0);
  
 	--Outputs
   signal s150w    : std_logic;
   signal s300w : std_logic;
	signal s650w  : std_logic;
	signal s800w  : std_logic;
	
   -- Clock period definitions
   constant iCLK_period : time := 10 ns;
 
begin
 
	-- Instantiate the Unit Under Test (UUT)
   uut: Semafor port map (
          iCLK => sCLK,
          iRST => sRST,
          isel => sseL,
          istart => sstart,
			 iduration=> sduration,
			 
          o150w => s150w,
			 o300w => s300w,
			 o650w => s650w,
			 o800w => s800w);

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
     
	srst<='0';
	ssel<="00";
	sduration<=(others=>('0'));
	sstart<='0';
	wait for 100*iclK_period;
   srsT<='1';
   ssel<="10";
	sduration<=x"C8";
	sstart<='1';
	wait for iclK_period;
	ssel<="10";
	sduration<=x"C8";
	sstart<='0';
	wait;
   end process;

END;