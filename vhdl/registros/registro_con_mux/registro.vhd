library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Registro donde dependiendo de la carga, se mantiene
-- el dato en el registro, o se guarda la entrada de
-- uno nuevo

entity registro is
    Port ( entrada : in  STD_LOGIC_VECTOR (7 downto 0);
           load : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           salida : out  STD_LOGIC_VECTOR (7 downto 0));
end registro;

architecture Behavioral of registro is

begin

process(load, clk, reset)
begin
	if reset = '1' then
		salida <= (others => '0');
	elsif rising_edge(clk) then
		-- Hace la función del mux
		if load = '1' then
			salida <= entrada;
		end if;
	end if;
end process;


end Behavioral;

