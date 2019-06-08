library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Se describe un flip-flop tipo d

entity flipFlop_D is
    Port (d : in  STD_LOGIC;
          clk : in  STD_LOGIC;
          q : out  STD_LOGIC);
end flipFlop_D;

architecture FlipFlop of flipFlop_D is

begin
	process(clk)
	begin
		if clk'event AND clk = '1' then
			q <= d;
		end if;
	end process;

end FlipFlop;

