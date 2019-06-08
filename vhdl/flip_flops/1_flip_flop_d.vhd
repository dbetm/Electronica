library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ffd is
    Port ( d : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           q : out  STD_LOGIC);
end ffd;

architecture Behavioral of ffd is
signal cuenta: natural range 0 to 25000001;
signal s1, q1, qn1: STD_LOGIC;
begin

process(clk)
begin
	if clk'event and clk = '1' then
		if cuenta = 25000000 then
			cuenta <= 0;
			s1 <= not s1; 
		else
			cuenta <= cuenta + 1;
		end if;
	end if;
end process;

process(s1, reset)
	begin
	if reset = '1' then 
		q1 <= '0';
	else 
		if s1'event AND s1 = '1' then
			q1 <= d;
		end if;
	end if;
end process;
q <= q1;

end Behavioral;

