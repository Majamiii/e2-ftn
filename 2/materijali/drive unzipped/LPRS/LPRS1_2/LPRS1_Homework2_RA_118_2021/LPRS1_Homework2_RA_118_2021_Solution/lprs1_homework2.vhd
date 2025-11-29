library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.ALL;
-- Libraries.

entity lprs1_homework2 is
	port(
		i_clk    :  in std_logic;
		i_rst    :  in std_logic;
		i_run    :  in std_logic;
		i_pause  :  in std_logic;
		o_digit0 : out std_logic_vector(3 downto 0);
		o_digit1 : out std_logic_vector(3 downto 0);
		o_digit2 : out std_logic_vector(3 downto 0);
		o_digit3 : out std_logic_vector(3 downto 0)
);
end entity;


architecture arch of lprs1_homework2 is
	-- Signals.
	signal s_en_1us : std_logic;
	signal s_cnt_1us : std_logic_vector(7 downto 0);
	signal s_tc_1us : std_logic;
	signal s_cnt0 : std_logic_vector(3 downto 0);
	signal s_en0 : std_logic;
	signal s_en1 : std_logic;
	signal s_tc0 : std_logic;
	signal s_cnt1 : std_logic_vector(3 downto 0);
	signal s_tc1 : std_logic;
	--const
	constant c1 : std_logic_vector(7 downto 0) :="11000111";--199(moduo za 200)
	constant c2 : std_logic_vector(3 downto 0) :="0111";--7(moduo za 8)
	constant c3 : std_logic_vector(3 downto 0) :="0101";--5(moduo za 6)
begin


	--dozvola brojanja
process(i_clk,i_rst) begin
	if(rising_edge(i_clk)) then
		if(i_rst = '1') then
			s_en_1us <= '0';
		elsif(i_run = '1') then
			s_en_1us <= '1';
		elsif(i_pause = '1') then
			s_en_1us <= '0';
		elsif(i_pause = '1' and i_run ='1') then
			s_en_1us <= '1';
		end if;
	end if;	
end process;
	
	--brojac jedne mikrosekunde
process(i_clk,i_rst) begin
	if(rising_edge(i_clk)) then
		if(i_rst = '1') then
			s_cnt_1us <= (others => '0');
		elsif(s_en_1us = '1') then
			if(s_cnt_1us < c1) then
				s_cnt_1us <= s_cnt_1us + 1;
			elsif(s_cnt_1us >= c1) then
				s_cnt_1us <= (others => '0');
			end if;
		end if;
	end if;		
end process;

--kominaciono, aktiviranje signala za kraj brojaca
s_tc_1us <= '1' when s_cnt_1us = "000000" else '0';
--aktivna kapija za oba signala
s_en0 <= '1' when (s_tc_1us = '1' and s_en_1us = '1') else '0';

	--brojac nulte cifre
process(i_clk,i_rst) begin
	if(rising_edge(i_clk)) then
		if(i_rst = '1') then
			s_cnt0 <= (others =>'0');
		elsif(s_en0 = '1') then
			if(s_cnt0 < c2) then
				s_cnt0 <= s_cnt0 + 1;
			elsif(s_cnt0 >= c2) then
				s_cnt0 <= (others => '0');
			end if;
		end if;
	end if;		
end process;
	 
--kombinaciono. akriviranje signala za kraj brojaca
	s_tc0 <= '1' when s_cnt0 = "0111" 
				 else '0';
				 
--aktivna kapija and
	s_en1 <= '1' when (s_tc0 ='1' and s_en0 = '1') 
	         else '0';
	o_digit0 <= s_cnt0;
	 
	 
--brojac prve cifre
process(i_clk,i_rst) begin
	if(rising_edge(i_clk)) then
		if(i_rst = '1') then
			s_cnt1 <= (others => '0');
		elsif(s_en1 = '1') then
			if(s_cnt1 < c3) then
				s_cnt1 <= s_cnt1 + 1;
			elsif(s_cnt1 >= c3) then
				s_cnt1 <= (others => '0');
			end if;
		end if;
	end if;
end process;

--kombinaciono. akriviranje signala za kraj brojaca
	s_tc1 <= '1' when s_cnt1 = "0101" else '0';
	o_digit1 <= s_cnt1;
	
--aktivna kapija 
	o_digit2 <= "0001"; --1
	o_digit3 <= "1111"; --15
	 
end architecture;
